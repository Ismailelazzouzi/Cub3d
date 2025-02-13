/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:13:22 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/11 21:13:25 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// void	cast_h_complete(t_data *data, t_ray *ray)
// {
// 	ray->inforays->grid_x = 
// 		floor (ray->inforays->next_horizontal_x / (double)TILE_SIZE);
// 	ray->inforays->grid_y = 
// 		floor (ray->inforays->next_horizontal_y / (double)TILE_SIZE);
// 	if (ray->inforays->grid_y < data->rows_num
// 		&& ray->inforays->grid_x
// 		< ft_strlen(data->map[ray->inforays->grid_y]))
// 		ray->inforays->s = data->map[(int) ray->inforays->grid_y]
// 		[(int) ray->inforays->grid_x];
// }

// void	cast_b_complete(t_data *data, t_ray *ray)
// {
// 	ray->wall_hit_x = ray->inforays->horizontal_hit_x;
// 	ray->wall_hit_y = ray->inforays->horizontal_hit_y;
// 	ray->distance = ray->inforays->h_d;
// 	ray->was_hit_vertical = 0;
// 	ray->color = get_rgba(128, 160, 128, 255);
// 	ray->texture_x = fmod(ray->wall_hit_x, TILE_SIZE) / TILE_SIZE;
// }

// void	cast_b_complete2(t_data *data, t_ray *ray)
// {
// 	ray->wall_hit_x = ray->inforays->vertical_hit_x;
// 	ray->wall_hit_y = ray->inforays->vertical_hit_y;
// 	ray->distance = ray->inforays->v_d;
// 	ray->color = get_rgba(255, 0, 0, 255);
// 	ray->texture_x = fmod(ray->wall_hit_y, TILE_SIZE) / TILE_SIZE;
// 	ray->was_hit_vertical = 1;
// 	if (ray->is_fasing_right)
// 		ray->wall_direction = 2;
// 	else
// 		ray->wall_direction = 3;
// }

// void	cast_v_complete(t_data *data, t_ray *ray)
// {
// 	ray->inforays->grid_x
// 		= floor(ray->inforays->next_vertical_x / (double)TILE_SIZE);
// 	ray->inforays->grid_y
// 		= floor(ray->inforays->next_vertical_y / (double)TILE_SIZE);
// 	if (ray->inforays->grid_y < data->rows_num 
// 		&& ray->inforays->grid_x
// 		< ft_strlen(data->map[ray->inforays->grid_y]))
// 		ray->inforays->s = data->map[(int) ray->inforays->grid_y]
// 		[(int) ray->inforays->grid_x];
// }

// void	cast_complete(t_data *data, t_ray *ray)
// {
// 	if (ray->is_fasing_right == 1)
// 		ray->inforays->first_intersection_x
// 			= (floor(data->player->x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
// 	else if (ray->is_fasing_left == 1)
// 		ray->inforays->first_intersection_x
// 			= (floor(data->player->x / TILE_SIZE) * TILE_SIZE) - 0.00000001;
// }

void	cast_horizontal(t_data *data, t_ray *ray)
{
	ray->inforays->xa = ray->inforays->ya / tan(ray->ray_angle);
	ray->inforays->next_horizontal_x = ray->inforays->first_intersection_x;
	ray->inforays->next_horizontal_y = ray->inforays->first_intersaction_y;
	while (ray->inforays->next_horizontal_x <= (data->column_num * 32)
		&& ray->inforays->next_horizontal_x >= 0
		&& ray->inforays->next_horizontal_y <= (data->rows_num * 32)
		&& ray->inforays->next_horizontal_y >= 0)
	{
		cast_h_complete(data, ray);
		if (ray->inforays->s == '1')
		{
			ray->inforays->found_horizontal_wall = 1;
			ray->inforays->horizontal_hit_x = ray->inforays->next_horizontal_x;
			ray->inforays->horizontal_hit_y = ray->inforays->next_horizontal_y;
			break ;
		}
		else
		{
			ray->inforays->next_horizontal_x += ray->inforays->xa;
			ray->inforays->next_horizontal_y += ray->inforays->ya;
		}
	}
}

void	before_cast_v(t_data *data, t_ray *ray)
{
	ray->inforays->first_intersaction_y
		= data->player->y
		+ (ray->inforays->first_intersection_x - data->player->x)
		* tan(ray->ray_angle);
	ray->inforays->next_vertical_x = ray->inforays->first_intersection_x;
	ray->inforays->next_vertical_y = ray->inforays->first_intersaction_y;
	if (ray->is_fasing_right == 1)
		ray->inforays->xa = TILE_SIZE;
	else if (ray->is_fasing_left == 1)
		ray->inforays->xa = TILE_SIZE * -1;
	ray->inforays->ya = ray->inforays->xa * tan(ray->ray_angle);
}

void	cast_vertical(t_data *data, t_ray *ray)
{
	before_cast_v(data, ray);
	while (ray->inforays->next_vertical_x
		<= (data->column_num * 32) && ray->inforays->next_vertical_x
		>= 0 && ray->inforays->next_vertical_y <= (data->rows_num * 32)
		&& ray->inforays->next_vertical_y >= 0)
	{
		cast_v_complete(data, ray);
		if (ray->inforays->s == '1')
		{
			ray->inforays->found_vertical_wall = 1;
			ray->inforays->vertical_hit_x = ray->inforays->next_vertical_x;
			ray->inforays->vertical_hit_y = ray->inforays->next_vertical_y;
			break ;
		}
		else
		{
			ray->inforays->next_vertical_x += ray->inforays->xa;
			ray->inforays->next_vertical_y += ray->inforays->ya;
		}
	}
}

void	cast_both(t_data *data, t_ray *ray)
{
	if (ray->inforays->found_horizontal_wall == 1)
		ray->inforays->h_d
			= calculate_distance(data->player->x, data->player->y,
				ray->inforays->horizontal_hit_x,
				ray->inforays->horizontal_hit_y);
	if (ray->inforays->found_vertical_wall == 1)
		ray->inforays->v_d
			= calculate_distance(data->player->x, data->player->y,
				ray->inforays->vertical_hit_x,
				ray->inforays->vertical_hit_y);
	if (ray->inforays->h_d < ray->inforays->v_d)
	{
		cast_b_complete(ray);
		if (ray->is_facing_down)
			ray->wall_direction = 0;
		else
			ray->wall_direction = 1;
	}
	else
		cast_b_complete2(ray);
	ray->distance *= cos(ray->ray_angle - data->player->rotation_angle);
}

void	cast(t_data *data, t_ray *ray)
{
	t_inforays	inforays;

	ray->inforays = &inforays;
	init_ray_info(ray);
	if (ray->is_fasing_up == 1)
		inforays.first_intersaction_y
			= floor(data->player->y / TILE_SIZE) * TILE_SIZE - 0.00000001;
	else if (ray->is_facing_down == 1)
		inforays.first_intersaction_y
			= (floor(data->player->y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
	inforays.first_intersection_x = data->player->x
		+ ((inforays.first_intersaction_y - data->player->y)
			/ tan(ray->ray_angle));
	if (ray->is_fasing_up == 1)
		inforays.ya = TILE_SIZE * -1;
	else if (ray->is_facing_down == 1)
		inforays.ya = TILE_SIZE;
	cast_horizontal(data, ray);
	cast_complete(data, ray);
	cast_vertical(data, ray);
	cast_both(data, ray);
}
