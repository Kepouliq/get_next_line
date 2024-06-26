/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kepouliq <kepouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:52:08 by kepouliq          #+#    #+#             */
/*   Updated: 2024/06/26 10:52:32 by kepouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	get_end_line(char *line)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] == '\n')
				return (i);
			i++;
		}
	}
	return (-1);
}

static int	checks(int fd, char *line, char **rest)
{
	if (read(fd, line, 0) == -1)
	{
		if (*rest)
		{
			free(*rest);
			*rest = NULL;
		}
		return (-1);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX - 1
		|| read(fd, line, 0) == -1)
		return (-1);
	return (0);
}

static char	*check_new_line_in_rest(char **rest)
{
	int		i;
	char	*line;
	char	*temp;

	line = NULL;
	i = 0;
	while ((*rest)[i])
	{
		if ((*rest)[i] == '\n')
		{
			line = ft_substr(*rest, 0, i + 1);
			temp = *rest;
			*rest = ft_strjoin("", *rest + i + 1);
			if (!*rest && temp[i + 1])
				return (NULL);
			free(temp);
			return (line);
		}
		i++;
	}
	line = ft_strdup(*rest);
	free(*rest);
	*rest = NULL;
	return (line);
}

static char	*check_new_line_in_buf(char **rest, char *buf, char *line, int i)
{
	char	*temp;

	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			*rest = ft_substr(buf, 0, i + 1);
			temp = line;
			line = ft_strjoin(temp, *rest);
			free(temp);
			free(*rest);
			*rest = ft_strjoin("", buf + i + 1);
			if (!*rest && buf[i + 1])
				return (NULL);
			free(buf);
			return (line);
		}
		i++;
	}
	temp = line;
	line = ft_strjoin(line, buf);
	free(temp);
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*rest;

	line = NULL;
	if (checks(fd, line, &rest) == -1)
		return (NULL);
	if (rest)
		line = check_new_line_in_rest(&rest);
	if (get_end_line(line) != -1)
		return (line);
	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (read(fd, buf, BUFFER_SIZE) > 0)
	{
		line = check_new_line_in_buf(&rest, buf, line, 0);
		if (get_end_line(line) != -1)
			return (line);
		buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (NULL);
	}
	free(buf);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*test;
// 	fd = open("test.txt", O_RDONLY);
// 	while ((test = get_next_line(fd)) != NULL)
// 	{
// 		printf("line = %s", test);
// 		free(test);
// 	}
// 	printf("last line = %s", test);
// 	free(test);
// }
