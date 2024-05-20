# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahuge <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 12:29:17 by ahuge             #+#    #+#              #
#    Updated: 2024/05/20 12:29:22 by ahuge            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g -pthread -Wall -Wextra -Werror

SRC = 	src/main_bonus.c src/check_values_bonus.c src/init_philo_bonus.c \
		src/philosophers_bonus.c src/routine_philo_bonus.c src/monitoring_bonus.c \
		src/utils_1_bonus.c src/utils_2_bonus.c

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
