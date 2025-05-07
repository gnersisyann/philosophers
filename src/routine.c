#include "../include/philo_bonus.h"
#include <semaphore.h>

static void	init_local_semaphore(t_philo *philo)
{
	char	name[32];

	// Инициализация семафора для last_meal
	snprintf(name, sizeof(name), "%s%d", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
	philo->local_last_meal = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->local_last_meal == SEM_FAILED)
	{
		printf("Error initializing last_meal semaphore for philosopher %d\n", philo->id);
		exit(1);
	}
	
	// Инициализация семафора для meals_eaten
	snprintf(name, sizeof(name), "%s%d_meals", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
	philo->local_meals_eaten = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->local_meals_eaten == SEM_FAILED)
	{
		printf("Error initializing meals_eaten semaphore for philosopher %d\n", philo->id);
		sem_close(philo->local_last_meal);
		exit(1);
	}
}

// Убираем static, чтобы функция была доступна из других файлов
void	cleanup_local_semaphores(t_philo *philo)
{
	char	name[32];

	sem_close(philo->local_last_meal);
	sem_close(philo->local_meals_eaten);
	
	snprintf(name, sizeof(name), "%s%d", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
	
	snprintf(name, sizeof(name), "%s%d_meals", SEM_PAUSE_NAME, philo->id);
	sem_unlink(name);
}

void	philosopher_routine(t_philo *philo)
{
	pthread_t	death_monitor_thread;
	pthread_t	meal_monitor_thread;

	init_local_semaphore(philo);
	// Создаем потоки мониторинга и ждем начала симуляции
	pthread_create(&death_monitor_thread, NULL, monitor_death, philo);
	pthread_detach(death_monitor_thread);
	if (philo->args->must_eat != -1)
	{
		pthread_create(&meal_monitor_thread, NULL, monitor_meals, philo);
		pthread_detach(meal_monitor_thread);
	}
	
	// Ждем начала симуляции
	sim_start_delay(philo->args->start_time);
	
	// Смещение старта для четных философов, чтобы избежать deadlock
	if (philo->id % 2 == 0)
		usleep(philo->args->t_eat * 500); // Увеличиваем задержку до половины времени приема пищи
		
	while (1)
	{
		// Добавляем небольшую паузу для "мышления" перед попыткой взять вилки
		// Это дает время другим философам завершить свои действия
		usleep(1000);
		
		sem_wait(philo->sems->forks);
		print_action(philo, CYAN "has taken a fork" RESET);
		sem_wait(philo->sems->forks);
		print_action(philo, CYAN "has taken a fork" RESET);
		
		// Обновляем время приема пищи до вывода сообщения, чтобы минимизировать задержку
		sem_wait(philo->local_last_meal);
		philo->last_meal = get_time();
		sem_post(philo->local_last_meal);
		
		// Обновляем счетчик приемов пищи
		sem_wait(philo->local_meals_eaten);
		philo->meals_eaten++;
		sem_post(philo->local_meals_eaten);
		
		print_action(philo, GREEN "is eating" RESET);
		precise_usleep(philo->args->t_eat);
		
		// Готовим сообщение о сне до освобождения вилок для минимизации задержки
		print_action(philo, GRAY "is sleeping" RESET);
		
		// Освобождаем вилки только после печати сообщения
		sem_post(philo->sems->forks);
		sem_post(philo->sems->forks);
		
		precise_usleep(philo->args->t_sleep);
		print_action(philo, DARK_BLUE "is thinking" RESET);
	}
}
