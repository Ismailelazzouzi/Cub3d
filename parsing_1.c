/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:04:21 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/11 23:04:23 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	get_info(t_data *data)
{
	char	*trimmed_line;
	int		i;

	i = 0;
	data->info = malloc((data->map_begins + 1) * sizeof(char *));
	if (!data->info)
	{
		free_data(data, data->map, false);
		free_data(data, data->maze, true);
	}
	while (i < data->map_begins)
	{
		trimmed_line = ft_strtrim(data->maze[i], " \t\v\f\r\n");
		data->info[i] = ft_strdup(trimmed_line);
		free(trimmed_line);
		i++;
	}
	data->info[i] = NULL;
}

void	check_order2(t_data *data)
{
	int	i;
	int	j;

	data->map = malloc((data->rows_num + 1) * sizeof(char *));
	if (!data->map)
		free_data(data, data->maze, true);
	i = data->map_begins;
	j = 0;
	while (i < data->map_ends + 1)
	{
		data->map[j] = ft_strdup(data->maze[i]);
		i++;
		j++;
	}
	data->map[j] = NULL;
	i = 0;
	get_info(data);
}

void	check_order(t_data *data)
{
	int	i;
	int	j;

	i = data->map_ends + 1;
	while (data->maze[i])
	{
		j = 0;
		while (j < (int)ft_strlen(data->maze[i]))
		{
			if (!ft_isspace(data->maze[i][j]))
				free_data(data, data->maze, true);
			j++;
		}
		i++;
	}
	check_order2(data);
}

void	check_file_content1(t_data *data)
{
	char	*trimmed_line;
	int		i;

	i = 0;
	while (i < data->map_ends)
	{
		trimmed_line = ft_strtrim(data->maze[i], " \t\v\f\r\n");
		if (trimmed_line[0] == '1')
		{
			data->map_begins = i;
			free(trimmed_line);
			break ;
		}
		free(trimmed_line);
		i++;
	}
	data->rows_num = data->map_ends - data->map_begins + 1;
	check_order(data);
}

void	check_file_content(t_data *data)
{
	int		len;
	int		i;
	char	*trimmed_line;

	len = data->fileheight - 1;
	while (len >= 0)
	{
		trimmed_line = ft_strtrim(data->maze[len], " \t\v\f\r\n");
		if (trimmed_line[0] == '1')
		{
			data->map_ends = len;
			free(trimmed_line);
			break ;
		}
		free(trimmed_line);
		trimmed_line = NULL;
		len--;
	}
	check_file_content1(data);
}
