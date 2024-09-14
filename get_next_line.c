/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfedorys <mfedorys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:58:50 by mfedorys          #+#    #+#             */
/*   Updated: 2024/09/14 16:29:46 by mfedorys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*before_nl(const char *s)
{
	char	*res;
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] != '\0' && s[i] == '\n')
		i++;
	res = ft_malloc_zero(i + 1, sizeof * res);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		res[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

char	*after_nl(const char *s)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	while (s && s[j])
		j++;
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] != '\0' && s[i] == '\n')
		i++;
	res = ft_malloc_zero((j - i) + 1, sizeof * res);
	if (!res)
		return (NULL);
	j = 0;
	while (s[i + j])
	{
		res[j] = s[i + j];
		j++;
	}
	return (res);
}

void	ft_read(int fd, char **remain_storage, char **temp_storage)
{
	char	*buff;
	int		r;

	buff = malloc(sizeof * buff * (BUFFER_SIZE + 1));
	if (!buff)
		return ;
	r = 1;
	while (r > 0)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			ft_free_str_mem(&buff, remain_storage, temp_storage);
			return ;
		}
		buff[r] = '\0';
		*temp_storage = ft_strdup(*remain_storage);
		ft_free_str_mem(remain_storage, 0, 0);
		*remain_storage = join_strs(*temp_storage, buff);
		ft_free_str_mem(temp_storage, 0, 0);
		if (contains_newline(*remain_storage))
			break ;
	}
	ft_free_str_mem(&buff, 0, 0);
}

char	*ft_parse_line(char **remain_storage, char **temp_storage)
{
	char	*line;

	*temp_storage = ft_strdup(*remain_storage);
	ft_free_str_mem(remain_storage, 0, 0);
	*remain_storage = after_nl(*temp_storage);
	line = before_nl(*temp_storage);
	ft_free_str_mem(temp_storage, 0, 0);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remain_storage = NULL;
	char		*temp_storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	temp_storage = NULL;
	ft_read(fd, &remain_storage, &temp_storage);
	if (remain_storage != NULL && *remain_storage != '\0')
		line = ft_parse_line(&remain_storage, &temp_storage);
	if (!line || *line == '\0')
	{
		ft_free_str_mem(&remain_storage, &line, &temp_storage);
		return (NULL);
	}
	return (line);
}
