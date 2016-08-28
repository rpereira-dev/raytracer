NAME = ./bin/raytracer

LIBC = ./C_data_structures
LIBC_STATIC = $(LIBC)/libcstruct.a

LIBM = ./C_maths
LIBM_STATIC = $(LIBM)/libcmaths.a

LIBS = $(LIBC_STATIC) $(LIBM_STATIC)

SRCS = $(wildcard ./srcs/*.c)
C_OBJ = $(SRCS:.c=.o)
CC = gcc
FLAGS = -Wall -Werror -Wextra
INC = -I includes -I $(LIBC)/includes -I $(LIBM)/includes

all: $(LIBS) $(NAME)

$(LIBS):
	git submodule init
	git submodule update
	make -C $(LIBC)
	make -C $(LIBM)

$(NAME): $(C_OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(C_OBJ) $(LIBS)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $< $(INC)

clean:
	make -C $(LIBC) clean
	make -C $(LIBM) clean
	rm -rf $(C_OBJ)

fclean: clean
	make -C $(LIBC) fclean
	make -C $(LIBM) fclean
	rm -rf $(NAME)

re: fclean all
