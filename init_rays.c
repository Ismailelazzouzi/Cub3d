/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:41:26 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/11 22:41:29 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_ray(t_ray *ray, double angle)
{
	init_ray1(ray, angle);
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
	{
		ray->is_facing_down = 1;
		ray->is_fasing_up = 0;
	}
	else
	{
		ray->is_facing_down = 0;
		ray->is_fasing_up = 1;
	}
	if (ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI)
	{
		ray->is_fasing_right = 1;
		ray->is_fasing_left = 0;
	}
	else
	{
		ray->is_fasing_right = 0;
		ray->is_fasing_left = 1;
	}
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->texture_x = 0;
}

void	init_ray1(t_ray *ray, double angle)
{
	ray->ray_angle = normalize(angle);
	ray->distance = 0;
	ray->color = get_rgba(255, 0, 0, 255);
	ray->is_facing_down = 0;
	ray->is_fasing_up = 0;
	ray->is_fasing_right = 0;
	ray->is_fasing_left = 0;
}

void	init_ray_info(t_ray *ray)
{
	ray->inforays->first_intersection_x = 0;
	ray->inforays->first_intersaction_y = 0;
	ray->inforays->xa = 0;
	ray->inforays->ya = 0;
	ray->inforays->found_horizontal_wall = 0;
	ray->inforays->horizontal_hit_x = 0;
	ray->inforays->horizontal_hit_y = 0;
	ray->inforays->found_vertical_wall = 0;
	ray->inforays->vertical_hit_x = 0;
	ray->inforays->vertical_hit_y = 0;
	ray->inforays->grid_x = 0;
	ray->inforays->grid_y = 0;
	ray->inforays->h_d = INT_MAX;
	ray->inforays->v_d = INT_MAX;
}
