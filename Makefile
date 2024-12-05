# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 11:54:44 by ncontin           #+#    #+#              #
#    Updated: 2024/12/05 12:28:08 by ncontin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = pipex.c

OBJS = $(SRC:.c=.o)
CC = cc
CCFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME = pipex.a

all: $(NAME)

libft:
	@make -C libft/

$(NAME): $(OBJS)
	ar rc $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
