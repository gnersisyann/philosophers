#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"
# define GRAY "\033[1;30m"
# define DARK_GREEN "\033[0;32m"
# define DARK_BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define BLUE "\033[0;34m"

#define SEM_FORKS_NAME      "/sem_forks"
#define SEM_PRINT_NAME      "/sem_print"
#define SEM_MEAL_NAME       "/sem_meal"
#define SEM_DEAD_NAME       "/sem_dead"
#define SEM_PAUSE_NAME       "/sem_"

typedef struct s_args {
    int     n_philo;
    long    t_die;
    long    t_eat;
    long    t_sleep;
    int     must_eat;
    long    start_time;
} t_args;

typedef struct s_semaphores {
    sem_t *forks;
    sem_t *print;
    sem_t *meal_check;
    sem_t *dead_signal;
} t_semaphores;

typedef struct s_philo {
    int             id;
    pid_t           pid;
    long            last_meal;
    int             meals_eaten;
    pthread_t       death_monitor;
    pthread_t       eat_monitor;
    t_args         *args;
    t_semaphores   *sems;
	sem_t *local_last_meal;
	sem_t *local_meals_eaten;
} t_philo;

// === utils.c ===
long    get_time(void);// +
void    precise_usleep(long time); // +
void    print_action(t_philo *philo, const char *action); // +
int		ft_atoi(const char *str); // +
void	sim_start_delay(time_t start_time);


// === args.c ===
int     parse_args(int argc, char **argv, t_args *args);// +

// === semaphores.c ===
int     init_semaphores(t_semaphores *sems, int n_philo); // +
void    close_semaphores(t_semaphores *sems);// +
void    unlink_semaphores(void);// +

// === philosopher.c ===
void    run_philosophers(t_args *args, t_semaphores *sems); // +

// === routine.c ===
void    philosopher_routine(t_philo *philo); // +

// === monitor.c ===
void    *monitor_death(void *arg); // +
void    *monitor_meals(void *arg); // +

// === parent_monitor.c ===
void    *monitor_all_deaths(void *arg); // +
void    *monitor_all_meals(void *arg); // +

// === cleanup.c ===
void    terminate_all(t_philo *philos, int n);
void	cleanup_local_semaphores(t_philo *philo);

#endif
