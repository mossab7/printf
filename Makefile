
NAME = libftprintf.a

SRC = ft_printf.c ft_printf_number_utilities.c \
       ft_printf_handlers.c ft_printf_utilities.c \
	   ft_printf_set_flags.c

BONUSSRC = ft_printf_handlers_bonus.c \
			ft_printf_bonus.c ft_printf_number_utilities_bonus.c\
 			ft_printf_set_flags_bonus.c ft_printf_utilities_bonus.c

all: $(NAME)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)
BONUSOBJS = $(BONUSSRC:.c=.o)

$(NAME): $(OBJS)
	ar rcs ${NAME} ${OBJS}

bonus: $(BONUSOBJS)
	ar rcs ${NAME} ${BONUSOBJS}

clean:
	rm -f $(OBJS) $(BONUSOBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all bonus clean fclean re
