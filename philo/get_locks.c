/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_locks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:08:13 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 17:08:55 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_state	lock_state_return(pthread_mutex_t *mutex, t_state *value)
{
	t_state	ret;

	check_mtx_return_err(pthread_mutex_lock(mutex), MTX_LOCK_UNLOCK_DSTY);
	ret = *value;
	check_mtx_return_err(pthread_mutex_unlock(mutex), MTX_LOCK_UNLOCK_DSTY);
	return (ret);
}

t_bool	lock_bool_return(pthread_mutex_t *mutex, t_bool *value)
{
	t_bool	ret;

	check_mtx_return_err(pthread_mutex_lock(mutex), MTX_LOCK_UNLOCK_DSTY);
	ret = *value;
	check_mtx_return_err(pthread_mutex_unlock(mutex), MTX_LOCK_UNLOCK_DSTY);
	return (ret);
}

int		lock_int_return(pthread_mutex_t *mutex, int *value)
{
	int	ret;

	check_mtx_return_err(pthread_mutex_lock(mutex), MTX_LOCK_UNLOCK_DSTY);
	ret = *value;
	check_mtx_return_err(pthread_mutex_unlock(mutex), MTX_LOCK_UNLOCK_DSTY);
	return (ret);
}

long	lock_long_return(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	check_mtx_return_err(pthread_mutex_lock(mutex), MTX_LOCK_UNLOCK_DSTY);
	ret = *value;
	check_mtx_return_err(pthread_mutex_unlock(mutex), MTX_LOCK_UNLOCK_DSTY);
	return (ret);
}
