#include "cube.h"

void	update_2(t_data *data, int i, int j)
{
	int	tile_x;
	int	tile_y;

	tile_x = j * tile_size;
	tile_y = i * tile_size;
	if (data->map[i][j] == '0' || data->map[i][j] == 'E')
		put_squer(data->colores->white_color, data->player->img, tile_size - 1, tile_size - 1, tile_x, tile_y);
	else if (data->map[i][j] == '1')
		put_squer(data->colores->gray_color, data->player->img, tile_size - 1, tile_size - 1, tile_x, tile_y);
	else if (data->map[i][j] != '0' && data->map[i][j] != '1')
		put_squer(data->colores->red_color, data->player->img, tile_size - 1, tile_size - 1, tile_x, tile_y);
}

void	update_1(t_data *data)
{
	int	i;
	int	j;
	int	tile_x;
	int	tile_y;

	i = 0;
	tile_x = 0;
	tile_y = 0;
	while (i < data->rows_num - 1)
	{
		j = 0;
		while (j < (int)ft_strlen(data->map[i]) - 1)
		{
			update_2(data, i, j);
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

void	update(struct mlx_key_data key_data, t_data *data)
{
	double	move_step;

	data->player->turn_direction = 0;
	data->player->walk_direction = 0;
	if (key_data.key == MLX_KEY_RIGHT)
		data->player->turn_direction = 1;
	if (key_data.key == MLX_KEY_LEFT)
		data->player->turn_direction = -1;
	if (key_data.key == MLX_KEY_UP)
		data->player->walk_direction = 1;
	if (key_data.key == MLX_KEY_DOWN)
		data->player->walk_direction = -1;
	clear_image(data->player->img, get_rgba(0, 0, 0, 255));
	//update_1(data);
	move_step = data->player->walk_direction * data->player->move_speed;
	data->player->rotation_angle += 
		data->player->turn_direction * data->player->retation_speed;
	data->player->x += cos(data->player->rotation_angle) * move_step;
	data->player->y += sin(data->player->rotation_angle) * move_step;
	//draw_circle(data->player->img, data->player->x, data->player->y, data->player->radius, get_rgba(255, 0, 0, 255));
	render_rays(data->player->rays, data);
}
