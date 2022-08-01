#include "../include/philo.h"
void	wait_finish(t_data *data)
{
	int	count_fed_philos;
	int i;

	while(!data->finish)
	{
		i = -1;
		while (++i < data->number_of_philo && !data->finish)
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
		count_fed_philos = 0;
		while (--i >= 0 && !data->finish &&
		data->must_eat != -1 && data->must_eat <= data->philos[i].count_eat)
				count_fed_philos++;
		if (count_fed_philos == data->number_of_philo)
			data->finish = 1;
	}
}

void	philo_actions(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->fork);
	print_log(philo, HAS_TAKEN_A_FORK);
	if (philo->right_philo)
	{
		pthread_mutex_lock(&philo->right_philo->fork);
		print_log(philo, HAS_TAKEN_A_FORK);
		print_log(philo, EAT);
		philo->count_eat++;
		pthread_mutex_lock(&data->check_live_status);
		philo->eat_last_time = ft_get_time();
		pthread_mutex_unlock(&data->check_live_status);
		ft_usleep(philo->data, philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->right_philo->fork);
		pthread_mutex_unlock(&philo->fork);
		print_log(philo, SLEEP);
		ft_usleep(data, data->time_to_sleep);
		print_log(philo, THINK);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		ft_usleep(data, data->time_to_die);
	}
}
void	*philo_proc(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	if (philo->number % 2 == 0)
		usleep(1000);
	while (!philo->data->finish)
		philo_actions(philo, philo->data);
	return (NULL);
}

int	emulate(t_data *data)
{
	int	i;
	pthread_t threads[data->number_of_philo];

	i = -1;
	while (++i < data->number_of_philo)
	{
		data->philos[i].eat_last_time = ft_get_time();
		if (pthread_create(&threads[i], NULL, &philo_proc, &data->philos[i]))
			return (1);
	}
	wait_finish(data);
	i = -1;
	while (++i < data->number_of_philo)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
	}
	i = -1;
	while (++i < data->number_of_philo)
		pthread_mutex_destroy(&data->philos[i].fork);
	pthread_mutex_destroy(&data->check_live_status);
	pthread_mutex_destroy(&data->print_logs);
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
	return (0);
}