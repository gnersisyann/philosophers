/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:15:45 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/03 20:26:30 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include <pthread.h>

int	main(int argc, char **argv)
{
	t_table	*table;

	if (arg_check(argc))
		return (1);
	table = parse_args(argv);
	if (!table)
		return (1);
	if (!start_program(table))
		return (table_cleanup(table, 1));
	if (table->nb_philos == 1)
		return (waitpid(table->pids[0], NULL, 0), table_cleanup(table, 0));
	if (!start_monitors_threads(table))
		return (table_cleanup(table, 1));
	end_program(table);
	return (table_cleanup(table, 0));
}
