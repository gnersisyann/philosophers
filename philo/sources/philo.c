/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:15:35 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/09 12:13:32 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_close_to_death(t_philo *philo)
{
	long	time_since_meal;
	long	current_time;

	pthread_mutex_lock(&philo->meal_time_lock);
	current_time = get_time_in_ms();
	time_since_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_time_lock);
	return (time_since_meal > (philo->table->time_to_die * 0.75));
}

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	print_status(philo, DARK_GREEN "has taken a fork" RESET);
	check_sleep(philo->table, philo->table->time_to_die);
	print_status(philo, RED "died" RESET);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->table->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_delay(philo->table->start_time);
	if (philo->table->nb_philos == 1)
		return (one_philo(philo));
	else if (philo->id % 2)
		think(philo, true);
	while (has_simulation_stopped(philo->table) == false)
	{
		if (!is_close_to_death(philo))
			usleep(500);
		eat_and_sleep(philo);
		if (has_simulation_stopped(philo->table))
			break ;
		think(philo, false);
	}
	return (NULL);
}
