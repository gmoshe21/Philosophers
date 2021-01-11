SRCS            =   main.c\
					ft_putchar_fd.c\
					ft_putstr_fd.c\
					ft_atoi.c\
					ft_putnbr_fd.c\
					ft_strlen.c\
					secondary_functions.c\

OBJS            = $(SRCS:.c=.o)

CFLAGS          =  -Wall -Werror -Wextra

NAME            = philo_three

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc -o $(NAME) $(CFLAGS) $^

clean:			
				rm -f $(OBJS)

%.o: %.c
	gcc $(CFLAGS) -I. -c $< -o $@

fclean:			clean
				rm -f $(NAME) $(LIBFT)

re:				fclean $(NAME)