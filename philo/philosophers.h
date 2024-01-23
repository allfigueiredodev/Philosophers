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

typedef enum t_state
{
	TOOK_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
} t_state;

typedef struct s_dclist
{
	t_philo			philo;
	struct s_dclist	*next;
	struct s_dclist	*prev;
} t_dclist;

typedef struct s_args
{
	int nbr_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int meals_must_eat;
} t_args;

typedef struct s_philo
{
	int		philo_id;
	t_state state;
	int		meals_ate;
	int		last_meal;
	int		left_fork_id; // this should point to a fork struct
	int		right_fork_id; // this should point to a fork struct
} t_philo;

typedef struct s_data
{
	t_args		args;
	int			simulation_start;
	t_dclist	*table;
} t_data;

long		philo_atoi(const char *str);
int			init_philo(t_data *data, char **argv);
int			input_validation(char **argv);
void		init_data(t_data *data); // prevents conditional jumps
void		set_data_args(t_data *data, t_args args);
int			dc_lstsize(t_dclist *lst);
t_dclist	*dc_lst_last(t_dclist *lst);
void		lst_prev_next(t_dclist **alst, t_dclist *new);
t_dclist	*lst_new_node(int id);
