CC = cc

CFLAGS = -g -pthread #-Wall -Wextra -Werror #-fsanitize=thread 

SRC = 	src/main.c src/check_values.c src/init_philo.c src/philosophers.c \
		src/routine_philo.c src/monitoring.c src/utils_1.c src/utils_2.c

OBJ = $(SRC:%.c=%.o)

NAME = philo

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(INCLUDE) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re