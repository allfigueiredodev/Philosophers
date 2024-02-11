/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_health_monitor.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:02:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/11 13:50:06 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_health check_philo_health(t_data *data)
{
	t_health result;
	t_dclist *head;
	t_dclist *temp;
	struct timeval current_time;
	long current;
	
	gettimeofday(&current_time, NULL);
	current = time_diff(data->simulation_start, current_time);
	head = data->table;
	result = (t_health){
		.death_score = 0,
		.eat_score = 0
	};
	while(head->philo.philo_id != data->args.nbr_of_philos)
	{
		temp = head->next;		
		if(current - head->philo.last_meal >= data->args.time_to_die && head->philo.state != DEAD)
			die(&head->philo);
		if(head->philo.state == DEAD)
		{
			result.death_score++;
			return (result);
		}
		if(data->args.meals_must_eat > 0)
		{
			if(head->philo.meals_ate >= data->args.meals_must_eat)
				result.eat_score++;		
		}
		head = temp;
	}
	if(current - head->philo.last_meal >= data->args.time_to_die && head->philo.state != DEAD)
		die(&head->philo);
	if(head->philo.state == DEAD)
	{
		result.death_score++;
		return (result);
	}
	if(data->args.meals_must_eat > 0)
	{
		if(head->philo.meals_ate >= data->args.meals_must_eat)
			result.eat_score++;		
	}
	return (result);
}

void *end_conditions(void *data)
{
	t_health	current_health;
	t_data		*cast;

	cast = (t_data *)data;
	current_health = check_philo_health(data);
	printf("dead: %d\neat score: %d\n", current_health.death_score, current_health.eat_score);
	if(current_health.death_score > 0
		|| current_health.eat_score == cast->args.nbr_of_philos)
		{
			// check_mtx_return_err(pthread_mutex_lock(&cast->data_mtx), MTX_LOCK_UNLOCK_DSTY);
			cast->health_status = true;
			// check_mtx_return_err(pthread_mutex_unlock(&cast->data_mtx), MTX_LOCK_UNLOCK_DSTY);
			return (NULL);
		}
	return (NULL);
}