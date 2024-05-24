#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main (void)
{
    int fd; 
    char *line;

    fd = 0;

    fd = open("quijote.txt", O_RDONLY);
    if (fd == -1)
        return (-1);
    line = get_next_line(fd);
    while (line) 
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    //printf(">%d\n", line == NULL ? 1 : 0);
}