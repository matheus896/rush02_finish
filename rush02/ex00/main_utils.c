/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matalmei <matalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 21:31:22 by matalmei          #+#    #+#             */
/*   Updated: 2026/02/01 21:31:26 by matalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_putword(char *word, int *first, int print)
{
	if (print == 0)
		return ;
	if (*word == '\0')
		return ;
	if (*first == 0)
		ft_putstr(" ");
	ft_putstr(word);
	*first = 0;
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	bad_input(int i)
{
	if (i == 0)
		write(1, "Error\n", 6);
	else
		write(1, "Dict Error\n", 11);
	return (0);
}
