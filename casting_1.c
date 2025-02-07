#include "cube.h"

void	clear_image(mlx_image_t *img, uint32_t color)
{
	int	y;
	int	x;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

double	normalize(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy)); 
}

void render_background(t_data *data)
{
	int	y;
	int	x;

	data->colores->floor_color = get_rgba(data->f[0], data->f[1], data->f[2], 100);
	data->colores->cieling_color = get_rgba(data->c[0], data->c[1], data->c[2], 100);
	y = 0;
    while (y < s_h)
	{
		x = 0;
        while (x < s_w)
		{
            if (y > s_h / 2)
                mlx_put_pixel(data->player->img, x, y, data->colores->floor_color);
            else
                mlx_put_pixel(data->player->img, x, y, data->colores->cieling_color);
			x++;
        }
		y++;
    }
}

void draw_rect(mlx_image_t *img, int x, int y, int width, int height, uint32_t color)
{
    for (int j = 0; j < height; j++) {  // Loop through height (vertical lines)
        for (int i = 0; i < width; i++) {  // Loop through width (horizontal lines)
            int px = x + i;  // Calculate the x-coordinate for each pixel
            int py = y + j;  // Calculate the y-coordinate for each pixel

            // Ensure pixel is within screen bounds
            if (px >= 0 && px < (int)img->width && py >= 0 && py < (int)img->height) {
                mlx_put_pixel(img, px, py, color);  // Draw pixel
            }
        }
    }
}
