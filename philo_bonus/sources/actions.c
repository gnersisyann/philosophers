#include "../include/philo_bonus.h"
#include <semaphore.h>

bool	has_simulation_stopped(t_table *table)
{
	bool	ret;

	sem_wait(table->sem_stop);
	ret = table->stop_sim;
	sem_post(table->sem_stop);
	return (ret);
}

void	check_sleep(time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		usleep(100);
	}
}

void	think(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	time_to_think = (philo->table->time_to_die - (get_time_in_ms()
				- philo->last_meal) - philo->table->time_to_eat) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!has_simulation_stopped(philo->table) && !silent)
		print_status(philo, YELLOW "is thinking" RESET);
	check_sleep(time_to_think);
}

void	print_status(t_philo *philo, char *str)
{
	sem_wait(philo->table->sem_write);
	if (!has_simulation_stopped(philo->table) || ft_strcmp(str,
			RED "died" RESET) == 0)
	{
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
			philo->id + 1, str);
	}
	sem_post(philo->table->sem_write);
}

int	eat_and_sleep(t_philo *philo)
{
	if (has_simulation_stopped(philo->table))
		return (1);
	sem_wait(philo->table->sem_waiter);
	sem_wait(philo->table->sem_forks);
	print_status(philo, DARK_GREEN "has taken a fork" RESET);
	sem_wait(philo->table->sem_forks);
	print_status(philo, DARK_GREEN "has taken a fork" RESET);
	if (has_simulation_stopped(philo->table))
	{
		sem_post(philo->table->sem_forks);
		sem_post(philo->table->sem_forks);
		sem_post(philo->table->sem_waiter);
		return (1);
	}
	philo->last_meal = get_time_in_ms();
	++philo->times_ate;
	if (has_simulation_stopped(philo->table))
	{
		sem_post(philo->table->sem_forks);
		sem_post(philo->table->sem_forks);
		sem_post(philo->table->sem_waiter);
		return (1);
	}
	print_status(philo, GREEN "is eating" RESET);
	check_sleep(philo->table->time_to_eat);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_waiter);
	if (has_simulation_stopped(philo->table))
		return (1);
	print_status(philo, GRAY "is sleeping" RESET);
	check_sleep(philo->table->time_to_sleep);
	return (0);
}
