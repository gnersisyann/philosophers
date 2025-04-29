/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:15:45 by ganersis          #+#    #+#             */
/*   Updated: 2025/04/29 19:15:46 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	end_program(table);
	return (0);
}
