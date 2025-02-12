/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:49:19 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/11 22:49:23 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	put_squer(uint32_t color, mlx_image_t *img, int x, int y)
{
	int	a;
	int	b;
	int	x1;

	a = y + (TILE_SIZE - 1);
	b = x + (TILE_SIZE - 1);
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
	if (x >= 0 && x < S_W && y >= 0 && y < S_H)
		mlx_put_pixel(img, x, y, color);
}
