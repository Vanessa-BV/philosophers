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
	long	current_time;

	current_time = timestamp_in_ms();
	ft_usleep(2, philo);
	pthread_mutex_lock(philo->meal_lock);
	if (current_time - philo->last_meal_time >= (long)philo->info->t_die)
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
			ft_usleep(3, philos);
			pthread_mutex_lock(&philos->info->dead_lock);
			philos->info->dead_flag = 1;
			pthread_mutex_unlock(&philos->info->dead_lock);
			action_msg("died", &philos[i], philos[i].id);
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
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (all_philos_ate(philos) == true || dead_flag_check(philos) == true)
			break ;
		usleep(1000);
	}
	return (NULL);
}
