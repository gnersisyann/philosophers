/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:20 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/09 17:34:20 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	set_finish(t_philo *philo, bool *finish)
{
	sem_wait(philo->local_finish);
	*finish = philo->finish;
	sem_post(philo->local_finish);
}

static void	update_finish(t_philo *philo, bool status)
{
	sem_wait(philo->local_finish);
	philo->finish = status;
	sem_post(philo->local_finish);
}

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	int		last_meal;
	bool	finish;

	philo = (t_philo *)arg;
	sim_start_delay(philo->args->start_time);
	while (1)
	{
		set_finish(philo, &finish);
		if (finish == true)
			break ;
		sem_wait(philo->local_last_meal);
		last_meal = philo->last_meal;
		sem_post(philo->local_last_meal);
		if (get_time() - philo->last_meal >= philo->args->t_die)
		{
			update_finish(philo, true);
			print_action(philo, RED "died" RESET);
			sem_post(philo->sems->dead_signal);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_philo	*philo;
	int		meals;
	bool	finish;

	philo = (t_philo *)arg;
	sim_start_delay(philo->args->start_time);
	while (1)
	{
		set_finish(philo, &finish);
		if (finish == true)
			break ;
		sem_wait(philo->local_meals_eaten);
		meals = philo->meals_eaten;
		sem_post(philo->local_meals_eaten);
		if (meals >= philo->args->must_eat)
		{
			sem_post(philo->sems->forks);
			sem_post(philo->sems->forks);
			sem_post(philo->sems->meal_check);
			update_finish(philo, true);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
