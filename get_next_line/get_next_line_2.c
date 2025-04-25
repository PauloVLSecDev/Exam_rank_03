/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:26:55 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/04/22 18:52:35 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char *get_next_line(int fd);

#endif

char *ft_strdup(char *str)
{
	int len = 0;
	char *dest;
	int i = 0;

	while (str[len])
		len++;			
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int pos;
	static int bytes_read;
	char line[70000];
	int i = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (pos >= bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			pos = 0;
			if (bytes_read <= 0)
				break ;
		}
		line[i++] = buffer[pos++];
		if (line[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

int	main (void)
{
	int	fd;
	char	*line;

	fd = open("teste.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)	
	{
		printf("%s", line);	
		free(line);
	}
	return (0);
}






