/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_error_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 15:58:32 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/05/17 15:58:32 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_app(t_application *app) // to be adjusted based on what will be included in the struct
{
	free(app);
}

void	exit_error(char * error_message, t_application *app_to_free)
{
	printf("%s\n", error_message);
	if (app_to_free != NULL)
		free_app(app_to_free);
	exit(EXIT_FAILURE);
}
