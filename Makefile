# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbricot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/05 16:51:59 by gbricot           #+#    #+#              #
#    Updated: 2023/08/30 14:19:13 by gbricot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

SRC =	src/main.c \
	src/ft_split.c \
	src/ft_split_2.c \
	src/utils.c \
	src/utils_2.c \
	src/utils_3.c \
	src/utils_4.c \
	src/ft_execute.c \
	src/ft_keyword.c \
	src/ft_trie.c \
	src/ft_replace_var.c \
	src/ft_add_var.c \
	src/ft_set_env.c \
	src/ft_bin.c \
	src/ft_bin_2.c \
	src/ft_bin_3.c \
	src/ft_redirect.c \
	src/ft_redirect_2.c \
	src/ft_redirect_3.c \
	src/ft_redirect_4.c \
	src/ft_pipe.c \
	src/ft_export.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
