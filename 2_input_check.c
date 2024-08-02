/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2_input_check.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 13:15:39 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/02 13:15:39 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	input_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

bool	input_within_int_range(int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > MAX_PHILOS
		|| ft_atoi(argv[2]) < 0 || ft_atoi(argv[2]) > INT_MAX
		|| ft_atoi(argv[3]) < 0 || ft_atoi(argv[3]) > INT_MAX
		|| ft_atoi(argv[4]) < 0 || ft_atoi(argv[4]) > INT_MAX)
		return (false);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 0 || ft_atoi(argv[5]) > INT_MAX)
			return (false);
	}
	return (true);
}

bool	input_check(int argc, char **argv)
{
	if (input_is_digit(argv[1]) == false || input_is_digit(argv[2]) == false \
		|| input_is_digit(argv[3]) == false || input_is_digit(argv[4]) == false \
		|| (argc == 6 && input_is_digit(argv[5]) == false))
		return (error_msg(2), false);
	if (input_within_int_range(argc, argv) == false)
		return (error_msg(2), false);
	return (true);
}
