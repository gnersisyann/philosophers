#include "../include/philo_bonus.h"

bool	start_monitors_threads(t_table *table)
{
	if (pthread_create(&table->satiety, NULL, &satiety_routine, table) != 0)
		return (error_failure("%s error: Could not create thread.\n", NULL,
				table));
	if (pthread_create(&table->starvation, NULL, &starvation_routine,
			table) != 0)
		return (error_failure("%s error: Could not create thread.\n", NULL,
				table));
	return (true);
}

bool	start_program(t_table *table)
{
	int		i;
	pid_t	pid;

	table->start_time = get_time_in_ms() + ((table->nb_philos * 2) * 10);
	i = -1;
	while (++i < table->nb_philos)
	{
		pid = fork();
		if (pid == -1)
			return (error_failure("%s error: Could not fork child.\n", NULL,
					table));
		else if (pid > 0)
			table->pids[i] = pid;
		else if (pid == 0)
		{
			table->this_philo = &table->philos[i];
			philosopher(table);
		}
	}
	if (start_monitors_threads(table) == false)
		return (false);
	return (true);
}

void	end_program(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philos)
	{
		if (kill(table->pids[i], SIGKILL) == -1)
		{
			error_failure("Error killing philosopher", NULL, table);
			continue ;
		}
	}
	free_table(table);
}
