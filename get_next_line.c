/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osredond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:34:58 by osredond          #+#    #+#             */
/*   Updated: 2024/05/18 15:30:29 by osredond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line_start(const char *str)
{
	char	*res_memory;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] != '\0' && str[i] == '\n')
		i++;
	res_memory = ft_calloc(i + 1, sizeof * res_memory);
	if (!res_memory)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		res_memory[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		res_memory[i] = str[i];
		i++;
	}
	return (res_memory);
}

char	*get_line_end(const char *str)
{
	char	*res_memory;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] != '\0' && str[i] == '\n')
		i++;
	j = 0;
	while (str && str[j])
		j++;
	res_memory = ft_calloc((j - i) + 1, sizeof * res_memory);
	if (!res_memory)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		res_memory[j] = str[i + j];
		j++;
	}
	return (res_memory);
}

void	read_line(int fd, char **storage, char **tempo)
{
	char	*mem_reserve;
	long	readed;

	mem_reserve = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!mem_reserve)
		return ;
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, mem_reserve, BUFFER_SIZE);
		if (readed < 0)
		{
			ft_free_strs(&mem_reserve, storage, tempo);
			return ;
		}
		mem_reserve[readed] = '\0';
		*tempo = ft_strdup(*storage);
		ft_free_strs(storage, 0, 0);
		*storage = ft_strjoin(*tempo, mem_reserve);
		ft_free_strs(tempo, 0, 0);
		if (ft_strchr(*storage, '\n'))
			break ;
	}
	ft_free_strs(&mem_reserve, 0, 0);
}

char	*process_current_line(char **storage, char **tempo)
{
	char	*line;

	*tempo = ft_strdup(*storage);
	ft_free_strs(storage, 0, 0);
	*storage = get_line_end(*tempo);
	line = get_line_start(*tempo);
	ft_free_strs(tempo, 0, 0);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*tempo;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	tempo = NULL;
	read_line(fd, &storage, &tempo);
	if (storage != NULL && *storage != '\0')
		line = process_current_line(&storage, &tempo);
	if (!line || *line == '\0')
	{
		ft_free_strs(&storage, &line, &tempo);
		return (NULL);
	}
	return (line);
}
/*
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;
	

	fd = 0;
	if (fd == -1)
		return (-1);
	fd = open("test1.txt", O_RDONLY);
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	fd = close(fd);
	return (0);
}*/