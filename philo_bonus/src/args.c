#include "../include/philo_bonus.h"

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

static int	is_int_range(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && num
				* sign < INT_MIN))
			return (0);
		i++;
	}
	return (1);
}

static int	check_bounds(t_args *args)
{
	if (args->n_philo <= 0 || args->t_die <= 0 || args->t_eat <= 0
		|| args->t_sleep <= 0)
		return (1);
	return (0);
}

static void	print_error(const char *msg)
{
	printf("Error: %s\n", msg);
}

int	parse_args(int argc, char **argv, t_args *args)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_numeric(argv[i]))
			return (print_error("Arguments must be numeric"), 1);
		if (!is_int_range(argv[i]))
			return (print_error("Arguments must be within integer range"), 1);
	}
	args->n_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->must_eat = -1;
	if (argv[5])
	{
		if (ft_atoi(argv[5]) <= 0)
			return (print_error("Number of times each philosopher \
		must eat must be positive"), 1);
		args->must_eat = ft_atoi(argv[5]);
	}
	if (check_bounds(args))
		return (print_error("All arguments must be positive"), 1);
	return (0);
}
