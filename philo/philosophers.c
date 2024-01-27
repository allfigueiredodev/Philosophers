/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:02:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/26 22:58:32 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

double time_diff(struct timeval start, struct timeval end)
{
	double	result;
	long	seconds;
	long	microseconds;

	// if (!start.tv_sec && !start.tv_usec)
	// {
	// 	result = start.tv_sec + start.tv_usec;
	// }
	seconds = (end.tv_sec - start.tv_sec) * 1e9;
	microseconds = (end.tv_usec - start.tv_usec) / 1e3;
	result = seconds + microseconds;
	return(result);
}

void run(t_data *data)
{
	t_dclist *head;
	t_dclist *temp;
	
	head = data->table;
	while(head->philo.philo_id != data->args.nbr_of_philos)
	{
		temp = head->next;
		pick_a_fork(data, &head->philo);
		head = temp;
	}
}

t_health check_philo_health(t_data *data)
{
	t_health result;
	t_dclist *head;
	t_dclist *temp;
	struct timeval current_time;
	double current;
	
	gettimeofday(&current_time, NULL);
	current = 00.0;
	head = data->table;
	result = (t_health){
		.death_score = 0,
		.eat_score = 0
	};
	while(head->philo.philo_id != data->args.nbr_of_philos)
	{
		temp = head->next;
		if(!head->philo.last_meal)
			head->philo.last_meal = 00.0;
		if(current - head->philo.last_meal >= data->args.time_to_die)
			head->philo.state = DEAD;
		if(head->philo.state == DEAD)
			result.death_score++;
		if(head->philo.meals_ate >= data->args.meals_must_eat)
			result.eat_score++;
		head = temp;
	}
	return (result);
}

int end_conditions(t_data *data)
{
	t_health current_health;

	current_health = check_philo_health(data);
	if(current_health.death_score == data->args.nbr_of_philos
		|| current_health.eat_score == data->args.nbr_of_philos)
		return (1);
	return (0);
}

void start_simulation(t_data *data)
{
	struct timeval start;
	
	gettimeofday(&start, NULL);
	data->simulation_start =  start;
	
	while(!end_conditions(data))
		run(data);
}

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

int main (int argc, char **argv)
{
	t_data data;
	
	if(argc < 5 || argc > 6 || !init_philo(&data, argv))
	{
		printf("%sNot enought arguments!%s\n", RED, DFT);
		return (0);
	}
	init_table(&data);
	start_simulation(&data);
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
// philosopher dies.// 	- number_of_philosophers: The number of philosophers and also the number
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