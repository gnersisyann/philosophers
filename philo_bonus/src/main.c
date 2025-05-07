#include "../include/philo_bonus.h"

static void	print_usage(void)
{
	printf("Usage: ./philo_bonus number_of_philosophers time_to_die \
		time_to_eat time_to_sleep \
		[number_of_times_each_philosopher_must_eat]\n");
	printf("\nParameters:\n");
	printf("  number_of_philosophers: Number of philosophers at the \
		table\n");
	printf("  time_to_die: Time in milliseconds after which a philosopher \
		dies if they haven't eaten\n");
	printf("  time_to_eat: Time in milliseconds it takes for a philosopher \
		to eat\n");
	printf("  time_to_sleep: Time in milliseconds a philosopher spends \
		sleeping\n");
	printf("  number_of_times_each_philosopher_must_eat: [Optional] \
		Program stops when all philosophers have eaten this many times\n");
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_semaphores	sems;

	if (argc < 5 || argc > 6)
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
