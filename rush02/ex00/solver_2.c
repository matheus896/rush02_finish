/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matalmei <matalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 21:31:10 by matalmei          #+#    #+#             */
/*   Updated: 2026/02/01 21:35:16 by matalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	get_chunk(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	solve_chunk(char *num_str, int chunk, int len, t_solver *s)
{
	char	temp_chunk[4];

	get_chunk(temp_chunk, num_str, chunk);
	if (ft_atoi(temp_chunk) > 0)
	{
		if (!print_3_digits(ft_atoi(temp_chunk), s))
			return (0);
		if (len - chunk > 0)
			if (!print_magnitude(len - chunk, s))
				return (0);
	}
	else if (*s->first == 1 && len == chunk)
	{
		if (!get_word("0", s->dict, s->size))
			return (0);
		search_and_print(0, s);
	}
	return (1);
}

int	ft_solve(char *num_str, t_solver *s)
{
	int		chunk;
	int		len;

	len = str_len(num_str);
	if (len == 0)
		return (1);
	chunk = len % 3;
	if (chunk == 0)
		chunk = 3;
	if (!solve_chunk(num_str, chunk, len, s))
		return (0);
	return (ft_solve(num_str + chunk, s));
}
