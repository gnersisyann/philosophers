/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:17:21 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/02 21:08:15 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"
# define GRAY "\033[1;30m"
# define DARK_GREEN "\033[0;32m"
# define DARK_BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define BLUE "\033[0;34m"

# define PTHREAD_ERR 40
# define SEM_ERR 41
# define FEED 42
# define DEAD 43

# define PTHREAD_ERR 40
# define CHILD_EXIT_ERR_SEM 41
# define CHILD_EXIT_PHILO_FULL 42
# define CHILD_EXIT_PHILO_DEAD 43

# define SEM_NAME_FORKS "/philo_global_forks"
# define SEM_NAME_WAITER "/philo_global_waiter"
# define SEM_NAME_WRITE "/philo_global_write"
# define SEM_NAME_FULL "/philo_global_full"
# define SEM_NAME_DEAD "/philo_global_dead"
# define SEM_NAME_STOP "/philo_global_stop"
# define SEM_NAME_MEAL "/philo_local_meal_"

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t				start_time;
	int					nb_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					must_eat_count;
	sem_t				*sem_forks;
	sem_t				*sem_write;
	sem_t				*sem_philo_full;
	int					philo_full_count;
	sem_t				*sem_philo_dead;
	sem_t				*sem_stop;
	bool				stop_sim;
	t_philo				*philos;
	t_philo				*this_philo;

	sem_t				*sem_waiter;

	pid_t				*pids;
	pthread_t			satiety;
	pthread_t			starvation;
}						t_table;

typedef struct s_philo
{
	pthread_t			personal_monitor;
	sem_t				*sem_forks;
	sem_t				*sem_write;
	sem_t				*sem_philo_full;
	sem_t				*sem_philo_dead;
	sem_t				*sem_meal;
	char				*sem_meal_name;
	int					nb_forks_held;
	unsigned int		id;
	unsigned int		times_ate;
	bool				ate_enough;
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
int						end_program(t_table *table);
void					sim_start_delay(time_t start_time);
void					print_status(t_philo *philo, char *str);
void					check_sleep(time_t sleep_time);
void					think(t_philo *philo, bool silent);
int						eat_and_sleep(t_philo *philo);
bool					has_simulation_stopped(t_table *table);
int						ft_strcmp(const char *s1, const char *s2);
int						sem_error_cleanup(t_table *table);
void					unlink_global_sems(void);
size_t					ft_strlen(const char *str);
char					*ft_strcat(char *dst, const char *src);
char					*ft_utoa(unsigned int nb, size_t len);
int						ft_strcmp(const char *s1, const char *s2);
int						table_cleanup(t_table *table, int exit_code);
void					*satiety_routine(void *args);
void					*starvation_routine(void *args);
void					philosopher(t_table *table);
void					*personal_monitor(void *args);
void					init_philo(t_table *table, t_philo *philo);
bool					end_condition_reached(t_table *table, t_philo *philo);
void					child_exit(t_table *table, int exit_code);
bool					start_monitors_threads(t_table *table);
#endif