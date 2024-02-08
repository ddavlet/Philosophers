CC := cc
NAME := phylo_bonus
FLAGS := -Wall -Werror -Wextra
INCLUDES := -Iinc
RM := rm -f
SRC_DIR := ./src/
SOURCE := philo_bonus.c process.c utils.c init.c routines.c utils_2.c
SRC := $(addprefix $(SRC_DIR), $(SOURCE))
OBJ := $(SRC:.c=.o)
DRAW := ./draw

all: draw $(NAME)

$(NAME): $(OBJ)
	@$(CC) -pthread $(FLAGS) -g $(OBJ) $(INCLUDES) -o $(NAME)
	@bash makedraw.sh

%.o: %.c
	@$(CC) -g -pthread $(FLAGS) -c $< -o $@

clean:
		@$(RM) $(OBJ)
		@$(RM) -r $(DRAW)
		@$(RM) makedraw.sh

fclean: clean
		@$(RM) $(NAME)

re: fclean all

draw:
	@if [ ! -d "$(DRAW)" ]; then\
		git clone git@github.com:ddavlet/draw.git $(DRAW);\
		mv $(DRAW)/makedraw.sh ./makedraw.sh;\
	fi

.PHONY: all clean fclean re
