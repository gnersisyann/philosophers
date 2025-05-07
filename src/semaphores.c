#include "../include/philo_bonus.h"

void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_PRINT_NAME);
	sem_unlink(SEM_MEAL_NAME);
	sem_unlink(SEM_DEAD_NAME);
}

int	init_semaphores(t_semaphores *sems, int n_philo)
{
	unlink_semaphores();
	sems->forks = sem_open(SEM_FORKS_NAME, O_CREAT | O_EXCL, 0644, n_philo);
	if (sems->forks == SEM_FAILED)
		return (1);
		
	sems->print = sem_open(SEM_PRINT_NAME, O_CREAT | O_EXCL, 0644, 1);
	if (sems->print == SEM_FAILED)
	{
		sem_close(sems->forks);
		return (1);
	}
	
	sems->meal_check = sem_open(SEM_MEAL_NAME, O_CREAT | O_EXCL, 0644, 0);
	if (sems->meal_check == SEM_FAILED)
	{
		sem_close(sems->forks);
		sem_close(sems->print);
		return (1);
	}
	
	sems->dead_signal = sem_open(SEM_DEAD_NAME, O_CREAT | O_EXCL, 0644, 0);
	if (sems->dead_signal == SEM_FAILED)
	{
		sem_close(sems->forks);
		sem_close(sems->print);
		sem_close(sems->meal_check);
		return (1);
	}
	return (0);
}

void	close_semaphores(t_semaphores *sems)
{
	sem_close(sems->forks);
	sem_close(sems->print);
	sem_close(sems->meal_check);
	sem_close(sems->dead_signal);
}
