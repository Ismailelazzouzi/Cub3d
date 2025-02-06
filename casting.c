#include "cube.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	put_squer(uint32_t color, mlx_image_t *img, int h, int w, int x, int y)
{
	int	a;
	int	b;
	int	x1;

	a = y + w;
	b = x + h;
	x1 = x;
	while (y < a)
	{
		x = x1;
		while (x < b)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	put_pixel(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && x < s_w && y >= 0 && y < s_h)
		mlx_put_pixel(img, x, y, color);
}

void	draw_circle(mlx_image_t *img, int cx, int cy, int radius, int color)
{
	int	y;
	int	x;

	y = cy - radius;
	while (y <= cy + radius)
	{
		x = cx - radius;
		while (x <= cx + radius)
		{
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius)
				put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		put_pixel(img, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break;
		e2 = err * 2;
		if (e2 > - dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}
