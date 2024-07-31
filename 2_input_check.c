#include "philo.h"

int	input_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	input_within_int_range(int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > MAX_PHILOS
		||ft_atoi(argv[2]) < MIN_TIME || ft_atoi(argv[2]) > INT_MAX
		|| ft_atoi(argv[3]) < MIN_TIME || ft_atoi(argv[3]) > INT_MAX
		|| ft_atoi(argv[4]) < MIN_TIME || ft_atoi(argv[4]) > INT_MAX)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0 || ft_atoi(argv[5]) > INT_MAX)
			return (-1);
	}
	return (0);
}

int	input_check(int argc, char **argv)
{
	if (input_is_digit(argv[1]) == -1 || input_is_digit(argv[2]) == -1 \
		|| input_is_digit(argv[3]) == -1 || input_is_digit(argv[4]) == -1 \
		|| (argc == 6 && input_is_digit(argv[5]) == -1))
		return (error_msg(2), -1);
	if (input_within_int_range(argc, argv) == -1)
		return (error_msg(2), -1);
	return (0);
}
