/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:24:20 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/09 12:24:20 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	start_program(t_table *table)
{
	int	i;

	table->start_time = get_time_in_ms() + table->nb_philos * 20;
	i = -1;
	while (++i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]) != 0)
			return (error_failure("%s error: Could not create thread.\n", NULL,
					table));
	}
	if (table->nb_philos > 1)
	{
		if (pthread_create(&table->monitor, NULL, monitor_routine,
				table) != 0)
			return (error_failure("%s error: Could not create thread.\n", NULL,
					table));
	}
	return (true);
}

void	end_program(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philos)
		pthread_join(table->philos[i].thread, NULL);
	if (table->nb_philos > 1)
		pthread_join(table->monitor, NULL);
	destroy_mutexes(table);
	free_table(table);
}
