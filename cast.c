#include "cube.h"


int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}



void put_squer(uint32_t color,mlx_image_t *img,int h, int w,int x, int y)
{
    int a = y + w;
int b = x + h;
int x1 = x;
    while ( y < a) {
        x = x1;
        while (x < b) {
            mlx_put_pixel(img, x, y, color);
            x++;
        }
        y++;
    }
}

void put_pixel(mlx_t *mlx, mlx_image_t *img, int x, int y, int color)
{
    if (x >= 0 && x < s_w && y >= 0 && y < s_h)
        mlx_put_pixel(img, x, y, color);
}

void draw_circle(mlx_t *mlx, mlx_image_t *img, int cx, int cy, int radius, int color)
{
    for (int y = cy - radius; y <= cy + radius; y++) {
        for (int x = cx - radius; x <= cx + radius; x++) {
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius) {
                put_pixel(mlx, img, x, y, color);
            }
        }
    }
}

void draw_line(mlx_t *mlx, mlx_image_t *img, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        put_pixel(mlx, img, x1, y1, color);

        if (x1 == x2 && y1 == y2)
            break;
        
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void clear_image(mlx_image_t *img, uint32_t color) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            mlx_put_pixel(img, x, y, color);
        } 
    }
}


double normalize(double angle)
{
   angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void init_ray(t_ray *ray, double angle)
{
    ray->ray_angle = normalize(angle);
    ray->distance = 0;
    ray->color = get_rgba(255,0,0,255);
    ray->is_facing_down = 0;
    ray->is_fasing_up = 0;
    ray->is_fasing_right = 0;
    ray->is_fasing_left = 0;
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

double calculate_distance(double x1, double y1, double x2, double y2) 
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy); 
}

void    cast_horizontal(t_data *data, t_ray *ray)
{
    ray->inforays->xa = ray->inforays->ya / tan(ray->ray_angle);
    ray->inforays->next_horizontal_x = ray->inforays->first_intersection_x;
    ray->inforays->next_horizontal_y = ray->inforays->first_intersaction_y;
    while (ray->inforays->next_horizontal_x <= (data->column_num * 32) && ray->inforays->next_horizontal_x >= 0 && ray->inforays->next_horizontal_y <= (data->rows_num * 32) && ray->inforays->next_horizontal_y >= 0)
    {
        ray->inforays->grid_x = floor(ray->inforays->next_horizontal_x /(double)tile_size);
        ray->inforays->grid_y = floor(ray->inforays->next_horizontal_y/ (double)tile_size);
        ray->inforays->s = data->map[(int) ray->inforays->grid_y][(int) ray->inforays->grid_x];
        if (ray->inforays->s == '1')
        {
            ray->inforays->found_horizontal_wall = 1;
            ray->inforays->horizontal_hit_x = ray->inforays->next_horizontal_x;
            ray->inforays->horizontal_hit_y = ray->inforays->next_horizontal_y;
            break;
        }
        else
        {
            ray->inforays->next_horizontal_x += ray->inforays->xa;
            ray->inforays->next_horizontal_y += ray->inforays->ya;
        }
    }
}

void    before_cast_v(t_data *data, t_ray *ray)
{
    ray->inforays->first_intersaction_y = data->player->y + (ray->inforays->first_intersection_x - data->player->x) * tan(ray->ray_angle);
    ray->inforays->next_vertical_x = ray->inforays->first_intersection_x;
    ray->inforays->next_vertical_y = ray->inforays->first_intersaction_y;
    if (ray->is_fasing_right == 1)
        ray->inforays->xa = tile_size;
    else if(ray->is_fasing_left == 1)
        ray->inforays->xa = tile_size * -1;
    ray->inforays->ya = ray->inforays->xa * tan(ray->ray_angle);
}

void    cast_vertical(t_data *data, t_ray *ray)
{
    before_cast_v(data, ray);
    while (ray->inforays->next_vertical_x <= (data->column_num * 32) && ray->inforays->next_vertical_x >= 0 && ray->inforays->next_vertical_y <= (data->rows_num * 32) && ray->inforays->next_vertical_y >= 0)
    {
        ray->inforays->grid_x = floor(ray->inforays->next_vertical_x /(double)tile_size);
        ray->inforays->grid_y = floor(ray->inforays->next_vertical_y/ (double)tile_size);
        ray->inforays->s = data->map[(int) ray->inforays->grid_y][(int) ray->inforays->grid_x];
        if (ray->inforays->s == '1')
        {
            ray->inforays->found_vertical_wall = 1;
            ray->inforays->vertical_hit_x = ray->inforays->next_vertical_x;
            ray->inforays->vertical_hit_y = ray->inforays->next_vertical_y;
            break;
        }
        else
        {
            ray->inforays->next_vertical_x += ray->inforays->xa;
            ray->inforays->next_vertical_y += ray->inforays->ya;
        }
    }
}

void    cast_both(t_data *data, t_ray *ray)
{
    if (ray->inforays->found_horizontal_wall == 1)
        ray->inforays->h_d = calculate_distance(data->player->x, data->player->y, ray->inforays->horizontal_hit_x, ray->inforays->horizontal_hit_y);
    if (ray->inforays->found_vertical_wall== 1)
        ray->inforays->v_d =  calculate_distance(data->player->x, data->player->y, ray->inforays->vertical_hit_x, ray->inforays->vertical_hit_y);
    if (ray->inforays->h_d < ray->inforays->v_d)
    {
        ray->wall_hit_x = ray->inforays->horizontal_hit_x;
        ray->wall_hit_y = ray->inforays->horizontal_hit_y;
        ray->distance = ray->inforays->h_d;
        ray->color = get_rgba(128,160,128,255);
    }
    else
    {
        ray->wall_hit_x = ray->inforays->vertical_hit_x;
        ray->wall_hit_y = ray->inforays->vertical_hit_y;
        ray->distance = ray->inforays->v_d;
        ray->color = get_rgba(255,0,0,255);
    }
    ray->distance *= cos(ray->ray_angle - data->player->rotation_angle); 
}

void    init_ray_info(t_data *data, t_ray *ray)
{
    ray->inforays->first_intersection_x = 0;
    ray->inforays->first_intersaction_y = 0;
    ray->inforays->xa = 0;
    ray->inforays->ya = 0;
    ray->inforays->found_horizontal_wall =  0;
    ray->inforays->horizontal_hit_x = 0;
    ray->inforays->horizontal_hit_y = 0;
    ray->inforays->found_vertical_wall  = 0;
    ray->inforays->vertical_hit_x = 0;
    ray->inforays->vertical_hit_y = 0;
    ray->inforays->grid_x = 0;
    ray->inforays->grid_y = 0;
    ray->inforays->h_d = INT_MAX;
    ray->inforays->v_d = INT_MAX;
}

void cast(t_data *data, t_ray *ray)
{
    t_inforays inforays;

    ray->inforays = &inforays;
    init_ray_info(data, ray);
    if (ray->is_fasing_up == 1)
        inforays.first_intersaction_y =floor(data->player->y / tile_size ) * tile_size - 0.00000001;
    else if(ray->is_facing_down == 1)
        inforays.first_intersaction_y = (floor(data->player->y/ tile_size ) * tile_size) + tile_size;
    inforays.first_intersection_x = data->player->x + ((inforays.first_intersaction_y - data->player->y) / tan(ray->ray_angle));
    if (ray->is_fasing_up == 1)
        inforays.ya = tile_size * -1;
    else if (ray->is_facing_down == 1)
        inforays.ya = tile_size;
    cast_horizontal(data, ray);
    if(ray->is_fasing_right == 1)
        inforays.first_intersection_x = (floor(data->player->x / tile_size) * tile_size) + tile_size;
    else if( ray->is_fasing_left == 1)
        inforays.first_intersection_x = (floor(data->player->x / tile_size) * tile_size) - 0.00000001;
    cast_vertical(data, ray);
    cast_both(data, ray);
}

 void cast_rays(t_ray **rays, t_data *data)
{
    int n_r = 2000;
    double ray_angl = data->player->rotation_angle - (fov / 2); 
    int a = 0;
    
    while (a < n_r)
    {
        
        init_ray(rays[a], ray_angl);
        cast(data, rays[a]);
        ray_angl += fov / n_r;
        a++;
    }
}

void render_rays(t_ray **rays,t_data *data)
{
    cast_rays(rays, data);
    int n_r = 2000;
    int a = 0;
    while(a < n_r)
    {
        draw_line(data->mlx, data->player->img, data->player->x, data->player->y, rays[a]->wall_hit_x, rays[a]->wall_hit_y, data->colores->red_color);
        a++;
    }
}

void update(struct mlx_key_data key_data, t_data *data)
{
    double move_step;

    uint32_t black_color = get_rgba(0,0,0,255);
    uint32_t white_color = get_rgba(255,250,255,255);
    uint32_t gray_color = get_rgba(128,128,128,255);
    uint32_t red_color = get_rgba(255,0,0,255);
	uint32_t green_color = get_rgba(0,255,0,255);

    data->player->turn_direction = 0;
    data->player->walk_direction = 0;

  if(key_data.key == MLX_KEY_RIGHT)
    {
       
        data->player->turn_direction = 1;
    }
    if(key_data.key == MLX_KEY_LEFT)
        data->player->turn_direction = -1;
    if(key_data.key == MLX_KEY_UP)
        data->player->walk_direction = 1;
    if(key_data.key == MLX_KEY_DOWN)
        data->player->walk_direction = -1;

    clear_image(data->player->img, get_rgba(0, 0, 0, 255));

    int i = 0, j = 0;
	int tile_x = 0, tile_y = 0;

	while (i < data->rows_num - 1)
	{
		j = 0;
		while (j < ft_strlen(data->map[i]) - 1)
		{
			tile_x = j * tile_size;
        	tile_y = i * tile_size;
			if (data->map[i][j] == '0' || data->map[i][j] == 'E')
            	put_squer(white_color,data->player->img,tile_size-1, tile_size-1,tile_x,tile_y);
			else if(data->map[i][j] == '1')
                put_squer(gray_color,data->player->img,tile_size-1, tile_size-1,tile_x,tile_y);
			else if (data->map[i][j] != '0' && data->map[i][j] != '1')
				put_squer(red_color, data->player->img,tile_size-1, tile_size-1,tile_x,tile_y);
			j++;
		}
        while(j < data->column_num)
		{
				tile_x = j * tile_size;
        	tile_y = i * tile_size;
			put_squer(red_color, data->player->img,tile_size-1, tile_size-1,tile_x,tile_y);
			j++;
		}
        i++;
    }
    move_step = data->player->walk_direction * data->player->move_speed;
    data->player->rotation_angle += data->player->turn_direction * data->player->retation_speed;
    data->player->x += cos(data->player->rotation_angle) * move_step;
    data->player->y += sin(data->player->rotation_angle) * move_step;
    draw_circle(data->mlx, data->player->img, data->player->x, data->player->y, data->player->radius, get_rgba(255, 0, 0, 255));
    render_rays(data->player->rays, data);

}