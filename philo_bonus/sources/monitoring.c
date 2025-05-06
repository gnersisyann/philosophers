#include "../include/philo_bonus.h"

int	kill_all_philos(t_table *table, int exit_code)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		kill(table->pids[i], SIGKILL);
		i++;
	}
	return (exit_code);
}

void	*satiety_routine(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	sim_start_delay(table->start_time);
	while (table->philo_full_count < table->nb_philos)
	{
		if (has_simulation_stopped(table) == true)
			return (NULL);
		sem_wait(table->sem_philo_full);
		if (has_simulation_stopped(table) == false)
		{
			table->philo_full_count += 1;
			if (table->philo_full_count == table->nb_philos)
			{
				
				sem_wait(table->sem_stop); //
				table->stop_sim = true; //
				sem_post(table->sem_stop); //
				printf("%ld\n",get_time_in_ms() - table->start_time);
				kill_all_philos(table, EXIT_SUCCESS); //
				sem_post(table->sem_philo_dead); //
				return (NULL); //
			}
		}
		else
		{
			sem_post(table->sem_philo_full); //
			return (NULL); //
		}
		usleep(100);
	}
	return (NULL);
}

void	*starvation_routine(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	if (table->nb_philos == 1)
		return (NULL);
	sim_start_delay(table->start_time);
	if (has_simulation_stopped(table) == true)
		return (NULL);
	sem_wait(table->sem_philo_dead);
	if (has_simulation_stopped(table) == true)
		return (NULL);
	sem_wait(table->sem_stop);
	table->stop_sim = true;
	kill_all_philos(table, EXIT_SUCCESS);
	sem_post(table->sem_philo_full);
	sem_post(table->sem_stop);
	return (NULL);
}

void	*personal_monitor(void *args)
{
	t_table *table;

	table = (t_table *)args;
	if (table->must_eat_count == 0)
		return (NULL);
	sem_wait(table->this_philo->sem_philo_dead);
	sem_wait(table->this_philo->sem_philo_full);
	sim_start_delay(table->start_time);
	while (!end_condition_reached(table, table->this_philo))
	{
		usleep(1000);
		continue ;
	}
	return (NULL);
}