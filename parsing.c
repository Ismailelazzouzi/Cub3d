/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:02:27 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/11 23:02:30 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit(1);
}

int	get_file_height(char *av1)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(av1, O_RDONLY);
	if (!fd)
		err("FD DZEB!\n");
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

void	init_game_data(t_data *data, t_player *player, t_colors *colores)
{
	data->player = player;
	data->colores = colores;
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->maze = NULL;
	data->map = NULL;
	data->info = NULL;
	data->map_begins = 0;
	data->map_ends = 0;
	data->rows_num = 0;
	data->column_num = 0;
	data->textures_num = 0;
	data->colors_num = 0;
	data->playercount = 0;
	data->killflag = false;
	data->shootflag = false;
	ft_memset(&data->c, 0, sizeof(data->c));
	ft_memset(&data->f, 0, sizeof(data->c));
}

void	get_file_content(t_data *data, char *av1)
{
	char	*line;
	int		fd;
	int		i;

	data->fileheight = get_file_height(av1);
	fd = open(av1, O_RDONLY);
	data->maze = malloc((data->fileheight + 1) * sizeof(char *));
	if (!fd)
		err("FD DZEB!\n");
	line = get_next_line(fd);
	if (!line)
		err("malloc fail");
	i = 0;
	while (line != NULL)
	{
		data->maze[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->maze[i] = NULL;
	close(fd);
}
