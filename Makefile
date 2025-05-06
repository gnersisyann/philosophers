CC						=	cc
CFLAGS					=	-Wall -Wextra -Werror -pthread # -g3 -fsanitize=address
RM						=	rm -f

NAME					=	bonus
PHILOSOPHERS			=	philo_bonus
MAKEFILE				=	Makefile

PHILO_SRC_DIR			=	src/

PHILO_INC				=	include/philo_bonus.h

PHILO_SRC				=	$(PHILO_SRC_DIR)main.c \
							$(PHILO_SRC_DIR)utils.c \
							$(PHILO_SRC_DIR)args.c \
							$(PHILO_SRC_DIR)monitor.c \
							$(PHILO_SRC_DIR)parent_monitor.c \
							$(PHILO_SRC_DIR)philosopher.c \
							$(PHILO_SRC_DIR)routine.c \
							$(PHILO_SRC_DIR)semaphores.c

OBJ_DIR					=	obj
PHILO_OBJ				=	$(PHILO_SRC:%.c=$(OBJ_DIR)/%.o)

all:					$(NAME)

$(NAME):				$(PHILOSOPHERS)

$(OBJ_DIR)/%.o:			%.c
						@mkdir -p $(dir $@)
						$(CC) $(CFLAGS) -c $< -o $@

$(PHILOSOPHERS):		$(PHILO_OBJ) $(PHILO_INC) $(MAKEFILE)
						$(CC) $(CFLAGS) $(PHILO_OBJ) $(LDFLAGS) -o $@

clean:
						rm -rf $(OBJ_DIR)

fclean:					clean
						$(RM) $(PHILOSOPHERS)

re:						fclean all

.PHONY:					all clean fclean re