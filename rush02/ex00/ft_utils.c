/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matalmei <matalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:23:00 by matalmei          #+#    #+#             */
/*   Updated: 2026/02/01 20:18:37 by matalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_trim(char *string)
{
	int	i;

	while (*string == ' ' || (*string >= 9 && *string <= 13))
		string++;
	i = 0;
	while (string[i])
		i++;
	while (--i >= 0 && (string[i] == ' ' || (*string >= 9 && *string <= 13)))
		string[i] = '\0';
	return (string);
}

int	str_len(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr++)
		;
	return (ptr - str - 1);
}

char	*ft_strdup(char *src)
{
	char	*buffer;
	int		i;

	buffer = malloc(str_len(src) + 1);
	i = 0;
	while (src[i] != '\0')
	{
		buffer[i] = src[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	atoi;

	i = 0;
	atoi = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		atoi *= 10;
		atoi += str[i] - '0';
		i++;
	}
	return (atoi);
}
