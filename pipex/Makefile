# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrisor <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/18 15:31:49 by patrisor          #+#    #+#              #
#    Updated: 2019/08/18 15:53:36 by patrisor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_PATH = src/
LIB_PATH = libft/
INC_PATH = includes/
OBJ_PATH = obj/

C = clang
WFLAGS = -Wall -Werror -Wextra
IFLAGS = -I $(INC_PATH) -I $(LIB_PATH)

LIB = $(LIB_PATH)libft.a
FILES = main 

SRCS = $(addprefix $(SRC_PATH), $(addsuffix .c, $(FILES)))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(C) $(WFLAGS) $(IFLAGS) $(OBJ) $(LIB) -o $(NAME)

$(LIB):
	make -C $(LIB_PATH)

$(OBJ): | $(OBJ_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)$(SRC_PATH)

$(OBJ_PATH)%.o: %.c
	$(C) $(WFLAGS) $(IFLAGS) -c $< -o $@

clean:
	make clean -C $(LIB_PATH)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIB_PATH)
	rm -f $(NAME)
	rm -rf $(OBJ_PATH)

re: fclean all

mclean:
	rm -f $(OBJ)

mfclean:
	rm -f $(NAME)
	rm -rf $(OBJ_PATH)

mre: mfclean all

.PHONY: all clean fclean re
