#include "../include/philo_bonus.h"

void	*monitor_all_deaths(void *arg)
{
	t_philo	*philosophers;
	int		i;

	philosophers = (t_philo *)arg;
	i = -1;
	sim_start_delay(philosophers->args->start_time);
	sem_wait(philosophers->sems->dead_signal);
	while (++i < philosophers->args->n_philo)
		kill(philosophers[i].pid, SIGKILL);
	return (NULL);
}

void	*monitor_all_meals(void *arg)
{
	t_philo	*philosophers;
	int		i;

	philosophers = (t_philo *)arg;
	i = -1;
	sim_start_delay(philosophers->args->start_time);
	while (++i < philosophers->args->n_philo)
		sem_wait(philosophers->sems->meal_check);
	sem_wait(philosophers->sems->print);
	i = -1;
	while (++i < philosophers->args->n_philo)
		kill(philosophers[i].pid, SIGKILL);
	return (NULL);
}
