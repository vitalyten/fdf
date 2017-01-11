# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/30 15:32:15 by vtenigin          #+#    #+#              #
#    Updated: 2016/11/30 15:44:37 by vtenigin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FILES = main.c makemap.c draw.c

OBJECTS = $(FILES:.c=.o)

CFLAG = -Wall -Werror -Wextra

ATTACH = -L libft/ -lft -L minilibx/ -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	make -C libft/
	make -C minilibx/
	gcc $(CFLAG) -o $(NAME) $(FILES) $(ATTACH)

clean:
	/bin/rm -f $(OBJECTS)
	make -C libft/ clean
	make -C minilibx/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re: fclean all