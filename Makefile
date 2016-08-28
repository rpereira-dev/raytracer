NAME = ./bin/raytracer
LIBDIR = ./C_data_structures

SRCS = $(wildcard ./srcs/*.c)
C_OBJ = $(SRCS:.c=.o)
CC = gcc
FLAGS =

all: $(NAME)

$(LIBDIR):
	git submodule init
	git submodule update

$(NAME): $(C_OBJ)
	$(CC) -o $(NAME) $(C_OBJ)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $< -I includes

clean:
	make -C $(LIBDIR) clean
	rm -rf $(C_OBJ)

fclean: clean
	make -C $(LIBDIR) fclean
	rm -rf $(NAME)

re: fclean all
