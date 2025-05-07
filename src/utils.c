#include "../include/philo_bonus.h"
#include <string.h>

void	sim_start_delay(time_t start_time)
{
	while (get_time() < start_time)
		continue ;
}

void	print_action(t_philo *philo, const char *action)
{
	long	timestamp;

	sem_wait(philo->sems->print);
	timestamp = get_time() - philo->args->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, action);
	if (strcmp(action, RED "died" RESET) != 0)
		sem_post(philo->sems->print);
}

void	precise_usleep(long time_in_ms)
{
	long	start;
	long	elapsed;
	long	remain;

	start = get_time();
	// Спать большими кусками, пока не останется ~2мс
	while ((elapsed = get_time() - start) < time_in_ms)
	{
		remain = time_in_ms - elapsed;
		if (remain > 2)
		{
			// Спим только 80% оставшегося времени для компенсации неточности usleep
			usleep((remain > 10 ? remain - 2 : remain * 800) / 1000);
		}
		else
		{
			// Активное ожидание для последних 2мс для повышения точности
			while (get_time() - start < time_in_ms)
				;
			break;
		}
	}
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res * sign);
}
