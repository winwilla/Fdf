#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

GREEN = \033[1;32m
SEA = \033[0;36m
NORMAL = \033[00m

all: $(NOM)

$(NOM):	$(OBJ)
	ar -r $(NOM) $(OBJ)
	ranlib $(NOM)
	@echo "$(GREEN)minilibx compiled!$(NORMAL)"

clean:
	rm -f $(NOM) $(OBJ) *~
	rm -f mlx_app
	@echo "$(SEA)minilibx clean done$(NORMAL)"

re: clean all
