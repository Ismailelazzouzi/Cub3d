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
	while (i < data->rows_num - 1)
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
}

void	init_textures(t_data *data)
{
	data->textures->north = mlx_load_png(data->no);
	data->textures->south = mlx_load_png(data->so);
	data->textures->east = mlx_load_png(data->ea);
	data->textures->west = mlx_load_png(data->no);
}

void	init_raycasting(t_data *data)
{
	int	n_r = 500;
	int	i = 0;
	data->player->x = (double)data->player->player_x * tile_size + tile_size / 2;
	data->player->y = (double)data->player->player_y * tile_size + tile_size / 2;
	data->player->radius = 3;
    data->player->rotation_angle = 0;
    data->player->turn_direction = 0;
    data->player->walk_direction = 0;
    data->player->move_speed = 4;
    data->player->retation_speed = 2 * (M_PI /180);
	data->player->rays = malloc(n_r * sizeof(t_ray *));
	while (i < n_r)
   		data->player->rays[i++] = malloc(sizeof(t_ray));
	data->mlx = mlx_init(s_w, s_h, "MLX42", true);
    data->player->img = mlx_new_image(data->mlx, s_w, s_h);
	init_textures(data);
	//black_window(data);
	//fill_window(data);
	// draw_circle(data->player->img, data->player->x, data->player->y, data->player->radius, data->colores->green_color);
    // draw_line(data->player->img, data->player->x, data->player->y, (data->player->x + cos(data->player->rotation_angle) * 50),(data->player->y + sin(data->player->rotation_angle) * 50), data->colores->red_color);
}