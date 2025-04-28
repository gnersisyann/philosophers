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
