#include "../include/philo.h"

int	arg_check(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf(RED "Error:" RESET " Invalid number of arguments.\n\n");
		printf("Usage: " GREEN "./philo" RESET " N T_DIE T_EAT"
				" T_SLEEP [EAT_COUNT]\n\n");
		printf("Arguments:\n");
		printf("  N         - number of threads\n");
		printf("  T_DIE     - time to die (ms)\n");
		printf("  T_EAT     - time to eat (ms)\n");
		printf("  T_SLEEP   - time to sleep (ms)\n");
		printf("  EAT_COUNT - (optional) times each philosopher must eat\n\n");
		printf("Example:\n");
		printf("  " GREEN "./philo 5 800 200 200" RESET "\n");
		printf("  " GREEN "./philo 5 800 200 200 7" RESET "\n\n");
		return (1);
	}
	return (0);
}


