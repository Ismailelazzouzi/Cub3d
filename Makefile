CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = Libft
MLX_DIR = MLX42/build

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx42.a
GLFW_LIB = -lglfw

SRCS = main.c parsing.c parsing_1.c parsing_2.c parsing_3.c parsing_4.c parsing_helpers.c init_raycasting.c cast.c init_rays.c cast_completers.c casting.c casting_1.c casting_2.c update.c get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

NAME = cub3d

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(GLFW_LIB) -o $(NAME)

%.o: %.c cube.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re