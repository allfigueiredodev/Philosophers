/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:02:31 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/31 21:18:22 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	pick_a_fork(data, &head->philo);
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
		if(current - head->philo.last_meal >= data->args.time_to_die && head->philo.state != DEAD)
			die(data, &head->philo);
		if(head->philo.state == DEAD)
			result.death_score++;
		if(head->philo.meals_ate >= data->args.meals_must_eat)
			result.eat_score++;
		
		head = temp;
	}
	if(!head->philo.last_meal)
		head->philo.last_meal = 00.0;
	if(current - head->philo.last_meal >= data->args.time_to_die && head->philo.state != DEAD)
		die(data, &head->philo);
	if(head->philo.state == DEAD)
		result.death_score++;
	if(head->philo.meals_ate >= data->args.meals_must_eat)
		result.eat_score++;
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

int main (int argc, char **argv)
{
	t_data data;
	pthread_t health_thread;
	pthread_t action_thread;

	pthread_mutex_init(&data.lock.lock_1, NULL);
	pthread_mutex_init(&data.lock.lock_2, NULL);
	if(argc < 5 || argc > 6 || !init_philo(&data, argv))
	{
		printf("%sNot enought arguments!%s\n", RED, DFT);
		return (0);
	}
	init_table(&data);
	while(!pthread_create(&health_thread, NULL, end_conditions, &data))
	{
		pthread_join(health_thread, NULL);
		pthread_create(&action_thread, NULL, run, &data);
		pthread_join(action_thread, NULL);
	}
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