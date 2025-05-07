#include "../include/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_args			args;
	t_semaphores	sems;

	if (parse_args(argc, argv, &args) != 0)
		return (1);
	if (init_semaphores(&sems, args.n_philo) != 0)
		return (2);
	args.start_time = get_time() + 200;  // Увеличиваем задержку до 200 мс для лучшей синхронизации
	run_philosophers(&args, &sems);
	close_semaphores(&sems);
	return (0);
}
