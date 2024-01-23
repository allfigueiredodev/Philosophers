/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:02:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/22 23:59:27 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void set_right_fork(t_data *data)
{
	
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

int main (int argc, char **argv)
{
	t_data data;
	
	if(argc < 5 || argc > 6 || !init_philo(&data, argv))
	{
		printf("%sNot enought arguments!%s\n", RED, DFT);
		return (0); 
	}
	init_table(&data);
	printf("%snbr of philos:%s %d\n", RED, DFT, data.args.nbr_of_philos);
	printf("%stime to die:%s %d\n", GREEN, DFT, data.args.time_to_die);
	printf("%stime to eat:%s %d\n", YELLOW, DFT, data.args.time_to_eat);
	printf("%stime to sleep:%s %d\n", BLUE, DFT, data.args.time_to_sleep);
	printf("%smeals must eat:%s %d\n", MAGENTA, DFT, data.args.meals_must_eat);
}
	
// 	- number_of_philosophers: The number of philosophers and also the number
// of forks.
// 	- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
// milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
// 	- time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
// During that time, they will need to hold two forks.
// 	- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
// 	- number_of_times_each_philosopher_must_eat (optional argument): If all
// philosophers have eaten at least number_of_times_each_philosopher_must_eat
// times, the simulation stops. If not specified, the simulation stops when a
// philosopher dies.