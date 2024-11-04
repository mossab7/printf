
NAME = libftprintf.a

SRC = ft_printf.c ft_printf_number_utilities.c \
       ft_printf_handlers.c ft_printf_utilities.c \
	   ft_printf_set_flags.c

all: $(NAME)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)

$(NAME): $(OBJS)
	ar rcs ${NAME} ${OBJS}
bonus: all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
