/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "minilibx/mlx.h"

# define W 119
# define S 115
# define A 97
# define D 100
# define ESC 65307

typedef struct s_map_list
{
	int		resolution_x;
	int		resolution_y;
	int		num_collectibles;
	int		count_str;
	char	**map_array;
	char	*argv;
}				t_map_list;
typedef struct s_player_list
{
	int		x_player;
	int		y_player;
	char	**to_free;
}				t_player_list;
typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	int				width;
	int				height;
	int				number_of_movements;
	int				game_over;
	int				flag_big_map;
	char			*back;
	char			*collectible;
	char			*player_image;
	char			*move_right;
	char			*move_left;
	char			*player_with_exit;
	char			*player_with_exit_right;
	char			*player_with_exit_left;
	char			*exit;
	char			*wall;
	char			*enemy;
	t_player_list	*player;
	t_map_list		*map;
}				t_data;
int		main(int argc, char **argv);
int		filling_lines(int n, int fd, t_map_list *map, t_player_list *player);
int		check_close_map(char **line);
int		check_exit(char **line, int i, int j);
int		check_player(char **line, t_player_list *player, int i, int j);
int		check_collectible(t_map_list *map, int i, int j);
int		check_other_symbols(char **line, int i, int j);
int		how_much_collectible(char **line, int *num_collectible, t_map_list *map,
			int i);
int		how_much_exits(char **line, int *num_exits, t_map_list *map, int i);
void	init(t_map_list *map, t_player_list *player, int width_pixels,
			int height_pixels);
int		if_exit(t_data *image, int out);
int		key_press_bonus(int keycode, t_data *image);
int		draw(t_data *image, int old_j, int x, int y);
void	free_two_char(char **first, char **second, int flag_exit,
			t_data *image);
void	x_player_coordinates_to_str(t_data *image, int x_player, char **str_x);
char	*y_player_coordinates_to_str(t_data *image, int y_player, char **str_y,
			char **str_x);
int		check_textures_continue(int fd);
void	xpm_file_to_image_continue(t_data *image, int width, int height);
void	get_image_continue(t_data *image, int x, int y);
void	string_movements_put(t_data *image, char *str, char *ptr);
void	ft_free_bonus(int i, t_data *image);
int		check_move_to_exit_bonus(t_data *image, int new_y, int new_x);

#endif