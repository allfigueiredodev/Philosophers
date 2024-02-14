/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_health_monitor.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:02:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 18:47:43 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void death(t_data *data, t_dclist *head)
{
	die(&head->philo);
	check_mtx_return_err(pthread_mutex_lock(&data->data_mtx),
		MTX_LOCK_UNLOCK_DSTY);
	data->health_status = true;
	check_mtx_return_err(pthread_mutex_unlock(&data->data_mtx),
		MTX_LOCK_UNLOCK_DSTY);
	return ;
}

void check_eat_score(t_data *data, t_dclist *head)
{
	if(lock_int_return(&head->philo.philo_mtx, &head->philo.meals_ate)
		>= data->args.meals_must_eat)
		data->eat_score++;
	if(data->eat_score == data->args.nbr_of_philos)
	{
		check_mtx_return_err(pthread_mutex_lock(&data->data_mtx),
			MTX_LOCK_UNLOCK_DSTY);
		data->health_status = true;
		check_mtx_return_err(pthread_mutex_unlock(&data->data_mtx),
			MTX_LOCK_UNLOCK_DSTY);
		return ;
	}
	if(head->philo.philo_id == data->args.nbr_of_philos)
		data->eat_score = 0;		
}

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
		if(current - lock_long_return(&head->philo.philo_mtx ,
			&head->philo.last_meal)  >= data->args.time_to_die
			&& lock_state_return(&head->philo.philo_mtx, &head->philo.state)
			!= DEAD)
		{
			death(data, head);
		}
		if(data->args.meals_must_eat > 0)
			check_eat_score(data, head);
		head = temp;
	}
}

