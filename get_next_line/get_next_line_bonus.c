/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:59:41 by smia              #+#    #+#             */
/*   Updated: 2021/12/03 19:48:25 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_line(char *rest)
{
	char	*line;
	int		index;
	int		i;

	i = 0;
	if (ft_strlen(rest) <= 0)
		return (NULL);
	index = find_new_line(rest);
	if (index == -1)
	{
		line = ft_strdup(rest);
		return (line);
	}
	line = (char *)malloc((index + 2) * sizeof(char));
	if (!line)
		return (NULL);
	while (rest[i] != '\n')
	{
		line[i] = rest[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*ft_rest(char *rest)
{
	int		len;
	int		index;
	char	*tmp;

	if (!rest)
		return (NULL);
	len = ft_strlen(rest);
	index = find_new_line(rest);
	if (index != -1)
	{
		tmp = ft_substr(rest, (index + 1), (len - index - 1));
		free (rest);
		rest = tmp;
		return (rest);
	}
	free (rest);
	return (NULL);
}

char	*ft_read(int fd, char *buff, char *rest)
{
	char	*tmp;
	int		n;

	n = 0;
	while (find_new_line(rest) == -1)
	{
		n = read (fd, buff, BUFFER_SIZE);
		if (n > 0)
		{
			buff[n] = '\0';
			tmp = ft_strjoin(rest, buff);
			if (rest)
				free(rest);
			rest = NULL;
			rest = tmp;
		}
		else
			break ;
	}
	free (buff);
	buff = NULL;
	if (n == -1)
		return (NULL);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest[1024];
	char		*line;
	char		*buff;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buff = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	rest[fd] = ft_read(fd, buff, rest[fd]);
	line = ft_line(rest[fd]);
	rest[fd] = ft_rest(rest[fd]);
	return (line);
}
