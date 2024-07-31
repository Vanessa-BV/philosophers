/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   1_main.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 14:51:56 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/07/31 20:02:15 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_philo philos[MAX_PHILOS];
    t_info info;
    pthread_mutex_t forks[MAX_PHILOS];

    if (argc < 5 || argc > 6)
        return (error_msg(1), EXIT_FAILURE);
    if (input_check(argc, argv) == -1)
        return (EXIT_FAILURE);
    if ((init_info(&info, philos, argc, argv) == -1)
        || (init_forks(forks, &info) == -1)
        || (init_philos(philos, &info, forks) == -1))
        return (EXIT_FAILURE);
    if (threads(&info) == -1)
    {
        destroy_mutexes(&info, forks);
        return (EXIT_FAILURE);
    }
    destroy_mutexes(&info, forks);
    return (EXIT_SUCCESS);
}
