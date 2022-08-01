#include "../include/philo.h"

size_t	ft_get_time()
{
	struct	timeval time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(t_data *data, ssize_t sleep_time)
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

	time = ft_get_time();
	if (philo->data->finish)
		return ;
	pthread_mutex_lock(&philo->data->print_logs);
	printf("%ld ", time - philo->data->launch_time);
	printf("%d ", philo->number + 1);
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
	pthread_mutex_unlock(&philo->data->print_logs);
}