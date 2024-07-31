/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   7_utils.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/26 14:42:31 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/07/31 21:44:28 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else
		return (-1);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	number;

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
	while (ft_isdigit(str[i]) == 0)
	{
		number = number * 10 + (str[i] - '0');
		if (number > INT_MAX)
			return (-1);
		i++;
	}
	number = number * sign;
	return (number);
}

long	timestamp_in_ms(void)
{
	struct timeval	time;
	long			time_in_milliseconds;

	time_in_milliseconds = 0;
	gettimeofday(&time, NULL);
	time_in_milliseconds = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time_in_milliseconds);
}

int	ft_usleep(int ms_for_action, t_philo *philo)
{
	int	start;

	start = timestamp_in_ms();
	if (start == -1)
		return (-1);
	while ((timestamp_in_ms() - start) < (long)ms_for_action && dead_loop(philo) != 0)
		usleep(500);
	return (0);
}

long	sim_time(long start_time)
{
	return (timestamp_in_ms() - start_time);
}