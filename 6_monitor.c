#include "philo.h"

int dead_loop(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->dead_lock);
    if (philo->info->dead_flag == 1)
	{
        pthread_mutex_unlock(&philo->info->dead_lock);
        return (0);
    }
    pthread_mutex_unlock(&philo->info->dead_lock);
    return (-1);
}

int	philo_starves(t_philo *philo) // to be returned to actions.c possibly later on
{
	long	current_time;

	current_time = timestamp_in_ms();
	pthread_mutex_lock(philo->meal_lock);
	if (current_time - philo->last_meal_time >= (long)philo->info->t_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (-1);
}

int dead_flag_check(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos->info->numb_philos)
    {
        if (philo_starves(&philos[i]) == 0) {
            pthread_mutex_lock(&philos->info->dead_lock);
            philos->info->dead_flag = 1;
            pthread_mutex_unlock(&philos->info->dead_lock);
            action_msg("has died", &philos[i], philos[i].id);
            return (0);
        }
        i++;
    }
    return (-1);
}

int	all_philos_ate(t_philo *philos)
{
	int i;
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
		return (0);
	}
	return (-1);
}

void	*monitor(void *arg)
{
    t_philo	*philos;
    philos = (t_philo *)arg;
    while(1)
    {
        if (all_philos_ate(philos) == 0 || dead_flag_check(philos) == 0)
            break;
        usleep(1000);
    }
    return (NULL);
}
