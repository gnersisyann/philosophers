/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:15:45 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/01 14:59:31 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (arg_check(argc))
		return (1);
	table = parse_args(argv);
	if (!table)
		return (1);
	if (!start_program(table))
		return (1);
	if (end_program(table) == -1)
		return (table_cleanup(table, 1));
	return (table_cleanup(table, 0));
}
