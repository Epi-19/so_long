#include "so_long.h"

int check_player(int x, int y, char **map, t_data *data)
{
    int found_p;
    int j;
    int i;

    found_p = 0;
    i = 0;
    while (i < y)
    {
        j = 0;
        while (j < x)
        {
            if (map[i][j] == 'P')
            {
                found_p++;
                data->player_x = j;
                data->player_y = i;
            }
            j++;
        }
        i++;
    }  
    return (found_p == 1);
}

int check_exit(int x, int y, char **map, t_data *data)
{
    int found_e;
    int i;
    int j;

    found_e = 0;
    i = 0;
    while (i < y)
    {
        j = 0;
        while (j < x)
        {
            if (map[i][j] == 'E')
            {
                found_e++;
                data->exit_x = j;
                data->exit_y = i;
            }
            j++;
        }
        i++;
    }
    return (found_e == 1);
}

int check_consumables(int x, int y, char **map, t_data *data)
{
    int conso_count;
    int i;
	int j;

    conso_count = 0;
    i = 0;
    while (i < y)
    {
        j = 0;
        while (j < x)
        {
            if (map[i][j] == 'C')
                conso_count++;
            j++;
        }
        i++;
    }
    data->conso = conso_count;
    return (conso_count > 0);
}

int check_updown(t_data *data)
{
    char **map;
    int j;

    map = get_map_cpy(data);
    if (!map)
        return (0);
    j = 0;
    while (j < data->width)
    {
        if (map[0][j] != '1')
            return(free_map(map, data->height), 0);
        j++;
    }
    j = 0;
    while (j < data->width)
    {
        if (map[data->height - 1][j] != '1')
            return(free_map(map, data->height), 0);
        j++;
    }
    free_map(map, data->height);
    return (1);
}
int check_sides(t_data *data)
{
    char **map;
    int i;

    map = get_map_cpy(data);
    if (!map)
        return (0);
    i = 0;
    while (i < data->height)
    {
        if (map[i][0] != '1' || map[i][data->width - 1] != '1')
            return(free_map(map, data->height), 0);
        i++;
    }
    free_map(map, data->height);
    return (1);
}


