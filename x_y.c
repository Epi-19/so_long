#include "so_long.h"

int get_map_width(char **map, int x)
{
    int width;

    width = 0;
    while (map[x][width] && map[x][width] != '\n')
        width++;
    return (width);
}

int get_map_height(char **map)
{
    int height;
    
	height = 0;
    while (map[height])
	    height++;
    return height;
}
void init_map_dimensions(char **map, t_data *data)
{
    data->width = get_map_width(map, 0);
    data->height = get_map_height(map);
    data->map_height = data->height;
    if(data->width <= 0 || data->width > 60)
    {
        printf("Error\nMap to big\n");
        free_all(data);
        exit(1);
    }
    if(data->height <= 0 || data->height > 30)
    {
        printf("Error\nMap to big\n");
        free_all(data);
        exit(1);
    }
}

