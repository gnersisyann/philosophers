/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:24 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/13 10:34:42 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*monitor_all_deaths(void *arg)
{
	t_philo	*philosophers;
	int		i;

	philosophers = (t_philo *)arg;
	sim_start_delay(philosophers->args->start_time);
	sem_wait(philosophers->sems->dead_signal);
	i = -1;
	while (++i < philosophers->args->n_philo)
		kill(philosophers[i].pid, SIGKILL);
	i = -1;
	while (++i < philosophers->args->n_philo)
		sem_post(philosophers[i].sems->meal_check);
	sem_post(philosophers->sems->print);
	return (NULL);
}

void	*monitor_all_meals(void *arg)
{
	t_philo	*philosophers;
	int		i;

	philosophers = (t_philo *)arg;
	i = -1;
	sim_start_delay(philosophers->args->start_time);
	while (++i < philosophers->args->n_philo)
		sem_wait(philosophers->sems->meal_check);
	sem_wait(philosophers->sems->print);
	sem_post(philosophers->sems->dead_signal);
	return (NULL);
}
