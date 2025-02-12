/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:17:03 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/12 20:17:06 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_and_exit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	exit(0);
}

void	keys_effects(struct mlx_key_data key_data, t_data *data)
{
	data->player->l_r = 0;
	data->player->turn_direction = 0;
	data->player->walk_direction = 0;
	if (key_data.key == MLX_KEY_RIGHT)
		data->player->turn_direction = 2;
	if (key_data.key == MLX_KEY_LEFT)
		data->player->turn_direction = -2;
	if (key_data.key == MLX_KEY_D)
		data->player->l_r = 1;
	if (key_data.key == MLX_KEY_A)
		data->player->l_r = -1;
	if (key_data.key == MLX_KEY_W)
		data->player->walk_direction = 2;
	if (key_data.key == MLX_KEY_S)
		data->player->walk_direction = -2;
	if (key_data.key == MLX_KEY_ESCAPE)
		free_and_exit(data);
}

void	update_complete2(t_data *data, double *x1, double *y1)
{
	if (data->player->l_r == 1 || data->player->turn_direction)
	{
		*x1 = data->player->x - sin(data->player->rotation_angle)
			* (data->player->move_speed * 2);
		*y1 = data->player->y + cos(data->player->rotation_angle)
			* (data->player->move_speed * 2);
	}
	if (data->player->l_r == -1 || data->player->turn_direction)
	{
		*x1 = data->player->x + sin(data->player->rotation_angle)
			* (data->player->move_speed * 2);
		*y1 = data->player->y - cos(data->player->rotation_angle)
			* (data->player->move_speed * 2);
	}
}

void	update_complete(t_data *data, double *x1, double *y1, double *move_step)
{
	if (data->player->walk_direction != 0 || data->player->turn_direction)
	{
		*move_step = data->player->walk_direction * data->player->move_speed;
		*x1 = data->player->x
			+ cos(data->player->rotation_angle) * (*move_step);
		*y1 = data->player->y
			+ sin(data->player->rotation_angle) * (*move_step);
	}
	else if (data->player->l_r != 0 || data->player->turn_direction)
		update_complete2(data, x1, y1);
	else
	{
		*x1 = data->player->x;
		*y1 = data->player->y;
	}
}

void	update(struct mlx_key_data key_data, t_data *data)
{
	double	move_step;
	double	x1;
	double	y1;
	char	s;

	x1 = 0;
	y1 = 0;
	keys_effects(key_data, data);
	clear_image(data->player->img, get_rgba(0, 0, 0, 255));
	data->player->rotation_angle += 
		data->player->turn_direction * data->player->retation_speed;
	update_complete(data, &x1, &y1, &move_step);
	s = data->map
	[(int)floor(y1 / (double)TILE_SIZE)][(int)floor(x1 / (double)TILE_SIZE)];
	if (s == '0' || s == data->player->player_id)
	{
		data->player->x = x1;
		data->player->y = y1;
	}
	render_rays(data->player->rays, data);
}
