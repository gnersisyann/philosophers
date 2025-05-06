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

	sem_wait(philo->sem_meal);
	time_to_think = (philo->table->time_to_die - (get_time_in_ms()
				- philo->last_meal) - philo->table->time_to_eat) / 2;
	sem_post(philo->sem_meal);
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
	sem_wait(philo->table->sem_stop);
	sem_wait(philo->table->sem_write);
	if (philo->table->stop_sim == false)
	{
		printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
			philo->id + 1, str);
	}
	sem_post(philo->table->sem_write);
	sem_post(philo->table->sem_stop);
}

int	eat_and_sleep(t_philo *philo)
{
	if (has_simulation_stopped(philo->table))
		return (1);
	sem_wait(philo->table->sem_waiter);
	sem_wait(philo->table->sem_forks);
	if (!has_simulation_stopped(philo->table))
		print_status(philo, DARK_GREEN "has taken a fork" RESET);
	sem_wait(philo->table->sem_forks);
	if (!has_simulation_stopped(philo->table))
		print_status(philo, DARK_GREEN "has taken a fork" RESET);
	if (has_simulation_stopped(philo->table))
	{
		sem_post(philo->table->sem_forks);
		sem_post(philo->table->sem_forks);
		sem_post(philo->table->sem_waiter);
		return (1);
	}
	sem_wait(philo->sem_meal); //
	philo->last_meal = get_time_in_ms(); //
	++philo->times_ate; //
	if (!has_simulation_stopped(philo->table))
		print_status(philo, GREEN "is eating" RESET);
	if (philo->table->must_eat_count != -1 && philo->times_ate >= (unsigned int)philo->table->must_eat_count && !philo->ate_enough) //
	{ //
		philo->ate_enough = true; //
		sem_post(philo->table->sem_philo_full); //
	} //
	sem_post(philo->sem_meal); //
	
	usleep(30000);
	check_sleep(philo->table->time_to_eat);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_waiter);
	if (!has_simulation_stopped(philo->table))
		print_status(philo, GRAY "is sleeping" RESET);
	check_sleep(philo->table->time_to_sleep);
	return (0);
}