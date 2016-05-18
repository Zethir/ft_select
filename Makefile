# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboussau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/24 14:55:22 by cboussau          #+#    #+#              #
#    Updated: 2016/05/18 16:25:26 by cboussau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select 

SRC = main.c lst_function.c termios.c termcap.c termcaparrow.c termcaprint.c\
	  deal_with_size.c signal.c tools.c

OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a -ltermcap
FLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

all : $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean $(NAME)

.PHONY : all clean fclean re
