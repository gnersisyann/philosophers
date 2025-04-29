/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:15:41 by ganersis          #+#    #+#             */
/*   Updated: 2025/04/29 19:36:17 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	set_sim_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

static bool	philo_die(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if (time - philo->last_meal >= philo->table->time_to_die)
	{
		set_sim_stop_flag(philo->table, true);
		print_status(philo, RED "died" RESET);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

bool	end_condition_reached(t_table *table)
{
	int		i;
	bool	all_ate_enough;

	i = -1;
	all_ate_enough = true;
	while (++i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_time_lock);
		if (philo_die(&table->philos[i]))
			return (true);
		if (table->must_eat_count != -1
			&& table->philos[i].times_ate < (unsigned int)table->must_eat_count)
			all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i].meal_time_lock);
	}
	if (table->must_eat_count != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(table, true);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	set_sim_stop_flag(table, false);
	sim_start_delay(table->start_time);
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
