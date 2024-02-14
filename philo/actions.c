/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:30:55 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 04:24:01 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	printf("%s%ld %d has taken a fork\n%s", YELLOW, time_difference,
		philo->philo_id ,DFT);
	if (data->args.nbr_of_philos > 1)
	{
		if (philo->philo_id % 2 == 0)
			check_mtx_return_err(pthread_mutex_lock(&philo->left_fork->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
		else	
			check_mtx_return_err(pthread_mutex_lock(&get_right_fork(philo)->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
		gettimeofday(&pick_up, NULL);
		time_difference = time_diff(data->simulation_start, pick_up);
		printf("%s%ld %d has taken a fork\n%s", YELLOW, time_difference,
			philo->philo_id ,DFT);
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
	printf("%s%ld %d is eating\n%s", RED, time_difference,
		philo->philo_id ,DFT);
	usleep(data->args.time_to_eat * 1000);
	gettimeofday(&ate, NULL);
	philo->last_meal = time_diff(data->simulation_start, ate);
	check_mtx_return_err(pthread_mutex_unlock(&philo->left_fork->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
	check_mtx_return_err(pthread_mutex_unlock(&get_right_fork(philo)->mtx_fork), MTX_LOCK_UNLOCK_DSTY);
	printf("philo: %d unlocked.\n", philo->philo_id);
}

void	philo_sleep(t_philo *philo)
{
	t_data *data;
	struct timeval sleep_time;
	long time_difference;
	
	data = get_data();
	gettimeofday(&sleep_time, NULL);
	time_difference = time_diff(data->simulation_start, sleep_time);
	printf("%s%ld %d is sleeping\n%s", BLUE, time_difference, 
		philo->philo_id ,DFT);
	philo->state = SLEEPING;
	usleep(data->args.time_to_sleep * 1000);
	gettimeofday(&sleep_time, NULL);
	time_difference = time_diff(data->simulation_start, sleep_time);
	philo->state = THINKING;
	printf("%s%ld %d is thinking\n%s", GREEN, time_difference, 
	philo->philo_id, DFT);
}

void	die(t_philo *philo)
{
	t_data	*data;
	struct	timeval death_time;
	long	time_difference;
	
	data = get_data();
	gettimeofday(&death_time, NULL);
	time_difference = time_diff(data->simulation_start, death_time);
	printf("%s%ld %d died\n%s", MAGENTA, time_difference, 
		philo->philo_id ,DFT);
	philo->state = DEAD;
}
