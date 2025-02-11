#include "cube.h"

void	update_2(t_data *data, int i, int j)
{
	int	tile_x;
	int	tile_y;

	tile_x = j * tile_size;
	tile_y = i * tile_size;
	if (data->map[i][j] == '0' || data->map[i][j] == data->player->player_id)
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
	while (i < data->rows_num)
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

void	free_and_exit(void *param)
{
	t_data *data;

	data = (t_data *)param;
	// cleanup_textures(data);
	// free_arr(data->map);
	// free_arr(data->maze);
	// free_arr(data->info);
	// int i = 0;
	// while(i < s_w)
	// {
	// 	if(data->player->rays[i])
	// 		free(data->player->rays[i]);
	// 	i++;
	// }
	// if(data->player->rays)
	// 	free(data->player->rays);
	// mlx_delete_image(data->mlx, data->player->img);
	// mlx_terminate(data->mlx);
	//(void)data;
	exit(0);
}

void	update(struct mlx_key_data key_data, t_data *data)
{
	double	move_step;
	double	x1;
	double	y1;

	x1 = 0;
	y1 = 0;
	data->player->l_r = 0;
	data->player->turn_direction = 0;
	data->player->walk_direction = 0;
	if (key_data.key == MLX_KEY_RIGHT)
		data->player->turn_direction = 2;
	if (key_data.key == MLX_KEY_LEFT)
		data->player->turn_direction = -2;
	if (key_data.key == MLX_KEY_D )
        data->player->l_r= 1;
    if (key_data.key == MLX_KEY_A )
        data->player->l_r= -1;
	if (key_data.key == MLX_KEY_W)
		data->player->walk_direction = 2;
	if (key_data.key == MLX_KEY_S)
		data->player->walk_direction = -2;
	if (key_data.key == MLX_KEY_ESCAPE)
		free_and_exit(data);
	
	clear_image(data->player->img, get_rgba(0, 0, 0, 255));
	update_1(data);
	
		data->player->rotation_angle += 
		data->player->turn_direction * data->player->retation_speed;
	
	
	// data->player->x += cos(data->player->rotation_angle) * move_step;
	// data->player->y += sin(data->player->rotation_angle) * move_step;
	if(data->player->walk_direction != 0 || data->player->turn_direction)
    {
		move_step = data->player->walk_direction * data->player->move_speed;
        x1 = data->player->x + cos(data->player->rotation_angle) * move_step;
        y1 = data->player->y + sin(data->player->rotation_angle) * move_step;
    }
	else if(data->player->l_r !=0 || data->player->turn_direction)
    {
        if(data->player->l_r == 1 || data->player->turn_direction)
        {
             x1 = data->player->x - sin(data->player->rotation_angle) * (data->player->move_speed * 2);
             y1 = data->player->y + cos(data->player->rotation_angle) * (data->player->move_speed * 2);
        }
        if(data->player->l_r == -1 || data->player->turn_direction)
        {
            x1 = data->player->x + sin(data->player->rotation_angle) * (data->player->move_speed * 2);
        	 y1 = data->player->y - cos(data->player->rotation_angle) * (data->player->move_speed * 2);
        }
             
    }
	else
	{
		x1 = data->player->x;
		y1 = data->player->y;
	}
	char s = data->map[(int)floor(y1 /(double)tile_size)][(int)floor(x1 /(double)tile_size)];

	if(s == '0' || s == data->player->player_id)
    {
        data->player->x = x1;
        data->player->y = y1;
    }
	draw_circle(data->player->img, data->player->x, data->player->y, data->player->radius, get_rgba(255, 0, 0, 255));
	render_rays(data->player->rays, data);
}
