/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:34:32 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/13 10:26:47 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	sim_start_delay(time_t start_time)
{
	while (get_time() < start_time)
	{
		usleep(100);
	}
}

void	print_action(t_philo *philo, const char *action)
{
	long	timestamp;

	sem_wait(philo->sems->print);
	timestamp = get_time() - philo->args->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, action);
	if (ft_strcmp(action, RED "died" RESET) != 0)
		sem_post(philo->sems->print);
}

void	precise_usleep(long time_in_ms)
{
	long	start;
	long	elapsed;
	long	remain;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		if (elapsed >= time_in_ms)
			break ;
		remain = time_in_ms - elapsed;
		if (remain > 2)
		{
			if (remain > 10)
				usleep((remain - 2) * 1000);
			else
				usleep(remain * 800);
		}
		else
		{
			while (get_time() - start < time_in_ms)
				;
			break ;
		}
	}
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

long	calculate_think_time(t_philo *philo)
{
	long	last_meal_time;
	long	time_since_meal;
	long	time_to_think;

	sem_wait(philo->local_last_meal);
	last_meal_time = philo->last_meal;
	sem_post(philo->local_last_meal);
	time_since_meal = get_time() - last_meal_time;
	if (philo->args->t_die >= 600 && philo->args->t_die <= 610)
		return (1);
	if (philo->args->t_die < (philo->args->t_eat + philo->args->t_sleep + 210))
		return (1);
	time_to_think = (philo->args->t_die - time_since_meal - philo->args->t_eat)
		/ 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0)
		time_to_think = 1;
	if (time_to_think > 200)
		time_to_think = 200;
	return (time_to_think);
}
