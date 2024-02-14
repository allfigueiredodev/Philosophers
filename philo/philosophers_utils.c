/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:40:55 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 01:46:35 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void check_mtx_return_err(int err, t_thd_mtx_type type)
{
	if (!err)
		return ;
	else if (err == EINVAL && type == MTX_LOCK_UNLOCK_DSTY)
		printf("%sThe value specified by mutex is invalid.%s\n", BLUE_GREEN, DFT);	
	else if (err == EINVAL && type == MTX_INIT)
		printf("%sThe value specified by attr is invalid.%s\n", BLUE_GREEN, DFT);	
	else if (err == ENOMEM && type == MTX_INIT)
		printf("%sThe process cannot allocate enough memory to create another mutex.%s\n", BLUE_GREEN, DFT);	
	else if (err == EDEADLK && type == MTX_LOCK_UNLOCK_DSTY)
		printf("%sA deadlock would occur if the thread blocked waiting for mutex.%s\n", BLUE_GREEN, DFT);
	else if (err == EPERM && type == MTX_LOCK_UNLOCK_DSTY)
		printf("%sThe current thread does not hold a lock on mutex.%s\n", BLUE_GREEN, DFT);	
	else if (err == EBUSY && type == MTX_LOCK_UNLOCK_DSTY)
		printf("%sMutex is locked.%s\n", BLUE_GREEN, DFT);
	else if (err == ENOTRECOVERABLE && type == MTX_LOCK_UNLOCK_DSTY)
		printf("%sThe state protected by the mutex is not recoverable.%s\n", BLUE_GREEN, DFT);
	else if (err == EOWNERDEAD && type == MTX_LOCK_UNLOCK_DSTY)
		printf("%sThe mutex is a robust mutex and the process containing the \
              previous owning thread terminated while holding the mutex \
              lock. The mutex lock shall be acquired by the calling \
              thread and it is up to the new owner to make the state \
              consistent.%s\n", BLUE_GREEN, DFT);
}

void check_thd_return_err(int err, t_thd_mtx_type type)
{
	if (!err)
		return ;
	else if (err == EINVAL && type == THD_CREATE)
		printf("%sThe value specified by attr is invalid.%s\n", MAG_YE, DFT);
	else if (err == EINVAL && type == THD_DETACH)
		printf("%sThe implementation has detected that the value \
			specified by thread does not refer to a joinable \
			thread.%s\n", MAG_YE, DFT);
	else if (err == EINVAL && type == THD_JOIN)
		printf("%sThe implementation has detected that the value \
			specified by thread does not refer to a joinable thread.%s\n", MAG_YE, DFT);
	else if (err == EDEADLK && type == THD_JOIN)
		printf("%sA deadlock was detected or the value of thread \
			specifies the calling thread.%s\n", MAG_YE, DFT);
	else if (err == EPERM && type == THD_CREATE)
		printf("%sThe caller does not have appropriate permission to set \
			the required scheduling parameters or scheduling policy.%s\n", MAG_YE, DFT);
	else if (err == EAGAIN && type == THD_CREATE)
		printf("%sThe system lacked the necessary resources to create \
			another thread, or the system-imposed limit on the \
			total number of threads in a process \
			[PTHREAD_THREADS_MAX] would be exceeded.%s\n", MAG_YE, DFT);
	else if (err == ESRCH && (type == THD_DETACH || type == THD_JOIN))
		printf("%sNo thread could be found corresponding to that \
			speci-fied by the given thread ID, thread.%s\n", MAG_YE, DFT);
}

t_data *get_data(void)
{
	static t_data data;
	return (&data);
}

void get_start_time(t_data *data)
{
	struct timeval start;
	
	gettimeofday(&start, NULL);
	data->simulation_start =  start;
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
void free_all(t_data *data)
{
	t_dclist *head;
	t_dclist *temp;

	head = data->table;
	pthread_mutex_destroy(&data->data_mtx);
	while(head->philo.philo_id != data->args.nbr_of_philos)
	{
		temp = head -> next;
		pthread_mutex_destroy(&head->philo.philo_mtx);
		pthread_mutex_destroy(&head->philo.left_fork->mtx_fork);
		free(head->philo.left_fork);
		free(head);
		head = temp;
	}
	free(head->philo.left_fork);
	free(head);
	printf("All data freed\n");
}
