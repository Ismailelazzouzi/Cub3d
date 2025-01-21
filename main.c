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
	if (strcmp(filename + i, ext) != 0)
		printf("SMYA DYAL MAP GHALTA AL3ACHIR\n"), exit(1);
}

void	init_game_data(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->maze = NULL;
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

void	parse_file(char *av1, t_data *data)
{
	int	fd;
	char	*line;
	char	*trimmed_line;

	fd = open(av1, O_RDONLY);
	if (fd < 0)
		printf("FILE DZEB HADA!\n"), exit(1);
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed_line = ft_strtrim(line, "\n \t	");
		if (trimmed_line[0] == 'N' && trimmed_line[1] == 'O' && trimmed_line[2] == ' ')
			data->no = ft_strdup(trimmed_line + 3);
		else if ((trimmed_line[0] == 'S' && trimmed_line[1] == 'O' && trimmed_line[2] == ' '))
			data->so = ft_strdup(trimmed_line + 3);
		else if (trimmed_line[0] == 'E' && trimmed_line[1] == 'A' && trimmed_line[2] == ' ')
			data->ea = ft_strdup(trimmed_line + 3);
		else if (trimmed_line[0] == 'W' && trimmed_line[1] == 'E' && trimmed_line[2] == ' ')
			data->we = ft_strdup(trimmed_line + 3);
		else if (trimmed_line[0] == 'C' && trimmed_line[1] == ' ')
			parse_colors(trimmed_line + 2, data->c);
		else if (trimmed_line[0] == 'F' && trimmed_line[1] == ' ')
			parse_colors(trimmed_line + 2, data->f);
		free(trimmed_line);
		free(line);
	}
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
	// testing
	printf("%s\n%s\n%s\n%s\n%d\n%d\n", data.no, data.so, data.ea, data.we, data.c[0], data.f[0]);
	return (0);
}