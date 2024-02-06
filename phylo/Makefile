CC := cc
NAME := phylo
FLAGS := -Wall -Werror -Wextra
INCLUDES := -Iinc
RM := rm -f
SRC_DIR := ./src/
SOURCE := phylo.c threads.c utils.c init.c routines.c check_dead.c utils_2.c terminate.c
SRC := $(addprefix $(SRC_DIR), $(SOURCE))
OBJ := $(SRC:.c=.o)

all: draw $(NAME)

$(NAME): $(OBJ)
	@$(CC) -pthread $(FLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@bash makedraw

%.o: %.c
	@$(CC) -pthread $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

draw:
	@if [ ! -d "$(DRAW)" ]; then\
		git clone git@github.com:ddavlet/draw.git $(DRAW);\
		mv $(DRAW)/makedraw.sh ./makedraw.sh;\
	fi

.PHONY: all clean fclean re
