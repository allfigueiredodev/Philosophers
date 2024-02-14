/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_time_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:40:55 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 18:56:31 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	time_diff(struct timeval start, struct timeval end)
{
	long	result;
	long	seconds;
	long	microseconds;

	seconds = (end.tv_sec - start.tv_sec) * 1000;
	microseconds = (end.tv_usec - start.tv_usec) / 1000;
	result = seconds + microseconds;
	return (result);
}

struct timeval	curr_time(void)
{
	struct timeval	temp;

	gettimeofday(&temp, NULL);
	return (temp);
}

void	c_usleep(long ms)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (ms > time_diff(start, curr_time()))
		usleep(100);
}
