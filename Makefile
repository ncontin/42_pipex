# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/10 19:13:12 by ncontin           #+#    #+#              #
#    Updated: 2025/02/10 17:33:57 by ncontin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	pipex.c\
		errors.c\
		parser.c\
		children.c\
		libft/libft.a\

$(NAME) :
	make all -C libft
	cc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	make clean -C libft

re : fclean all

.PHONY: all clean fclean re
