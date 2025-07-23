# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 15:34:37 by adpinhei          #+#    #+#              #
#    Updated: 2025/07/23 17:38:46 by adpinhei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

CC := cc

FLAGS := -Wall -Wextra -Werror -g

LIBFT_PATH := ./libft

LIBFT := $(LIBFT_PATH)/libft.a

BUILD_DIR := build/

#Source files
SRC_FILES := main.c ft_execute.c ft_errclose.c

#Object files
OBJ_FILES := $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean fclean re valgrind norm

all: $(BUILD_DIR) $(LIBFT) $(NAME)

#Compile library
$(LIBFT):
	@make -C $(LIBFT_PATH)

#Create build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $@
	@echo "$(GREEN)Creating$(RESET) $(BUILD_DIR)"

#Compile object files into build
$(BUILD_DIR)/%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(GREEN)Compiling objects$(RESET)"

#Building executable
$(NAME): $(OBJ_FILES)
	@make -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) $(OBJ_FILES) $(LIBFT) -o $@
	@echo "$(YELLOW)Compiled$(RESET) $(NAME)"

norm:
	@norminette -R CheckForbiddenSourceHeader

valgrind: $(NAME)
	@echo "$(YELLOW)Valgrind Report$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
	--track-origins=yes ./$(NAME) infile "grep a" "wc -w" outfile

#Cleanup
clean:
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_PATH) clean
	@echo "$(BLUE)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@echo "$(BLUE)Cleaned executable$(RESET) $(NAME)"

re: fclean all

#Color editing
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

BLUE = \033[1;34m

RESET = \033[0m