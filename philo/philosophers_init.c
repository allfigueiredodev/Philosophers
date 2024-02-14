/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:43:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 18:56:11 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_data_args(t_data *data, t_args args)
{
	(&data->args)->nbr_of_philos = args.nbr_of_philos;
	(&data->args)->time_to_die = args.time_to_die;
	(&data->args)->time_to_eat = args.time_to_eat;
	(&data->args)->time_to_sleep = args.time_to_sleep;
	(&data->args)->meals_must_eat = args.meals_must_eat;
}

void	init_data(t_data *data)
{
	memset(data, 0, sizeof(t_data));
	(&data->args)->nbr_of_philos = 0;
	(&data->args)->time_to_die = 0;
	(&data->args)->time_to_eat = 0;
	(&data->args)->time_to_sleep = 0;
	(&data->args)->meals_must_eat = 0;
}

int	input_validation(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (philo_atoi(argv[i]) < 1)
			return (0);
		i++;
	}
	return (1);
}

int	init_philo(t_data *data, int argc, char **argv)
{
	init_data(data);
	if (input_validation(argv) && argc == 5)
		set_data_args(data,
			(t_args){
			.nbr_of_philos = philo_atoi(argv[1]),
			.time_to_die = philo_atoi(argv[2]),
			.time_to_eat = philo_atoi(argv[3]),
			.time_to_sleep = philo_atoi(argv[4]),
			.meals_must_eat = -1,
		});
	else if (input_validation(argv) && argc == 6)
		set_data_args(data,
			(t_args){
			.nbr_of_philos = philo_atoi(argv[1]),
			.time_to_die = philo_atoi(argv[2]),
			.time_to_eat = philo_atoi(argv[3]),
			.time_to_sleep = philo_atoi(argv[4]),
			.meals_must_eat = philo_atoi(argv[5]),
		});
	else
		return (0);
	return (1);
}
