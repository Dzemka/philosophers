#include "../include/philo.h"

size_t	ft_get_time()
{
	struct	timeval time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(t_data *data, size_t sleep_time)
{
	ssize_t start_sleep;

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
	size_t	time;

    time = ft_get_time() - philo->data->launch_time;
    pthread_mutex_lock(&philo->data->print_logs);
    if (!philo->data->finish)
    {
        printf("%ld ", time);
        printf("%d ", philo->number);
        if (status == HAS_TAKEN_A_FORK)
            printf("has taken a fork");
        if (status == EAT)
            printf("is eating");
        if (status == SLEEP)
            printf("is sleeping");
        if (status == THINK)
            printf("is thinking");
        if (status == DIED)
            printf("is died");
        printf("\n");
    }
	pthread_mutex_unlock(&philo->data->print_logs);
}