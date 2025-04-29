/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:17:21 by ganersis          #+#    #+#             */
/*   Updated: 2025/04/29 19:19:29 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"
# define GRAY "\033[1;30m"
# define DARK_GREEN "\033[0;32m"
# define DARK_BLUE "\033[0;34m"

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t				start_time;
	int					nb_philos;
	pthread_t			monitor;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	bool				sim_stop;
	pthread_mutex_t		sim_stop_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		*fork_locks;
	t_philo				*philos;
}						t_table;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_table				*table;
}						t_philo;

int						ft_atoi(const char *str);
int						arg_check(int argc);
t_table					*parse_args(char **argv);
int						error_failure(char *str, char *details, t_table *table);
void					*error_null(char *str, char *details, t_table *table);
time_t					get_time_in_ms(void);
bool					start_program(t_table *table);
void					destroy_mutexes(t_table *table);
void					*free_table(t_table *table);
void					end_program(t_table *table);
void					*philo_routine(void *args);
void					*monitor_routine(void *args);
void					sim_start_delay(time_t start_time);
void					print_status(t_philo *philo, char *str);
void					check_sleep(t_table *table, time_t sleep_time);
void					think(t_philo *philo, bool silent);
int						eat_and_sleep(t_philo *philo);
bool					has_simulation_stopped(t_table *table);
int						ft_strcmp(const char *s1, const char *s2);
#endif