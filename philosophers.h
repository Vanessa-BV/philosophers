/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 14:52:56 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/05/17 14:52:56 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_application
{
	int		number_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_philos_eat;
}	t_application;

// Utils
void	exit_error(char * error_message, t_application *app_to_free);

#endif