#include "minilibx-linux/mlx.h"
#include "so_long.h"

void	free_mlx(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
}
void	move_player(t_data *data, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_y = data->player_y + dy;
	new_x = data->player_x + dx;
	if (data->map[new_y][new_x] == '1')
		return ;
	if (data->map[new_y][new_x] == 'C')
		data->conso--;
	if (data->map[new_y][new_x] == 'E' && data->conso == 0)
	{
		printf("Bravo ! Vous avez gagné !\n");
		free_all(data);
	}
	if (data->map[data->player_y][data->player_x] != 'E')
		data->map[data->player_y][data->player_x] = '0';
	if (data->map[new_y][new_x] != 'E')
		data->map[new_y][new_x] = 'P';
	data->player_x = new_x;
	data->player_y = new_y;
	render_map(data, data->map);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		free_all(data);
	if (keycode == UP_KEY || keycode == W_KEY)
		move_player(data, 0, -1);
	if (keycode == DOWN_KEY || keycode == S_KEY)
		move_player(data, 0, 1);
	if (keycode == LEFT_KEY || keycode == A_KEY)
		move_player(data, -1, 0);
	if (keycode == RIGHT_KEY || keycode == D_KEY)
		move_player(data, 1, 0);
	
	return (0);
}

void	load_textures(t_data *data)
{
	int width, height;
	data->img_size = 64;
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "texture/wall.xpm",
			&width, &height);
	data->floor_img = mlx_xpm_file_to_image(data->mlx, "texture/floor.xpm",
			&width, &height);
	data->player_img = mlx_xpm_file_to_image(data->mlx, "texture/tete0.xpm",
			&width, &height);
	data->exit_img = mlx_xpm_file_to_image(data->mlx, "texture/porte_ferme.xpm",
			&width, &height);
	data->exit2_img = mlx_xpm_file_to_image(data->mlx, "texture/porte_ouverte.xpm",
			&width, &height);
	data->collec_img = mlx_xpm_file_to_image(data->mlx, "texture/pelote.xpm",
			&width, &height);
	if (!data->wall_img || !data->floor_img || !data->player_img || !data->exit2_img || !data->exit_img || !data->collec_img)
	{
		write(2, "Erreur: Impossible de charger les textures\n", 43);
		exit(1);
	}
}

void	free_textures(t_data *data)
{
	if (!data)
		return ;
	if (data->wall_img)
		mlx_destroy_image(data->mlx, data->wall_img);
	if (data->floor_img)
		mlx_destroy_image(data->mlx, data->floor_img);
	if (data->player_img)
		mlx_destroy_image(data->mlx, data->player_img);
	if (data->exit_img)
		mlx_destroy_image(data->mlx, data->exit_img);
	if (data->exit2_img)
		mlx_destroy_image(data->mlx, data->exit2_img);
	if (data->collec_img)
		mlx_destroy_image(data->mlx, data->collec_img);
}
int	free_all(t_data *data)
{
	if (!data)
		return (0);
	free_textures(data);
	if (data->map)
	{
		free_map(data->map, data->map_height);
		data->map = NULL;
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
    {
        mlx_loop_end(data->mlx);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        data->mlx = NULL;
    }
	free(data);
    data = NULL;
	exit(0);
	return (125);
}
void 	display_img(t_data *data, char **map, int x, int y)
{
	if (map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wall_img, x
					* data->img_size, y * data->img_size);
			else if (map[y][x] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->floor_img, x
					* data->img_size, y * data->img_size);
			else if (map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx, data->win, data->player_img,
					x * data->img_size, y * data->img_size);
			else if (map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->collec_img,
					x * data->img_size, y * data->img_size);
			else if (map[y][x] == 'E' && data->conso != 0)
				mlx_put_image_to_window(data->mlx, data->win, data->exit_img, x
					* data->img_size, y * data->img_size);
			else
				mlx_put_image_to_window(data->mlx, data->win, data->exit2_img, x
					* data->img_size, y * data->img_size);
}

void	render_map(t_data *data, char **map)
{
	int x;
	int y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			display_img(data, map, x, y);
			x++;
		}
		y++;
	}
	printf("%d\n", data->count);
	if (data->count == INT_MAX)
	{
		printf("Error\nTrop de move\n");
		free_all(data);
	}
	data->count++;
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (printf("Error\nargs != 2\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error\nmalloc a échoué\n"), 1);
	*data = (t_data){0};
	data->count = 2147483646;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (printf("Error\nErreur: mlx_init() a échoué\n"), 1);
	load_textures(data);
	if (test_ber(av[1]) == 1)
		return (0);
	data->map = read_map(av[1]);
	if (!data->map)
        free_all(data);
	if (!map_check(data, data->map))
        free_all(data);    
	data->win = mlx_new_window(data->mlx, data->width * 64, data->height * 64,
			"So_long");
	if (!data->win)
		return (printf("Erreur: mlx_new_window() a échoué\n"), 1);
	render_map(data, data->map);
	mlx_key_hook(data->win, handle_keypress, data);
	mlx_hook(data->win, 17, 0, free_all, data);
	mlx_loop(data->mlx);
	return (0);
}
