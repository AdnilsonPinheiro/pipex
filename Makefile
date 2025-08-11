# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 15:34:37 by adpinhei          #+#    #+#              #
#    Updated: 2025/08/11 16:38:45 by adpinhei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

BONUS_NAME := pipex_bonus

CC := cc

FLAGS := -Wall -Wextra -Werror -g

LIBFT_PATH := ./libft

LIBFT := $(LIBFT_PATH)/libft.a

BUILD_DIR := build/

#Source files
SRC_FILES := mandatory/main.c utils.c mandatory/error.c

#Bonus files
BONUS_SRCS := bonus/main.c bonus/error_bonus.c utils.c bonus/utils_bonus.c\
			bonus/ft_here.c bonus/ft_struct.c\
			libft/get_next_line.c

#Object files
OBJ_FILES := $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

BONUS_OBJ := $(BONUS_SRCS:%.c=$(BUILD_DIR)/%.o)

.PHONY: all bonus clean fclean re valgrind norm

all: $(BUILD_DIR) $(LIBFT) $(NAME)

bonus: $(BUILD_DIR) $(LIBFT) $(BONUS_NAME)

#Compile library
$(LIBFT):
	@make -C $(LIBFT_PATH)

#Create build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $@
	@echo "$(GREEN)Creating$(RESET) $(BUILD_DIR)"
	@echo "$(GREEN)Compiled objects$(RESET)"

#Compile object files into build
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

#Building executable
$(NAME): $(OBJ_FILES)
	@make -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) $(OBJ_FILES) $(LIBFT) -o $@
	@echo "$(YELLOW)Compiled$(RESET) $(NAME)"

$(BONUS_NAME): $(BONUS_OBJ)
	@make -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) $(BONUS_OBJ) $(LIBFT) -o $@
	@echo "$(YELLOW)Compiled bonus executable$(RESET) $(BONUS_NAME)"

norm:
	@norminette -R CheckForbiddenSourceHeader

valgrind: $(NAME)
	@echo "$(YELLOW)Valgrind Report$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
	--track-origins=yes --trace-children=yes \
	./$(NAME) infile wc "cat -e" outfile

bonusvalgrind: $(BONUS_NAME)
	@echo "$(YELLOW)Valgrind Report$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
	--track-origins=yes --trace-children=yes \
	./$(BONUS_NAME) Makefile "cat -e" "cat -e" outfile

gdb: $(NAME)
	@gdb --tui --args ./$(NAME) Makefile "cat -e" "cat -e" outfile

bonusgdb:
	@gdb --tui --args ./$(BONUS_NAME) Makefile "cat -e" "cat -e" "cat -e" "cat -e" outfile

#Cleanup
clean:
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_PATH) clean
	@echo "$(BLUE)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	@make -C $(LIBFT_PATH) fclean
	@echo "$(BLUE)Cleaned executables$(RESET) $(NAME) $(BONUS_NAME)"

re: fclean all

#Color editing
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

BLUE = \033[1;34m

RESET = \033[0m