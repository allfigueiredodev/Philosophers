/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_health_monitor.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:02:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/13 14:33:47 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *check_philo_health(void *main)
{
	int eat_score;
	t_dclist *head;
	t_dclist *temp;
	struct timeval current_time;
	t_data *data = (t_data *)main;
	
	gettimeofday(&current_time, NULL);
	head = data->table;
	eat_score = 0;
	while(1)
	{
		temp = head->next;		
		// check_mtx_return_err(pthread_mutex_lock(&head->philo.philo_mtx), MTX_LOCK_UNLOCK_DSTY);
		if(time_diff(data->simulation_start, current_time)
			- head->philo.last_meal >= data->args.time_to_die
			&& head->philo.state != DEAD)
		{
		// check_mtx_return_err(pthread_mutex_unlock(&head->philo.philo_mtx), MTX_LOCK_UNLOCK_DSTY);
			die(&head->philo);
			data->health_status = true;
			return (NULL);
		}
		if(data->args.meals_must_eat > 0)
		{
			if(head->philo.meals_ate >= data->args.meals_must_eat)
				eat_score++;
			if(eat_score == data->args.nbr_of_philos)
			{
				data->health_status = true;
				return (NULL);
			}			
		}		
		if(head->philo.philo_id == data->args.nbr_of_philos)
			eat_score = 0;
		head = temp;
	}
	return (NULL);
}
