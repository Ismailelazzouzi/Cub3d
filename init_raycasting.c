#include "cube.h"

void	black_window(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < s_h)
	{
		x = 0;
        while (x < s_w)
		{
            mlx_put_pixel(data->player->img, x, y, data->colores->black_color);
			x++;
        }
		y++;
    }
}

void	fill_window(t_data *data)
{
	int	i;
	int	j;
	int	tile_x;
	int	tile_y;

	i = 0;
	while (i < data->rows_num)
	{
		j = 0;
		while (j < (int)ft_strlen(data->map[i]) - 1)
		{
			tile_x = j * tile_size;
        	tile_y = i * tile_size;
			if (data->map[i][j] == '0' || data->map[i][j] == 'E')
            	put_squer(data->colores->white_color, data->player->img, tile_size - 1, tile_size - 1, tile_x, tile_y);
			else if(data->map[i][j] == '1')
                put_squer(data->colores->gray_color, data->player->img, tile_size - 1, tile_size - 1, tile_x, tile_y);
			else if (data->map[i][j] != '0' && data->map[i][j] != '1')
				put_squer(data->colores->red_color, data->player->img, tile_size - 1, tile_size - 1,tile_x,tile_y);
			j++;
		}
		while (j < data->column_num)
		{
			tile_x = j * tile_size;
        	tile_y = i * tile_size;
			put_squer(data->colores->red_color, data->player->img, tile_size - 1, tile_size - 1, tile_x, tile_y);
			j++;
		}
		i++;
	}
}

void cleanup_textures(t_data *data)
{
    mlx_delete_texture(data->textures->north);
    mlx_delete_texture(data->textures->south);
    mlx_delete_texture(data->textures->east);
    mlx_delete_texture(data->textures->west);
	free(data->textures);
	data->textures = NULL;
}

void	init_textures(t_data *data)
{
	data->textures = malloc(sizeof(t_texture));
	if (!data->textures)
		err("zebi\n");
	data->textures->north = NULL;
	data->textures->south = NULL;
	data->textures->west = NULL;
	data->textures->east = NULL;
	data->textures->north = mlx_load_png(data->no);
	if (!data->textures->north)
		err("zebi\n");
	data->textures->east = mlx_load_png(data->ea);
	if (!data->textures->east)
		err("zebi\n");
	data->textures->west = mlx_load_png(data->we);
	if (!data->textures->west)
		err("zebi\n");
	data->textures->south = mlx_load_png(data->so);
	if (!data->textures->south)
		err("zebi\n");
}

void	set_direction(t_player *player, char c)
{
	if (c == 'N')
		player->rotation_angle = (3 * M_PI) / 2;
	else if (c == 'E')
	    player->rotation_angle = 0;
	else if (c == 'S')
	    player->rotation_angle = M_PI / 2;
	else if(c == 'W')
		player->rotation_angle = M_PI;
}

void	init_raycasting(t_data *data)
{
	int	i = 0;
	data->player->x = (double)data->player->player_x * tile_size + tile_size / 2;
	data->player->y = (double)data->player->player_y * tile_size + tile_size / 2;
	data->player->radius = 3;
    set_direction(data->player, data->player->player_id);
    data->player->turn_direction = 0;
    data->player->walk_direction = 0;
    data->player->move_speed = 4;
    data->player->retation_speed = 2 * (M_PI /180);
	data->player->rays = malloc(s_w * sizeof(t_ray *));
	while (i < s_w)
   		data->player->rays[i++] = malloc(sizeof(t_ray));
	data->mlx = mlx_init(s_w, s_h, "MLX42", true);
    data->player->img = mlx_new_image(data->mlx, s_w, s_h);
	init_textures(data);
	black_window(data);
	//fill_window(data);
	//draw_circle(data->player->img, data->player->x, data->player->y, data->player->radius, data->colores->green_color);
    //draw_line(data->player->img, data->player->x, data->player->y, (data->player->x + cos(data->player->rotation_angle) * 50),(data->player->y + sin(data->player->rotation_angle) * 50), data->colores->red_color);
}