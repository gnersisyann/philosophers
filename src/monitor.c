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
			sem_post(philo->sems->dead_signal);
			cleanup_local_semaphores(philo);
			exit(0);
		}
		sem_post(philo->local_last_meal);
		usleep(1000);  // Увеличиваем задержку до 1 мс
	}
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_philo	*philo;
	int		meals;

	philo = (t_philo *)arg;
	sim_start_delay(philo->args->start_time);
	while (1)
	{
		sem_wait(philo->local_meals_eaten);
		meals = philo->meals_eaten;
		sem_post(philo->local_meals_eaten);
		
		if (meals >= philo->args->must_eat)
		{
			sem_post(philo->sems->forks);
			sem_post(philo->sems->forks);
			sem_post(philo->sems->meal_check);
			cleanup_local_semaphores(philo);
			exit(0);
		}
		usleep(1000);  // Увеличиваем задержку до 1 мс, как и в monitor_death
	}
	return (NULL);
}
