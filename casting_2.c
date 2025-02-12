/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:25:57 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/11 22:25:59 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_texture(t_data *data, t_ray *ray)
{
	if (ray->was_hit_vertical == 0)
	{
		if (ray->is_facing_down)
			ray->texture = data->textures->west;
		else
			ray->texture = data->textures->east;
	}
	else
	{
		if (ray->is_fasing_right)
			ray->texture = data->textures->north;
		else
			ray->texture = data->textures->south;
	}
}

mlx_texture_t	*innit_draw(t_data *data, t_ray *ray)
{
	ray->texture = NULL;
	set_texture(data, ray);
	if (ray->was_hit_vertical)
		ray->tex_x = (int)((ray->wall_hit_y / TILE_SIZE) * ray->texture->width)
			% ray->texture->width;
	else
		ray->tex_x = (int)((ray->wall_hit_x / TILE_SIZE) * ray->texture->width)
			% ray->texture->width;
	if (ray->tex_x < 0)
		ray->tex_x += ray->texture->width;
	if ((!ray->was_hit_vertical && ray->is_facing_down) || 
		(ray->was_hit_vertical && ray->is_fasing_left))
		ray->tex_x = (int)ray->texture->width - ray->tex_x - 1;
	return (ray->texture);
}

void	draw_textured_wall(t_data *data, int x,
	double draw_start, double draw_end)
{
	int			y;
	double		step;
	double		tex_pos;
	uint32_t	color;
	uint8_t		*pixel;

	tex_pos = 0;
	data->ray->texture = innit_draw(data, data->ray);
	step = (double)data->ray->texture->height / (draw_end - draw_start);
	y = (int)draw_start;
	while (y < (int)draw_end)
	{
		if (y >= 0 && y < S_H && x >= 0 && x < S_W)
		{
			data->ray->tex_y = (int)tex_pos & (data->ray->texture->height - 1);
			pixel = &data->ray->texture->pixels[
				(data->ray->tex_y
					* data->ray->texture->width + data->ray->tex_x)
				* data->ray->texture->bytes_per_pixel];
			color = get_rgba(pixel[0], pixel[1], pixel[2], pixel[3]);
			mlx_put_pixel(data->player->img, x, y, color);
		}
		tex_pos += step;
		y++;
	}
}

void	render_rays(t_ray **rays, t_data *data)
{
	int		a;
	double	line_height;
	double	draw_begin;
	double	draw_end;

	a = 0;
	render_background(data);
	cast_rays(rays, data);
	while (a < S_W)
	{
		line_height = (32 / rays[a]->distance)
			* ((S_W / 2.0) / tan(data->fov / 2));
		draw_begin = (S_H / 2) - (line_height / 2);
		draw_end = draw_begin + line_height;
		data->ray = rays[a];
		draw_textured_wall(data, a, draw_begin, draw_end);
		a++;
	}
}

void	cast_rays(t_ray **rays, t_data *data)
{
	double	ray_angl; 
	int		a;

	ray_angl = data->player->rotation_angle - (data->fov / 2);
	a = 0;
	while (a < S_W)
	{
		init_ray(rays[a], ray_angl);
		cast(data, rays[a]);
		ray_angl += data->fov / S_W;
		a++;
	}
}
