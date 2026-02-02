/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matalmei <matalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 14:36:12 by matalmei          #+#    #+#             */
/*   Updated: 2026/02/01 21:33:15 by matalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	print_magnitude(int zeros, t_solver *s)
{
	int		i;
	char	*key;
	char	*word;

	key = malloc(sizeof(char) * (zeros + 2));
	if (!key)
		return (0);
	key[0] = '1';
	i = 1;
	while (i <= zeros)
	{
		key[i] = '0';
		i++;
	}
	key[i] = '\0';
	word = get_word(key, s->dict, s->size);
	if (!word)
	{
		free(key);
		return (0);
	}
	ft_putword(word, s->first, s->print);
	free(key);
	return (1);
}

static int	print_hundreds(int *n, t_solver *s)
{
	char	*k;

	if (*n >= 100)
	{
		k = itokey(*n / 100);
		if (!get_word(k, s->dict, s->size)
			|| !get_word("100", s->dict, s->size))
		{
			free(k);
			return (0);
		}
		search_and_print(*n / 100, s);
		ft_putword(get_word("100", s->dict, s->size), s->first, s->print);
		*n = *n % 100;
		free(k);
	}
	return (1);
}

int	print_3_digits(int n, t_solver *s)
{
	char	*k;

	if (!print_hundreds(&n, s))
		return (0);
	if (n >= 20)
	{
		k = itokey((n / 10) * 10);
		if (!get_word(k, s->dict, s->size))
		{
			free(k);
			return (0);
		}
		search_and_print((n / 10) * 10, s);
		free(k);
		if (n % 10 > 0)
			search_and_print(n % 10, s);
	}
	else if (n > 0)
	{
		search_and_print(n, s);
	}
	return (1);
}

char	*itokey(int n)
{
	char	*key;
	int		len;

	if (n >= 100)
		len = 3;
	else if (n >= 10)
		len = 2;
	else
		len = 1;
	key = malloc(len + 1);
	if (!key)
		return (NULL);
	key[len] = '\0';
	while (len > 0)
	{
		len--;
		key[len] = n % 10 + '0';
		n /= 10;
	}
	return (key);
}

char	*get_word(char *key, t_dict *dictionary, int dict_size)
{
	int	i;

	i = 0;
	while (i < dict_size)
	{
		if (dictionary[i].key != NULL && ft_strcmp(key, dictionary[i].key) == 0)
			return (dictionary[i].word);
		i++;
	}
	return (NULL);
}
