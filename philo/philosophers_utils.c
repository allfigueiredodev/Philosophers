/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:40:55 by aperis-p          #+#    #+#             */
/*   Updated: 2024/01/31 19:43:39 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void get_start_time(t_data *data)
{
	struct timeval start;
	
	gettimeofday(&start, NULL);
	data->simulation_start =  start;
}

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
	// seconds = (end.tv_sec - start.tv_sec) * 1000;
	microseconds = (end.tv_usec - start.tv_usec) / 1e3;
	result = seconds + microseconds;
	return(result);
}

long	philo_atoi(const char *str)
{
	int		i;
	int		sign;
	int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
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