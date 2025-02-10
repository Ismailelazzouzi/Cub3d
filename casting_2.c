#include "cube.h"

mlx_texture_t	*innit_draw(t_data *data, t_ray *ray)
{
	ray->texture = NULL;
	if (ray->was_hit_vertical == 0)
	    if (ray->is_facing_down)
	        ray->texture = data->textures->west;
	    else
	        ray->texture = data->textures->east;
	else
	    if (ray->is_fasing_right)
	        ray->texture = data->textures->north;
	    else
	        ray->texture = data->textures->south;
	if (ray->was_hit_vertical)
		ray->tex_x = (int)((ray->wall_hit_y / tile_size) * ray->texture->width)
			% ray->texture->width;
	else
		ray->tex_x = (int)((ray->wall_hit_x / tile_size) * ray->texture->width)
			% ray->texture->width;
	if (ray->tex_x < 0)
		ray->tex_x += ray->texture->width;

    if ((!ray->was_hit_vertical && ray->is_facing_down) || 
        (ray->was_hit_vertical && ray->is_fasing_left))
	ray->tex_x = (int)ray->texture->width - ray->tex_x - 1;
	return (ray->texture);
}

void draw_textured_wall(t_data *data, int x, double draw_start, double draw_end)
{
	int	y;
    double step;
    double tex_pos = 0;
	uint32_t color;
	uint8_t *pixel;

	data->ray->texture = innit_draw(data, data->ray);
	step = (double)data->ray->texture->height / (draw_end - draw_start);
	y = (int)draw_start;
    while (y < (int)draw_end)
    {
        if (y >= 0 && y < s_h && x >= 0 && x < s_w)
        {
            data->ray->tex_y = (int)tex_pos & (data->ray->texture->height - 1);
            pixel = &data->ray->texture->pixels[
                (data->ray->tex_y * data->ray->texture->width + data->ray->tex_x) * data->ray->texture->bytes_per_pixel];
            
            color = get_rgba(pixel[0], pixel[1], pixel[2], pixel[3]);
            mlx_put_pixel(data->player->img, x, y, color);
        }
        tex_pos += step;
		y++;
    }
}

void	render_rays(t_ray **rays, t_data *data)
{
	int	a;
	double line_height;
    double draw_begin;
    double draw_end;

	a = 0;
	render_background(data);
	cast_rays(rays, data);
	// while (a < s_w)
	// {
	// 	draw_line(data->player->img, data->player->x, data->player->y,
	// 		rays[a]->wall_hit_x, rays[a]->wall_hit_y, data->colores->red_color);
	// 	a++;
	// }
	while (a < s_w)
	{
		line_height = (32 / rays[a]->distance) * ((s_w/ 2.0) / tan(fov / 2));
		draw_begin = (s_h / 2) - (line_height / 2);
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

	ray_angl = data->player->rotation_angle - (fov / 2);
	a = 0;
	while (a < s_w)
	{
		init_ray(rays[a], ray_angl);
		cast(data, rays[a]);
		ray_angl += fov / s_w;
		a++;
	}
}

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
