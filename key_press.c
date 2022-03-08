/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_move_to_exit(t_data *image, int new_y, int new_x)
{
	if ((image->map->map_array[new_y][new_x] == 'E')
		&& !image->map->num_collectibles)
	{
		image->map->map_array[new_y][new_x] = 'P';
		image->map->map_array[image->player->y_player][image->player->x_player]
			= '0';
		free(image->player_image);
		image->player_image = image->player_with_exit;
		image->game_over = 1;
	}
	else if ((image->map->map_array[new_y][new_x] == 'E')
		|| (image->map->map_array[new_y][new_x] == '1'))
		return (1);
	return (0);
}

int	check_wall(t_data *image, int new_y, int new_x, int *flag_move)
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
	else if (check_move_to_exit(image, new_y, new_x))
		return (1);
	printf("%d movement to x=%d, y=%d\n", ++image->number_of_movements, new_x,
		new_y);
	*flag_move = 0;
	return (0);
}

void	press_a_or_d(t_data *image, int keycode, int *flag_move)
{
	if (keycode == A)
	{
		if (check_wall(image, image->player->y_player,
				image->player->x_player - 1, flag_move) == 0)
			image->player->x_player -= 1;
	}
	else if (keycode == D)
	{
		if (check_wall(image, image->player->y_player,
				image->player->x_player + 1, flag_move) == 0)
			image->player->x_player += 1;
	}
	return ;
}

void	press_w_or_s(t_data *image, int keycode, int *flag_move)
{
	if (keycode == W)
	{
		if (check_wall(image, image->player->y_player - 1,
				image->player->x_player, flag_move) == 0)
			image->player->y_player -= 1;
	}
	else if (keycode == S)
	{
		if (check_wall(image, image->player->y_player + 1,
				image->player->x_player, flag_move) == 0)
			image->player->y_player += 1;
	}
	return ;
}

int	key_press(int keycode, t_data *image)
{
	int	flag_move;

	flag_move = 1;
	if (keycode == ESC)
		if_exit(image, 0);
	if (image->game_over)
		return (0);
	if ((keycode == W) || (keycode == S))
		press_w_or_s(image, keycode, &flag_move);
	else if ((keycode == A) || (keycode == D))
		press_a_or_d(image, keycode, &flag_move);
	if (!flag_move)
		draw(image, 0, 0, 0);
	return (0);
}
