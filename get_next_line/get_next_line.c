/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvitor-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:16:52 by pvitor-l          #+#    #+#             */
/*   Updated: 2025/04/20 15:17:37 by pvitor-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>


# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char *get_next_line(int fd);

#endif


char 	*ft_strdup(const char *s)
{
	int i = 0;
	int len = 0;
	char	*dest;

	while (s[len])
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int pos;
	static int bytes_read;
	char line[70000];
	int	i;

	i = 0;
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

int	main(void)
{
	int fd;
	char *line;

	fd = open("teste.txt", O_RDONLY);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);	
		free(line);
	}
	return (0);
}





















