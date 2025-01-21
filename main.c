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


void	check_extention(char *filename, char *ext)
{
	int	i;

	i = 0;
	while (filename[i])
	{
		if (filename[i] == '.')
			break;
		i++;
	}
	if (ft_strncmp(filename + i, ext, ft_strlen(filename)) != 0)
		printf("SMYA DYAL MAP GHALTA AL3ACHIR\n"), exit(1);
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
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		data->no = ft_strdup(line + 3);
	else if ((line[0] == 'S' && line[1] == 'O' && line[2] == ' '))
		data->so = ft_strdup(line + 3);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		data->ea = ft_strdup(line + 3);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		data->we = ft_strdup(line + 3);
	else if (line[0] == 'C' && line[1] == ' ')
		parse_colors(line + 2, data->c);
	else if (line[0] == 'F' && line[1] == ' ')
		parse_colors(line + 2, data->f);
	else if (line[0] == '\n')
		line[1] = '\0';
	else
		data->maze[i] = ft_strdup(line);
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
	close(fd);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		printf("ARGUMENTS GHALAT A BRO/SIS\n"), exit(1);
	if (argv[1])
		check_extention(argv[1], ".cub");
	init_game_data(&data);
	parse_file(argv[1], &data);
	int i = 0;
	printf("NO %s\nSO %s\nWE %s\nEA %s\n\nF %d, %d, %d\nC %d, %d, %d\n\n", data.no, data.so, data.ea, data.we, data.c[0], data.c[1], data.c[2], data.f[0], data.f[1], data.f[2]);
	while (data.maze[i])
		printf("%s", data.maze[i++]);
	return (0);
}