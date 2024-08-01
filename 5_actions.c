/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_actions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/26 15:45:24 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/01 15:42:01 by vbusekru      ########   odam.nl         */
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

void put_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->fork1);
    pthread_mutex_unlock(philo->fork2);
}

void	routine(t_philo *philo)
{
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
	ft_usleep(philo->info->t_sleep, philo);
	if (dead_loop(philo) != true)
	action_msg("is thinking", philo, philo->id);
	ft_usleep(1, philo); // not sure if necessary
}

void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	pthread_mutex_lock(philo->fork1);
	if (dead_loop(philo) != 0)
		action_msg("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->fork2);
	if (dead_loop(philo) != 0)
		action_msg("has taken a fork", philo, philo->id);
	routine(philo);
}
