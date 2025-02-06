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
#define s_w 500
#define s_h 600

typedef	struct s_colors
{
	uint32_t black_color;
	uint32_t white_color;
	uint32_t gray_color;
	uint32_t red_color;
	uint32_t green_color;
	uint32_t floor_color;
	uint32_t cieling_color;
}	t_colors;

typedef struct s_inforays
{
	double first_intersection_x;
    double first_intersaction_y;
    double xa;
    double ya;
    int found_horizontal_wall;
    double horizontal_hit_x;
    double horizontal_hit_y;

    int found_vertical_wall;
    double vertical_hit_x;
    double vertical_hit_y;
    double next_horizontal_x;
    double next_horizontal_y;
    int grid_x;
    int grid_y;
    char s;

	double next_vertical_x;
    double next_vertical_y;
	double h_d;
    double v_d;
}	t_inforays;

typedef struct s_ray
{
	struct s_inforays *inforays;
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
	struct s_colors *colores;
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


void	init_game_data(t_data *data, t_player *player, t_colors *colores);
void	get_file_content(t_data *data, char *av1);
void	err(char *str);
void	check_file_content(t_data *data);
void	free_data(t_data *data, char **content ,bool flag);
int		ft_isspace(char c);


int	get_rgba(int r, int g, int b, int a);
void put_squer(uint32_t color,mlx_image_t *img,int h, int w,int x, int y);
void put_pixel(mlx_image_t *img, int x, int y, int color);
void draw_circle(mlx_image_t *img, int cx, int cy, int radius, int color);
void draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color);
void draw_rect(mlx_image_t *img, int x, int y, int width, int height, uint32_t color);
void render_background(t_data *data);
void render_rays(t_ray **rays,t_data *data);
void update(struct mlx_key_data key_data, t_data *data);
void	clear_image(mlx_image_t *img, uint32_t color);
double	normalize(double angle);
double	calculate_distance(double x1, double y1, double x2, double y2);
void	init_ray_info(t_ray *ray);
void	init_ray1(t_ray *ray, double angle);
void	init_ray(t_ray *ray, double angle);
void	cast_rays(t_ray **rays, t_data *data);
void	render_rays(t_ray **rays, t_data *data);
void	cast(t_data *data, t_ray *ray);
void	init_raycasting(t_data *data);

#endif
