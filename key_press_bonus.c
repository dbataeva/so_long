/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_wall_bonus(t_data *image, int new_y, int new_x, int *flag_move)
{
	if (image->map->map_array[new_y][new_x] == '0')
	{
		image->map->map_array[new_y][new_x] = 'P';
		image->map->map_array[image->player->y_player][image->player->x_player]
			= '0';
	}
	else if (image->map->map_array[new_y][new_x] == 'C')
	{
		image->map->num_collectibles--;
		image->map->map_array[new_y][new_x] = 'P';
		image->map->map_array[image->player->y_player][image->player->x_player]
			= '0';
	}
	else if (image->map->map_array[new_y][new_x] == 'H')
	{
		image->map->map_array[image->player->y_player][image->player->x_player]
			= '0';
		image->game_over = 2;
	}
	else if (check_move_to_exit_bonus(image, new_y, new_x))
		return (1);
	*flag_move = 0;
	image->number_of_movements++;
	return (0);
}

void	press_a(t_data *image, int *flag_move)
{
	if (check_wall_bonus(image, image->player->y_player,
			image->player->x_player - 1, flag_move) == 0)
	{
		image->player->x_player -= 1;
		if (image->number_of_movements == 0)
			free(image->player_image);
		image->player_image = image->move_left;
		if (image->game_over == 1)
			image->player_image = image->player_with_exit_left;
	}
	return ;
}

void	press_d(t_data *image, int *flag_move)
{
	if (check_wall_bonus(image, image->player->y_player,
			image->player->x_player + 1, flag_move) == 0)
	{
		image->player->x_player += 1;
		if (image->number_of_movements == 0)
			free(image->player_image);
		image->player_image = image->move_right;
		if (image->game_over == 1)
			image->player_image = image->player_with_exit_right;
	}
	return ;
}

void	press_w_or_s_bonus(t_data *image, int keycode, int *flag_move)
{
	if (keycode == W)
	{
		if (check_wall_bonus(image, image->player->y_player - 1,
				image->player->x_player, flag_move) == 0)
			image->player->y_player -= 1;
	}
	else if (keycode == S)
	{
		if (check_wall_bonus(image, image->player->y_player + 1,
				image->player->x_player, flag_move) == 0)
			image->player->y_player += 1;
	}
	return ;
}

int	key_press_bonus(int keycode, t_data *image)
{
	int	flag_move;

	flag_move = 1;
	if (keycode == ESC)
		if_exit(image, 0);
	if (image->game_over)
		return (0);
	if ((keycode == W) || (keycode == S))
		press_w_or_s_bonus(image, keycode, &flag_move);
	else if (keycode == A)
		press_a(image, &flag_move);
	else if (keycode == D)
		press_d(image, &flag_move);
	if (!flag_move)
		draw(image, 0, 0, 0);
	return (0);
}
