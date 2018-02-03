CC	= gcc

RM	= rm -f

CFLAGS	+= -w -Wall -fpic -Iincludes
LDFLAGS	+= -shared

SRC	= $(addprefix src/, \
	malloc.c \
	realloc.c \
	calloc.c \
	free.c \
	show_alloc_mem.c)

OBJ	= $(SRC:.c=.o)

LIBNAME= libmy_malloc.so

NAME	= $(LIBNAME)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBNAME)

re: fclean all

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean fclean re
