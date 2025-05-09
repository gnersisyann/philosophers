/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:31 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/09 19:45:37 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	is_close_to_death(t_philo *philo)
{
	long	time_since_meal;
	long	current_time;

	sem_wait(philo->local_last_meal);
	current_time = get_time();
	time_since_meal = current_time - philo->last_meal;
	sem_post(philo->local_last_meal);
	return (time_since_meal > (philo->args->t_die * 0.75));
}

static void	routine_logic(t_philo *philo)
{
	long	think_time;

	sem_wait(philo->local_last_meal);
	philo->last_meal = get_time();
	sem_post(philo->local_last_meal);
	sem_wait(philo->local_meals_eaten);
	philo->meals_eaten++;
	sem_post(philo->local_meals_eaten);
	print_action(philo, GREEN "is eating" RESET);
	precise_usleep(philo->args->t_eat);
	print_action(philo, GRAY "is sleeping" RESET);
	sem_post(philo->sems->forks);
	sem_post(philo->sems->forks);
	precise_usleep(philo->args->t_sleep);
	think_time = calculate_think_time(philo);
	print_action(philo, DARK_BLUE "is thinking" RESET);
	precise_usleep(think_time);
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->sems->forks);
	print_action(philo, CYAN "has taken a fork" RESET);
	sem_wait(philo->sems->forks);
	print_action(philo, CYAN "has taken a fork" RESET);
}

static void	create_threads(pthread_t *death_monitor_thread,
		pthread_t *meal_monitor_thread, t_philo *philo)
{
	pthread_create(death_monitor_thread, NULL, monitor_death, philo);
	pthread_detach(*death_monitor_thread);
	if (philo->args->must_eat != -1)
	{
		pthread_create(meal_monitor_thread, NULL, monitor_meals, philo);
		pthread_detach(*meal_monitor_thread);
	}
}

void	philosopher_routine(t_philo *philo)
{
	pthread_t	death_monitor_thread;
	pthread_t	meal_monitor_thread;
	bool		finish;

	finish = 0;
	init_local_semaphores(philo);
	create_threads(&death_monitor_thread, &meal_monitor_thread, philo);
	sim_start_delay(philo->args->start_time);
	if (philo->id % 2 == 0)
		usleep(philo->args->t_eat * 500);
	while (1)
	{
		sem_wait(philo->local_finish);
		finish = philo->finish;
		sem_post(philo->local_finish);
		if (finish == true)
			break ;
		if (!is_close_to_death(philo))
			usleep(philo->args->t_die / 10);
		take_forks(philo);
		routine_logic(philo);
	}
	usleep(1000);
	cleanup_local_semaphores(philo);
}
