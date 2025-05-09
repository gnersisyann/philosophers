/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:17:11 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/09 12:20:53 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>

bool	has_simulation_stopped(t_table *table)
{
	bool	status;

	status = false;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop == true)
		status = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (status);
}

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (!has_simulation_stopped(philo->table) || ft_strcmp(str,
			RED "died" RESET) == 0)
	{
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
			philo->id + 1, str);
	}
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	check_sleep(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (!has_simulation_stopped(table) && get_time_in_ms() < wake_up)
		usleep(50);
}

void	think(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->table->time_to_die - (get_time_in_ms()
				- philo->last_meal) - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (has_simulation_stopped(philo->table) != true && silent == false)
		print_status(philo, YELLOW "is thinking" RESET);
	check_sleep(philo->table, time_to_think);
}

int	eat_and_sleep(t_philo *philo)
{
	if (has_simulation_stopped(philo->table))
		return (1);
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_status(philo, DARK_GREEN "has taken a fork" RESET);
	if (has_simulation_stopped(philo->table))
		return (pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]),
			1);
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	print_status(philo, DARK_GREEN "has taken a fork" RESET);
	if (has_simulation_stopped(philo->table))
		return (pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]),
			pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]), 1);
	if (has_simulation_stopped(philo->table))
		return (pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]),
			pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]), 1);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_in_ms();
	++philo->times_ate;
	pthread_mutex_unlock(&philo->meal_time_lock);
	print_status(philo, GREEN "is eating" RESET);
	check_sleep(philo->table, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	print_status(philo, GRAY "is sleeping" RESET);
	return (check_sleep(philo->table, philo->table->time_to_sleep), 0);
}
