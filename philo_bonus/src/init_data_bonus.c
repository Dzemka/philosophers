#include "../include/philo_bonus.h"

static int check_data_incorrect(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (error_message(-1, NULL));
	while (--argc > 0)
	{
        if (argv[argc][0] == '0')
            return (error_message(-2, NULL));
		i = -1;
		while (argv[argc][++i])
		{
			if (argv[argc][i] < '0' || argv[argc][i] > '9')
				return (error_message(argc, argv[argc]));
		}
		if (i >= 10)
			if (argc > 10 || ft_strncmp(argv[argc], "2147483647", 10) > 0)
				return (error_message(argc, argv[argc]));
	}
	return (0);
}

static int fill_basic_data(t_data **data, int argc, char **argv)
{
	if (check_data_incorrect(argc, argv))
		return (1);
	*data = malloc(sizeof (t_data));
	if (!*data)
		return (1);
	(*data)->number_of_philo = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	(*data)->must_eat = -1;
	if (argc == 6)
		(*data)->must_eat = ft_atoi(argv[5]);
	(*data)->finish = 0;
	return (0);
}

static int init_philo(t_data *data, int n)
{
	data->philos[n].number = n + 1;
	data->philos[n].data = data;
    data->philos[n].count_eat = 0;
	return (0);
}

static int	init_process_data(t_data *data)
{
	int i;

	i = -1;
	data->philos = malloc(sizeof (t_philo) * data->number_of_philo);
	if (!data->philos)
	{
		free(data);
		return (1);
	}
	while (++i < data->number_of_philo)
		init_philo(data, i);
    sem_unlink("/check_live_status");
    sem_unlink("/print_logs");
    sem_unlink("/forks");
    data->check_live_status = sem_open("/check_live_status", O_CREAT, 0644, 1);
    data->print_logs = sem_open("/print_logs", O_CREAT, 0644, 1);
    data->forks = sem_open("/forks", O_CREAT, 0644, data->number_of_philo);
    if (data->check_live_status == SEM_FAILED || data->print_logs == SEM_FAILED
    || data->forks == SEM_FAILED)
        error_message(-3, NULL);
    sem_unlink("/check_live_status");
    sem_unlink("/print_logs");
    sem_unlink("/forks");
	return (0);
}

int	init_data(t_data **data, int argc, char **argv)
{
	if (fill_basic_data(data, argc, argv) == 0)
		if (init_process_data(*data) == 0)
			return (0);
	return (1);
}