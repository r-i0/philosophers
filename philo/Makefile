NAME = philo

SRCS_DIR = ./

SRCS_NAME =	main.c \
			ft_atoi.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			philo_init.c \
			philo_action.c \
			start_dining.c \
			observer.c \
			philo_routine.c \
			join_threads.c \
			free_info.c \
			utils.c

SRCS = ${addprefix ${SRCS_DIR}, ${SRCS_NAME}}

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -pthread -Wall -Wextra -Werror

all: $(NAME)

$(NAME): ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

sanitize: $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=undefined -fsanitize=thread -g -o $(NAME) $(OBJS)

address: $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=undefined -fsanitize=address -o $(NAME) $(OBJS)

.phony: all clean fclean re
