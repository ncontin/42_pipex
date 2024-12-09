# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 11:54:44 by ncontin           #+#    #+#              #
#    Updated: 2024/12/09 13:32:08 by ncontin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = pipex.c \
		libft/libft.a \

CC = gcc
CCFLAGS = -Wall -Wextra -Werror -w
RM = rm -f
NAME = pipex.a

$(NAME):
	make -C libft
	gcc $(CCFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(NAME)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all, clean, fclean, re
