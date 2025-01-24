/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-azz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:25:41 by isel-azz          #+#    #+#             */
/*   Updated: 2025/01/22 11:25:44 by isel-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include "Libft/libft.h"
# include "get_next_line.h"

typedef struct s_player
{
	char	player_id;
	int		player_x;
	int		player_y;
}	t_player;

typedef struct s_data
{
	struct s_player	*player;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	char			**maze;
	int				c[3];
	int				f[3];
	int				fileheight;
	int				rows_num;
	int				column_num;
	int				textures_num;
	int				colors_num;
	int				playercount;
	int				map_start;
	int				map_begins;
	int				map_ends;
	bool			shootflag;
	bool			killflag;
}	t_data;

#endif
