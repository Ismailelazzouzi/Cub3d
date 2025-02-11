/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:52:56 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/11 22:52:58 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	cleanup_textures(t_data *data)
{
	mlx_delete_texture(data->textures->north);
	mlx_delete_texture(data->textures->south);
	mlx_delete_texture(data->textures->east);
	mlx_delete_texture(data->textures->west);
	free(data->textures);
	data->textures = NULL;
}

void	init_textures(t_data *data)
{
	data->textures = malloc(sizeof(t_texture));
	if (!data->textures)
		err("zebi\n");
	data->textures->north = NULL;
	data->textures->south = NULL;
	data->textures->west = NULL;
	data->textures->east = NULL;
	data->textures->north = mlx_load_png(data->no);
	if (!data->textures->north)
		err("zebi\n");
	data->textures->east = mlx_load_png(data->ea);
	if (!data->textures->east)
		err("zebi\n");
	data->textures->west = mlx_load_png(data->we);
	if (!data->textures->west)
		err("zebi\n");
	data->textures->south = mlx_load_png(data->so);
	if (!data->textures->south)
		err("zebi\n");
}

void	set_direction(t_player *player, char c)
{
	if (c == 'N')
		player->rotation_angle = (3 * M_PI) / 2;
	else if (c == 'E')
		player->rotation_angle = 0;
	else if (c == 'S')
		player->rotation_angle = M_PI / 2;
	else if (c == 'W')
		player->rotation_angle = M_PI;
}

void	init_raycasting(t_data *data)
{
	int	i;

	i = 0;
	data->player->x = (double)data->player->player_x
		* tile_size + tile_size / 2;
	data->player->y = (double)data->player->player_y
		* tile_size + tile_size / 2;
	data->player->radius = 3;
	set_direction(data->player, data->player->player_id);
	data->player->turn_direction = 0;
	data->player->walk_direction = 0;
	data->player->move_speed = 4;
	data->player->retation_speed = 2 * (M_PI / 180);
	data->player->rays = malloc(s_w * sizeof(t_ray *));
	while (i < s_w)
		data->player->rays[i++] = malloc(sizeof(t_ray));
	data->mlx = mlx_init(s_w, s_h, "MLX42", true);
	data->player->img = mlx_new_image(data->mlx, s_w, s_h);
	init_textures(data);
}
