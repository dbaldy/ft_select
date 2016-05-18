# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbaldy <mail>                              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 16:13:53 by dbaldy            #+#    #+#              #
#    Updated: 2016/03/18 16:11:03 by dbaldy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

SRC = main.c list_param.c aux.c ft_select.c cursor_mvt.c read_key.c signal.c\
	  get_nb_row.c get_nb_col.c open_history.c manage_hist.c support.c\
	  suppr_elem.c

LIB1 = libft/

LIB2 = ft_dprintf/

SRC2 = $(addprefix src/, $(SRC))

INCLUDE = -I include/

BIN = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@echo "\x1b[0;01mproceeding"
	@gcc $(FLAGS) -c $(SRC2) $(INCLUDE)
	@make -C libft/ fclean && make -C libft/ && make -C libft/ clean
	@make -C ft_dprintf/ fclean && make -C ft_dprintf/ && make -C ft_dprintf/ clean
	@gcc -o $(NAME) $(BIN) -L $(LIB1) -L $(LIB2) -ltermcap -lft -lftprintf
	@echo "\x1b[32;02m$(NAME) done\x1b[0;m"

clean:
	@/bin/rm -rf $(BIN)
	@echo "\x1b[0;00mclean done"

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo "\x1b[0;01mfclean done"

re: fclean all
