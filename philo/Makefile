CC						=	cc
CFLAGS					=	-Wall -Wextra -Werror -pthread
RM						=	rm -f

NAME					=	mandatory
PHILOSOPHERS			=	philo
MAKEFILE				=	Makefile

PHILO_SRC_DIR			=	sources/

PHILO_INC				=	include/philo.h

PHILO_SRC				=	$(PHILO_SRC_DIR)main.c \
							$(PHILO_SRC_DIR)main_utils.c \
							$(PHILO_SRC_DIR)utils.c \
							$(PHILO_SRC_DIR)philo.c \
							$(PHILO_SRC_DIR)error.c \
							$(PHILO_SRC_DIR)init.c \
							$(PHILO_SRC_DIR)time.c \
							$(PHILO_SRC_DIR)start_end.c \
							$(PHILO_SRC_DIR)actions.c \
							$(PHILO_SRC_DIR)monitor.c

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