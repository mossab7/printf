.SILENT:
CC = gcc
CFLAGS = -Werror -Wall -Wextra
NAME = libftprintf.a
HEADER = libftprintf.h

SRCS = ft_printf.c ft_printf_number_utilities.c \
       ft_printf_handlers.c ft_printf_utilities.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
