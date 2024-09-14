/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   6_monitor.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 13:50:16 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/02 13:50:16 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead_lock);
	if (philo->info->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->info->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->dead_lock);
	return (false);
}

bool	philo_starves(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (timestamp_in_ms() - philo->last_meal_time >= (long)philo->info->t_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (false);
}

bool	dead_flag_check(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->numb_philos)
	{
		if (philo_starves(&philos[i]) == true)
		{
			pthread_mutex_lock(&philos->info->dead_lock);
			philos->info->dead_flag = 1;
			pthread_mutex_unlock(&philos->info->dead_lock);
			printf("%zu %d died\n", \
			sim_time(philos->start_time), i + 1);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	all_philos_ate(t_philo *philos)
{
	int	i;
	int	numb_philos_finished_eating;

	i = 0;
	numb_philos_finished_eating = 0;
	while (i < philos->info->numb_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos->info->numb_of_meals)
			numb_philos_finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (numb_philos_finished_eating == philos->info->numb_philos)
	{
		pthread_mutex_lock(&philos->info->dead_lock);
		philos->info->dead_flag = 1;
		pthread_mutex_unlock(&philos->info->dead_lock);
		return (true);
	}
	return (false);
}

void	*monitor(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	pthread_mutex_lock(&info->lock);
	pthread_mutex_unlock(&info->lock);
	if (info->numb_of_meals == INT_MAX)
	{
		while (dead_flag_check(info->philos) == false)
			usleep(500);
	}
	else
	{
		while (all_philos_ate(info->philos) == false \
		&& dead_flag_check(info->philos) == false)
			usleep(500);
	}
	return (NULL);
}
