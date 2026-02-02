/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matalmei <matalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:24:56 by gabrielo          #+#    #+#             */
/*   Updated: 2026/02/01 21:31:37 by matalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_dict	*parse_dict(char *path, int *count)
{
	char	*file_str;
	t_dict	*dict;
	int		i;

	file_str = read_file(path);
	if (!file_str)
		return (NULL);
	*count = get_lines(file_str);
	dict = malloc(sizeof(t_dict) * (*count));
	if (!dict)
		return (NULL);
	i = 0;
	while (i < *count)
	{
		dict[i].key = 0;
		dict[i].word = 0;
		i++;
	}
	fill_dict(file_str, dict);
	free(file_str);
	return (dict);
}

void	process_solve(t_dict *dict, char *num, int count)
{
	int			first;
	t_solver	s;

	first = 1;
	s.dict = dict;
	s.size = count;
	s.first = &first;
	s.print = 0;
	if (ft_solve(num, &s))
	{
		first = 1;
		s.print = 1;
		ft_solve(num, &s);
		write(1, "\n", 1);
	}
	else
		write(1, "Dict Error\n", 11);
}

int	main(int argc, char **argv)
{
	char	*path;
	char	*num;
	t_dict	*dict;
	int		count;

	num = 0;
	path = "numbers.dict";
	if (argc == 2)
		num = argv[1];
	else if (argc == 3)
	{
		path = argv[1];
		num = argv[2];
	}
	if ((argc != 2 && argc != 3) || !is_digit(num))
		return (bad_input(0));
	dict = parse_dict(path, &count);
	if (!dict)
		return (bad_input(1));
	process_solve(dict, num, count);
	free_dictionary(dict, count);
	free(dict);
	return (0);
}
