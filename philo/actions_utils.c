/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:18:38 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 19:25:23 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_validator(t_data *data, long time, int id, t_state state)
{
	if (!lock_bool_return(&data->data_mtx, &data->health_status))
	{
		pthread_mutex_lock(&data->print_mtx);
		if (state == TOOK_A_FORK)
			printf("%s%ld %d has taken a fork\n%s", YELLOW, time, id, DFT);
		else if (state == EATING)
			printf("%s%ld %d is eating\n%s", RED, time, id, DFT);
		else if (state == SLEEPING)
			printf("%s%ld %d is sleeping\n%s", BLUE, time, id, DFT);
		else if (state == THINKING)
			printf("%s%ld %d is thinking\n%s", GREEN, time, id, DFT);
		else if (state == DEAD)
			printf("%s%ld %d died\n%s", MAGENTA, time, id, DFT);
		pthread_mutex_unlock(&data->print_mtx);
	}
}

void	fork_selection(t_philo *philo, int flag)
{
	if (!flag)
	{
		if (philo->philo_id % 2 == 0)
			pthread_mutex_lock(&get_right_fork(philo)->mtx_fork);
		else
			pthread_mutex_lock(&philo->left_fork->mtx_fork);
	}
	else if (flag)
	{
		if (philo->philo_id % 2 == 0)
			pthread_mutex_lock(&philo->left_fork->mtx_fork);
		else
			pthread_mutex_lock(&get_right_fork(philo)->mtx_fork);
	}
}
