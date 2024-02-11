/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:02:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/11 13:38:15 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *run(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	
	// check_mtx_return_err(pthread_mutex_lock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	if(philo->state == DEAD)
	{
		// check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		usleep(10000);
	pick_a_fork(philo);
	// check_mtx_return_err(pthread_mutex_lock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	if(philo->state == TOOK_BOTH_FORKS)
		eat(philo);
	else
	{
	// 	check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
		return (NULL);
	}
	// check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	philo_sleep(philo);
	return (NULL);
}

void simulation_runner(t_data *data)
{
	int i;
	int j;
	t_dclist *head;
	t_dclist *temp;

	i = 0;
	j = 0;
	head = data->table;
	// check_mtx_return_err(pthread_mutex_lock(&data->data_mtx), MTX_LOCK_UNLOCK_DSTY);
	while(i != data->args.nbr_of_philos && !data->health_status)
	{
		// check_mtx_return_err(pthread_mutex_unlock(&data->data_mtx), MTX_LOCK_UNLOCK_DSTY);
		temp = head->next;
		check_thd_return_err(pthread_create(&head->philo.tid, NULL, run, &head->philo), THD_CREATE);
		// check_thd_return_err(pthread_detach(head->philo.tid), THD_DETACH);
		head = temp;
		i++;
		j++;
	}
	i = 0;
	head = data->table;
	while(i++ != j)
	{
		temp = head->next;
		check_thd_return_err(pthread_join(head->philo.tid, NULL), THD_JOIN);
		head = temp;
	}
}

int main (int argc, char **argv)
{
	t_data 		*data;
	pthread_t 	health_thread;

	data = get_data();
	if(argc < 5 || argc > 6 || !init_philo(data, argc, argv))
	{
		printf("%sNot enought arguments!%s\n", RED, DFT);
		return (0);
	}
	init_table(data);
	while (!data->health_status)
	{
		check_thd_return_err(pthread_create(&health_thread, NULL, end_conditions, data), THD_CREATE);
		simulation_runner(data);
		check_thd_return_err(pthread_join(health_thread, NULL), THD_JOIN);
	}
}
