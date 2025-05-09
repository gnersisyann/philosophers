/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ganersis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:33:45 by ganersis          #+#    #+#             */
/*   Updated: 2025/05/09 19:38:47 by ganersis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	print_usage(void)
{
	printf(RED "Error:" RESET " Invalid number of arguments.\n\n");
	printf("Usage: " GREEN "./philo_bonus" RESET " N T_DIE"\
" T_EAT T_SLEEP [EAT_COUNT]\n\n");
	printf("Arguments:\n");
	printf("  N         - number of philosophers (and forks)\n");
	printf("  T_DIE     - time to die (ms)\n");
	printf("  T_EAT     - time to eat (ms)\n");
	printf("  T_SLEEP   - time to sleep (ms)\n");
	printf("  EAT_COUNT - (optional) times each philosopher must eat\n\n");
	printf("Example:\n");
	printf("  " GREEN "./philo_bonus 5 800 200 200" RESET "\n");
	printf("  " GREEN "./philo_bonus 5 800 200 200 7" RESET "\n\n");
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_semaphores	sems;

	if (argc != 5 && argc != 6)
	{
		print_usage();
		return (0);
	}
	if (parse_args(argc, argv, &args) != 0)
		return (1);
	if (init_semaphores(&sems, args.n_philo) != 0)
	{
		printf("Error: Failed to initialize semaphores\n");
		return (2);
	}
	args.start_time = get_time() + 200;
	run_philosophers(&args, &sems);
	close_semaphores(&sems);
	return (0);
}
