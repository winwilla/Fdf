# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdean <hdean@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 21:28:17 by hdean             #+#    #+#              #
#    Updated: 2019/12/22 18:18:22 by hdean            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC_DIR = ./src/
SRC_LST = main.c read.c point.c fdf.c math.c matrix.c hooks_util_add.c add.c \
			draw.c color.c transform.c vector.c hooks_util.c \
			menu.c key_mouse.c free.c add_color_scheme.c

SRC = $(addprefix $(SRC_DIR), $(SRC_LST))

OBJ = $(SRC:.c=.o)

HEADER_DIR = ./includes/
HEADER_LST = fdf.h
HEADER = $(addprefix $(HEADER_DIR), $(HEADER_LST))

FLAGS = -Wall -Wextra -Werror 

FRAMEFLAGS = -framework OpenGL -framework AppKit

LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a

LIBMLX_DIR = ./minilibx_macos/
LIBMLX = $(LIBMLX_DIR)libmlx.a

INCL = -I $(LIBFT_DIR) -I $(LIBMLX_DIR) -I $(HEADER_DIR)

LIBS = -L $(LIBFT_DIR) -lft -L $(LIBMLX_DIR) -lmlx -lm

RED = \033[0;31m
GREEN = \033[1;32m
SEA = \033[0;36m
NORMAL = \033[00m

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME):$(LIBFT) $(LIBMLX) $(OBJ)
	gcc $(OBJ) -o $(NAME) $(LIBS) $(FRAMEFLAGS)
	@echo "$(GREEN)fdf compiled!$(NORMAL)"

$(OBJ): %.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@ $(INCL) 

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBMLX):
	make -C $(LIBMLX_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(LIBMLX_DIR) clean
	rm -f $(OBJ)
	@echo "$(SEA)fdf clean done$(NORMAL)"

fclean: clean
	rm -f $(LIBFT)
	rm -f $(LIBMLX)
	rm -f $(NAME)
	@echo "$(RED)fdf fclean done$(NORMAL)"

re: fclean all	
