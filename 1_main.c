/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   1_main.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 14:51:56 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/01 13:34:04 by vbusekru      ########   odam.nl         */
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
    if (input_check(argc, argv) == false)
        return (EXIT_FAILURE);
    if ((init_info(&info, philos, argc, argv) == false)
        || (init_forks(forks, &info) == false))
        return (EXIT_FAILURE);
    init_philos(philos, &info, forks);
    if (threads(&info) == false)
    {
        destroy_mutexes(&info, forks);
        return (EXIT_FAILURE);
    }
    destroy_mutexes(&info, forks);
    return (EXIT_SUCCESS);
}
