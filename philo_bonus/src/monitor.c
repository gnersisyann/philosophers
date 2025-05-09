#include "../include/philo_bonus.h"

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	int		last_meal;
	bool	finish;

	philo = (t_philo *)arg;
	sim_start_delay(philo->args->start_time);
	while (1)
	{
		sem_wait(philo->local_finish);
		finish = philo->finish;
		sem_post(philo->local_finish);
		if (finish == true)
			break ;
		sem_wait(philo->local_last_meal);
		last_meal = philo->last_meal;
		sem_post(philo->local_last_meal);
		if (get_time() - philo->last_meal >= philo->args->t_die)
		{
			sem_wait(philo->local_finish);
			philo->finish = true;
			sem_post(philo->local_finish);
			print_action(philo, RED "died" RESET);
			sem_post(philo->sems->dead_signal);
			break;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_philo	*philo;
	int		meals;
	bool	finish;

	philo = (t_philo *)arg;
	sim_start_delay(philo->args->start_time);
	while (1)
	{
		sem_wait(philo->local_finish);
		finish = philo->finish;
		sem_post(philo->local_finish);
		if (finish == true)
			break ;
		sem_wait(philo->local_meals_eaten);
		meals = philo->meals_eaten;
		sem_post(philo->local_meals_eaten);
		if (meals >= philo->args->must_eat)
		{
			sem_post(philo->sems->forks);
			sem_post(philo->sems->forks);
			sem_post(philo->sems->meal_check);
			sem_wait(philo->local_finish);
			philo->finish = true;
			sem_post(philo->local_finish);
			break;
		}
		usleep(1000);
	}
	return (NULL);
}
