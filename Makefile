# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/07 02:32:29 by zoulhafi          #+#    #+#              #
#    Updated: 2018/11/30 11:06:43 by zoulhafi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

__SRC = srcs/

__INCLUDES = includes

_INCLUDES = libft/includes

_SRC = ft_ls.c ls_advanced.c files_ops.c files_ops2.c files_ops3.c flags.c tools.c

SRC = $(patsubst %.c, $(__SRC)%.c, $(_SRC))

OBJ = $(patsubst %.c, %.o, $(_SRC))

FLAG = -Wall -Wextra -Werror

all: $(NAME)
	
$(NAME) : $(__INCLUDES)/ft_ls.h $(_INCLUDES)/libft.h
	make -C libft re
	gcc $(FLAG) -c $(SRC) -I $(__INCLUDES) -I $(_INCLUDES)
	gcc $(FLAG) -o $(NAME) $(OBJ) -L libft -lft

clean:
	make -C libft clean
	rm -Rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -Rf $(NAME)

re: fclean all
