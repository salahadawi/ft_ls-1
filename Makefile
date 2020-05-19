# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helvi <helvi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 12:00:35 by hlaineka          #+#    #+#              #
#    Updated: 2020/05/19 10:00:36 by helvi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_ls.c

OSRC = $(SRC:.c=.o)

INC_LS = includes/ft_ls.h

all: $(NAME)

$(NAME): fclean
	cd libft && make re
	cd printf && make re
	ar rc $(NAME) $(LIB_LIBFT) $(LIB_PRINTF)
	make clean

clean:
	rm -f $(OSRC)

fclean: clean
	rm -f $(NAME)

mclean: fclean

re: fclean all
