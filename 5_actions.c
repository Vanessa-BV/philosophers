/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   5_actions_copy.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/26 15:45:24 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/07/31 21:42:42 by vbusekru      ########   odam.nl         */
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

void put_forks(t_philo *philo) {
    pthread_mutex_unlock(philo->fork1);
    printf("Philo %d has put down fork %p\n", philo->id, philo->fork1);

    pthread_mutex_unlock(philo->fork2);
    printf("Philo %d has put down fork %p\n", philo->id, philo->fork2);
}

void	routine(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = timestamp_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	action_msg("is eating", philo, philo->id);
	ft_usleep(philo->info->t_eat, philo);
	put_forks(philo);
	action_msg("is sleeping", philo, philo->id);
	ft_usleep(philo->info->t_sleep, philo);
	action_msg("is thinking", philo, philo->id);
}

// void take_forks(t_philo *philo) {
//     if (philo->id % 2 == 0) {
//         pthread_mutex_lock(philo->fork1);
//         action_msg("has taken a fork", philo, philo->id);
//         pthread_mutex_lock(philo->fork2);
//         action_msg("has taken a fork", philo, philo->id);
//     } else {
//         pthread_mutex_lock(philo->fork1);
//         action_msg("has taken a fork", philo, philo->id);
//         pthread_mutex_lock(philo->fork2);
//         action_msg("has taken a fork", philo, philo->id);
//     }
// }

void take_forks(t_philo *philo) {
    printf("Philo %d is attempting to take fork %p\n", philo->id, philo->fork1);
    pthread_mutex_lock(philo->fork1);
    printf("Philo %d has taken fork %p\n", philo->id, philo->fork1);

    printf("Philo %d is attempting to take fork %p\n", philo->id, philo->fork2);
    pthread_mutex_lock(philo->fork2);
    printf("Philo %d has taken fork %p\n", philo->id, philo->fork2);
}

void	eat_sleep_think(t_philo *philo)
{
	take_forks(philo);
	routine(philo);
}