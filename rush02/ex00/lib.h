/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matalmei <matalmei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 15:30:48 by matalmei          #+#    #+#             */
/*   Updated: 2026/02/01 21:31:58 by matalmei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_dict
{
	char	*key;
	char	*word;
}			t_dict;

typedef struct s_solver
{
	t_dict	*dict;
	int		size;
	int		*first;
	int		print;
}			t_solver;

void		search_and_print(int n, t_solver *s);
int			str_len(char *str);
char		*ft_strdup(char *src);
int			is_digit(char *num);
int			get_lines(char *string);
void		ft_putstr(char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_atoi(char *str);
char		*ft_trim(char *string);
void		ft_putword(char *word, int *first, int print);
void		free_dictionary(t_dict *dict, int count);

int			print_magnitude(int zeros, t_solver *s);
int			print_3_digits(int n, t_solver *s);
char		*itokey(int n);
char		*get_word(char *key, t_dict *dictionary, int dict_size);
int			ft_solve(char *num_str, t_solver *s);
int			bad_input(int i);

char		*read_file(char *filename);
int			fill_struct(char *line, t_dict *dict_i);
void		fill_dict(char *str, t_dict *dictionary);
t_dict		*parse_dict(char *path, int *count);

#endif
