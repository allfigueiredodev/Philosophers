/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_health_monitor.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:02:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 04:22:46 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void check_philo_health(t_data *data)
{
	t_dclist *head;
	t_dclist *temp;
	struct timeval current_time;
	long current;
	
	head = data->table;
	while(!data->health_status)
	{
		gettimeofday(&current_time, NULL);
		current = time_diff(data->simulation_start, current_time);
		temp = head->next;		
		if(current - head->philo.last_meal >= data->args.time_to_die && head->philo.state != DEAD)
		{
			die(&head->philo);
			data->health_status = true;
			return ;
		}
		// if(head->philo.state == DEAD)
		// {
		// 	data->health_status = true;
		// 	return ;
		// }
		if(data->args.meals_must_eat > 0)
		{
			if(head->philo.meals_ate >= data->args.meals_must_eat)
				data->eat_score++;
			if(data->eat_score == data->args.nbr_of_philos)
			{
				data->health_status = true;
				return ;
			}
			if(head->philo.philo_id == data->args.nbr_of_philos)
				data->eat_score = 0;					
		}
		head = temp;
	}
}

	// // t_data	*data;
	// struct	timeval current_time;
	
	// gettimeofday(&current_time, NULL);
	// // data = get_data();
	// if (time_diff(data->simulation_start, current_time)
	// 	- philo->last_meal >= data->args.time_to_die
	// 	&& philo->state != DEAD)
	// {
	// 	die(philo);
	// 	check_mtx_return_err(pthread_mutex_lock(&data->data_mtx), MTX_LOCK_UNLOCK_DSTY);
	// 	data->health_status = true;
	// 	check_mtx_return_err(pthread_mutex_unlock(&data->data_mtx), MTX_LOCK_UNLOCK_DSTY);
	// 	return ;
	// }
	// if(data->args.meals_must_eat > 0)
	// {
	// 	if(philo->meals_ate == data->args.meals_must_eat)
	// 	{
	// 		check_mtx_return_err(pthread_mutex_lock(&data->data_mtx), MTX_LOCK_UNLOCK_DSTY);
	// 		data->eat_score++;
	// 		check_mtx_return_err(pthread_mutex_unlock(&data->data_mtx), MTX_LOCK_UNLOCK_DSTY);
	// 	}
	// 	check_mtx_return_err(pthread_mutex_lock(&data->data_mtx), MTX_LOCK_UNLOCK_DSTY);
	// 	if(data->eat_score == data->args.nbr_of_philos)
	// 	{
	// 		data->health_status = true;
	// 		check_mtx_return_err(pthread_mutex_unlock(&data->data_mtx), MTX_LOCK_UNLOCK_DSTY);
	// 		return ;
	// 	}			
	// 	check_mtx_return_err(pthread_mutex_unlock(&data->data_mtx), MTX_LOCK_UNLOCK_DSTY);
	// }		

