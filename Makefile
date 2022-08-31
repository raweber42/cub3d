NAME = cub3d
SRC_DIR = src/
######## add subdirs here
#BUILTIN_DIR = src/builtins/
########
OBJ_DIR = obj/
INC_DIR = inc/
LIBFT_DIR = libft/
LIBFT_EXEC = libft.a
OS = $(shell uname)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
GREEN = \033[0;32m
RED = \033[0;31m
UNDO_COL = \033[0m
MLX_EXEC = libmlx.a

ifeq ($(OS), Darwin)
	MINILBX = minilibx_macos/
endif
ifeq ($(OS), Linux)
	MINILBX = minilibx_linux/
endif

# place all source files here
SRC = 	$(SRC_DIR)main.c \
		$(SRC_DIR)destroy.c \
		$(SRC_DIR)events.c \
		$(SRC_DIR)my_put_pixel.c \
		$(SRC_DIR)raycasting.c \
		$(SRC_DIR)helpers.c \
		$(SRC_DIR)attributes.c \
		$(SRC_DIR)matrix.c \
		$(SRC_DIR)raycast_helpers.c \
		$(SRC_DIR)raycast_helpers_2.c \
		$(SRC_DIR)linus_utils.c \
		$(SRC_DIR)recursive_madness.c \
		$(SRC_DIR)tests.c \
		$(SRC_DIR)closed_map.c \
		$(SRC_DIR)setter_and_init.c \
		$(SRC_DIR)linus_utils2.c \
		$(SRC_DIR)setter_and_init2.c \
		$(SRC_DIR)recursive_madness2.c \
		$(SRC_DIR)mutated_libft.c

# takes all named source files and converts them to .o files in the /obj directory
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# prevents rules from being considered as files
.PHONY: all clean fclean re

all: $(NAME)

# creates subdirectory /obj and subdirectories
$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# compiles all object files and builds executable file 'cub3d'
$(NAME): $(OBJ)
	@echo "$(RED)Compiling libft...$(UNDO_COL)"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(RED)Compiling minilibx...$(UNDO_COL)"
	$(MAKE) -C $(MINILBX)
	@echo "$(RED)Compiling $(NAME)...$(UNDO_COL)"
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $^ $(LIBFT_DIR)$(LIBFT_EXEC) $(MINILBX)$(MLX_EXEC) -framework OpenGL -framework AppKit -o $@
endif
ifeq ($(OS), Linux)
	$(CC) $(CFLAGS) $^ -L/usr/lib minilibx_linux/libmlx.a libft/libft.a -lXext -lX11 -lm -lz -o $@
endif
	@echo "$(GREEN)SUCCESSFULLY CREATED CUB3D!$(UNDO_COL)"

# removes all object files and the /obj directory and cleans libft
clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -r $(OBJ_DIR)
	@echo "$(RED)Finished clean$(UNDO_COL)"

# calls 'clean' and removes the executable
fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
	@echo "$(RED)Finished fclean$(UNDO_COL)"

# re-makes the whole compilation from scratch
re: fclean all

credit: 
	@echo "\n"
	@echo "                     █████      ████████      █████"
	@echo "                    ░░███      ███░░░░███    ░░███ "
	@echo "  ██████  █████ ████ ░███████ ░░░    ░███  ███████ "
	@echo " ███░░███░░███ ░███  ░███░░███   ██████░  ███░░███ "
	@echo "░███ ░░░  ░███ ░███  ░███ ░███  ░░░░░░███░███ ░███ "
	@echo "░███  ███ ░███ ░███  ░███ ░███ ███   ░███░███ ░███ "
	@echo "░░██████  ░░████████ ████████ ░░████████ ░░████████"
	@echo " ░░░░░░    ░░░░░░░░ ░░░░░░░░   ░░░░░░░░   ░░░░░░░░ "
	@echo "\n"                                
