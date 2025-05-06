#include "../include/philo_bonus.h"

static int	check_bounds(t_args *args)
{
	if (args->n_philo <= 0 || args->t_die <= 0 || args->t_eat <= 0
		|| args->t_sleep <= 0)
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv, t_args *args)
{
	if (argc < 5 || argc > 6)
		return (1);
	args->n_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->must_eat = -1;
	if (argv[5])
	{
		if (ft_atoi(argv[5]) <= 0)
			return (1);
		args->must_eat = ft_atoi(argv[5]);
	}
	return (check_bounds(args));
}