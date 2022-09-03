#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
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
	ssize_t			launch_time;
	int				finish;
	struct s_philo *philos;
    sem_t           *check_live_status;
    sem_t           *print_logs;
    sem_t           *forks;
} t_data;

typedef struct s_philo
{
	int 			number;
	struct s_data	*data;
	pthread_mutex_t	fork;
	ssize_t			eat_last_time;
	int 			count_eat;
    pid_t           pid;

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
void    finish_processes(t_data *data);
#endif
