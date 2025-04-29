/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:15:53 by ganersis          #+#    #+#             */
/*   Updated: 2025/04/29 19:17:03 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*init_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = (t_philo *)malloc(table->nb_philos * sizeof(t_philo));
	if (!philos)
		return (error_null("%s error: Could not allocate memory.\n", NULL,
				NULL));
	while (++i < table->nb_philos)
	{
		if (pthread_mutex_init(&philos[i].meal_time_lock, NULL) != 0)
			return (error_null("%s error: Could not create mutex.\n", NULL,
					table));
		philos[i].times_ate = 0;
		philos[i].id = i;
		philos[i].table = table;
		philos[i].fork[0] = philos[i].id;
		philos[i].fork[1] = (philos[i].id + 1) % philos->table->nb_philos;
		if (philos[i].id % 2 == 0)
		{
			philos[i].fork[0] = (philos[i].id + 1) % philos->table->nb_philos;
			philos[i].fork[1] = philos[i].id;
		}
	}
	return (philos);
}

pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*fork_locks;
	int				i;

	i = -1;
	fork_locks = (pthread_mutex_t *)malloc(table->nb_philos
			* sizeof(pthread_mutex_t));
	if (!fork_locks)
		return (error_null("%s error: Could not allocate memory.\n", NULL,
				NULL));
	while (++i < table->nb_philos)
	{
		if (pthread_mutex_init(&fork_locks[i], NULL) != 0)
			return (error_null("%s error: Could not create mutex.\n", NULL,
					table));
	}
	return (fork_locks);
}

bool	init_mutexes(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (false);
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (error_failure("%s error: Could not create mutex.\n", NULL,
				table));
	if (pthread_mutex_init(&table->sim_stop_lock, NULL) != 0)
		return (error_failure("%s error: Could not create mutex.\n", NULL,
				table));
	return (true);
}

static int	check_bounds(int value, const char *name)
{
	if (value < 0 || value > INT_MAX)
	{
		printf(RED "Error:" RESET " %s is out of range. Must be a" \
					" positive integer within the range of \
					" RED "int" RESET ".\n", name);
		return (1);
	}
	return (0);
}

t_table	*parse_args(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (error_null("%s error: Could not allocate memory.\n", NULL, 0));
	table->nb_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->must_eat_count = -1;
	if (argv[5])
		table->must_eat_count = ft_atoi(argv[5]);
	if (check_bounds(table->nb_philos, "Philosopher count")
		|| check_bounds(table->time_to_die, "Time to die")
		|| check_bounds(table->time_to_eat, "Time to eat")
		|| check_bounds(table->time_to_sleep, "Time to sleep") || (argv[5]
			&& check_bounds(table->must_eat_count, "Eat count")))
		return (NULL);
	table->philos = init_philos(table);
	if (!table->philos)
		return (NULL);
	if (!init_mutexes(table))
		return (NULL);
	table->sim_stop = false;
	return (table);
}
