#include "../include/philo_bonus.h"

void	*monitor_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sim_start_delay(philo->args->start_time);
	while (1)
	{
		sem_wait(philo->local_last_meal);
		if (get_time() - philo->last_meal >= philo->args->t_die)
		{
			print_action(philo, RED "died" RESET);
			sem_wait(philo->sems->print);
			sem_post(philo->sems->dead_signal);
			exit(0);
		}
		sem_post(philo->local_last_meal);
		usleep(100);
	}
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sim_start_delay(philo->args->start_time);
	while (1)
	{
		if (philo->meals_eaten >= philo->args->must_eat)
		{
			sem_post(philo->sems->forks);
			sem_post(philo->sems->forks);
			sem_post(philo->sems->meal_check);
			exit(0);
		}
		usleep(100);
	}
	return (NULL);
}
