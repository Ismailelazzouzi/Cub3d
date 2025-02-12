/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:29:35 by isel-azz          #+#    #+#             */
/*   Updated: 2025/02/12 21:29:38 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	info_check_1(t_data *data, int *i)
{
	if ((data->info[*i][0] == 'N' && data->info[*i][1] == 'O'
			&& data->info[*i][2] == ' ') || (data->info[*i][0] == 'S'
			&& data->info[*i][1] == 'O' && data->info[*i][2] == ' ')
			|| (data->info[*i][0] == 'W'
			&& data->info[*i][1] == 'E' && data->info[*i][2] == ' ')
			|| (data->info[*i][0] == 'E'
			&& data->info[*i][1] == 'A' && data->info[*i][2] == ' '))
		data->textures_num++;
	if ((data->info[*i][0] == 'C' && data->info[*i][1] == ' ')
		|| (data->info[*i][0] == 'F' && data->info[*i][1] == ' '))
		data->colors_num++;
}

void	info_check_2(t_data *data, int *i)
{
	if (data->info[*i][0] == 'N' && data->info[*i][1] == 'O'
		&& data->info[*i][2] == ' ' && data->no == NULL)
		data->no = ft_strtrim(data->info[*i] + 3, " \t\v\f\r\n");
	else if (data->info[*i][0] == 'S' && data->info[*i][1] == 'O'
		&& data->info[*i][2] == ' ' && data->so == NULL)
		data->so = ft_strtrim(data->info[*i] + 3, " \t\v\f\r\n");
	else if (data->info[*i][0] == 'W' && data->info[*i][1] == 'E'
		&& data->info[*i][2] == ' ' && data->we == NULL)
		data->we = ft_strtrim(data->info[*i] + 3, " \t\v\f\r\n");
	else if (data->info[*i][0] == 'E' && data->info[*i][1] == 'A'
		&& data->info[*i][2] == ' ' && data->ea == NULL)
		data->ea = ft_strtrim(data->info[*i] + 3, " \t\v\f\r\n");
	else if (data->info[*i][0] == 'C' && data->info[*i][1] == ' ')
		parse_colors(data, data->info[*i] + 2, data->c);
	else if (data->info[*i][0] == 'F' && data->info[*i][1] == ' ')
		parse_colors(data, data->info[*i] + 2, data->f);
}

void	info_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->info[i])
	{
		info_check_1(data, &i);
		info_check_2(data, &i);
		i++;
	}
	if (data->colors_num != 2 || data->textures_num != 4)
		data->killflag = true;
}

void	check_holes1(t_data *data, char **illusion, int *i, int *j)
{
	if (illusion[*i][*j] == '0' || playerpos(illusion[*i][*j], "NESW"))
	{
		if (illusion[*i][*j - 1] == ' ' || illusion[*i][*j + 1] == ' ' ||
		illusion[*i - 1][*j] == ' ' || illusion[*i + 1][*j] == ' ')
			free_data(data, illusion, true);
		if (playerpos(illusion[*i][*j], "NSWE"))
		{
			data->player->player_x = *j;
			data->player->player_y = *i;
			data->player->player_id = data->map[*i][*j];
		}
	}
}

void	check_holes(t_data *data, char **illusion)
{
	int	i;
	int	j;

	i = 0;
	while (illusion[i])
	{
		j = 0;
		while (illusion[i][j])
		{
			check_holes1(data, illusion, &i, &j);
			j++;
		}
		i++;
	}
	free_arr(illusion);
}
