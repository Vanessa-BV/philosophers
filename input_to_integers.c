/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_to_integers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 15:28:11 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/05/17 15:28:11 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	number = number * sign;
	if (number < INT_MIN || number > INT_MAX)
		exit_error("Input is not within the integer range.", NULL);
	return (number);
}

void	convert_to_integers(t_application *app, int argc, char **argv)
{
	app->number_philosophers = ft_atoi(argv[1]);
	if (app->number_philosophers <= 0)
		exit_error("Number of philosophers must be minimum 1.", NULL);
	else if (app->number_philosophers > 999)
		exit_error("Number of philosophers must be maximum 999.", NULL);
	app->time_to_die = ft_atoi(argv[2]);
	app->time_to_eat = ft_atoi(argv[3]);
	app->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		app->times_philos_eat = ft_atoi(argv[5]);
	else
		app->times_philos_eat = INT_MAX;
	if (app->time_to_die < 0 || app->time_to_eat < 0 \
	|| app->time_to_sleep < 0 || app->times_philos_eat < 0)
		exit_error("Time or # of times philos eat must be minium 1.", NULL);
	printf("Number of philosophers: %d\n", app->number_philosophers); // to be deleted 
	printf("Time to die: %d\n", app->time_to_die);// to be deleted 
	printf("Time to eat: %d\n", app->time_to_eat);// to be deleted 
	printf("Time to sleep: %d\n", app->time_to_sleep);// to be deleted 
	printf("Times philosophers eat: %d\n", app->times_philos_eat);// to be deleted 
}
