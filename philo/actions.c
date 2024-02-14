/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:30:55 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 18:19:38 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pick_a_fork(t_philo *philo)
{
	t_data *data;
	struct timeval pick_up;
	long time_difference;
	
	data = get_data();
	fork_selection(philo, 0);
	gettimeofday(&pick_up, NULL);
	time_difference = time_diff(data->simulation_start, pick_up);
	print_validator(data, time_difference, philo->philo_id, TOOK_A_FORK);
	if (data->args.nbr_of_philos > 1)
	{
		fork_selection(philo, 1);
		gettimeofday(&pick_up, NULL);
		time_difference = time_diff(data->simulation_start, pick_up);
		print_validator(data, time_difference, philo->philo_id, TOOK_A_FORK);
		philo->state = TOOK_BOTH_FORKS;
	}
	if (data->args.nbr_of_philos == 1)
	{
		usleep(data->args.time_to_die * 1000);
		check_mtx_return_err(pthread_mutex_unlock(&philo->left_fork->mtx_fork),
			MTX_LOCK_UNLOCK_DSTY);
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
	check_mtx_return_err(pthread_mutex_lock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	philo->meals_ate++;
	check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	gettimeofday(&ate, NULL);
	check_mtx_return_err(pthread_mutex_lock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	philo->last_meal = time_diff(data->simulation_start, ate);
	philo->state = EATING;
	check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	print_validator(data, time_difference, philo->philo_id, EATING);
	usleep(data->args.time_to_eat * 1000);
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
	check_mtx_return_err(pthread_mutex_lock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	philo->state = SLEEPING;
	check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	usleep(data->args.time_to_sleep * 1000);
	gettimeofday(&sleep_time, NULL);
	time_difference = time_diff(data->simulation_start, sleep_time);
	check_mtx_return_err(pthread_mutex_lock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	philo->state = THINKING;
	check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
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
	check_mtx_return_err(pthread_mutex_lock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	philo->state = DEAD;
	check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	print_validator(data, time_difference, philo->philo_id, DEAD);
}
