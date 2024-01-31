CC = gcc
NAME = phylosophers
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I.
RM = rm -f
RANNAME = ranlib $(NAME)
# UTILS_DIR = ./utils/
SRC = phylosophers.c threads.c utils.c init.c routines.c check_dead.c utils_2.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -pthread $(FLAGS) -g $(OBJ) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(CC) -g  -pthread $(FLAGS) -c $< -o $@

clean:
		$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
		$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re
