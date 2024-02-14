/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:02:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 19:33:33 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*run(void *data)
{
	t_philo	*philo;
	t_data	*main_data;

	philo = (t_philo *)data;
	main_data = get_data();
	while (!lock_bool_return(&main_data->data_mtx, &main_data->health_status))
	{
		if (!lock_bool_return(&main_data->data_mtx, &main_data->health_status))
			pick_a_fork(philo);
		if (lock_state_return(&philo->philo_mtx,
				&philo->state) == TOOK_BOTH_FORKS)
		{
			if (lock_bool_return(&main_data->data_mtx,
					&main_data->health_status))
			{
				pthread_mutex_unlock(&philo->left_fork->mtx_fork);
				pthread_mutex_unlock(&get_right_fork(philo)->mtx_fork);
				return (NULL);
			}
			eat(philo);
			philo_sleep(philo);
		}
	}
	return (NULL);
}

void	simulation_runner(t_data *data)
{
	int			i;
	t_dclist	*head;
	t_dclist	*temp;

	i = 0;
	head = data->table;
	while (i != data->args.nbr_of_philos)
	{
		temp = head->next;
		pthread_create(&head->philo.tid, NULL, run, &head->philo);
		head = temp;
		i++;
	}
	check_philo_health(data);
	i = 0;
	while (i != data->args.nbr_of_philos)
	{
		temp = head->next;
		pthread_join(head->philo.tid, NULL);
		head = temp;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = get_data();
	if (argc < 5 || argc > 6 || !init_philo(data, argc, argv))
	{
		printf("%sNot enought arguments!%s\n", RED, DFT);
		return (0);
	}
	init_table(data);
	simulation_runner(data);
	free_all(data);
}
