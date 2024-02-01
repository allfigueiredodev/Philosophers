// #define YE_BLUE     "\033[34;43m" yellow background with blue text
#define RED     	"\033[1;31m"
#define GREEN   	"\033[1;32m"
#define YELLOW 		"\033[1;33m"
#define BLUE    	"\033[1;34m"
#define MAGENTA    	"\033[1;35m"
#define CYAN    	"\033[1;36m"
#define WHITE    	"\033[1;37m"
#define DFT   		"\033[0m"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef enum t_bool
{
	false,
	true
} t_bool;

typedef enum t_state
{
	TOOK_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
} t_state;

typedef struct s_forks
{
	int		id;
	t_bool	available;
} t_forks;

typedef struct s_args
{
	int nbr_of_philos;
	double time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int meals_must_eat;
} t_args;

typedef struct s_philo
{
	int			philo_id;
	t_state 	state;
	int			meals_ate;
	double		last_meal;
	t_forks		left_fork;
	t_forks		right_fork;
} t_philo;

typedef struct s_dclist
{
	t_philo			philo;
	struct s_dclist	*next;
	struct s_dclist	*prev;
} t_dclist;

typedef struct s_data
{
	t_args		args;
	struct		timeval simulation_start;
	t_dclist	*table;
	t_locks		lock;
} t_data;

typedef struct s_health
{
	int eat_score;
	int death_score;
}	t_health;

typedef	struct s_locks
{
	pthread_mutex_t	lock_1;
	pthread_mutex_t	lock_2;
}	t_locks;

long		philo_atoi(const char *str);
int			init_philo(t_data *data, char **argv);
int			input_validation(char **argv);
void		init_data(t_data *data); // prevents conditional jumps
void		set_data_args(t_data *data, t_args args);
int			dc_lstsize(t_dclist *lst);
t_dclist	*dc_lst_last(t_dclist *lst);
void		lst_prev_next(t_dclist **alst, t_dclist *new);
t_dclist	*lst_new_node(int id);
void		pick_a_fork(t_data *data, t_philo *philo);
void		eat(t_data *data, t_philo *philo);
void		die(t_data *data, t_philo *philo);
double		time_diff(struct timeval start, struct timeval end);
void		set_right_fork(t_data *data);
void		init_table(t_data *data);
