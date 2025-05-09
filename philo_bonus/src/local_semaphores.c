#include "../include/philo_bonus.h"

void	init_local_semaphores(t_philo *philo)
{
	char	name[32];

	snprintf(name, sizeof(name), "%s%d", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
	philo->local_last_meal = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->local_last_meal == SEM_FAILED)
	{
		printf("Error initializing last_meal semaphore for philosopher %d\n",
			philo->id);
		exit(1);
	}
	snprintf(name, sizeof(name), "%s%d_meals", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
	philo->local_meals_eaten = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->local_meals_eaten == SEM_FAILED)
	{
		printf("Error initializing meals_eaten semaphore for philosopher %d\n",
			philo->id);
		sem_close(philo->local_last_meal);
		exit(1);
	}
	snprintf(name, sizeof(name), "%s%d_finish", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
	philo->local_finish = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->local_finish == SEM_FAILED)
	{
		printf("Error initializing finish semaphore for philosopher %d\n",
			philo->id);
		sem_close(philo->local_last_meal);
		sem_close(philo->local_meals_eaten);
		exit(1);
	}
}

void	cleanup_local_semaphores(t_philo *philo)
{
	char	name[32];

	sem_close(philo->local_last_meal);
	sem_close(philo->local_meals_eaten);
	sem_close(philo->local_finish);
	snprintf(name, sizeof(name), "%s%d", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
	snprintf(name, sizeof(name), "%s%d_meals", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
	snprintf(name, sizeof(name), "%s%d_finish", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
}