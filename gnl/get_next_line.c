/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodebacq <rodebacq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:23:51 by Rodebacq          #+#    #+#             */
/*   Updated: 2025/03/16 16:32:13 by rodebacq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_cut_str(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!res)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (free(str), res);
}

char	*ft_read_to_left_str(int fd, char *str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (ft_strchr(str, '\n') == NULL && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		str = ft_strjoin_free(str, buff);
		if (!str)
			return (free(buff), NULL);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	if (!left_str)
	{
		left_str = ft_strdup("");
		if (!left_str)
			return (NULL);
	}
	left_str = ft_read_to_left_str(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_get_line(left_str);
	if (!line)
	{
		free(left_str);
		left_str = NULL;
		return (NULL);
	}
	left_str = ft_cut_str(left_str);
	return (line);
}
//#include <fcntl.h>
//#include <stdio.h>
//#include <stdlib.h>

//int	main(void)
//{
//	int fd;
//	char *line;
//	// Ouvre le fichier test.txt en mode lecture
//	fd = open("test.txt", O_RDONLY);
//	if (fd < 0)
//	{
//		perror("Error opening file");
//		return (EXIT_FAILURE);
//	}

//	// Appelle get_next_line en boucle pour lire toutes les lignes
//	while ((line = get_next_line(fd)) != NULL)
//	{
//		printf("%s", line);
//		free(line); // Libère la mémoire allouée pour chaque ligne
//	}

//	// Ferme le fichier
//	close(fd);
//	if (line == NULL)
//		return (17);
//	return (EXIT_SUCCESS);
//}