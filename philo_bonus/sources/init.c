#include "../include/philo_bonus.h"

static int	check_bounds(int value, const char *name)
{
	if (value <= 0 || value > INT_MAX)
	{
		printf(RED "Error:" RESET " %s is out of range. Must be a"
					" positive integer within the range of" RED " int" RESET ".\n",
				name);
		return (1);
	}
	return (0);
}

static bool	init_sems(t_table *table)
{
	unlink_global_sems();
	table->sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT, S_IRUSR | S_IWUSR,
			table->nb_philos);
	if (table->sem_forks == SEM_FAILED)
		return (sem_error_cleanup(table));
	table->sem_write = sem_open(SEM_NAME_WRITE, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (table->sem_write == SEM_FAILED)
		return (sem_error_cleanup(table));
	table->sem_philo_full = sem_open(SEM_NAME_FULL, O_CREAT, S_IRUSR | S_IWUSR,
			table->nb_philos);
	if (table->sem_philo_full == SEM_FAILED)
		return (sem_error_cleanup(table));
	table->sem_philo_dead = sem_open(SEM_NAME_DEAD, O_CREAT, S_IRUSR | S_IWUSR,
			table->nb_philos);
	if (table->sem_philo_dead == SEM_FAILED)
		return (sem_error_cleanup(table));
	table->sem_stop = sem_open(SEM_NAME_STOP, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (table->sem_stop == SEM_FAILED)
		return (sem_error_cleanup(table));
	return (true);
}

static char	*set_local_sem_name(const char *str, unsigned int id)
{
	unsigned int	i;
	unsigned int	digit_count;
	char			*sem_name;
	char			*tmp;

	digit_count = 0;
	i = id;
	while (i)
	{
		digit_count++;
		i /= 10;
	}
	i = ft_strlen(str) + digit_count;
	sem_name = malloc(sizeof *sem_name * (i + 1));
	if (sem_name == NULL)
		return (NULL);
	sem_name[0] = '\0';
	sem_name = ft_strcat(sem_name, str);
	tmp = ft_utoa(id, digit_count);
	sem_name = ft_strcat(sem_name, tmp);
	free(tmp);
	return (sem_name);
}

static bool	set_philo_sem_names(t_philo *philo)
{
	philo->sem_meal_name = set_local_sem_name(SEM_NAME_MEAL, philo->id + 1);
	if (philo->sem_meal_name == NULL)
		return (false);
	free(philo->sem_meal_name);
	return (true);
}

static t_philo	*init_philosophers(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(table->nb_philos * sizeof(t_philo));
	if (!philos)
		return (error_null("%s error: Could not allocate memory.\n", NULL, 0));
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i].table = table;
		philos[i].id = i;
		if (!set_philo_sem_names(&philos[i]))
			return (error_null("%s error: Could not allocate memory.\n", NULL,
					table));
		philos[i].times_ate = 0;
		philos[i].nb_forks_held = 0;
		philos[i].ate_enough = false;
		i++;
	}
	return (philos);
}

t_table	*parse_args(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (error_null("Error: Could not allocate memory.\n", NULL, NULL));
	table->nb_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->must_eat_count = -1;
	if (argv[5])
		table->must_eat_count = ft_atoi(argv[5]);
	if (check_bounds(table->nb_philos, "Philosopher count")
		|| check_bounds(table->time_to_die, "Time to die")
		|| check_bounds(table->time_to_eat, "Time to eat")
		|| check_bounds(table->time_to_sleep, "Time to sleep") || (argv[5]
			&& check_bounds(table->must_eat_count, "Eat count")))
	{
		free(table);
		table = NULL;
		return (NULL);
	}
	table->philo_full_count = 0;
	table->stop_sim = false;
	if (!init_sems(table))
		return (NULL);
	table->philos = init_philosophers(table);
	if (!table->philos)
		return (NULL);
	table->pids = malloc(sizeof *table->pids * table->nb_philos);
	if (!table->pids)
		return (error_null("%s error: Could not allocate memory.\n", NULL, 0));
	return (table);
}
