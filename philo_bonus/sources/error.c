#include "../include/philo_bonus.h"

int	msg(char *str, const char *detail, int exit_no)
{
	if (!detail)
		printf(str, "philo:");
	else
		printf(str, "philo:", detail);
	return (exit_no);
}

void	*error_null(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	msg(str, details, 1);
	return (NULL);
}

void	child_exit(t_table *table, int exit_code)
{
	if (table->this_philo->sem_meal)
		sem_post(table->this_philo->sem_meal);
	pthread_join(table->this_philo->personal_monitor, NULL);
	if (exit_code == SEM_ERR)
		msg("%s error: Could not create semaphore.\n", NULL, 0);
	if (exit_code == PTHREAD_ERR)
		msg("%s error: Could not create thread.\n", NULL, 0);
	if (table->this_philo->sem_forks)
		sem_close(table->this_philo->sem_forks);
	if (table->this_philo->sem_philo_full)
		sem_close(table->this_philo->sem_philo_full);
	if (table->this_philo->sem_philo_dead)
		sem_close(table->this_philo->sem_philo_dead);
	if (table->this_philo->sem_write)
		sem_close(table->this_philo->sem_write);
	if (table->this_philo->sem_meal)
		sem_close(table->this_philo->sem_meal);
	free_table(table);
	exit(exit_code);
}

int	error_failure(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	return (msg(str, details, 0));
}

void	unlink_global_sems(void)
{
	sem_unlink(SEM_NAME_FORKS);
	sem_unlink(SEM_NAME_WRITE);
	sem_unlink(SEM_NAME_FULL);
	sem_unlink(SEM_NAME_DEAD);
	sem_unlink(SEM_NAME_STOP);
	sem_unlink(SEM_NAME_WAITER);
}

int	sem_error_cleanup(t_table *table)
{
	sem_close(table->sem_forks);
	sem_close(table->sem_write);
	sem_close(table->sem_philo_full);
	sem_close(table->sem_philo_dead);
	sem_close(table->sem_stop);
	sem_close(table->sem_waiter);
	unlink_global_sems();
	return (error_failure("%s error: Could not create semaphore.\n", NULL,
			table));
}

void	*free_table(t_table *table)
{
	if (!table)
		return (NULL);
	if (table->philos != NULL)
	{
		free(table->philos);
		table->philos = NULL;
	}
	if (table->pids)
	{
		free(table->pids);
		table->pids = NULL;
	}
	if (table)
	{
		free(table);
		table = NULL;
	}
	return (NULL);
}
