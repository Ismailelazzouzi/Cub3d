#include "cube.h"

void draw_textured_wall(t_data *data, t_ray *ray, int x, double draw_start, double draw_end)
{
	mlx_texture_t *texture;

	if (ray->wall_direction == NORTH)
    	texture = data->textures->north;
	else if (ray->wall_direction == SOUTH)
    	texture = data->textures->south;
	else if (ray->wall_direction == EAST)
    	texture = data->textures->east;
	else
    	texture = data->textures->west;
	

	int tex_x = (int)(ray->texture_x * texture->width);
    if ((!ray->was_hit_vertical && ray->is_facing_down) || 
        (ray->was_hit_vertical && ray->is_fasing_left))
        tex_x = texture->width - tex_x - 1;
    
    // Calculate step size for texture coordinate
    double step = (double)texture->height / (draw_end - draw_start);
    double tex_pos = 0;
    // Draw the vertical strip
    for (int y = (int)draw_start; y < (int)draw_end; y++)
    {
        if (y >= 0 && y < s_h && x >= 0 && x < s_w)
        {
            int tex_y = (int)tex_pos & (texture->height - 1);
            uint8_t *pixel = &texture->pixels[
                (tex_y * texture->width + tex_x) * texture->bytes_per_pixel];
            
            uint32_t color = get_rgba(pixel[0], pixel[1], pixel[2], pixel[3]);
            mlx_put_pixel(data->player->img, x, y, color);
        }
        tex_pos += step;
    }
}

void	render_rays(t_ray **rays, t_data *data)
{
	int	n_r;
	int	a;

	a = 0;
	n_r = 500;
	render_background(data);
	cast_rays(rays, data);
	// while (a < n_r)
	// {
	// 	draw_line(data->player->img, data->player->x, data->player->y,
	// 		rays[a]->wall_hit_x, rays[a]->wall_hit_y, data->colores->red_color);
	// 	a++;
	// }
	while (a < n_r)
	{
		double line_height = (32 / rays[a]->distance) * ((s_w/ 2.0) / tan(fov / 2));  // Calculate wall slice height
    	double draw_begin = (s_h / 2) - (line_height / 2);  // Top of the wall slice
    	double draw_end = draw_begin + line_height;  // Bottom of the wall slice

    	// Cast draw_begin and draw_end to integers (if required by your function)
   	 	//draw_rect(data->player->img, a * 1, (int)draw_begin, 1, (int)(draw_end - draw_begin), rays[a]->color);
		draw_textured_wall(data, rays[a], a, draw_begin, draw_end);
		a++;
	}
}

void	cast_rays(t_ray **rays, t_data *data)
{
	int		n_r;
	double	ray_angl; 
	int		a;

	n_r = 500;
	ray_angl = data->player->rotation_angle - (fov / 2);
	a = 0;
	while (a < n_r)
	{
		init_ray(rays[a], ray_angl);
		cast(data, rays[a]);
		ray_angl += fov / n_r;
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
