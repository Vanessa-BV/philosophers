/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 14:52:56 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/01 13:21:14 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

# define MAX_PHILOS 200

typedef struct s_philo
{
	int						id;
	int						meals_eaten;
	long					start_time;
	long					last_meal_time;
	pthread_t				thread;
	pthread_mutex_t			*fork1;
	pthread_mutex_t			*fork2;
	pthread_mutex_t			*output_lock;
	pthread_mutex_t			*meal_lock;
	struct s_info	*info;
} t_philo;

typedef struct s_info
{
	int						numb_philos;
	int						t_die;
	int						t_eat;
	int						t_sleep;
	int						numb_of_meals;
	int						dead_flag;
	pthread_mutex_t			output_lock;
	pthread_mutex_t			dead_lock;
	pthread_mutex_t			meal_lock;
	t_philo					*philos;
} t_info;

// Data verification
bool		input_check(int argc, char **argv);
bool		input_within_int_range(int argc, char **argv);

// Data initialization
bool		init_info(t_info *info, t_philo *philos, int argc, char **argv);
bool		init_forks(pthread_mutex_t *forks, t_info *info);
void		init_philos(t_philo *philos, t_info *info, \
			pthread_mutex_t *forks);

// Mutexes
bool		init_mutexes(t_info *info);
void	destroy_mutexes(t_info *info, pthread_mutex_t *forks);

// Utils
int		ft_atoi(char *str);
bool	input_is_digit(char *str);
bool	ft_isdigit(char c);
long	timestamp_in_ms(void);
void	ft_usleep(int ms_for_action, t_philo *philo);
long	sim_time(long start_time);

// Print messages 
void	error_msg(int error_number);
void	action_msg(char *message, t_philo *philos, int id);

// Threads
bool	threads(t_info *info);
void	*philo_thread(void *arg);

// Monitoring
void	*monitor(void *arg);
bool	dead_flag_check(t_philo *philos);
bool	all_philos_ate(t_philo *philos);
bool	dead_loop(t_philo *philos);
bool	philo_starves(t_philo *philos);
// int		all_ate_or_philo_died(t_philo *philos);
// int		philo_starving(t_philo *philo);


//Actions (eat, sleep, think)
// int		philo_dies(t_philo *philo);
void	routine(t_philo *philo);
void	one_philo(t_philo *philo);
void	take_forks(t_philo *philo);
void	put_forks(t_philo *philo);

#endif