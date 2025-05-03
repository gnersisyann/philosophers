#include "../include/philo_bonus.h"

bool	end_condition_reached(t_table *table, t_philo *philo)
{
	sem_wait(philo->sem_meal);
	if (has_simulation_stopped(table)) //
	{                                  //
		sem_post(philo->sem_meal);     //
		return (true);                 //
	}                                  //
	if (get_time_in_ms() - philo->last_meal >= table->time_to_die)
	{
		sem_wait(table->sem_stop);     //
		if (!table->stop_sim)          //
		{                              //
			table->stop_sim = true;    //
			sem_post(table->sem_stop); //
			print_status(philo, RED "died" RESET);
			sem_post(philo->table->sem_philo_dead);
		}                              //
		else                           //
			sem_post(table->sem_stop); //
		sem_post(philo->sem_meal);
		return (true);
	}
	if (table->must_eat_count != -1 && philo->ate_enough == false
		&& philo->times_ate >= (unsigned int)table->must_eat_count)
	{
		sem_post(table->sem_philo_full);
		philo->ate_enough = true;
	}
	sem_post(philo->sem_meal);
	return (false);
}

// bool	end_condition_reached(t_table *table, t_philo *philo)
// {
// 	sem_wait(philo->sem_meal);

// 	// Проверить сначала, не остановлена ли уже симуляция
// 	if (has_simulation_stopped(table))
// 	{
// 		sem_post(philo->sem_meal);
// 		return (true);
// 	}

// 	if (get_time_in_ms() - philo->last_meal >= table->time_to_die)
// 	{
// 		// Установить флаг остановки перед печатью
// 		sem_wait(table->sem_stop);
// 		if (!table->stop_sim) // Только первый умерший печатает сообщение
// 		{
// 			table->stop_sim = true;
// 			sem_post(table->sem_stop);
// 			print_status(philo, RED "died" RESET);
// 			sem_post(table->this_philo->sem_philo_dead);
// 		}
// 		else
// 			sem_post(table->sem_stop);

// 		sem_post(philo->sem_meal);
// 		return (true);
// 	}

// 	if (table->must_eat_count != -1 && philo->ate_enough == false
// 		&& philo->times_ate >= (unsigned int)table->must_eat_count)
// 	{
// 		sem_post(philo->sem_philo_full);
// 		philo->ate_enough = true;
// 	}

// 	sem_post(philo->sem_meal);
// 	return (false);
// }