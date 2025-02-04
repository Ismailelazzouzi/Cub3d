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
# include "MLX42/include/MLX42/MLX42.h"
#include "math.h"


#define tile_size 32
#define fov (60 * (M_PI / 180))
#define s_w 2000
#define s_h 4000


typedef struct s_ray
{
    double ray_angle;
    int is_facing_down;
    int is_fasing_up;
    int is_fasing_right;
    int is_fasing_left;

    double wall_hit_x;
    double wall_hit_y;
    double distance;
     uint32_t color;
}t_ray;

typedef struct s_player
{
	char	player_id;
	int		player_x;
	int		player_y;
	double x;
    double y;
    double radius;
    double turn_direction;
    double walk_direction;
    double rotation_angle;
    double move_speed;
    double retation_speed;
    t_ray **rays;
    mlx_image_t* img;
}	t_player;

typedef struct s_data
{
	struct s_player	*player;
	char			**maze;
	char			**map;
	char			**info;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
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
	mlx_t* mlx;
}	t_data;


int get_rgba(int r, int g, int b, int a);
void put_squer(uint32_t color,mlx_image_t *img,int h, int w,int x, int y);
void put_pixel(mlx_t *mlx, mlx_image_t *img, int x, int y, int color);
void draw_circle(mlx_t *mlx, mlx_image_t *img, int cx, int cy, int radius, int color);
void draw_line(mlx_t *mlx, mlx_image_t *img, int x1, int y1, int x2, int y2, int color);
void render_rays(t_ray **rays,t_data *data);
void update(struct mlx_key_data key_data, t_data *data);

#endif
