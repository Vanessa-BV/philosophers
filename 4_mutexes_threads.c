/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   4_mutexes_threads.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 13:16:33 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/02 13:16:33 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->info->numb_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (dead_loop(philo) != true)
		take_forks(philo);
	return (NULL);
}

bool	init_mutexes(t_info *info)
{
	if (pthread_mutex_init(&info->dead_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&info->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&info->dead_lock);
		return (false);
	}
	if (pthread_mutex_init(&info->output_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&info->dead_lock);
		pthread_mutex_destroy(&info->meal_lock);
		return (false);
	}
	return (true);
}

void	destroy_mutexes(t_info *info, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info->meal_lock);
	pthread_mutex_destroy(&info->dead_lock);
	pthread_mutex_destroy(&info->output_lock);
	if (forks != NULL)
	{
		while (i < info->numb_philos)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
	}
}

bool	threads(t_info *info)
{
	pthread_t	monitoring;
	int			i;

	if (pthread_create(&monitoring, NULL, &monitor, info->philos) != 0)
		return (error_msg(4), false);
	i = 0;
	while (i < info->numb_philos)
	{
		if (pthread_create(&info->philos[i].thread, NULL, \
			&philo_thread, &info->philos[i]) != 0)
			return (error_msg(4), false);
		i++;
	}
	i = 0;
	if (pthread_join(monitoring, NULL) != 0)
		return (error_msg(6), false);
	while (i < info->numb_philos)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			return (error_msg(6), false);
		i++;
	}
	return (true);
}
