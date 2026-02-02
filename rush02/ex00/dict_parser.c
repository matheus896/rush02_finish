/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matalmei <matalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:46:01 by matalmei          #+#    #+#             */
/*   Updated: 2026/02/01 20:08:10 by matalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	fill_dict(char *str, t_dict *dict)
{
	int		i;
	int		idx;
	char	*start;

	i = 0;
	idx = 0;
	start = str;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			if (*start != '\0' && !fill_struct(start, &dict[idx]))
			{
				write(1, "Dict Error\n", 11);
				return ;
			}
			if (dict[idx].key)
				idx++;
			start = &str[i + 1];
		}
		i++;
	}
}

int	fill_struct(char *line, t_dict *dict_i)
{
	int		i;
	char	*trimmed_key;

	i = 0;
	while (line[i] && line[i] != ':')
		i++;
	if (line[i] != ':')
		return (0);
	line[i] = '\0';
	trimmed_key = ft_trim(line);
	if (*trimmed_key == '\0' || !is_digit(trimmed_key))
		return (0);
	dict_i->key = ft_strdup(trimmed_key);
	dict_i->word = ft_strdup(ft_trim(&line[i + 1]));
	return (1);
}

char	*read_file(char *filename)
{
	int		fd;
	int		total_size;
	char	*content;
	char	buffer;
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	total_size = 0;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, &buffer, 1);
		total_size++;
	}
	close(fd);
	content = malloc(sizeof(char) * (total_size));
	if (!content)
		return (0);
	fd = open(filename, O_RDONLY);
	read(fd, content, total_size);
	close(fd);
	content[total_size - 1] = '\0';
	return (content);
}

int	get_lines(char *string)
{
	int	i;
	int	lines;

	lines = 0;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\n')
			lines++;
		i++;
	}
	return (lines);
}

int	is_digit(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '+')
		i++;
	else if (!num[i])
		return (0);
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
