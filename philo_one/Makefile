SRC		=	check.c ft_annexe.c main.c philo.c print.c

CC		=	gcc -pthread -Wall -Werror -Wextra

OBJ		=	$(SRC:.c=.o)

NAME	=	philo_two

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

1		:	$(NAME)
			./$(NAME) 4 410 200 200

die		:	$(NAME)
			./$(NAME) 4 310 200 100

5		:	$(NAME)
			./$(NAME) 5 800 200 200 5

4		:	$(NAME)
			./$(NAME) 5 800 200 200

2		:	$(NAME)
			./$(NAME) 2 5 100 100

clean	:	
			rm -rf $(OBJ)

fclean	:	clean 
			rm -rf $(NAME)

re		:	clean all
