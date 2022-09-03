#include "../include/philo_bonus.h"

void    finish_processes(t_data *data)
{
    int i;
    int status;

    i = -1;
    while (++i < data->number_of_philo)
    {
        waitpid(-1, &status, 0);
        if (WEXITSTATUS(status) == 1)
        {
            i = -1;
            while (++i < data->number_of_philo)
                kill(data->philos[i].pid, SIGKILL);
            break;
        }
    }
    sem_close(data->check_live_status);
    sem_close(data->print_logs);
    sem_close(data->forks);
}

size_t	ft_get_time()
{
	struct	timeval time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(t_data *data, size_t sleep_time)
{
	size_t start_sleep;

	start_sleep = ft_get_time();
	while (!data->finish)
	{
		if (ft_get_time() - start_sleep >= sleep_time)
			break ;
		usleep(100);
	}
}

void	print_log(t_philo *philo, int status)
{
    size_t time;

    sem_wait(philo->data->print_logs);
    if (!philo->data->finish)
    {
        time = ft_get_time() - philo->data->launch_time;
        printf("%ld ", time);
        printf("%d ", philo->number);
        if (status == HAS_TAKEN_A_FORK)
            printf("has taken a fork\n");
        if (status == EAT)
            printf("is eating\n");
        if (status == SLEEP)
            printf("is sleeping\n");
        if (status == THINK)
            printf("is thinking\n");
        if (status == DIED)
            printf("is died\n");
    }
    sem_post(philo->data->print_logs);
}