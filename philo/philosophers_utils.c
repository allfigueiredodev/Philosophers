/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:40:55 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 19:33:40 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	get_start_time(t_data *data)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	data->simulation_start = start;
}

long	philo_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

void	free_all(t_data *data)
{
	t_dclist	*head;
	t_dclist	*temp;

	head = data->table;
	pthread_mutex_destroy(&data->data_mtx);
	while (head->philo.philo_id != data->args.nbr_of_philos)
	{
		temp = head->next;
		pthread_mutex_destroy(&head->philo.philo_mtx);
		pthread_mutex_destroy(&head->philo.left_fork->mtx_fork);
		free(head->philo.left_fork);
		free(head);
		head = temp;
	}
	free(head->philo.left_fork);
	free(head);
}
