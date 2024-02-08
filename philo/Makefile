CC := cc
NAME := philo
FLAGS := -Wall -Werror -Wextra
INCLUDES := -Iinc
RM := rm -f
SRC_DIR := ./src/
SOURCE := philo.c threads.c utils.c init.c routines.c check_dead.c utils_2.c terminate.c
SRC := $(addprefix $(SRC_DIR), $(SOURCE))
OBJ := $(SRC:.c=.o)
DRAW := ./draw

all: draw $(NAME)

$(NAME): $(OBJ)
	@$(CC) -pthread $(FLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@bash makedraw.sh

%.o: %.c
	@$(CC) -pthread $(FLAGS) -c $< -o $@

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
