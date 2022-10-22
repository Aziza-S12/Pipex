# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asadritd <asadritd@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 18:04:59 by asadritd          #+#    #+#              #
#    Updated: 2022/10/22 18:04:21 by asadritd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_DIR = Source

SRC = bonus_mfunc.c bonus_utils.c\

OBJ = $(SRC: *.c=*.o)

LIB_DIR = libft

CC = gcc

MAKE = make

FLAGS =  -Werror -Wextra -Wall

AR = ar cr

all: $(NAME)

LIBRARY:
	make -C libft

$(NAME): LIBRARY $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) $(LIB_DIR)/libft.a -o pipex

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C libft


fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a
	rm -f pipex

re: fclean all

.PHONY: all fclean clean re
