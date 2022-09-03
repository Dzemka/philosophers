#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	long	res;

	res = 0;
	while (*str != '\0')
		res = *str++ + res * 10 - 48;
	if (res < 0)
		return (-1);
	return (res);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str1[i] && str2[i] && i < n - 1)
	{
		if (str1[i] > str2[i])
			return (1);
		if (str2[i] > str1[i])
			return (-1);
		i++;
	}
	return (str1[i] - str2[i]);
}

int error_message(int argc, char *argv)
{
    if (argc == -1)
    {
        printf("incorrect numbers of arguments!\n"
               " available arguments:\n"
               "number_of_philosophers, "
               "time_to_die, "
               "time_to_eat,"
               " time_to_sleep, "
               "number_of_times_each_philosopher_must_eat (optional)\n");
    }
    else if (argc == -2)
        printf("Value must be greater than zero\n");
    else
    {
        printf("Argument number %d - \"%s\" incorrect\n", argc, argv);
    }
    return (1);
}