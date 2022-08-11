/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialgac <ialgac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:50:33 by ialgac            #+#    #+#             */
/*   Updated: 2022/01/27 20:13:55 by ialgac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	isnin(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			return (1);
	return (0);
}

static char	*rtake(int fd, char *s)
{
	char	*buf;
	int		byte;
	char	*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!s)
		s = ft_strdup("");
	byte = 1;
	while (!isnin(s) && byte)
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte == -1)
			break ;
		buf[byte] = 0;
		temp = s;
		s = ft_strjoin(temp, buf);
		free(temp);
	}
	free(buf);
	return (s);
}

static void	ft_getline(char *s, char **line)
{
	int	i;

	i = ft_strchr(s, '\n') - s + 1;
	if (i < 0)
		i = ft_strlen(s) + 1;
	*line = ft_substr(s, 0, i);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	char		*old;

	buffer[fd] = rtake(fd, buffer[fd]);
	if (!buffer[fd])
		return (0);
	ft_getline(buffer[fd], &line);
	if (line)
	{
		if (line[0] == 0)
		{
			free(line);
			line = 0;
		}
	}
	old = buffer[fd];
	buffer[fd] = ft_substr(old, ft_strchr(old, '\n') - old + 1, ft_strlen(old));
	if (line == 0)
	{
		free(buffer[fd]);
		buffer[fd] = 0;
	}
	free (old);
	return (line);
}
