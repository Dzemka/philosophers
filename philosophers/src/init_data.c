#include "../include/philo.h"

static int check_data_incorrect(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("incorrect numbers of arguments!\n available arguments:\n"
			   "number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, "
			   "number_of_times_each_philosopher_must_eat (optional)\n");
		return (1);
	}
	while (--argc > 0)
	{
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
	(*data)->launch_time = ft_get_time();
	(*data)->finish = 0;
	return (0);
}

static int init_philo(t_data *data, int n, int count)
{
	data->philos[n].number = n;
	if (data->number_of_philo > 1)
		data->philos[n].right_philo = &data->philos[(n + 1) % count];
	else
		data->philos[n].right_philo = NULL;
	data->philos[n].data = data;
	pthread_mutex_init(&data->philos[n].fork, NULL);
	data->philos[n].count_eat = 0;
	return (0);
}

static int	init_process_data(t_data **data)
{
	int i;

	i = -1;
	(*data)->philos = malloc(sizeof (t_philo) * (*data)->number_of_philo);
	if (!(*data)->philos)
	{
		free(*data);
		return (1);
	}
	while (++i < (*data)->number_of_philo)
		init_philo(*data, i, ((*data)->number_of_philo));
	pthread_mutex_init(&(*data)->check_live_status, NULL);
	pthread_mutex_init(&(*data)->print_logs, NULL);
	return (0);
}

int	init_data(t_data **data, int argc, char **argv)
{
	if (fill_basic_data(data, argc, argv) == 0)
		if (init_process_data(data) == 0)
			return (0);
	return (1);
}