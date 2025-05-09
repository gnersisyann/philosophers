/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_semaphores.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:33:53 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/09 17:34:12 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	init_named_semaphore(sem_t **sem, const char *base, int id)
{
	char	*name;

	name = strjoin_int(base, id);
	if (!name)
	{
		printf("Error allocating memory for semaphore name\n");
		exit(1);
	}
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if (*sem == SEM_FAILED)
	{
		printf("Error initializing semaphore \"%s\" for philosopher %d\n", base,
			id);
		free(name);
		exit(1);
	}
	free(name);
}

void	init_local_semaphores(t_philo *philo)
{
	init_named_semaphore(&philo->local_last_meal, SEM_LLASTMEAL_NAME,
		philo->id);
	init_named_semaphore(&philo->local_meals_eaten, SEM_LMEALSEATEN_NAME,
		philo->id);
	init_named_semaphore(&philo->local_finish, SEM_LFINISH_NAME, philo->id);
}

static void	error_exit(void)
{
	printf("Error allocating memory for semaphore name\n");
	exit(1);
}

void	cleanup_local_semaphores(t_philo *philo)
{
	char	*name;

	sem_close(philo->local_last_meal);
	sem_close(philo->local_meals_eaten);
	sem_close(philo->local_finish);
	name = strjoin_int(SEM_LLASTMEAL_NAME, philo->id);
	if (!name)
		error_exit();
	sem_unlink(name);
	name = strjoin_int(SEM_LMEALSEATEN_NAME, philo->id);
	if (!name)
		error_exit();
	sem_unlink(name);
	name = strjoin_int(SEM_LFINISH_NAME, philo->id);
	if (!name)
		error_exit();
	sem_unlink(name);
}
