/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matalmei <matalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:09:54 by gabrielo          #+#    #+#             */
/*   Updated: 2026/02/01 21:30:50 by matalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	search_and_print(int n, t_solver *s)
{
	char	*k;
	char	*word;

	k = itokey(n);
	word = get_word(k, s->dict, s->size);
	if (word)
		ft_putword(word, s->first, s->print);
	free(k);
}

void	free_dictionary(t_dict *dict, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(dict[i].key);
		free(dict[i].word);
		i++;
	}
	return ;
}
