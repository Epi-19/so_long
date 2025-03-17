
#ifndef SO_LONG_H

#define	SO_LONG_H

#include "minilibx-linux/mlx.h"
#include "gnl/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define ESC_KEY 65307
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define UP_KEY 65362
#define DOWN_KEY 65364
#define LEFT_KEY 65361
#define RIGHT_KEY 65363

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void    *wall_img;
    void    *floor_img;
	void	*player_img;
	void	*collec_img;
	void	*exit_img;
	void	*exit2_img;
    int     img_size;
	char    **map;
	int		player_x;
	int		player_y;
	int 	exit_x;
	int		exit_y;
	int 	conso;
	int		width;
	int		height;
	int		map_height;
	int 	count;
}			t_data;
//				 READ_MAP.C
int count_lines(const char *filename);
char **read_map(const char *filename);
//				 SO_LONG.C
void load_textures(t_data *data);
int close_window(t_data *data);
void render_map(t_data *data, char **map);
int main(int ac, char ** av);
void    free_textures(t_data *data);
int free_all(t_data *data);
//				CHECK.C
int check_player(int x, int y, char **map, t_data *data);
int check_exit(int x, int y, char **map, t_data *data);
int check_consumables(int x, int y, char **map, t_data *data);
int check_updown(t_data *data);
int check_sides(t_data *data);
//				CHECK_FINITO.C
int check_vmap(char **map_copy, int width, int height);
void flood_fill(char **map, int x, int y, int max_x, int max_y);
int map_check(t_data *data, char **map);
char **get_map_cpy(t_data *data);
void free_map(char **map, int height);
int check_map_elements(int x, int y, char **map, t_data *data);
//				X_Y.C
int get_map_width(char **map, int x);
int get_map_height(char **map);
void init_map_dimensions(char **map, t_data *data);
//				ERROR.C
int test_ber(char *str);

#endif