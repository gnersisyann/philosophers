/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:15:48 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/02 21:09:54 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	arg_check(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf(RED "Error:" RESET " Invalid number of arguments.\n\n");
		printf("Usage: " GREEN "./philo_bonus" RESET " N T_DIE T_EAT"
				" T_SLEEP [EAT_COUNT]\n\n");
		printf("Arguments:\n");
		printf("  N         - number of processes\n");
		printf("  T_DIE     - time to die (ms)\n");
		printf("  T_EAT     - time to eat (ms)\n");
		printf("  T_SLEEP   - time to sleep (ms)\n");
		printf("  EAT_COUNT - (optional) times each philosopher must eat\n\n");
		printf("Example:\n");
		printf("  " GREEN "./philo_bonus 5 800 200 200" RESET "\n");
		printf("  " GREEN "./philo_bonus 5 800 200 200 7" RESET "\n\n");
		return (1);
	}
	return (0);
}

int	table_cleanup(t_table *table, int exit_code)
{
	if (table != NULL)
	{
		if (table->satiety)
			pthread_join(table->satiety, NULL);
		if (table->starvation)
			pthread_join(table->starvation, NULL);
		sem_close(table->sem_forks);
		sem_close(table->sem_write);
		sem_close(table->sem_philo_full);
		sem_close(table->sem_philo_dead);
		sem_close(table->sem_stop);
		sem_close(table->sem_waiter);
		unlink_global_sems();
		free_table(table);
	}
	return (exit_code);
}
