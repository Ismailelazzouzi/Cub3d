/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:19:08 by isel-azz          #+#    #+#             */
/*   Updated: 2025/01/22 11:19:12 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	leakcheck(void)
{
	system("leaks cub3d");
}

void	parse(t_data *data, t_player *player, t_colors *colores, char *argv1)
{
	init_game_data(data, player, colores);
	get_file_content(data, argv1);
	check_file_content(data);
	check_data_validity(data);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	cleanup_textures(data);
	free_data(data, data->map, false);
	free_arr(data->maze);
	free_arr(data->info);
	while (i < S_W)
	{
		if (data->player->rays[i])
			free(data->player->rays[i]);
		i++;
	}
	if (data->player->rays)
		free(data->player->rays);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_player	player;
	t_colors	colores;
	int			i;

	i = 0;
	atexit(leakcheck);
	if (argc != 2)
		err("wrong number of args\n");
	if (argv[1])
		check_extention(argv[1], ".cub", false, &data);
	parse(&data, &player, &colores, argv[1]);
	init_raycasting(&data);
	render_rays(player.rays, &data);
	mlx_image_to_window(data.mlx, player.img, 0, 0);
	mlx_key_hook(data.mlx, (mlx_keyfunc)update, &data);
	mlx_close_hook(data.mlx, &free_and_exit, &data);
	mlx_loop(data.mlx);
	free_all(&data);
	mlx_delete_image(data.mlx, data.player->img);
	mlx_terminate(data.mlx);
	return (0);
}
