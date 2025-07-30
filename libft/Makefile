NAME := libft.a

INC := libft.h

SRCS := ft_isalnum.c ft_isprint.c ft_memmove.c ft_strdup.c ft_strlen.c ft_strtrim.c \
		ft_atoi.c ft_isalpha.c ft_memchr.c ft_memset.c ft_strjoin.c ft_strncmp.c \
		ft_substr.c ft_bzero.c ft_isascii.c ft_memcmp.c ft_split.c ft_strlcat.c \
		ft_strnstr.c ft_tolower.c ft_calloc.c ft_isdigit.c ft_memcpy.c ft_strchr.c \
		ft_strlcpy.c ft_strrchr.c ft_toupper.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		get_next_line.c get_next_line_utils.c

BONUS_SRCS :=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
				ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

CC := cc

FLAGS = -Wall -Wextra -Werror 

OBJS = $(SRCS:%.c=%.o)

BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)

all: $(NAME)
# c: creates a library, if it didn't exist
# r: replace the old files within an existing library with the new ones
# s: index ("sort") the library, so it is easier to access the functions
$(NAME): $(OBJS)
	@ar crs $(NAME) $(OBJS)
	@echo "$(GREEN)Compiling static library$(RESET) $(NAME)"
# -c makes cc produce a .o file for each source file
$(OBJS):
	@$(CC) $(FLAGS) -c $(SRCS)

bonus: $(NAME) $(BONUS_OBJS)
	@ar rcs $(NAME) $(BONUS_OBJS)

$(BONUS_OBJS):
	@$(CC) $(FLAGS) -c $(BONUS_SRCS)

clean:
	@rm -rf $(OBJS) $(BONUS_OBJS)
	@echo "$(BLUE)Cleaned library objects$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BLUE)Deleted static library$(RESET) $(NAME)"

re: fclean all

RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

BLUE = \033[1;34m

RESET = \033[0m