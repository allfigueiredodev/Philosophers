/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:45:16 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 17:22:16 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_table(t_data *data)
{
	int total_of_philos;
	int i;

	total_of_philos = data->args.nbr_of_philos;
	check_mtx_return_err(pthread_mutex_init(&data->data_mtx, NULL), MTX_INIT);
	check_mtx_return_err(pthread_mutex_init(&data->print_mtx, NULL), MTX_INIT);
	data->health_status = false;
	gettimeofday(&data->simulation_start, NULL);
	i = 1;
	while (i <= total_of_philos)
	{
		lst_prev_next(&data->table, lst_new_node(i));
		i++;
	}
}
