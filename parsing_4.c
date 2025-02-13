/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:35:38 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/12 21:35:40 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	fill_illusion(t_data *data, char **illusion)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (j < data->column_num - 1)
		{
			if (!playerpos(data->map[i][j], "10NSEW")
				|| j > (int)ft_strlen(data->map[i]))
				illusion[i][j] = ' ';
			else
				illusion[i][j] = data->map[i][j];
			j++;
		}
		illusion[i][j] = '\0';
		i++;
	}
}

void	create_illusion(t_data *data)
{
	int		i;
	char	**illusion;

	illusion = malloc((data->rows_num + 1) * sizeof(char *));
	if (!illusion)
		err("malloc failed!\n");
	i = 0;
	while (i < data->rows_num)
	{
		illusion[i] = malloc(data->column_num + 1);
		if (!illusion[i])
			err("malloc failed!\n");
		i++;
	}
	illusion[i] = NULL;
	i = 0;
	fill_illusion(data, illusion);
	check_holes(data, illusion);
}

void	map_check1(t_data *data, int *i, int *j)
{
	if (!playerpos(data->map[*i][*j], "1WESN0\n "))
		free_data(data, data->map, true);
	if (*i == 0 && !ft_isspace(data->map[*i][*j])
		&& data->map[*i][*j] != '1')
		free_data(data, data->map, true);
	if (data->map[*i][*j] == '\n'
		&& data->map[*i][*j - 1] != '1'
		&& !ft_isspace(data->map[*i][*j - 1]))
		free_data(data, data->map, true);
	if (*i == data->rows_num - 1 && !ft_isspace(data->map[*i][*j])
		&& data->map[*i][*j] != '1')
		free_data(data, data->map, true);
	if (playerpos(data->map[*i][*j], "NESW"))
		data->playercount++;
	if (data->map[*i][*j] == '\n' && data->column_num <= *j)
		data->column_num = *j;
}

void	map_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows_num)
	{
		j = 0;
		while (ft_isspace(data->map[i][j]) || data->map[i][j] == '\0')
			j++;
		if (data->map[i][j] != '1')
			free_data(data, data->map, true);
		while (data->map[i][j])
		{
			map_check1(data, &i, &j);
			j++;
		}
		i++;
	}
	if (data->playercount != 1)
		free_data(data, data->map, true);
	create_illusion(data);
}
