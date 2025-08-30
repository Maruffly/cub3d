NAME		= cub3D

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g $(BONUS_FLAG)

INC			= -I ./includes

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR		= ./src/

SRC_FILES	= main.c \
			  events/mouse.c \
			  events/keyboard.c \
			  display/display.c \
			  display/texture.c \
			  bonus/weapon_bonus.c \
			  bonus/weapon_utils_bonus.c \
			  bonus/minimap_bonus.c \
			  bonus/minimap_utils_bonus.c \
			  bonus/minimap_draw_bonus.c \
			  bonus/damage_bonus.c \
			  init/init_game.c \
			  init/init_mlx.c \
			  init/load_xpm.c \
			  init/init_textures.c \
			  parsing/check_arg.c \
			  parsing/check_config.c \
			  parsing/check_file.c \
			  parsing/check_map.c \
			  parsing/check_map_utils.c \
			  parsing/check_doors.c \
			  parsing/check_map_load.c \
			  parsing/check_utils.c \
			  parsing/check_textures.c \
			  player/check_player_pos.c \
			  player/init_player_direction.c \
			  player/player_moves.c \
			  player/doors_bonus.c \
			  player/player_rotation.c \
			  raycasting/raycasting.c \
			  raycasting/raycasting_utils.c \
			  cleaning/errors.c \
			  cleaning/free.c \
			  bonus_enemy/enemy_init_bonus.c \
			  bonus_enemy/enemy_logic_bonus.c \
			  bonus_enemy/enemy_utils_bonus.c \
			  bonus_enemy/enemy_moves_bonus.c \
			  bonus_enemy/enemy_repulsion_bonus.c \
			  bonus_enemy/enemy_visibility_bonus.c \

SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJS		= $(SRC:.c=.o)

LIBFT_DIR	= ./libft

LIBFT_LIB	= $(LIBFT_DIR)/libft.a

LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

MLX			= ./mlx

MLX_FLAGS	= -L$(MLX) -lmlx -lXext -lX11 -lm

# Colors
CYAN		= \033[36m
GREEN		= \033[32m
BOLD		= \033[1m
RESET		= \033[0m

all: $(NAME)

rebuild_libft:
	@echo "$(CYAN)Rebuilding libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(LIBFT_LIB):
	@echo "$(CYAN)Building libft if needed...$(RESET)"
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	@echo "$(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)creating...$(RESET)"
	@$(CC) $(INC) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(CYAN)$(BOLD)$(NAME):$(GREEN) created!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

bonus: BONUS_FLAG = -DBONUS=1
bonus: fclean
	@$(MAKE) all BONUS_FLAG="$(BONUS_FLAG)"

clean:
	@rm -f $(OBJS)
	@echo "$(GREEN)Obj files cleaned $(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)Executable cleaned $(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus rebuild_libft
