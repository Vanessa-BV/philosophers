#include "philo.h"

// void	*philo_thread(void *arg)
// {
// 	t_philo *philo;

// 	philo = (t_philo *) arg;
// 	if (philo->info->numb_philos == 1)
// 	{
// 		one_philo(philo);
// 		return (NULL);
// 	}
// 	while (1)
// 	{
//         pthread_mutex_lock(&philo->info->dead_lock);
//         if (philo->info->dead_flag == 1)
//         {
//             pthread_mutex_unlock(&philo->info->dead_lock);
//             break;
//         }
//         pthread_mutex_unlock(&philo->info->dead_lock);
//         eat_sleep_think(philo);
// 	}
// 	return (NULL);
// }

void	*philo_thread(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	if (philo->info->numb_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (dead_loop(philo) != 0)
		eat_sleep_think(philo);
	return (NULL);
}

int	init_mutexes(t_info *info)
{
	if (pthread_mutex_init(&info->dead_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&info->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&info->dead_lock);
		return (-1);
	}
	if (pthread_mutex_init(&info->output_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&info->dead_lock);
		pthread_mutex_destroy(&info->meal_lock);
		return (-1);
	}
	return (0);
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

int	threads(t_info *info)
{
	pthread_t	monitoring;
	int			i;

	if (pthread_create(&monitoring, NULL, &monitor, info->philos) != 0)
		return (error_msg(4), -1);
	i = 0;
	while (i < info->numb_philos)
	{
		if (pthread_create(&info->philos[i].thread, NULL, &philo_thread, &info->philos[i]) != 0)
			return(error_msg(4), -1);
		i++;
	}
	i = 0;
	if (pthread_join(monitoring, NULL) != 0)
		return (error_msg(6), -1);
	while (i < info->numb_philos)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			return (error_msg(6), -1);
		i++;
	}
	return (0);
}