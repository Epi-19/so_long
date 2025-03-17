#include "so_long.h"

int test_ber(char *str)
{
	int i;

	i = ft_strlen(str);
	if(str[i - 1] == 'r' && str[i - 2] == 'e' && str[i - 3] == 'b')
		return 0;
	printf("Error\nneed map.ber\n");
	return 1;
}