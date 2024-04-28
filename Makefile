CC = cc

CFLAGS = -g -pthread #-Wall -Wextra -Werror 

SRC = src/main.c src/utils.c src/philo.c

OBJ = $(SRC:%.c=%.o)

NAME = philo

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME) : $(OBJ) $(OBJ_BONUS) 
	$(CC) $(OBJ) $(OBJ_BONUS) $(INCLUDE) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ) $(OBJ_BONUS)


fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re