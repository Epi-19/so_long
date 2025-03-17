#include "so_long.h"

int count_lines(const char *filename)
{
    int fd; 
    int count;
    char *line;

    count = 0;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (-1);
    while ((line = get_next_line(fd)))
    {
        count++;
        free(line);
    }
    close(fd);
    return (count);
}
//char **read_map(const char *filename)
//{
//    int fd;
//    int i;
//    int line_count;
//    char **map;
//    char *line;

//    line_count = count_lines(filename);
//    if (line_count <= 0)
//        return (NULL);

//    map = malloc(sizeof(char *) * (line_count + 1));
//    if (!map)
//        return (NULL);

//    fd = open(filename, O_RDONLY);
//    if (fd < 0)
//    {
//        free(map); // Libérer la map en cas d'échec
//        return (printf("Impossible de lire le fichier\n"), NULL);
//    }

//    i = 0;
//    while ((line = get_next_line(fd)))
//    {
//        map[i] = line; // On stocke la ligne
//        if (!map[i])  // Vérification de l’allocation
//        {
//            while (i > 0) // Libérer toutes les lignes déjà allouées
//                free(map[--i]);
//            free(map);
//            close(fd);
//            return (NULL);
//        }
//        i++;
//    }
//    map[i] = NULL;
//    close(fd);
//    return (map);
//}

char **read_map(const char *filename)
{
    int fd;
    int i;
    int line_count;
    char **map;
    char *line;

    line_count = count_lines(filename);
    if (line_count <= 0)
        return (printf("Error\nEmpty map\n"),NULL);
    map = malloc(sizeof(char *) * (line_count + 1));
    if (!map)
        return (NULL);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (printf("impossible de lire le fichier\n"), NULL);
    i = 0;
    line = get_next_line(fd);
    while(line)
    {
        map[i++] = line;
        line = get_next_line(fd);
    }
    map[i] = NULL;
    close(fd);
    return (map);
}
