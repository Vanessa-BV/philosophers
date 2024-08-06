/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3_init_data.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 17:04:15 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/01 14:59:56 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_start_time(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->numb_philos)
	{
		philo[i].start_time = timestamp_in_ms();
		philo[i].last_meal_time = philo[i].start_time;
		i++;
	}
}

bool	init_info(t_info *info, t_philo *philos, int argc, char **argv)
{
	info->numb_philos = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->numb_of_meals = ft_atoi(argv[5]);
	else
		info->numb_of_meals = INT_MAX;
	if (info->numb_philos == -1 || info->t_die == -1 \
	|| info->t_eat == -1 || info->t_sleep == -1 \
	|| info->numb_of_meals == -1)
		return (error_msg(2), false);
	info->dead_flag = 0;
	info->philos = philos;
	if (init_mutexes(info) == false)
		return (error_msg(5), false);
	info->start_flag = 0;
	return (true);
}

bool	init_forks(pthread_mutex_t *forks, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->numb_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&forks[i]);
			}
			destroy_mutexes(info, NULL);
			return (error_msg(5), false);
		}
		i++;
	}
	return (true);
}

void	fork_assignment(t_philo *philos, t_info *info, \
		pthread_mutex_t *forks, int i)
{
	if (i == 0)
	{
		philos[i].fork1 = &forks[info->numb_philos - 1];
		philos[i].fork2 = &forks[0];
	}
	else if (i % 2 == 0)
	{
		philos[i].fork1 = &forks[i - 1];
		philos[i].fork2 = &forks[i];
	}
	else
	{
		philos[i].fork1 = &forks[i];
		philos[i].fork2 = &forks[i - 1];
	}
}

void	init_philos(t_philo *philos, t_info *info, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < info->numb_philos)
	{
		philos[i].meals_eaten = 0;
		philos[i].start_time = 0;
		philos[i].last_meal_time = philos[i].start_time;
		philos[i].id = i + 1;
		philos[i].info = info;
		philos[i].output_lock = &info->output_lock;
		philos[i].meal_lock = &info->meal_lock;
		fork_assignment(philos, info, forks, i);
		i++;
	}
}
