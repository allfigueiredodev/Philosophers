/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:02:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/13 15:02:00 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *run(void *data)
{
	t_philo *philo;
	t_data	*main_data;
	
	philo = (t_philo *)data;
	main_data = get_data();
	while(!main_data->health_status)
	{
		// check_mtx_return_err(pthread_mutex_lock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
		if (philo->philo_id % 2 == 0)
			usleep(10000);
		pick_a_fork(philo);
		// check_mtx_return_err(pthread_mutex_lock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
		if(philo->state == TOOK_BOTH_FORKS)
		{
			eat(philo);
			philo_sleep(philo);		
		}
		else
		{
			// check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
			return (NULL);
		}
		// check_mtx_return_err(pthread_mutex_unlock(&philo->philo_mtx), MTX_LOCK_UNLOCK_DSTY);
	}
	return (NULL);
}

void simulation_runner(t_data *data)
{
	int i;
	t_dclist	*head;
	t_dclist	*temp;
	pthread_t	health;

	i = 0;
	head = data->table;
	check_thd_return_err(pthread_create(&health, NULL, check_philo_health, data), THD_CREATE);
	// check_philo_health(data);
	while(i != data->args.nbr_of_philos)
	{
		temp = head->next;
		check_thd_return_err(pthread_create(&head->philo.tid, NULL, run, &head->philo), THD_CREATE);
		printf("thread created: %d\n", i + 1);
		head = temp;
		i++;
	}
	i = 0;
	while(i != data->args.nbr_of_philos)
	{
		temp = head->next;
		printf("joining thread tid: %d\n", (int)head->philo.tid);
		check_thd_return_err(pthread_join(head->philo.tid, NULL), THD_JOIN);
		// check_thd_return_err(pthread_detach(head->philo.tid), THD_DETACH);
		printf("joinned thread id: %d\n", head->philo.philo_id);
		head = temp;
		i++;
	}
}

int main (int argc, char **argv)
{
	t_data 		*data;

	data = get_data();
	if(argc < 5 || argc > 6 || !init_philo(data, argc, argv))
	{
		printf("%sNot enought arguments!%s\n", RED, DFT);
		return (0);
	}
	init_table(data);
	simulation_runner(data);
	free_all(data);
	printf("THE END\n");
}
