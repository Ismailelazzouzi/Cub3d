#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include "Libft/libft.h"
#include "get_next_line.h"

typedef struct s_data
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	**maze;
	int		c[3];
	int		f[3];
	int		rows_num;
	int		column_num;
}	t_data;


void	free_data(t_data *data, bool flag)
{
	int	i;

	i = 0;
	if(data->so)
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
		printf("INVALID INPUT\n"), exit(1);
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
		printf("SMYA GHALTA AL3ACHIR\n");
		if (flag == true)
			free_data(data, false);
		exit(1);
	}
}

void	init_game_data(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->maze = NULL;
	data->rows_num = 0;
	data->column_num = 0;
	ft_memset(&data->c, 0, sizeof(data->c));
	ft_memset(&data->f, 0, sizeof(data->c));
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
		printf("LAYN3ALTABONMHOM COLORS\n"), exit(1);
}

void	parse_colors(char *line, int col[3])
{
	int	i;
	char	**splitted;
	bool	flag;

	flag = false;
	i = 0;
	splitted = ft_split(line, ',');
	if (splitted == NULL)
		printf("SPLIT DZEBI\n"), exit(1);

	while (splitted[i] != NULL)
	{
		col[i] = ft_atoi(splitted[i]);
		if (col[i] < 0 || col[i] > 255)
		{
			printf("AR9AM DZEBI HADO!!\n");
			flag = true;
			break;
		}
		i++;
	}
	if (i != 3)
		printf("HAD L COLORS LWEN BIHOM SWTEK"), flag = true;
	free_splitted(splitted, flag);
}

void	parse_map(t_data *data, char *av1)
{
	char	**matrix;
	int	fd;
	char	*line;
	int	i;

	i = 0;
	matrix = malloc((data->rows_num + 1) * sizeof(char *));
	if (!matrix)
		printf("MALLOC DZEB!!\n"), exit (1);
	fd = open(av1, O_RDONLY);
	if (fd < 0)
		printf("FILE DESCRIPTOR DZEB");
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W'
			&& line[0] != '\n' && line[0] != 'C' && line[0] != 'F')
		{
			matrix[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	matrix[i] = NULL;
	i = 0;
	while (matrix[i] != NULL)
		printf("%s", matrix[i]);
}

void	get_columns(t_data *data)
{
	int	i;

	i = 0;
	while (data->maze[i] != NULL)
	{
		if (data->column_num < ft_strlen(data->maze[i]))
			data->column_num = ft_strlen(data->maze[i]);
		i++;
	}
}

void	get_rows(char *av1, t_data *data)
{
	int	fd;
	char	*line;

	fd = open(av1, O_RDONLY);
	if (fd < 0)
		printf("FILE DZEB HADA!\n"), exit(1);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W'
			&& line[0] != '\n' && line[0] != 'C' && line[0] != 'F')
			data->rows_num++;
		free(line);
	}
	close(fd);
}

void	data_entry(char *line, t_data *data, int i)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\v\f\r\n");
	if (trimmed_line[0] == 'N' &&trimmed_line[1] == 'O' &&trimmed_line[2] == ' ')
		data->no = ft_strdup(trimmed_line + 3);
	else if (trimmed_line[0] == 'S' && trimmed_line[1] == 'O' && trimmed_line[2] == ' ')
		data->so = ft_strdup(trimmed_line + 3);
	else if (trimmed_line[0] == 'E' && trimmed_line[1] == 'A' &&trimmed_line[2] == ' ')
		data->ea = ft_strdup(trimmed_line + 3);
	else if (trimmed_line[0] == 'W' && trimmed_line[1] == 'E' && trimmed_line[2] == ' ')
		data->we = ft_strdup(trimmed_line + 3);
	else if (trimmed_line[0] == 'C' && trimmed_line[1] == ' ')
		parse_colors(trimmed_line + 2, data->c);
	else if (trimmed_line[0] == 'F' && trimmed_line[1] == ' ')
		parse_colors(trimmed_line + 2, data->f);
	else
		data->maze[i] = ft_strdup(line);
	free(trimmed_line);
}

void	parse_file(char *av1, t_data *data)
{
	int	fd;
	char	*line;
	int	i;

	i = 0;
	get_rows(av1, data);
	data->maze = malloc((data->rows_num + 1) * sizeof(char *));
	if (!data->maze)
		printf("MALLOC DZABI!!!\n"), exit(1);
	fd = open(av1, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		data_entry(line, data, i);
		if (line[0] != 'N' && line[0] != 'S' && line[0] != 'E' && line[0] != 'W'
			&& line[0] != '\n' && line[0] != 'C' && line[0] != 'F')
			i++;
		free(line);
	}
	data->maze[i] = NULL;
	get_columns(data);
	close(fd);
}

int	ft_isspace(char c)
{
	if (c && (c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	check_map(t_data *data)
{
	int	i;
	int	j;
	int holder;

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
				while (data->maze[i][j] != '\0' && !ft_isalnum(data->maze[i][j]))
					j++;
				holder = j;
			}
			if (i == 0 && (data->maze[i][j] != '1' && data->maze[i][j] != '\n'))
				free_data(data, true);
			if ((j == holder && data->maze[i][j] != '1') || ((j == ft_strlen(data->maze[i]) - 2) && data->maze[i][j] != '1'))
				free_data(data, true);
			if (ft_isalnum(data->maze[i][j]) && (data->maze[i][j] != '1' && data->maze[i][j] != '0' 
				&& data->maze[i][j] != '\n' && data->maze[i][j] != ' '
				&& data->maze[i][j] != 'N' && data->maze[i][j] != 'E'
				&& data->maze[i][j] != 'W' && data->maze[i][j] != 'S'))
				free_data(data, true);
			if (i == data->rows_num -1 && (data->maze[i][j] != '1' && !ft_isspace(data->maze[i][j])))
				free_data(data, true);
			j++;
		}
		i++;
	}
}

void	check_input(t_data *data)
{
	int	fd[4];
	int	i;

	i = 0;
	if (!data->so || !data->no || !data->ea || !data->we)
		free_data(data, true);
	check_extention(data->no, ".png", true, data);
	check_extention(data->so, ".png", true, data);
	check_extention(data->ea, ".png", true, data);
	check_extention(data->we, ".png", true, data);
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

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		printf("ARGUMENTS GHALAT A BRO/SIS\n"), exit(1);
	if (argv[1])
		check_extention(argv[1], ".cub", false, &data);
	init_game_data(&data);
	parse_file(argv[1], &data);
	int i = 0;
	check_input(&data);
	return (0);
}