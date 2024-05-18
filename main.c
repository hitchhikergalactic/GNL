#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
    int     iterations;
	char	*line;
	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("File descriptor error\n"), -1);
    iterations = atoi(argv[2]);
	while (iterations--)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	fd = close(fd);
	return (0);
}
