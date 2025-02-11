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

void	cast_h_complete(t_data *data, t_ray *ray)
{
	ray->inforays->grid_x = 
		floor (ray->inforays->next_horizontal_x / (double)tile_size);
	ray->inforays->grid_y = 
		floor (ray->inforays->next_horizontal_y / (double)tile_size);
	if (ray->inforays->grid_y < data->rows_num
		&& ray->inforays->grid_x
		< ft_strlen(data->map[ray->inforays->grid_y]))
		ray->inforays->s = data->map[(int) ray->inforays->grid_y]
		[(int) ray->inforays->grid_x];
}

void	cast_b_complete(t_data *data, t_ray *ray)
{
	ray->wall_hit_x = ray->inforays->horizontal_hit_x;
	ray->wall_hit_y = ray->inforays->horizontal_hit_y;
	ray->distance = ray->inforays->h_d;
	ray->was_hit_vertical = 0;
	ray->color = get_rgba(128, 160, 128, 255);
	ray->texture_x = fmod(ray->wall_hit_x, tile_size) / tile_size;
}

void	cast_b_complete2(t_data *data, t_ray *ray)
{
	ray->wall_hit_x = ray->inforays->vertical_hit_x;
	ray->wall_hit_y = ray->inforays->vertical_hit_y;
	ray->distance = ray->inforays->v_d;
	ray->color = get_rgba(255, 0, 0, 255);
	ray->texture_x = fmod(ray->wall_hit_y, tile_size) / tile_size;
	ray->was_hit_vertical = 1;
	if (ray->is_fasing_right)
		ray->wall_direction = 2;
	else
		ray->wall_direction = 3;
}

void	cast_v_complete(t_data *data, t_ray *ray)
{
	ray->inforays->grid_x
		= floor(ray->inforays->next_vertical_x / (double)tile_size);
	ray->inforays->grid_y
		= floor(ray->inforays->next_vertical_y / (double)tile_size);
	if (ray->inforays->grid_y < data->rows_num 
		&& ray->inforays->grid_x
		< ft_strlen(data->map[ray->inforays->grid_y]))
		ray->inforays->s = data->map[(int) ray->inforays->grid_y]
		[(int) ray->inforays->grid_x];
}

void	cast_complete(t_data *data, t_ray *ray)
{
	if (ray->is_fasing_right == 1)
		ray->inforays->first_intersection_x
			= (floor(data->player->x / tile_size) * tile_size) + tile_size;
	else if (ray->is_fasing_left == 1)
		ray->inforays->first_intersection_x
			= (floor(data->player->x / tile_size) * tile_size) - 0.00000001;
}
