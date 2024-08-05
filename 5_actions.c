/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_actions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/26 15:45:24 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/01 15:55:42 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	action_msg("has taken a fork", philo, philo->id);
	ft_usleep(philo->info->t_die, philo);
	pthread_mutex_unlock(philo->fork1);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	if (dead_loop(philo) != true)
		action_msg("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->fork2);
	if (dead_loop(philo) != true)
		action_msg("has taken a fork", philo, philo->id);
}

void	routine(t_philo *philo)
{
	int	lifetime;

	take_forks(philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = timestamp_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	if (dead_loop(philo) != true)
		action_msg("is eating", philo, philo->id);
	ft_usleep(philo->info->t_eat, philo);
	put_forks(philo);
	if (dead_loop(philo) != true)
		action_msg("is sleeping", philo, philo->id);
	if (dead_loop(philo) != true)
		action_msg("is thinking", philo, philo->id);
	ft_usleep(philo->info->t_sleep, philo);
	pthread_mutex_lock(philo->meal_lock);
	lifetime = philo->info->t_die - (timestamp_in_ms() - philo->last_meal_time);
	pthread_mutex_unlock(philo->meal_lock);
	if (lifetime > philo->info->t_eat)
		ft_usleep(philo->info->t_eat, philo);
}
