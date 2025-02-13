/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:15:35 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/11 22:15:39 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	render_background(t_data *data)
{
	int	y;
	int	x;

	data->colores->floor_color
		= get_rgba(data->f[0], data->f[1], data->f[2], 100);
	data->colores->cieling_color
		= get_rgba(data->c[0], data->c[1], data->c[2], 100);
	y = 0;
	while (y < S_H)
	{
		x = 0;
		while (x < S_W)
		{
			if (y > S_H / 2)
				mlx_put_pixel(data->player->img, x,
					y, data->colores->floor_color);
			else
				mlx_put_pixel(data->player->img, x,
					y, data->colores->cieling_color);
			x++;
		}
		y++;
	}
}
