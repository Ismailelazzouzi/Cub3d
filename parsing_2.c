/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:29:51 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/12 20:29:54 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	parse_colors(t_data *data, char *col, int *color)
{
	char	**splitted;
	int		i;

	splitted = ft_split(col, ',');
	if (!splitted)
	{
		free_data(data, data->map, false);
		free_data(data, data->maze, false);
		free_data(data, data->info, true);
	}
	i = 0;
	while (splitted && splitted[i] != NULL)
	{
		color[i] = ft_atoi(splitted[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			data->killflag = true;
			break ;
		}
		i++;
	}
	if (i != 3)
		data->killflag = true;
	free_splitted(splitted);
}

void	check_extention(char *filename, char *ext, bool flag, t_data *data)
{
	int	namelen;
	int	extlen;

	namelen = ft_strlen(filename);
	extlen = ft_strlen(ext);
	filename = filename + (namelen - extlen);
	if (ft_strncmp(filename, ext, extlen) != 0)
	{
		ft_putstr_fd("SMYA GHALTA AL3ACHIR\n", 2);
		if (flag == true)
			free_data(data, NULL, false);
		exit(1);
	}
}

int	playerpos(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

void	check_data_validity(t_data *data)
{
	int	i;

	i = 0;
	info_check(data);
	if (data->killflag == true)
		free_data(data, data->info, true);
	map_check(data);
}

void	free_textures(t_data *data)
{
	if (data->textures->north)
		free(data->textures->north);
	if (data->textures->east)
		free(data->textures->east);
	if (data->textures->west)
		free(data->textures->west);
	if (data->textures->south)
		free(data->textures->south);
}
