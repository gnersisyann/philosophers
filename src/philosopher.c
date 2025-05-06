#include "../include/philo_bonus.h"

void	run_philosophers(t_args *args, t_semaphores *sems)
{
	t_philo *philosophers;
	int i;
	pid_t pid;

	// create philo processes
	philosophers = malloc(sizeof(t_philo) * args->n_philo);
	if (!philosophers)
		return ;
	i = -1;
	while (++i < args->n_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].last_meal = get_time();
		philosophers[i].meals_eaten = 0;
		philosophers[i].args = args;
		philosophers[i].sems = sems;

		pid = fork();
		if (pid == 0)
		{
			philosopher_routine(&philosophers[i]);
			exit(0);
		}
		philosophers[i].pid = pid;
	}

	// create monitoring threads
	pthread_t all_death_monitor_thread;
	pthread_t all_meal_monitor_thread;

	pthread_create(&all_death_monitor_thread, NULL, monitor_all_deaths,philosophers);
	pthread_detach(all_death_monitor_thread);
	if (args->must_eat != -1)
	{
		pthread_create(&all_meal_monitor_thread, NULL, monitor_all_meals,philosophers);
		pthread_detach(all_meal_monitor_thread);
	}

	// wait philos
	i = -1;
	while (++i < args->n_philo)
		waitpid(philosophers[i].pid, NULL, 0);

	free(philosophers);
	close_semaphores(sems);
}
