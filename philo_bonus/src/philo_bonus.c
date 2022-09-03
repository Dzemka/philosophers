#include "../include/philo_bonus.h"

void	*wait_finish(void *arg)
{
    t_data  *data;
    t_philo *philo;

    philo = (t_philo *)arg;
    data = philo->data;
    while(!data->finish)
	{
        sem_wait(data->check_live_status);
        if (ft_get_time() - philo->eat_last_time >
        (size_t)data->time_to_die)
        {
            print_log((t_philo *)philo, DIED);
            exit (1);
        }
        sem_post(data->check_live_status);
        if (data->finish)
            break ;
        if (data->must_eat != -1 && philo->count_eat >= data->must_eat)
        {
            data->finish = 1;
            break;
        }
        usleep(1000);
    }
    return (NULL);
}

void	philo_actions(t_philo *philo, t_data *data)
{
    sem_wait(philo->data->forks);
	print_log(philo, HAS_TAKEN_A_FORK);
	if (philo->data->number_of_philo > 1)
	{
        sem_wait(philo->data->forks);
        print_log(philo, HAS_TAKEN_A_FORK);
        print_log(philo, EAT);
        sem_wait(data->check_live_status);
        philo->count_eat++;
        philo->eat_last_time = ft_get_time();
        sem_post(data->check_live_status);
        ft_usleep(philo->data, philo->data->time_to_eat);
        sem_post(philo->data->forks);
        sem_post(philo->data->forks);
        if (data->must_eat != -1 && philo->count_eat >= data->must_eat)
        {
            data->finish = 1;
            return ;
        }
        print_log(philo, SLEEP);
		ft_usleep(data, data->time_to_sleep);
		print_log(philo, THINK);
	}
	else
	{
        sem_post(philo->data->forks);
        ft_usleep(data, data->time_to_die + 1000);
    }
}
void	*philo_proc(void *arg)
{
	t_philo     *philo;
    pthread_t   philo_th;

	philo = (t_philo *) arg;
    philo->eat_last_time = philo->data->launch_time;
    pthread_create(&philo_th, NULL, &wait_finish, philo);
    if (philo->number % 2 == 0)
		usleep(1000);
	while (!philo->data->finish)
        philo_actions(philo, philo->data);
    pthread_join(philo_th, NULL);
    exit(0);
}

int	emulate(t_data *data)
{
	int	i;

	i = -1;
    data->launch_time = ft_get_time();
    while (++i < data->number_of_philo)
    {
        data->philos[i].pid = fork();
        if (data->philos[i].pid == -1)
        {
            printf("Fork error\n");
            exit(errno);
        }
        if (data->philos[i].pid == 0)
            philo_proc(&data->philos[i]);
    }
    finish_processes(data);
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