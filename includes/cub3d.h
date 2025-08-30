/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaruffy <jmaruffy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:12:30 by jlaine            #+#    #+#             */
/*   Updated: 2025/04/23 12:48:06 by jmaruffy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef BONUS
#  define IS_BONUS	1

# else
#  define IS_BONUS	0
# endif

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# include <X11/Xlib.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define BUFFER 	1000

# define WIDTH		1000
# define HEIGHT		700

# define WALL		'1'
# define FLOOR		'0'
# define NORTH		'N'
# define SOUTH		'S'
# define EAST		'E'
# define WEST		'W'
# define DOOR		'D'
# define DOOR_OPEN	'O'

# define KEY_W		119
# define KEY_S		115
# define KEY_A		97
# define KEY_D		100
# define KEY_E		101
# define KEY_M		109
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

# define KEY_Q		113
# define KEY_ESC	65307

# define UP			1
# define DOWN		2
# define LEFT		3
# define RIGHT		4

# define MOVESPEED 0.0125
# define ROTSPEED 0.015
# define MARGIN 0.2
# define MINIMAP_X 1
# define MINIMAP_Y 1
# define MAX_MINIMAP_WIDTH 300
# define MAX_MINIMAP_HEIGHT 300
# define MIN_MINIMAP_SIZE 85
# define CELL_SIZE 6

# define RESET	"\033[0m"
# define RED	"\033[31m"
# define BOLD	"\033[1m"

typedef struct s_vector
{
	double		dir_x;
	double		dir_y;
	double		dist;
}				t_vector;

typedef struct s_map
{
	int			fd;
	char		**map;
	char		*path;
	int			player;
	char		**file;
	int			map_start;
	int			map_width;
	int			map_height;
	int			line_count;
	int			end_of_map;
}				t_map;

typedef struct s_tex_paths
{
	int			x;
	int			y;
	int			cardinal;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*door;
	double		step;
	double		pos;
}				t_tex_paths;

typedef struct s_color
{
	int	sky;
	int	floor;
}				t_color;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_doors	t_doors;

typedef struct s_doors
{
	int		x;
	int		y;
	int		state;
	int		count;
	int		capacity;
	double	max_distance;
	t_doors	*doors;
}				t_doors;

typedef struct s_minimap
{
	int			minimap_width;
	int			minimap_height;
	int			line_length;
	int			player_x;
	int			player_y;
	int			delta_x;
	int			delta_y;
	double		x;
	double		y;
	double		x_inc;
	double		y_inc;
	int			steps;
	double		dir_x;
	double		dir_y;
	t_img		img;
}				t_minimap;

typedef struct s_texture
{
	t_img	img;
	int		width;
	int		height;
}				t_texture;

typedef struct s_ray
{
	double	pos_x;
	double	pos_y;
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		line_height;
	int		side;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	double	wall_dist;
	bool	is_door;
	int		color;
}				t_ray;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			move_x;
	int			move_y;
	int			rotate;
	int			dir;
	bool		moved;
}				t_player;

typedef struct s_enemy
{
	double		x;
	double		y;
	double		speed;
	double		distance;
	int			screen_x;
	int			height;
	int			draw_start_y;
	int			draw_end_y;
	bool		is_alive;
	bool		visible;
	bool		targeted;
	t_texture	texture;
}				t_enemy;

typedef struct s_weapon_draw
{
	int			width;
	int			height;
	int			line_len;
	int			bpp;
	char		*addr;
	int			weapon_x;
	int			weapon_y;
	int			src_i;
	int			src_j;
}				t_weapon;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	int			mouse_enabled;
	t_texture	player_face;
	t_texture	gun;	
	t_texture	textures[5];
	t_texture	omar;
	t_texture	door;
	t_player	player;
	t_map		map;
	t_img		img;
	t_ray		ray;
	t_color		color;
	t_tex_paths	tex_paths;
	t_minimap	mini;
	t_doors		doors;
	t_enemy		*enemies;
	t_weapon	wd;
	int			enemy_count;
	bool		weapon_anim;
	int			weapon_anim_frames;
	double		weapon_anim_counter;
	double		proximity_threshold;
	bool		screen_red;
	int			attack_counter;
}				t_game;

typedef struct s_best
{
	int		x;
	int		y;
	double	dist;
}	t_best;

typedef struct s_enemy_nav
{
	t_game	*game;
	t_enemy	*enemy;
	t_best	*best;
}	t_enemy_nav;

// PARSING
bool	is_dir(char *arg);
int		get_lines(char *path);
int		is_player_char(char c);
int		read_map(t_game *game);
int		load_map(t_game *game);
int		is_map_line(char *line);
void	count_doors(t_game *game);
int		is_color_line(char *line);
int		is_valid_map_char(char c);
int		ft_isdigit_str(char *str);
int		is_empty_line(char *line);
int		parse_config(t_game *game);
int		validate_map(t_game *game);
bool	is_xpm_file(char *filename);
int		parse_map_walls(t_map *map);
int		parse_map_chars(t_map *map);
int		is_texture_line(char *line);
int		check_map_height(t_map *map);
int		extract_map_only(t_game *game);
int		parse_cub_file(char *filename);
int		is_valid_xpm(const char *path);
int		parse_extension(char *filename);
int		parse_arg(t_game *game, char **av);
int		is_rgb_valid(char **rgb, int *values);
int		parse_color_line(t_game *game, char *line);
int		parse_texture_line(t_game *game, char *line);
void	check_texture_split_errors(char **split, t_game *game);
void	check_and_store_path(char **dest, char *path, t_game *game);

// MINIMAP UTILS
void	minimap_dimensions(t_game *game);
void	render_minimap_tiles(t_game *game);
void	render_tile(t_game *game, int map_x, int map_y);
void	initialize_ray(t_game *game, int i, int ray_count, t_ray *ray);
void	draw_minimap_rectangle(t_game *game, int x, int y, int color);
void	draw_minimap_pixel( t_game *game, int x, int y, int color);
int		check_wall_collision(t_game *game, double x, double y);
int		heck_minimap_bounds(t_game *game, double x, double y);
int		count_newlines_in_buffer(char *buffer, ssize_t bytes);

// EVENTS
int		mouse_move_handler(int x, int y, t_game *game);
int		mouse_button_handler(int button, int x, int y, t_game *game);

// CLEANING
int		exit_cub3d(t_game *game);
int		free_split(char **split);
int		error_msg(const char *msg);
void	exit_and_free(t_game *game);
void	exit_parse_error(t_game *game);
void	free_parsing_data(t_game *game);

// RENDER
int		display(t_game *game);
void	raycaster(t_game *game);
void	free_enemies(t_game *game);
void	render_frame(t_game *game);
void	render_weapon(t_game *game);
void	render_red_effect(t_game *game);
void	free_tex_paths(t_game *game);
void	render_minimap(t_game *game);
void	free_main_image(t_game *game);
void	key_events_handler(t_game *game);
void	destroy_loaded_textures(t_game *game);
void	draw_pixel(t_img *img, int x, int y, int color);
void	draw_weapon_animating(t_game *game, int i, int j, double angle);
void	draw_weapon_pixel(t_game *game, int screen_x, int screen_y);
void	update_texture(t_game *game, t_ray *ray, int x, int texture_size);

// RENDER MINIMAP
void	render_minimap(t_game *game);
void	render_minimap_background(t_game *game);
void	render_tile(t_game *game, int map_x, int map_y);
void	draw_ray_beam(t_game *game, int player_x, int player_y);

// INIT
void	init_map(t_map *map);
void	init_img(t_img *img);
void	init_ray(t_ray *ray);
void	init_mlx(t_game *game);
void	init_game(t_game *game);
void	init_doors(t_game *game);
void	init_each_door(t_game *game);
void	init_texture(t_tex_paths *text);
void	set_texture(t_game *game);
void	init_player(t_player *player);
void	init_player_dir(char dir, t_game *game);
void	init_raycasting(t_player *player, int x, t_ray *ray);
void	load_texture(t_game *game, char *path, t_texture *tex);

// ENEMY
void	init_enemies(t_game *game);
void	create_pathmap(t_game *game);
void	uwwpdate_enemy(t_game *game);
void	render_enemies(t_game *game);
void	update_enemies(t_game *game);
double	normalize_angle(double angle);
void	update_enemy_visibility(t_game *game);
void	sort_enemies_by_distance(t_game *game);
void	check_enemy_proximity(t_game *game);
bool	is_walkable(t_game *game, int x, int y);
void	repulse_enemy(t_game *game, t_enemy *enemy);
bool	is_enemy_visible(t_game *game, t_enemy *enemy);
double	get_distance(double x1, double y1, double x2, double y2);
void	get_best_direction(t_game *game, t_enemy *enemy, t_best *best);
void	move_enemy_towards_player(t_game *game, t_enemy *enemy);
void	init_ray_step(t_game *game, t_enemy *enemy, double *dx, double *dy);

// UTILS
int		is_doors(char c);
int		move(t_game *game);
int		load_gun(t_game *game);
void	draw_weapon(t_game *game);
void	interact_door(t_game *game);
void	dda(t_game *game, t_ray *ray);
int		load_player_face(t_game *game);
t_doors	*find_nearest_door(t_game *game);
int		process_movement_inputs(t_game *game);
bool	rotate_player(t_game *game, double rotdir);
bool	is_bounds(double x, double y, t_game *game);
void	draw_player_face(t_game *game, int x, int y);
bool	check_position(double x, double y, t_game *game);
bool	is_valid_pos(double new_x, double new_y, t_game *game);
void	draw_player_face(t_game *game, int x, int y);
int		load_player_face(t_game *game);
int		load_gun(t_game *game);
int		get_texture_pixel(t_texture *buff, int x, int y);
void	toggle_door(t_game *game, int door_x, int door_y);
void	set_texture_cardinal(t_tex_paths *tex, t_ray *ray);
bool	is_valid_pos(double new_x, double new_y, t_game *game);
void	calculate_coordinates(t_tex_paths *tex, t_ray *ray, int texture_size);
void	draw_minimap_pixel(t_game *game, int x, int y, int color);

#endif