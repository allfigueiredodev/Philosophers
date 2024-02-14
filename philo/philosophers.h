/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis-p <aperis-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:13:11 by aperis-p          #+#    #+#             */
/*   Updated: 2024/02/14 19:22:36 by aperis-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define BLUE_GREEN "\033[32;44m"
# define MAG_YE "\033[33;45m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define DFT "\033[0m"

# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum t_bool
{
	false,
	true
}					t_bool;

typedef enum t_state
{
	TOOK_A_FORK,
	TOOK_BOTH_FORKS,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}					t_state;

typedef enum t_thd_mtx_type
{
	MTX_INIT,
	MTX_LOCK_UNLOCK_DSTY,
	THD_CREATE,
	THD_DETACH,
	THD_JOIN
}					t_thd_mtx_type;

typedef struct s_forks
{
	int				id;
	pthread_mutex_t	mtx_fork;
	t_bool			available;
}					t_forks;

typedef struct s_args
{
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_must_eat;
}					t_args;

typedef struct s_philo
{
	int				philo_id;
	t_state			state;
	pthread_mutex_t	philo_mtx;
	pthread_t		tid;
	int				meals_ate;
	long			last_meal;
	t_forks			*left_fork;
}					t_philo;

typedef struct s_dclist
{
	t_philo			philo;
	struct s_dclist	*next;
	struct s_dclist	*prev;
}					t_dclist;

typedef struct s_data
{
	t_args			args;
	struct timeval	simulation_start;
	t_dclist		*table;
	pthread_mutex_t	data_mtx;
	pthread_mutex_t	print_mtx;
	t_bool			health_status;
	int				eat_score;
}					t_data;

long				philo_atoi(const char *str);
int					init_philo(t_data *data, int argc, char **argv);
int					input_validation(char **argv);
void				init_data(t_data *data);
void				set_data_args(t_data *data, t_args args);
int					dc_lstsize(t_dclist *lst);
t_dclist			*dc_lst_last(t_dclist *lst);
void				lst_prev_next(t_dclist **alst, t_dclist *new);
t_dclist			*lst_new_node(int id);
void				pick_a_fork(t_philo *philo);
void				eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				die(t_philo *philo);
long				time_diff(struct timeval start, struct timeval end);
void				init_table(t_data *data);
t_forks				*get_right_fork(t_philo *philo);
t_data				*get_data(void);
void				check_philo_health(t_data *data);
void				end_conditions(t_data *data);
void				free_all(t_data *data);
long				lock_long_return(pthread_mutex_t *mutex, long *value);
int					lock_int_return(pthread_mutex_t *mutex, int *value);
t_bool				lock_bool_return(pthread_mutex_t *mutex, t_bool *value);
t_state				lock_state_return(pthread_mutex_t *mutex, t_state *value);
void				fork_selection(t_philo *philo, int flag);
void				print_validator(t_data *data, long time, int id,
						t_state state);

#endif