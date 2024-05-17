/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 14:51:56 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/05/17 14:51:56 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	convert_to_integers(t_application *app, int argc, char **argv);

int	main(int argc, char **argv)
{
	t_application	philo;

	if (argc < 5 || argc > 6)
	{
		printf("Enter:\n(1) Number of philosophers (1-999)\n(2) Time to die ");
		printf("(ms)\n(3) Time to eat (ms)\n(4) Time to sleep (ms)\n(5) ");
		printf("Number of times each philosopher eats (ms) (optional)\n");
		return (EXIT_FAILURE);
	}
	convert_to_integers(&philo, argc, argv);
}
