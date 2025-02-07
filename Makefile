# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
INCLUDE_DIR = include
LIBFT_DIR = Libft
MLX_DIR = MLX42/build

# Libraries and frameworks
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx42.a
GLFW_LIB = -L"/Users/isel-azz/.brew/opt/glfw/lib" -lglfw
FRAMEWORKS = -fsanitize=address -g -framework Cocoa -framework OpenGL -framework IOKit

# Source files and object files
SRCS = main.c parsing.c parsing_1.c init_raycasting.c cast.c casting.c casting_1.c casting_2.c update.c get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

# Output executable
NAME = cub3d

# Rule to create the executable
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(GLFW_LIB) $(FRAMEWORKS) -o $(NAME)

# Rule to create object files from .c files
%.o: %.c cube.h
	$(CC) -I$(INCLUDE_DIR) -c $< -o $@

# Rule to clean object files
clean:
	rm -f $(OBJS)

# Rule to clean all generated files (object files + executable)
fclean: clean
	rm -f $(NAME)

# Rule to recompile everything from scratch
re: fclean $(NAME)

# Phony targets to avoid conflicts with file names
.PHONY: clean fclean re
