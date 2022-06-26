# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 13:34:10 by mtiesha           #+#    #+#              #
#    Updated: 2022/04/20 13:53:54 by mtiesha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./src/main.c ./src/init.c ./src/monitor_create.c \
        ./src/print_mess.c ./src/utils.c \
		./src/actions.c ./src/validation.c

HEADER = ./include/philosophers.h

OBJ = ${SRCS:.c=.o}

RM = rm -rf

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

${NAME} : ${OBJ} Makefile $(HEADER)
		$(CC) $(OBJ) -lpthread -o $(NAME)
		@echo "\033[32mProject Compiled"

%.o : %.c Makefile ${HEADER}
		$(CC) ${CFLAGS} -I./include -O3 -c $< -o $@

clean :
		@${RM} $(OBJ)

fclean : clean
		@$(RM) $(NAME)
		@clear
		@echo "\033[32mFclean"

re : fclean all

.PHONY : all clean fclean re
