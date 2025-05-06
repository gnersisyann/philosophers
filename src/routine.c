#include "../include/philo_bonus.h"
#include <semaphore.h>

static void	init_local_semaphore(t_philo *philo)
{
	char	name[32];

	snprintf(name, sizeof(name), "%s%d", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
	philo->local_last_meal = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
}

void	philosopher_routine(t_philo *philo)
{
	pthread_t	death_monitor_thread;
	pthread_t	meal_monitor_thread;

	init_local_semaphore(philo);
	sim_start_delay(philo->args->start_time);
	sem_wait(philo->local_last_meal);
	philo->last_meal = get_time();
	sem_post(philo->local_last_meal);
	pthread_create(&death_monitor_thread, NULL, monitor_death, philo);
	pthread_detach(death_monitor_thread);
	if (philo->args->must_eat != -1)
	{
		pthread_create(&meal_monitor_thread, NULL, monitor_meals, philo);
		pthread_detach(meal_monitor_thread);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		sem_wait(philo->sems->forks);
		print_action(philo, CYAN "has taken a fork" RESET);
		sem_wait(philo->sems->forks);
		print_action(philo, CYAN "has taken a fork" RESET);

		sem_wait(philo->local_last_meal);
		philo->last_meal = get_time();
		sem_post(philo->local_last_meal);
		
		print_action(philo, GREEN "is eating" RESET);
		philo->meals_eaten++;
		precise_usleep(philo->args->t_eat);
		sem_post(philo->sems->forks);
		sem_post(philo->sems->forks);
		print_action(philo, GRAY "is sleeping" RESET);
		precise_usleep(philo->args->t_sleep);
		print_action(philo, DARK_BLUE "is thinking" RESET);
	}
}
