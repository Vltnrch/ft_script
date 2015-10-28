# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroche <vroche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/16 10:49:38 by vroche            #+#    #+#              #
#    Updated: 2015/10/28 19:02:32 by vroche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_script

LIB = -ltermcap -L./libft -lft

HDR = -I./libft/includes

FLAGS = -Wall -Wextra -Werror

C =	main.c \
	ft_find_open_pty.c \
	ft_manage.c \
	ft_script.c \
	ft_execve.c \
	ft_check_arg.c

O = $(C:.c=.o)

all: $(NAME)

$(NAME): $(O)
	make -C ./libft
	gcc $(FLAGS) $(HDR) $(LIB) $(O) -o $(NAME)

%.o:%.c
	gcc $(FLAGS) $(HDR) -c $<

clean:
	make -C ./libft clean
	rm -f $(O)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
