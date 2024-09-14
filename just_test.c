#include <stdio.h>
#include <fcntl.h>
#include <limits.h>

#include "get_next_line.h"

int main ()
{
	int	fd;
	char	*line;

	printf("---------------------------\nBUFFER_SIZE\t=\t%llu\n---------------------------\n", (unsigned long long int)BUFFER_SIZE);
	
	fd = open("tests/no_new_line.txt", O_RDONLY);
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf(">>>%s<<<", line);
	}
	return (0);
}