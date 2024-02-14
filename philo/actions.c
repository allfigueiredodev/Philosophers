/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:30:55 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 11:19:56 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	lock_bool_return(pthread_mutex_t *mutex, t_bool *value)
{
	t_bool	ret;

	check_mtx_return_err(pthread_mutex_lock(mutex), MTX_LOCK_UNLOCK_DSTY);
	ret = *value;
	check_mtx_return_err(pthread_mutex_unlock(mutex), MTX_LOCK_UNLOCK_DSTY);
	return (ret);
}

int		lock_int_return(pthread_mutex_t *mutex, int *value)
{
	int	ret;

	check_mtx_return_err(pthread_mutex_lock(mutex), MTX_LOCK_UNLOCK_DSTY);
	ret = *value;
	check_mtx_return_err(pthread_mutex_unlock(mutex), MTX_LOCK_UNLOCK_DSTY);
	return (ret);
}

long	lock_long_return(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	check_mtx_return_err(pthread_mutex_lock(mutex), MTX_LOCK_UNLOCK_DSTY);
	ret = *value;
	check_mtx_return_err(pthread_mutex_unlock(mutex), MTX_LOCK_UNLOCK_DSTY);
	return (ret);
}

void print_validator(t_data *data, long time, int id, t_state state)
{
	if(!lock_bool_return(&data->data_mtx, &data->health_status))
	{
		if (state == TOOK_A_FORK)
			printf("%s%ld %d has taken a fork\n%s", YELLOW, time, id, DFT);
		else if (state == EATING)
			printf("%s%ld %d is eating\n%s", RED, time, id, DFT);
		else if (state == SLEEPING)
			printf("%s%ld %d is sleeping\n%s", BLUE, time, id, DFT);
		else if (state == THINKING)
			printf("%s%ld %d is thinking\n%s", GREEN, time, id, DFT);
		else if (state == DEAD)
			printf("%s%ld %d died\n%s", MAGENTA, time, id, DFT);
	}
}

void	pick_a_fork(t_philo *philo)
{
	t_data *data;
	struct timeval pick_up;
	long time_difference;
	
	data = get_data();
	if (philo->philo_id % 2 == 0)
		check_mtx_return_err(pthread_mutex_lock(&get_right_fork(philo)->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
	else
		check_mtx_return_err(pthread_mutex_lock(&philo->left_fork->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
	gettimeofday(&pick_up, NULL);
	time_difference = time_diff(data->simulation_start, pick_up);
	print_validator(data, time_difference, philo->philo_id, TOOK_A_FORK);
	if (data->args.nbr_of_philos > 1)
	{
		if (philo->philo_id % 2 == 0)
			check_mtx_return_err(pthread_mutex_lock(&philo->left_fork->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
		else	
			check_mtx_return_err(pthread_mutex_lock(&get_right_fork(philo)->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
		gettimeofday(&pick_up, NULL);
		time_difference = time_diff(data->simulation_start, pick_up);
		print_validator(data, time_difference, philo->philo_id, TOOK_A_FORK);
		philo->state = TOOK_BOTH_FORKS;
	}
	if (data->args.nbr_of_philos == 1)
	{
		usleep(data->args.time_to_die * 1000);
		check_mtx_return_err(pthread_mutex_unlock(&philo->left_fork->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
	}
}

void	eat(t_philo *philo)
{
	t_data	*data;
	struct	timeval ate;
	long	time_difference;
	
	data = get_data();
	gettimeofday(&ate, NULL);
	time_difference = time_diff(data->simulation_start, ate);
	philo->meals_ate++;
	philo->state = EATING;
	print_validator(data, time_difference, philo->philo_id, EATING);
	usleep(data->args.time_to_eat * 1000);
	gettimeofday(&ate, NULL);
	// check_mtx_return_err(pthread_mutex_lock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	philo->last_meal = time_diff(data->simulation_start, ate);
	// check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	check_mtx_return_err(pthread_mutex_unlock(&philo->left_fork->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
	check_mtx_return_err(pthread_mutex_unlock(&get_right_fork(philo)->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
}

void	philo_sleep(t_philo *philo)
{
	t_data *data;
	struct timeval sleep_time;
	long time_difference;
	
	data = get_data();
	gettimeofday(&sleep_time, NULL);
	time_difference = time_diff(data->simulation_start, sleep_time);
	print_validator(data, time_difference, philo->philo_id, SLEEPING);
	philo->state = SLEEPING;
	usleep(data->args.time_to_sleep * 1000);
	gettimeofday(&sleep_time, NULL);
	time_difference = time_diff(data->simulation_start, sleep_time);
	philo->state = THINKING;
	usleep(1000);
	print_validator(data, time_difference, philo->philo_id, THINKING);
}

void	die(t_philo *philo)
{
	t_data	*data;
	struct	timeval death_time;
	long	time_difference;
	
	data = get_data();
	gettimeofday(&death_time, NULL);
	time_difference = time_diff(data->simulation_start, death_time);
	philo->state = DEAD;
	print_validator(data, time_difference, philo->philo_id, DEAD);
}
