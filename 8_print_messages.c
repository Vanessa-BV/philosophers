/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   8_print_messages.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/18 15:48:29 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/01 12:35:33 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(int error_number)
{
	if (error_number == 1)
	{
		printf("Enter:\n(1) Number of philosophers (1-200)\n(2) Time to die ");
		printf("(ms)\n(3) Time to eat (ms)\n(4) Time to sleep (ms)\n(5) ");
		printf("Number of times each philosopher eats (optional)\n");
	}
	else if (error_number == 2)
	{
		printf("Error: Invalid argument input.\n");
		error_msg(1);
	}
	else if (error_number == 3)
		printf("Error: Could not retrieve time of day.\n");
	else if (error_number == 4)
		printf("Error: Could not create thread.\n");
	else if (error_number == 5)
		printf("Error: Could not initialize mutexes.\n");
	else if (error_number == 6)
		printf("Error: Could not join threads.\n");
}

void	action_msg(char *message, t_philo *philos, int id)
{
	pthread_mutex_lock(&philos->info->output_lock);
	if (dead_loop(philos) != true)
		printf("%zu %d %s\n", sim_time(philos->start_time), id, message);
	pthread_mutex_unlock(&philos->info->output_lock);
}
