CC := cc
NAME := phylo
FLAGS := -Wall -Werror -Wextra
INCLUDES := -Iinc
RM := rm -f
SRC_DIR := ./src/
SOURCE := phylo.c threads.c utils.c init.c routines.c check_dead.c utils_2.c
SRC := $(addprefix $(SRC_DIR), $(SOURCE))
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -pthread $(FLAGS) -g $(OBJ) $(INCLUDES) -o $(NAME)
	@bash makedraw

%.o: %.c
	@$(CC) -g -pthread $(FLAGS) -c $< -o $@

clean:
		@$(RM) $(OBJ)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
