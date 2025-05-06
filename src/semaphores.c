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
	sems->print = sem_open(SEM_PRINT_NAME, O_CREAT | O_EXCL, 0644, 1);
	sems->meal_check = sem_open(SEM_MEAL_NAME, O_CREAT | O_EXCL, 0644, 0);
	sems->dead_signal = sem_open(SEM_DEAD_NAME, O_CREAT | O_EXCL, 0644, 0);
	return (0);
}

void	close_semaphores(t_semaphores *sems)
{
	sem_close(sems->forks);
	sem_close(sems->print);
	sem_close(sems->meal_check);
	sem_close(sems->dead_signal);
}
