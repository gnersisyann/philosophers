#include "../include/philo_bonus.h"

static void	one_philo(t_philo *philo)
{
	sim_start_delay(philo->table->start_time);
	print_status(philo, "has taken a fork");
	check_sleep(philo->table->time_to_die);
	print_status(philo, "died");
	sem_post(philo->table->sem_forks);
    sem_post(philo->table->sem_waiter);
	free_table(philo->table);
	exit(DEAD);
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
	while (1)
	{
		eat_and_sleep(philo);
		think(philo, false);
	}
}
