#include "../include/philo_bonus.h"

static bool	init_global_semaphores(t_philo *philo)
{
	philo->sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT, S_IRUSR | S_IWUSR,
			philo->table->nb_philos);
	if (philo->sem_forks == SEM_FAILED)
		return (false);
	philo->sem_write = sem_open(SEM_NAME_WRITE, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (philo->sem_write == SEM_FAILED)
		return (false);
	philo->sem_philo_full = sem_open(SEM_NAME_FULL, O_CREAT, S_IRUSR | S_IWUSR,
			philo->table->nb_philos);
	if (philo->sem_philo_full == SEM_FAILED)
		return (false);
	philo->sem_philo_dead = sem_open(SEM_NAME_DEAD, O_CREAT, S_IRUSR | S_IWUSR,
			philo->table->nb_philos);
	if (philo->sem_philo_dead == SEM_FAILED)
		return (false);
	return (true);
}

static bool	init_local_semaphores(t_philo *philo)
{
	philo->sem_meal = sem_open(philo->sem_meal_name, O_CREAT, S_IRUSR | S_IWUSR,
			1);
	if (philo->sem_meal == SEM_FAILED)
		return (false);
	sem_unlink(philo->sem_meal_name);
	return (true);
}

void	init_philo(t_table *table, t_philo *philo)
{
	if (table->nb_philos == 1)
		return ;
	sem_unlink(philo->sem_meal_name);
	if (!init_global_semaphores(philo))
		child_exit(table, SEM_ERR);
	if (!init_local_semaphores(philo))
		child_exit(table, SEM_ERR);
	if (pthread_create(&philo->personal_monitor, NULL, &personal_monitor,
			table) != 0)
		child_exit(table, PTHREAD_ERR);
	return ;
}