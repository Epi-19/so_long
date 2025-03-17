#include "so_long.h"

int	check_vmap(char **map_copy, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map_copy[i][j] == 'C' || map_copy[i][j] == 'E')
			{
				printf("Error\nmap blocked\n");
				free_map(map_copy, height);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
int	check_idk(char **map_copy, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
            if(map_copy[i][j] != '0' && map_copy[i][j] != '1' &&
            map_copy[i][j] != 'C' && map_copy[i][j] != 'E' &&
            map_copy[i][j] != 'P')
            {
                printf("Error\nWrong letters in map\n");
                free_map(map_copy, height);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}
int check_rectangular(char **map_copy, int width, int height) 
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			int bob = get_map_width(map_copy, i);
            if(bob != width)
            {
                printf("Error\nMap not rectangular\n");
                free_map(map_copy, height);
                return (0);
            }
            j++;
        }
        i++;
    }
	return 1;
}
void	flood_fill(char **map, int x, int y, int max_x, int max_y)
{
	if (x < 0 || x >= max_x || y < 0 || y >= max_y || map[y][x] == '1'
		|| map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, max_x, max_y);
	flood_fill(map, x - 1, y, max_x, max_y);
	flood_fill(map, x, y + 1, max_x, max_y);
	flood_fill(map, x, y - 1, max_x, max_y);
}
int	map_check(t_data *data, char **map)
{
	char	**map_copy;

	init_map_dimensions(map, data);
	map_copy = get_map_cpy(data);
    if (!check_rectangular(map, data->width, data->height))
		return (free_all(data), 0);
	if (!check_map_elements(data->width, data->height, map, data))
		return (free_map(map_copy, data->height), free_all(data), 0);
    if (!check_idk(map_copy, data->width, data->height))
		return (free_all(data), 0);
	flood_fill(map_copy, data->player_x, data->player_y, data->width,
		data->height);
	if (!check_vmap(map_copy, data->width, data->height))
		return (free_all(data), 0);
	free_map(map_copy, data->height);
	return (1);
}

char	**get_map_cpy(t_data *data)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(data->height * sizeof(char *));
	i = 0;
	while (i < data->height)
	{
		map_copy[i] = ft_strdup(data->map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	return (map_copy);
}

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}
int	check_map_elements(int x, int y, char **map, t_data *data)
{
	if (check_player(x, y, map, data) != 1)
		return (printf("Error\nnerror player\n"), 0);
	if (check_exit(x, y, map, data) != 1)
		return (printf("Error\nerror exit\n"), 0);
	if (check_consumables(x, y, map, data) != 1)
		return (printf("Error\nerror cosno\n"), 0);
	if (check_sides(data) != 1)
		return (printf("Error\error sides\n"), 0);
	if (check_updown(data) != 1)
		return (printf("Error\nerror updown\n"), 0);
	return (1);
}
