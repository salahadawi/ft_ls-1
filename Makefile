# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 12:00:35 by hlaineka          #+#    #+#              #
#    Updated: 2020/09/11 10:25:16 by hlaineka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls.c ls_print.c ls_sort.c ls_helpers.c ls_dirlist.c ls_print_helpers.c ls_dirlist2.c

OSRC = $(SRC:.c=.o)

INC_LS = includes/ft_ls.h



LIB_FT = libft/libft.a

all: $(NAME)

$(NAME): fclean
	@gcc -Wall -Wextra -Werror $(LIB_FT) $(SRC) -o $(NAME) -I$(INC_LS)
	@make clean

debug:
	@cd libft && make
	@gcc -Wall -Wextra -Werror $(LIB_FT) $(SRC) -o $(NAME) -I$(INC_LS) -g
	@make clean

lib: fclean
	@cd libft && make
	@make clean

ft:	
	@gcc $(LIB_FT) ft_ls.c -o $(NAME) -I$(INC_LS)

main2: fclean
	@cd libft && make
	@gcc $(LIB_FT) get_started1.c -o test2 -I$(INC_LS)
	@make clean

main3: fclean
	@cd libft && make
	@gcc $(LIB_FT) get_started2.c -o test3 -I$(INC_LS)
	@make clean

clean:
	@rm -f $(OSRC)

fclean: clean
	@rm -f $(NAME)

mclean: fclean

re: fclean all
