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

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	free_data(t_data *data, char **content ,bool flag)
{
	int	i;
	int	contentlen;

	i = 0;
	contentlen = 0;
	while (content && content[contentlen])
		contentlen++;
	if (data->so)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->ea)
		free(data->ea);
	if (data->we)
		free(data->we);
	while (content && i < contentlen)
		free(content[i++]);
	if (content)
		free(content);
	if (flag == true)
		err("INVALID INPUT! azabi\n");
}

void	init_game_data(t_data *data, t_player *player, char *av1)
{
	data->player = player;
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

int	get_file_height(char *av1)
{
	char	*line;
	int	fd;
	int	i;

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
	return (i);
}

void	get_file_content(t_data *data, char *av1)
{
	char	*line;
	int		fd;
	int		len;
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
}

void	get_info(t_data *data)
{
	char	*trimmed_line;
	int	i;

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

void	check_order(t_data *data)
{
	int	i;
	int	j;

	i = data->map_ends + 1;
	while (data->maze[i])
	{
		j = 0;
		while (j < ft_strlen(data->maze[i]))
		{
			if (!ft_isspace(data->maze[i][j]))
				free_data(data, data->maze, true);
			j++;
		}
		i++;
	}
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

void	check_file_content(t_data *data)
{
	int	len;
	int	i;
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

void	free_splitted(t_data *data, char **splitted)
{
	int	i;

	i = 0;
	while (splitted && splitted[i] && i < 3)
	{
		free(splitted[i]);
		i++;
	}
	if (splitted)
		free(splitted);
}

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
		if (color[i] <= 0 || color[i] >= 255)
		{
			data->killflag = true;
			break ;
		}
		i++;
	}
	if (i != 3)
		data->killflag = true;
	free_splitted(data, splitted);
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

void	info_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->info[i])
	{
		if ((data->info[i][0] == 'N' && data->info[i][1] == 'O' && data->info[i][2] == ' ')
			|| (data->info[i][0] == 'S' && data->info[i][1] == 'O' && data->info[i][2] == ' ')
			|| (data->info[i][0] == 'W' && data->info[i][1] == 'E' && data->info[i][2] == ' ')
			|| (data->info[i][0] == 'E' && data->info[i][1] == 'A' && data->info[i][2] == ' '))
				data->textures_num++;
		if ((data->info[i][0] == 'C' && data->info[i][1] == ' ')
			|| (data->info[i][0] == 'F' && data->info[i][1] == ' '))
			data->colors_num++;
		if (data->info[i][0] == 'N' && data->info[i][1] == 'O' && data->info[i][2] == ' ')
			data->no = ft_strtrim(data->info[i] + 3, " \t\v\f\r\n");
		else if (data->info[i][0] == 'S' && data->info[i][1] == 'O' && data->info[i][2] == ' ')
			data->so = ft_strtrim(data->info[i] + 3, " \t\v\f\r\n");
		else if (data->info[i][0] == 'W' && data->info[i][1] == 'E' && data->info[i][2] == ' ')
			data->we = ft_strtrim(data->info[i] + 3, " \t\v\f\r\n");
		else if (data->info[i][0] == 'E' && data->info[i][1] == 'A' && data->info[i][2] == ' ')
			data->no = ft_strtrim(data->info[i] + 3, " \t\v\f\r\n");
		else if (data->info[i][0] == 'C' && data->info[i][1] == ' ')
			parse_colors(data, data->info[i] + 2, data->c);
		else if (data->info[i][0] == 'F' && data->info[i][1] == ' ')
			parse_colors(data, data->info[i] + 2, data->f);
		i++;
	}
	if (data->colors_num != 2 || data->textures_num != 4)
		data->killflag = true;
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

void	check_holes(t_data *data, char **illusion)
{
	int	i;
	int	j;

	i = 0;
	while (illusion[i])
	{
		j = 0;
		while (illusion[i][j])
		{
			if (illusion[i][j] == '0' || playerpos(illusion[i][j], "NESW"))
			{
				if (illusion[i][j - 1] == ' ' || illusion[i][j + 1] == ' ' ||
				illusion[i - 1][j] == ' ' || illusion[i + 1][j] == ' ')
					free_data(data, illusion, true);
				if (playerpos(illusion[i][j], "NSWE"))
				{
					data->player->player_x = j;
					data->player->player_y = i;
					data->player->player_id = data->map[i][j];
				}
			}
			j++;
		}
		i++;
	}
}

void	create_illusion(t_data *data)
{
	int	i;
	int	j;
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
	while (data->map[i])
	{
		j = 0;
		while (j < data->column_num - 1)
		{
			if (!playerpos(data->map[i][j], "10NSEW") || j > ft_strlen(data->map[i]))
				illusion[i][j] = ' ';
			else
				illusion[i][j] = data->map[i][j];
			j++;
		}
		illusion[i][j] = '\0';
		i++;
	}
	check_holes(data, illusion);
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
			if (!playerpos(data->map[i][j], "1WESN0\n "))
				free_data(data, data->map, true);
			if (i == 0 && !ft_isspace(data->map[i][j]) && data->map[i][j] != '1')
				free_data(data, data->map, true);
			if (data->map[i][j] == '\n' && data->map[i][j - 1] != '1' && !ft_isspace(data->map[i][j - 1]))
				free_data(data, data->map, true);
			if (i == data->rows_num - 1 && !ft_isspace(data->map[i][j])
				&& data->map[i][j] != '1')
				free_data(data, data->map, true);
			if (playerpos(data->map[i][j], "NESW"))
				data->playercount++;
			if (data->map[i][j] == '\n' && data->column_num <= j)

				data->column_num = j;
			j++;
		}
		
		i++;
	}
	if (data->playercount != 1)
		free_data(data, data->map, true);
	create_illusion(data);
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

void	fill_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->rows_num - 1)
	{
		printf("%s", data->map[i]);
		i++;
	}
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
	get_file_content(&data, argv[1]);
	check_file_content(&data);
	check_data_validity(&data);
	int mapwidth = data.column_num * tile_size;
	int mapheight = data.rows_num * tile_size;

	player.x = (double)player.player_x * tile_size + tile_size / 2;
	player.y = (double)player.player_y * tile_size + tile_size / 2;
	player.radius = 3;
    player.rotation_angle = 0;
    player.turn_direction = 0;
    player.walk_direction = 0;
    player.move_speed = 4;
    player.retation_speed = 2 * (M_PI /180);
	int n_r = 2000;
	player.rays = malloc(n_r * sizeof(t_ray *)); // Array of pointers
for (int i = 0; i < n_r; i++) {
    player.rays[i] = malloc(sizeof(t_ray)); // Allocate each struct individually
}
	data.mlx = mlx_init(s_w, s_h, "MLX42", true);
 
    player.img = mlx_new_image(data.mlx, s_w, s_h);

	uint32_t black_color = get_rgba(0,0,0,255);
    uint32_t white_color = get_rgba(255,250,255,255);
    uint32_t gray_color = get_rgba(128,128,128,255);
    uint32_t red_color = get_rgba(255,0,0,255);
	uint32_t green_color = get_rgba(0,255,0,255);

	    for (int y = 0; y < s_h; y++) {
        for (int x = 0; x < s_w; x++) {
            mlx_put_pixel(player.img, x, y, black_color);
        }
    }

	//  for (int i = 0; i < data.column_num; i++) {
    //     for (int j = 0; j < data.rows_num; j++) {
    //         int tile_x = j * tile_size;
    //         int tile_y = i * tile_size;
    //         // printf("%d ", map[i][j]);
    //         if(data.map[i][j] == 0)
    //             put_squer(white_color,player.img,tile_size-1, tile_size-1,tile_x,tile_y);
    //         if(data.map[i][j] == 1)
    //             put_squer(gray_color,player.img,tile_size-1, tile_size-1,tile_x,tile_y);
    //     }
    //     // printf("\n");
    // }
	int i = 0, j = 0;
	int tile_x = 0, tile_y = 0;

	//printf("%d\n", tile_size);
	while (i < data.rows_num - 1)
	{
		j = 0;
			//printf("%zu\n",ft_strlen(data.map[i]));
		while (j < ft_strlen(data.map[i]) - 1)
		{
			tile_x = j * tile_size;
        	tile_y = i * tile_size;
			if (data.map[i][j] == '0' || data.map[i][j] == 'E')
            	put_squer(white_color,player.img,tile_size-1, tile_size-1,tile_x,tile_y);
			else if(data.map[i][j] == '1')
                put_squer(gray_color,player.img,tile_size-1, tile_size-1,tile_x,tile_y);
			else if (data.map[i][j] != '0' && data.map[i][j] != '1')
			{
			
					put_squer(red_color, player.img,tile_size-1, tile_size-1,tile_x,tile_y);
				
			}
	
			
			j++;
		}
		//printf("%d\n", j);
		while(j < data.column_num)
		{
				tile_x = j * tile_size;
        	tile_y = i * tile_size;
			put_squer(red_color, player.img,tile_size-1, tile_size-1,tile_x,tile_y);
			j++;
		}
		i++;
	}
//	printf("player x : %d\n", player.player_x);
	draw_circle(data.mlx, player.img, player.x, player.y, player.radius, green_color);
    draw_line(data.mlx,player.img, player.x, player.y, (player.x + cos(player.rotation_angle) * 50),(player.y + sin(player.rotation_angle)*50), red_color);
	render_rays(player.rays, &data);
	mlx_image_to_window(data.mlx, player.img, 0, 0);
	mlx_key_hook(data.mlx, (mlx_keyfunc)update, &data);
	mlx_loop(data.mlx);
	        for (int i = 0; i < n_r; i++) {
        free(player.rays[i]);
    }
	mlx_terminate(data.mlx);
	return (0);
}
