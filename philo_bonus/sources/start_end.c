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

	table->start_time = get_time_in_ms() + (table->nb_philos * 20);
	i = -1;
	while (++i < table->nb_philos)
	{
		pid = fork();
		if (pid < 0)
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
	return (true);
}

int	end_program(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
		kill(table->pids[i++], SIGKILL);
	pthread_join(table->satiety, NULL);
	pthread_join(table->starvation, NULL);
	sem_post(table->sem_waiter);
	return (0);
}
