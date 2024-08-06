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
	pthread_mutex_lock(&philo->info->lock);
	if (philo->info->start_flag == 0)
	{
		pthread_mutex_unlock(&philo->info->lock);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->info->lock);
	if (philo->info->numb_philos == 1)
		one_philo(philo);
	else
	{
		if (philo->id % 2 == 0)
		{
			action_msg("is thinking", philo, philo->id);
			ft_usleep(philo->info->t_eat / 2, philo);
		}
		while (dead_loop(philo) != true)
			routine(philo);
	}
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
	if (pthread_mutex_init(&info->lock, NULL) != 0)
	{
		pthread_mutex_destroy(&info->dead_lock);
		pthread_mutex_destroy(&info->meal_lock);
		pthread_mutex_destroy(&info->output_lock);
		return (false);
	}
	return (true);
}

void	destroy_mutexes(t_info *info, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (info != NULL)
	{
		pthread_mutex_destroy(&info->meal_lock);
		pthread_mutex_destroy(&info->dead_lock);
		pthread_mutex_destroy(&info->output_lock);
		pthread_mutex_destroy(&info->lock);
	}
	if (forks != NULL)
	{
		while (i < info->numb_philos)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
	}
}

bool	join_threads(t_info *info, int num_threads)
{
	int	j;

	j = 0;
	while (j < num_threads)
	{
		if (pthread_join(info->philos[j].thread, NULL) != 0)
			return (error_msg(6), false);
		j++;
	}
	if (num_threads == info->numb_philos)
		return (true);
	return (false);
}

bool	threads(t_info *info)
{
	pthread_t	monitoring;
	int			i;

	i = 0;
	pthread_mutex_lock(&info->lock);
	while (i < info->numb_philos)
	{
		if (pthread_create(&info->philos[i].thread, NULL, \
			&philo_thread, &info->philos[i]) != 0)
			return (error_msg(4), false);
		i++;
	}
	if (pthread_create(&monitoring, NULL, &monitor, info) != 0)
		return (error_msg(4), false);
	info->start_flag = 1;
	set_start_time(info->philos);
	pthread_mutex_unlock(&info->lock);
	if (pthread_join(monitoring, NULL) != 0)
		return (error_msg(6), false);
	return (join_threads(info, i));
}
