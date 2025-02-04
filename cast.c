// #include "MLX42/include/MLX42/MLX42.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <limits.h>
#include "cube.h"

// #define RED     0xFF00FF00
// #define GREEN   0xFF00FF00
// #define BLUE    0xFF0000FF
// #define WHITE   0xFFFFFFFF
// #define BLACK   0xFF000000

// // # define PI 3.14159265358979323846
// // #define tile_size 32
// // #define fov (60 * (M_PI / 180))
// // #define rows 10
// // #define cols 15
// // #define s_w 500
// // #define s_h 400
// // #define res 2;
// //#define num_rays (s_h / res)


// typedef struct s_ray
// {
//     double ray_angle;
//     int is_facing_down;
//     int is_fasing_up;
//     int is_fasing_right;
//     int is_fasing_left;

//     double wall_hit_x;
//     double wall_hit_y;
//     double distance;
//      uint32_t color;
// }t_ray;

// typedef struct s_player
// {
//     double x;
//     double y;
//     double radius;
//     double turn_direction;
//     double walk_direction;
//     double rotation_angle;
//     double move_speed;
//     double retation_speed;
//     t_ray **rays;
//     mlx_image_t* img;
// }t_player;





// // int map[10][15] = {
// //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// //     {1,0,0,1,0,0,0,0,0,0,0,1,0,0,1}, 
// //     {1,0,0,1,0,0,0,1,1,1,0,1,0,0,1},
// //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// //     {1,1,1,1,0,0,0,0,0,0,0,1,1,1,1},
// //     {1,0,0,0,0,1,0,0,1,0,0,0,0,0,1},
// //     {1,0,0,0,0,1,0,1,0,1,0,1,0,0,1},
// //     {1,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
// //     {1,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
// //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// // };

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}



void put_squer(uint32_t color,mlx_image_t *img,int h, int w,int x, int y)
{
    int a = y + w;
int b = x + h;
int x1 = x;
    while ( y < a) {
        x = x1;
        while (x < b) {
            mlx_put_pixel(img, x, y, color);
            x++;
        }
        y++;
    }
}

void put_pixel(mlx_t *mlx, mlx_image_t *img, int x, int y, int color)
{
    if (x >= 0 && x < s_w && y >= 0 && y < s_h)
        mlx_put_pixel(img, x, y, color);
}

// // Function to draw a circle
void draw_circle(mlx_t *mlx, mlx_image_t *img, int cx, int cy, int radius, int color)
{
    for (int y = cy - radius; y <= cy + radius; y++) {
        for (int x = cx - radius; x <= cx + radius; x++) {
            // Check if the point (x, y) is within the circle using the equation of the circle
            if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius) {
                put_pixel(mlx, img, x, y, color);
            }
        }
    }
}

void draw_line(mlx_t *mlx, mlx_image_t *img, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        put_pixel(mlx, img, x1, y1, color);

        if (x1 == x2 && y1 == y2)
            break;
        
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void clear_image(mlx_image_t *img, uint32_t color) {
    for (int y = 0; y < img->height; y++) {
        for (int x = 0; x < img->width; x++) {
            mlx_put_pixel(img, x, y, color);
        } 
    }
}


double normalize(double angle)
{
   angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void init_ray(t_ray *ray, double angle)
{
    ray->ray_angle = normalize(angle); // Using pointer dereference for ray

    ray->distance = 0;
    ray->color = get_rgba(255,0,0,255);

    ray->is_facing_down = 0;
    ray->is_fasing_up = 0;
    ray->is_fasing_right = 0;
    ray->is_fasing_left = 0;

    if(ray->ray_angle > 0 && ray->ray_angle < M_PI)
    {
        ray->is_facing_down = 1;
        ray->is_fasing_up = 0;
    }else
    {
         ray->is_facing_down = 0;
        ray->is_fasing_up = 1;
    }
    if(ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI)
    {
         ray->is_fasing_right = 1;
         ray->is_fasing_left = 0;
    }
    else
    {
             ray->is_fasing_right = 0;
         ray->is_fasing_left = 1;
    }
       

    ray->wall_hit_x = 0;
    ray->wall_hit_y = 0;
    
}

// int has_wall_at(double x, double y) {
//     int grid_x = floor(x /tile_size); // Calculate grid row index
//     int  grid_y = floor(y/ tile_size);

//     // if (grid_x >= 0 && grid_x < rows && grid_y >= 0 && grid_y < cols) {
        
//     // }
//     if (map[grid_y][grid_x] == 1) {
//             //printf("has_wall\n");
//             return 1; // Return 1 if a wall exists
//         }
//     return 0; // Return 0 if no wall or out of bounds
// }

double calculate_distance(double x1, double y1, double x2, double y2) 
{
     double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy); 
}

void cast(t_data *data, t_ray *ray)
{
    int found_horizontal_wall =  0;
    double horizontal_hit_x = 0;
    double horizontal_hit_y = 0;

    double first_intersection_x = 0;
    double first_intersaction_y = 0;
    if(ray->is_fasing_up == 1)
        first_intersaction_y =floor(data->player->y / tile_size ) * tile_size - 0.00000001;
    else if(ray->is_facing_down == 1)
        first_intersaction_y = (floor(data->player->y/ tile_size ) * tile_size) + tile_size;

    first_intersection_x = data->player->x + ((first_intersaction_y - data->player->y) / tan(ray->ray_angle));
//      printf("p_y : %f\n",player->y);
//  printf("first_intersaction_y : %f\n",first_intersaction_y);
    double next_horizontal_x = first_intersection_x;
    double next_horizontal_y = first_intersaction_y;

    double xa = 0;
    double ya =0;
    if(ray->is_fasing_up == 1)
        ya = tile_size * -1;
    else if(ray->is_facing_down == 1)
        ya = tile_size;

    xa = ya / tan(ray->ray_angle);

    int i = 0;
    while(next_horizontal_x <= (data->column_num * 32) && next_horizontal_x >= 0 && next_horizontal_y <= (data->rows_num * 32) && next_horizontal_y >=0)
    {
         int grid_x = floor(next_horizontal_x /(double)tile_size); // Calculate grid row index
            int grid_y = floor(next_horizontal_y/ (double)tile_size);
          
            // printf("x: %d , x in double : %f\n",grid_x,next_horizontal_x /tile_size );
            //  printf("y: %d, y in double: %f\n",grid_y,next_horizontal_y/ tile_size);

               char s;
      
             s = data->map[(int) grid_y][(int) grid_x];
            //   int r = data->map[(int) grid_y][(int) grid_x + 1];
            //   int f = data->map[(int) grid_y - 1][(int) grid_x ];

            //   int a =  data->map[(int) grid_y][(int) grid_x + 1];
            //   int b =  data->map[(int) grid_y + 1][(int) grid_x];

            //     int e =  data->map[(int) grid_y][(int) grid_x - 1];
            //   int g =  data->map[(int) grid_y + 1][(int) grid_x];

            // int u =  data->map[(int) grid_y][(int) grid_x - 1];
            //   int v =  data->map[(int) grid_y - 1][(int) grid_x];
            //  printf("map num:%d\n",s);
          if(s == '1')
        //if(s== 1 || (ray->is_facing_down && ray->is_fasing_left && r && f) || (ray->is_fasing_up && ray->is_fasing_right && e && g) || (ray->is_fasing_up && ray->is_fasing_left && a && b) || (ray->is_facing_down && ray->is_fasing_right && u && v))
        {
           
        //    printf("ooo\n");
            found_horizontal_wall = 1;
            horizontal_hit_x = next_horizontal_x;
            horizontal_hit_y = next_horizontal_y;
            break;
        }
        else{
            next_horizontal_x += xa;
            next_horizontal_y += ya;
            //  printf("next_horizontal_x: %f\n",next_horizontal_x);
            //  printf("next_horizontal_y: %f\n",next_horizontal_y);
        }
        

    }

        // ray->wall_hit_x = horizontal_hit_x;
        // ray->wall_hit_y = horizontal_hit_y;

    int found_vertical_wall  =0;
    double vertical_hit_x = 0;
    double vertical_hit_y = 0;


    if(ray->is_fasing_right == 1)
        first_intersection_x = (floor(data->player->x / tile_size) * tile_size) + tile_size;
    else if( ray->is_fasing_left == 1)
        first_intersection_x = (floor(data->player->x / tile_size) * tile_size) - 0.00000001;

    first_intersaction_y = data->player->y + (first_intersection_x - data->player->x) * tan(ray->ray_angle);

    double next_vertical_x = first_intersection_x;
    double next_vertical_y = first_intersaction_y;

     if(ray->is_fasing_right == 1)
        xa = tile_size;
    else if(ray->is_fasing_left == 1)
        xa = tile_size * -1;
    
    ya= xa * tan(ray->ray_angle);
     i = 0;
   // printf("aa\n");
    while(next_vertical_x <= (data->column_num * 32) && next_vertical_x >= 0 && next_vertical_y <= (data->rows_num * 32) && next_vertical_y >=0)
    {
         int grid_x = floor(next_vertical_x /(double)tile_size); // Calculate grid row index
            int grid_y = floor(next_vertical_y/ (double)tile_size);
          
            // printf("x: %d , x in double : %f\n",grid_x,next_vertical_x /tile_size );
            //  printf("y: %d, y in double: %f\n",grid_y,next_vertical_y/ tile_size);
           char s;
         
             s = data->map[(int) grid_y][(int) grid_x];
        //       int r = data->map[(int) grid_y][(int) grid_x + 1];
        //       int f = data->map[(int) grid_y - 1][(int) grid_x ];

        //    int a =  map[(int) grid_y][(int) grid_x + 1];
        //       int b =  map[(int) grid_y + 1][(int) grid_x];

        //            int e =  map[(int) grid_y][(int) grid_x - 1];
        //       int g =  map[(int) grid_y + 1][(int) grid_x];
        //       int u =  map[(int) grid_y][(int) grid_x - 1];
        //       int v =  map[(int) grid_y - 1][(int) grid_x];
            //  printf("map num:%d\n",s);
          if(s == '1')
       // if(s== 1 || (ray->is_facing_down && ray->is_fasing_left && r && f) || (ray->is_fasing_up && ray->is_fasing_right && e && g) || (ray->is_fasing_up && ray->is_fasing_left && a && b) || (ray->is_facing_down && ray->is_fasing_right && u && v))
        {
            // printf("ooo1\n");
            found_vertical_wall = 1;
            vertical_hit_x = next_vertical_x;
            vertical_hit_y = next_vertical_y;
            break;
        }
        else
        {
            next_vertical_x += xa;
        next_vertical_y += ya;
        }
        

    }

    double h_d = INT_MAX;
    double v_d = INT_MAX;
    if(found_horizontal_wall == 1)
        h_d = calculate_distance(data->player->x, data->player->y, horizontal_hit_x, horizontal_hit_y);
    // else
    //     h_d = 9999;
    if(found_vertical_wall== 1)
        v_d =  calculate_distance(data->player->x, data->player->y, vertical_hit_x, vertical_hit_y);
    // else
    //     v_d = 9999;

    if(h_d < v_d){
        ray->wall_hit_x = horizontal_hit_x;
        ray->wall_hit_y = horizontal_hit_y;
        ray->distance = h_d;
        ray->color = get_rgba(128,160,128,255);
    }
    else
    {
         ray->wall_hit_x = vertical_hit_x;
        ray->wall_hit_y = vertical_hit_y;
        ray->distance = v_d;
        ray->color = get_rgba(255,0,0,255);
    }
        ray->distance *= cos(ray->ray_angle - data->player->rotation_angle); 

}

 void cast_rays(t_ray **rays, t_data *data)
{
    // int n_r = s_w / res;
  int n_r = 2000;
   // player->rays = malloc(n_r * sizeof(t_ray));
    double ray_angl = data->player->rotation_angle - (fov / 2); 
  
    int a = 0;
    while (a < n_r)
    {
        
        init_ray(rays[a], ray_angl);  // Pass ray by reference using `&`
        // printf("***********************/n\n");
        //  printf("ray:%d\n",a);
        cast(data, rays[a]);
        ray_angl += fov / n_r;  // Increment the angle for the next ray
        a++;
    }
}
// void draw_rect(mlx_image_t *img, int x, int y, int width, int height, uint32_t color) {
//     for (int j = 0; j < height; j++) {  // Loop through height (vertical lines)
//         for (int i = 0; i < width; i++) {  // Loop through width (horizontal lines)
//             int px = x + i;  // Calculate the x-coordinate for each pixel
//             int py = y + j;  // Calculate the y-coordinate for each pixel

//             // Ensure pixel is within screen bounds
//             if (px >= 0 && px < img->width && py >= 0 && py < img->height) {
//                 mlx_put_pixel(img, px, py, color);  // Draw pixel
//             }
//         }
//     }
// }
void render_rays(t_ray **rays,t_data *data)
{
     uint32_t red_color = get_rgba(255,0,0,255);
        uint32_t s_color = get_rgba(255,255,0,255);
    cast_rays(rays, data);
//   double n_r = s_w / res;
    int n_r = 2000;
   int a = 0;

   
    while(a < n_r)
    {
    //   double line_height = (32 / rays[a]->distance) * ((s_w/ 2.0) / tan(fov / 2));  // Calculate wall slice height
    // double draw_begin = (s_h / 2) - (line_height / 2);  // Top of the wall slice
    // double draw_end = draw_begin + line_height;  // Bottom of the wall slice

    // Cast draw_begin and draw_end to integers (if required by your function)
    // draw_rect(player->img, a * 1, (int)draw_begin, 1, (int)(draw_end - draw_begin), rays[a]->color);
        // cast(player, &rays[a]);
      // draw_line(data->mlx,data->player->img, data->player->x, data->player->y, (data->player->x + cos(rays[a]->ray_angle) *50),(data->player->y + sin(rays[a]->ray_angle)*50), red_color);
      //cast(player, &rays[a]);
      draw_line(data->mlx, data->player->img, data->player->x, data->player->y, rays[a]->wall_hit_x, rays[a]->wall_hit_y,red_color);
        a++;
    }
  // printf("*******************\n");
}

void update(struct mlx_key_data key_data, t_data *data)
{
    double move_step;

    uint32_t black_color = get_rgba(0,0,0,255);
    uint32_t white_color = get_rgba(255,250,255,255);
    uint32_t gray_color = get_rgba(128,128,128,255);
    uint32_t red_color = get_rgba(255,0,0,255);
	uint32_t green_color = get_rgba(0,255,0,255);

    data->player->turn_direction = 0;
    data->player->walk_direction = 0;

  if(key_data.key == MLX_KEY_RIGHT)
    {
       
        data->player->turn_direction = 1;
    }
    if(key_data.key == MLX_KEY_LEFT)
        data->player->turn_direction = -1;
    if(key_data.key == MLX_KEY_UP)
        data->player->walk_direction = 1;
    if(key_data.key == MLX_KEY_DOWN)
        data->player->walk_direction = -1;

     // Clear image
    clear_image(data->player->img, get_rgba(0, 0, 0, 255));

    int i = 0, j = 0;
	int tile_x = 0, tile_y = 0;

	//printf("%d\n", tile_size);
	while (i < data->rows_num - 1)
	{
		j = 0;
			//printf("%zu\n",ft_strlen(data.map[i]));
		while (j < ft_strlen(data->map[i]) - 1)
		{
			tile_x = j * tile_size;
        	tile_y = i * tile_size;
			if (data->map[i][j] == '0' || data->map[i][j] == 'E')
            	put_squer(white_color,data->player->img,tile_size-1, tile_size-1,tile_x,tile_y);
			else if(data->map[i][j] == '1')
                put_squer(gray_color,data->player->img,tile_size-1, tile_size-1,tile_x,tile_y);
			else if (data->map[i][j] != '0' && data->map[i][j] != '1')
				put_squer(red_color, data->player->img,tile_size-1, tile_size-1,tile_x,tile_y);
			j++;
		}
        while(j < data->column_num)
		{
				tile_x = j * tile_size;
        	tile_y = i * tile_size;
			put_squer(red_color, data->player->img,tile_size-1, tile_size-1,tile_x,tile_y);
			j++;
		}
        i++;
    }
    // Redraw player circle

//   for (int i = 0; i < s_w; i++) {
//         for (int j = 0; j < s_h; j++) {
//             int tile_x = j * tile_size;
//             int tile_y = i * tile_size;
//            mlx_put_pixel(player->img, i, j, get_rgba(255,255,255,255));
//         }
//     }

    move_step = data->player->walk_direction * data->player->move_speed;
    data->player->rotation_angle += data->player->turn_direction * data->player->retation_speed;
   
    // if(has_wall_at(x1,y1) == 0)
    // {
    data->player->x += cos(data->player->rotation_angle) * move_step;
    data->player->y += sin(data->player->rotation_angle) * move_step;
    // }
    draw_circle(data->mlx, data->player->img, data->player->x, data->player->y, data->player->radius, get_rgba(255, 0, 0, 255));
     //draw_line(mlx,player->img, player->x, player->y, (player->x + cos(player->rotation_angle) *50),(player->y + sin(player->rotation_angle)*50), red_color);
    //  printf("y: %d\n",player->y);

    render_rays(data->player->rays, data);
    //  printf("%d\n",player->y);
    // mlx_image_to_window(mlx, player->img, 0, 0);
}

// int main()
// {
    
//     t_player *player = malloc(sizeof(t_player));
//     player->x = (cols * 32) / 2;
//     player->y = (rows * 32)/ 2;
//     player->radius = 3;
//     player->rotation_angle = 0;
//     player->turn_direction = 0;
//     player->walk_direction = 0;
//     player->move_speed = 4;
//     player->retation_speed = 2 * (PI /180);

//     //   int n_r = s_w / res;
//       int n_r = 500;
// player->rays = malloc(n_r * sizeof(t_ray *)); // Array of pointers
// for (int i = 0; i < n_r; i++) {
//     player->rays[i] = malloc(sizeof(t_ray)); // Allocate each struct individually
// }
// //    int n_r = s_h / res;
// // t_ray *rays = malloc(n_r * sizeof(t_ray));

//  cast_rays(player->rays,player);

// //    int a = 0;
// //     while(a < n_r)
// //     {
       
// //        printf("%f\n",rays[a].ray_angle);
// //         a++;
// //     }


//     mlx = mlx_init(s_w, s_h, "MLX42", true);
 
//     player->img = mlx_new_image(mlx, s_w, s_h);

//       uint32_t black_color = get_rgba(0,0,0,255);
//     uint32_t white_color = get_rgba(255,250,255,255);
//     uint32_t gray_color = get_rgba(128,128,128,255);
//     uint32_t red_color = get_rgba(255,0,0,255);
    // for (int y = 0; y < s_h; y++) {
    //     for (int x = 0; x < s_w; x++) {
    //         mlx_put_pixel(player->img, x, y, black_color);
    //     }
    // }

//  for (int i = 0; i < 10; i++) {
//         for (int j = 0; j < 15; j++) {
//             int tile_x = j * tile_size;
//             int tile_y = i * tile_size;
//             // printf("%d ", map[i][j]);
//             if(map[i][j] == 0)
//                 put_squer(white_color,player->img,tile_size-1, tile_size-1,tile_x,tile_y);
//             if(map[i][j] == 1)
//                 put_squer(gray_color,player->img,tile_size-1, tile_size-1,tile_x,tile_y);
//         }
//         // printf("\n");
//     }

//     //  for (int i = 0; i < 480; i++) {
//     //     for (int j = 0; j < 400; j++) {
//     //         int tile_x = j * tile_size;
//     //         int tile_y = i * tile_size;
//     //        mlx_put_pixel(player->img, i, j, white_color);
//     //     }
//     // }
//      draw_circle(mlx, player->img, player->x, player->y, player->radius, red_color);
//     // draw_line(mlx,player->img, player->x, player->y, (player->x + cos(player->rotation_angle) *50),(player->y + sin(player->rotation_angle)*50), red_color);
//   //put_squer(green_color,img,tile_size, tile_size,40,70);
//    render_rays(player->rays,player);
//     mlx_image_to_window(mlx, player->img, 0, 0);
//     mlx_key_hook(mlx, (mlx_keyfunc)update, player);
//    // mlx_key_hook(mlx, (mlx_keyfunc)render_rays, player);
//     mlx_loop(mlx);
//         for (int i = 0; i < n_r; i++) {
//         free(player->rays[i]);
//     }
//     free(player->rays);
//     free(player);
// 	mlx_terminate(mlx);
// 	//return (EXIT_SUCCESS);
//     return 0;
//}