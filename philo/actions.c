/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:30:55 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/26 22:15:46 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pick_a_fork(t_data *data, t_philo *philo)
{
	struct timeval pick_up;
	double time_difference;
	
	gettimeofday(&pick_up, NULL);
	time_difference = time_diff(data->simulation_start, pick_up);
	// time_difference = pick_up.tv_sec * 1000.0 + pick_up.tv_usec / 1000.0;
	// time_difference = time_difference - data->simulation_start;
	if (philo->left_fork.available &&
		philo->right_fork.available)
	{
		philo->state = TOOK_A_FORK;
		philo->left_fork.available = false;
		philo->right_fork.available = false;
		printf("%s%.2f %d has taken a fork\n%s", RED, time_difference, 
			philo->philo_id ,DFT);
		eat(data, philo);
	}
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	struct timeval sleep_time;
	double time_difference;
	
	gettimeofday(&sleep_time, NULL);
	time_difference = time_diff(data->simulation_start, sleep_time);
	// time_difference = sleep_time.tv_sec * 1000.0 + sleep_time.tv_usec / 1000.0;
	// time_difference = time_difference - data->simulation_start;
	printf("%s%.2f %d is sleeping\n%s", GREEN, time_difference, 
		philo->philo_id ,DFT);
	philo->state = SLEEPING;
	usleep(data->args.time_to_sleep);
	gettimeofday(&sleep_time, NULL);
	// time_difference = sleep_time.tv_sec * 1000.0 + sleep_time.tv_usec / 1000.0;
	// time_difference = time_difference - data->simulation_start;
	philo->state = THINKING;
	printf("%s%.2f %d is thinking\n%s", BLUE, time_difference, 
	philo->philo_id, DFT);
}

void	eat(t_data *data, t_philo *philo)
{
	struct timeval ate;
	double time_difference;
	
	gettimeofday(&ate, NULL);
	time_difference = time_diff(data->simulation_start, ate);
	// time_difference = ate.tv_sec * 1000.0 + ate.tv_usec / 1000.0;
	// time_difference = time_difference - data->simulation_start;
	philo->meals_ate++; 
	printf("%s%.2f %d is eating\n%s", GREEN, time_difference, 
	philo->philo_id ,DFT);
	usleep(data->args.time_to_eat);
	gettimeofday(&ate, NULL);
	// time_difference = ate.tv_sec * 1000.0 + ate.tv_usec / 1000.0;
	// philo->last_meal = time_difference - data->simulation_start;
	philo->left_fork.available = true;
	philo->right_fork.available = true;
	philo_sleep(data, philo);
}	

void	die(t_data *data, t_philo *philo)
{
	struct timeval death_time;
	double time_difference;
	
	gettimeofday(&death_time, NULL);
	time_difference = time_diff(data->simulation_start, death_time);
	// time_difference = death_time.tv_sec * 1000.0 + death_time.tv_usec / 1000.0;
	// time_difference = time_difference - data->simulation_start;
	printf("%s%.2f %d died\n%s", MAGENTA, time_difference, 
	philo->philo_id ,DFT);
	philo->state = DEAD;
}