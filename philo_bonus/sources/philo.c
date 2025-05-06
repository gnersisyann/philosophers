#include "../include/philo_bonus.h"

static void	one_philo(t_philo *philo)
{
	if (!init_local_semaphores(philo))
		exit(SEM_ERR);
	sem_wait(philo->sem_meal);
	philo->last_meal = philo->table->start_time;
	sem_post(philo->sem_meal);
	sim_start_delay(philo->table->start_time);
	print_status(philo, DARK_GREEN "has taken a fork" RESET);
	check_sleep(philo->table->time_to_die);
	print_status(philo, RED "died" RESET);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_waiter);
	sem_close(philo->sem_meal);
	sem_unlink(philo->sem_meal_name);
	exit(table_cleanup(philo->table, DEAD));
}

void	philosopher(t_table *table)
{
	t_philo	*philo;

	philo = table->this_philo;
	if (philo->table->nb_philos == 1)
		one_philo(philo);
	init_philo(table, philo);
	sem_wait(philo->sem_meal);
	philo->last_meal = philo->table->start_time;
	sem_post(philo->sem_meal);
	sim_start_delay(philo->table->start_time);
	if (philo->id % 2 == 0)
		usleep(100);
	while (!has_simulation_stopped(table))
	{
		if (has_simulation_stopped(philo->table))
			child_exit(table, EXIT_SUCCESS);
		eat_and_sleep(philo);
		think(philo, false);
	}
}
