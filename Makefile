# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 13:52:45 by mdsiurds          #+#    #+#              #
#    Updated: 2025/03/18 14:23:42 by mdsiurds         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRC = pipex.c	children_do.c	find_paths.c	extract_args.c \
clear_free_exit.c	open.c	strjoin_three.c
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = ./temp
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFT_DIR = ./libft
LIBFT_LIB = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
		@echo "Compiling Pipex..."
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME)
		@echo "Pipex successfully compiled.\n"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_LIB): 
	@echo	"Compiling libft..."
	@make -C $(LIBFT_DIR) >/dev/null 2>&1
	@echo "Libft successfully compiled."
clean:
	@echo	"Cleaning..."
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@echo	"Successfully cleaned !\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	
re: fclean all

.PHONY: all clean fclean re 