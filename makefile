# Nom de l'exécutable
NAME = so_long

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
#-fsanitize=address -g

# Fichiers sources (ajoute tes fichiers .c ici)
SRCS = so_long.c read_map.c gnl/get_next_line.c gnl/get_next_line_utils.c check.c check_finito.c x_y.c error.c

# Générer les fichiers objets
OBJS = $(SRCS:.c=.o)

# MiniLibX
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd

# Commandes de compilation
all: $(NAME)

$(NAME): $(OBJS) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)

# Compiler les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

# Compilation de MiniLibX
$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

# Nettoyer les fichiers objets
clean:
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean

# Nettoyer tout (exécutable + objets)
fclean: clean
	rm -f $(NAME)

# Recompiler entièrement
re: fclean all

# Éviter les conflits avec des fichiers du même nom
.PHONY: all clean fclean re
