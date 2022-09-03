#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>

# define HAS_TAKEN_A_FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIED 4

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	size_t			launch_time;
	int				finish;
	struct s_philo *philos;
	pthread_mutex_t check_live_status;
	pthread_mutex_t print_logs;
} t_data;

typedef struct s_philo
{
	int 			number;
	struct s_data	*data;
	struct s_philo	*right_philo;
	pthread_mutex_t	fork;
	ssize_t			eat_last_time;
	int 			count_eat;
}	t_philo;
//init
int		init_data(t_data **data, int argc, char **argv);
//init_utils
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		error_message(int argc, char *argv);
//utils
size_t	ft_get_time();
void	print_log(t_philo *philo, int status);
void	ft_usleep(t_data *data, size_t sleep_time);
#endif
