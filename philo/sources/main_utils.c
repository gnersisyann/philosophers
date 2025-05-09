/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:15:48 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/09 19:36:56 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	arg_check(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf(RED "Error:" RESET " Invalid number of arguments.\n\n");
		printf("Usage: " GREEN "./philo" RESET " N T_DIE T_EAT"
			" T_SLEEP [EAT_COUNT]\n\n");
		printf("Arguments:\n");
		printf("  N         - number of threads\n");
		printf("  T_DIE     - time to die (ms)\n");
		printf("  T_EAT     - time to eat (ms)\n");
		printf("  T_SLEEP   - time to sleep (ms)\n");
		printf("  EAT_COUNT - (optional) times each philosopher must eat\n\n");
		printf("Example:\n");
		printf("  " GREEN "./philo 5 800 200 200" RESET "\n");
		printf("  " GREEN "./philo 5 800 200 200 7" RESET "\n\n");
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (!is_numeric(argv[i]))
			return (printf(RED "Arguments must be numeric\n" RESET), 1);
	}
	return (0);
}
