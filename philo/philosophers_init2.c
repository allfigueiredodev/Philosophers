/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:45:16 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/29 15:46:06 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void set_right_fork(t_data *data)
{
	t_dclist *head;
	t_dclist *temp;

	head = data->table;
	while(!head->philo.right_fork.id)
	{
		temp = head->next;
		head->philo.right_fork.id = head->prev->philo.left_fork.id;
		head->philo.right_fork.available = true;
		head = temp;
	}
}

void init_table(t_data *data)
{
	int total_of_philos;
	int i;

	total_of_philos = data->args.nbr_of_philos;
	i = 1;
	while (i <= total_of_philos)
	{
		lst_prev_next(&data->table, lst_new_node(i));
		i++;
	}
	set_right_fork(data);
}