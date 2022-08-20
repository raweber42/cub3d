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
# MINILIBX_MAC = minilibx_macos/libmlx.a
# MINILIBX_LINUX = minilibx_linux/libmlx.a
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

# takes all named source files and converts them to .o files in the /obj directory
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# prevents rules from being considered as files
.PHONY: all clean fclean re

all: $(NAME) #credit <- INSERT LATER

# creates subdirectory /obj
# makes sure to make a /obj dir before compiling .o files
$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# compiles all object files and builds executable file 'minishell' -> ADJUST READLINE FOR LINUX!
$(NAME): $(OBJ)
	@echo "$(RED)Compiling libft...$(UNDO_COL)"
	$(MAKE) -C libft
	@echo "$(RED)Compiling minilibx...$(UNDO_COL)"
	$(MAKE) -C $(MINILBX)
	@echo "$(RED)Compiling $(NAME)...$(UNDO_COL)"
	$(CC) $(CFLAGS) $^ $(LIBFT_DIR)$(LIBFT_EXEC) $(MINILBX)$(MLX_EXEC) -framework OpenGL -framework AppKit -o $@
	@echo "$(GREEN)SUCCESSFULLY CREATED CUB3D!$(UNDO_COL)"

# removes all object files and the /obj directory and cleans libft
clean:
	$(MAKE) clean -C libft
	rm -r $(OBJ_DIR)
	@echo "$(RED)Finished clean$(UNDO_COL)"

# calls 'clean' and removes the executable
fclean: clean
	$(MAKE) fclean -C libft
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
