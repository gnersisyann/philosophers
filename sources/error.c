#include "../include/philo.h"

int	msg(char *str, const char *detail, int exit_no)
{
	if (!detail)
		printf(str, "philo:");
	else
		printf(str, "philo:", detail);
	return (exit_no);
}

void	*free_table(t_table *table)
{
	if (!table)
		return (NULL);
	if (table->fork_locks != NULL)
		free(table->fork_locks);
	if (table->philos != NULL)
		free(table->philos);
	free(table);
	return (NULL);
}

void	*error_null(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	msg(str, details, 1);
	return (NULL);
}

int	error_failure(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	return (msg(str, details, 0));
}

void	destroy_mutexes(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_time_lock);
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->sim_stop_lock);
}