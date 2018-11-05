#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 11:04:04 by dmendelo          #+#    #+#              #
#    Updated: 2018/11/05 13:26:40 by dmendelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
LIBFT = libft/libft.a
MLX = mlx/libmlx.a

SRC_DIR = src
SRC = wolf3d

INC = -I inc -I libft/ -I mlx/
FRAMEWORK = -framework OpenGl -framework AppKit

OBJ_DIR = $(SRC_DIR)/obj
OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ) 
		@printf "\nCompiling wolf3d\n"
		@gcc $(CFLAGS) $(LIBFT) $(MLX) $(OBJ) $(FRAMEWORK) -o $(NAME)
		@echo "Done!\n"

$(LIBFT):
		@printf "\nCompiling Libft\n"
		@make -C libft
		@echo "Done!\n"

$(MLX):
		@printf "\nCompiling MLX\n"
		@make -C mlx
		@echo "Done!\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@echo "Compiling...\n"
		@gcc $(CFLAGS) $(INC) -c $< -o $@

clean:
		@rm -rf $(OBJ_DIR)
		@make -C libft clean
		@make -C mlx clean
		@echo "clleeeeaaned\n"

fclean: clean
		@make -C libft fclean
		@make -C mlx fclean
		@rm -f $(NAME)
		@echo "Executable D E S T R O Y E D\n"

re: fclean all
