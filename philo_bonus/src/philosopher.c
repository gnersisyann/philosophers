/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:26 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/13 10:17:43 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	run_helper(t_args *args, t_semaphores *sems, t_philo *philosophers)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < args->n_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].last_meal = args->start_time;
		philosophers[i].meals_eaten = 0;
		philosophers[i].args = args;
		philosophers[i].sems = sems;
		philosophers[i].finish = false;
		pid = fork();
		if (pid == 0)
		{
			philosopher_routine(&philosophers[i]);
			free(philosophers);
			exit(0);
		}
		philosophers[i].pid = pid;
	}
}

static void	clean_funcs(t_philo *philosophers, t_args *args, t_semaphores *sems)
{
	int	i;

	i = -1;
	while (++i < args->n_philo)
		cleanup_local_semaphores(&philosophers[i]);
	free(philosophers);
	close_semaphores(sems);
}

void	run_philosophers(t_args *args, t_semaphores *sems)
{
	t_philo		*philosophers;
	int			i;
	pthread_t	all_death_monitor_thread;
	pthread_t	all_meal_monitor_thread;

	philosophers = malloc(sizeof(t_philo) * args->n_philo);
	if (!philosophers)
		return ;
	memset(philosophers, 0, sizeof(t_philo) * args->n_philo);
	run_helper(args, sems, philosophers);
	pthread_create(&all_death_monitor_thread, NULL, monitor_all_deaths,
		philosophers);
	if (args->must_eat != -1)
	{
		pthread_create(&all_meal_monitor_thread, NULL, monitor_all_meals,
			philosophers);
	}
	i = -1;
	while (++i < args->n_philo)
		waitpid(philosophers[i].pid, NULL, 0);
	pthread_join(all_death_monitor_thread, NULL);
	if (args->must_eat != -1)
		pthread_join(all_meal_monitor_thread, NULL);
	clean_funcs(philosophers, args, sems);
}
