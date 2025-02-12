# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/10 19:13:12 by ncontin           #+#    #+#              #
#    Updated: 2025/02/12 11:39:57 by ncontin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Werror -Wall -Wextra
RM = rm -rf
OBJ_DIR = obj
INCLUDES = -I./libft
SRCS = pipex.c errors.c parser.c children.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
LIBFT = libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	make all -C libft
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(OBJ_DIR)
	make clean -C libft

re : fclean all

.PHONY: all clean fclean re
