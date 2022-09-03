#include "../include/philo.h"

static void wait_finish(t_data *data)
{
	int i;

	while(!data->finish)
	{
		i = -1;
		while (!data->finish && ++i < data->number_of_philo)
		{
			pthread_mutex_lock(&data->check_live_status);
			if (ft_get_time() - (size_t)data->philos[i].eat_last_time >
			(size_t)data->time_to_die)
			{
				print_log(&data->philos[i], DIED);
				data->finish = 1;
			}
			pthread_mutex_unlock(&data->check_live_status);
			usleep(100);
		}
        i = 0;
        while (data->must_eat != -1 && !data->finish && i < data->number_of_philo &&
               data->philos[i].count_eat >= data->must_eat)
            i++;
        if (i  == data->number_of_philo)
            data->finish = 1;
    }
}

static void	philo_actions(t_philo *philo, t_data *data)
{
    pthread_mutex_lock(&philo->fork);
	print_log(philo, HAS_TAKEN_A_FORK);
	if (philo->right_philo)
	{
		pthread_mutex_lock(&philo->right_philo->fork);
		print_log(philo, HAS_TAKEN_A_FORK);
        pthread_mutex_lock(&data->check_live_status);
        print_log(philo, EAT);
        philo->count_eat++;
        philo->eat_last_time = ft_get_time();
        pthread_mutex_unlock(&data->check_live_status);
        ft_usleep(philo->data, philo->data->time_to_eat);
        pthread_mutex_unlock(&philo->fork);
        pthread_mutex_unlock(&philo->right_philo->fork);
        print_log(philo, SLEEP);
		ft_usleep(data, data->time_to_sleep);
		print_log(philo, THINK);
	}
	else
	{
        pthread_mutex_unlock(&philo->fork);
        ft_usleep(data, data->time_to_die + 1000);
    }
}
static void	*philo_proc(void *arg)
{
	t_philo *philo;

    philo = (t_philo *) arg;
    if (philo->number % 2 == 0)
		usleep(1000);
	while (!philo->data->finish)
		philo_actions(philo, philo->data);
	return (NULL);
}

static int	emulate(t_data *data)
{
	int	i;
	pthread_t   threads[data->number_of_philo];

    data->launch_time = ft_get_time();
    i = -1;
	while (++i < data->number_of_philo)
	{
        data->philos[i].eat_last_time = data->launch_time;
        if (pthread_create(&threads[i], NULL, &philo_proc, &data->philos[i]))
        {
            printf("Thread create error\n");
            return (1);
        }
	}
	wait_finish(data);
	i = -1;
	while (++i < data->number_of_philo)
        pthread_join(threads[i], NULL);
	i = -1;
	while (++i < data->number_of_philo)
		pthread_mutex_destroy(&data->philos[i].fork);
    pthread_mutex_destroy(&data->print_logs);
    pthread_mutex_destroy(&data->check_live_status);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	*data;

	if (init_data(&data, argc, argv) == 1)
		return (1);
	emulate(data);
	free(data->philos);
	free(data);
	return (errno);
}