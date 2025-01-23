/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:19:08 by isel-azz          #+#    #+#             */
/*   Updated: 2025/01/22 11:19:12 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit(1);
}

void	free_data(t_data *data, bool flag)
{
	int	i;

	i = 0;
	if (data->so)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->ea)
		free(data->ea);
	if (data->we)
		free(data->we);
	while (i < data->rows_num)
		free(data->maze[i++]);
	if (data->maze)
		free(data->maze);
	if (flag == true)
		err("INVALID INPUT!");
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
			free_data(data, false);
		exit(1);
	}
}

void	get_rows(t_data *data, char *av1)
{
	char	*line;
	int		fd;

	fd = open(av1, O_RDONLY);
	if (fd < 0)
		err("open failed!\n");
	line = get_next_line(fd);
	if (!line)
		err("failed get_next_line!\n");
	while (line != NULL)
	{
		if (line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W'
			&& line[0] != '\n' && line[0] != 'C' && line[0] != 'F')
			data->rows_num++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	get_columns(t_data *data, char *av1)
{
	char	*line;
	char	*trimmed_line;
	int		fd;

	fd = open(av1, O_RDONLY);
	if (fd < 0)
		err("open failed!\n");
	line = get_next_line(fd);
	if (!line)
		err("failed get_next_line!\n");
	while (line != NULL)
	{
		trimmed_line = ft_strtrim(line, " \t\v\f\r\n");
		if (trimmed_line[0] != 'N' && trimmed_line[0] != 'S'
			&& trimmed_line[0] != 'E' && trimmed_line[0] != 'W'
			&& trimmed_line[0] != '\n' && trimmed_line[0] != 'C'
			&& trimmed_line[0] != 'F')
			if (data->column_num < ft_strlen(trimmed_line))
				data->column_num = ft_strlen(trimmed_line);
		free(line);
		free(trimmed_line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	init_game_data(t_data *data, t_player *player, char *av1)
{
	data->player = player;
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->maze = NULL;
	data->rows_num = 0;
	data->column_num = 0;
	ft_memset(&data->c, 0, sizeof(data->c));
	ft_memset(&data->f, 0, sizeof(data->c));
	get_columns(data, av1);
	get_rows(data, av1);
}

void	free_splitted(char **splitted, bool flag)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	if (flag == true)
		err("invalid input!\n");
}

void	parse_colors(char *line, int col[3])
{
	char	**splitted;
	int		i;
	bool	flag;

	flag = false;
	i = 0;
	splitted = ft_split(line, ',');
	if (splitted == NULL)
		err("allocation fail!\n");
	while (splitted[i] != NULL)
	{
		col[i] = ft_atoi(splitted[i]);
		if (col[i] < 0 || col[i] > 255)
		{
			ft_putstr_fd("INVALID RGB VALUE!!\n", 1);
			flag = true;
			break ;
		}
		i++;
	}
	if (i != 3)
		flag = true;
	free_splitted(splitted, flag);
}

void	data_entry(char *line, t_data *data, int *i)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\v\f\r\n");
	if (trimmed_line[0] == 'N' && trimmed_line[1] == 'O'
		&& trimmed_line[2] == ' ')
		data->no = ft_strdup(trimmed_line + 3);
	else if (trimmed_line[0] == 'S' && trimmed_line[1] == 'O'
		&& trimmed_line[2] == ' ')
		data->so = ft_strdup(trimmed_line + 3);
	else if (trimmed_line[0] == 'E' && trimmed_line[1] == 'A'
		&& trimmed_line[2] == ' ')
		data->ea = ft_strdup(trimmed_line + 3);
	else if (trimmed_line[0] == 'W' && trimmed_line[1] == 'E'
		&& trimmed_line[2] == ' ')
		data->we = ft_strdup(trimmed_line + 3);
	else if (trimmed_line[0] == 'C' && trimmed_line[1] == ' ')
		parse_colors(trimmed_line + 2, data->c);
	else if (trimmed_line[0] == 'F' && trimmed_line[1] == ' ')
		parse_colors(trimmed_line + 2, data->f);
	else
		data->maze[*i] = ft_strdup(line);
	if (line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W'
		&& line[0] != '\n' && line[0] != 'C' && line[0] != 'F')
		(*i)++;
	free(trimmed_line);
}

void	parse_file(char *av1, t_data *data)
{
	char	*line;
	int		fd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	data->maze = malloc((data->rows_num + 1) * sizeof(char *));
	if (!data->maze)
		err("malloc fail!\n");
	fd = open(av1, O_RDONLY);
	if (fd < 0)
		err("open fail!\n");
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		data_entry(line, data, &i);
		free(line);
		line = get_next_line(fd);
		j++;
	}
	data->maze[i] = NULL;
	close(fd);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	isplayer(char c)
{
	if (c == 'E' || c == 'N' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

void	check_map_normed(t_data *data, int i, int j, int holder)
{
	static int	playercount;

	if (i == 0 && (data->maze[i][j] != '1' && data->maze[i][j] != '\n'))
		free_data(data, true);
	if ((j == holder && data->maze[i][j] != '1')
	|| ((j == ft_strlen(data->maze[i]) - 2)
		&& data->maze[i][j] != '1'))
		free_data(data, true);
	if (ft_isalnum(data->maze[i][j]) && (data->maze[i][j] != '1' 
		&& data->maze[i][j] != '0' && data->maze[i][j] != '\n'
		&& data->maze[i][j] != ' '
		&& data->maze[i][j] != 'N' && data->maze[i][j] != 'E'
		&& data->maze[i][j] != 'W' && data->maze[i][j] != 'S'))
		free_data(data, true);
	if (i == data->rows_num -1 && (data->maze[i][j] != '1'
		&& !ft_isspace(data->maze[i][j])))
		free_data(data, true);
	if (isplayer(data->maze[i][j]))
	{
		playercount++;
		data->player->player_x = i;
		data->player->player_y = j;
	}
	if (playercount > 1)
		free_data(data, true);
}

void	check_map(t_data *data)
{
	int	i;
	int	j;
	int	holder;

	i = 0;
	j = 0;
	while (i < data->rows_num)
	{
		j = 0;
		while (j < ft_strlen(data->maze[i]))
		{
			holder = 0;
			if (j == 0 && !ft_isalnum(data->maze[i][j]))
			{
				while (data->maze[i][j] != '\0'
					&& !ft_isalnum(data->maze[i][j]))
					j++;
				holder = j;
			}
			check_map_normed(data, i, j, holder);
			j++;
		}
		i++;
	}
}

void	extention_check(t_data *data)
{
	check_extention(data->no, ".png", true, data);
	check_extention(data->so, ".png", true, data);
	check_extention(data->ea, ".png", true, data);
	check_extention(data->we, ".png", true, data);
}

void	check_input(t_data *data)
{
	int	fd[4];
	int	i;

	i = 0;
	if (!data->so || !data->no || !data->ea || !data->we)
		free_data(data, true);
	fd[0] = open(data->no, O_RDONLY);
	fd[1] = open(data->so, O_RDONLY);
	fd[2] = open(data->ea, O_RDONLY);
	fd[3] = open(data->we, O_RDONLY);
	while (i < 4)
	{
		if (fd[i] < 0)
		{
			free_data(data, true);
			break ;
		}
		i++;
	}
	while (i >= 0)
		close(fd[i--]);
	check_map(data);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_player	player;

	if (argc != 2)
		err("wrong number of args\n");
	if (argv[1])
		check_extention(argv[1], ".cub", false, &data);
	init_game_data(&data, &player, argv[1]);
	parse_file(argv[1], &data);
	check_input(&data);
	return (0);
}
