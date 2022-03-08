/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move_to_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	change_player_image(t_data *image, int new_x)
{
	if (image->player->x_player > new_x)
	{
		image->player_image = image->player_with_exit_left;
		free(image->player_with_exit_right);
		image->player_with_exit_right = NULL;
	}
	else if (image->player->x_player < new_x)
	{
		image->player_image = image->player_with_exit_right;
		free(image->player_with_exit_left);
		image->player_with_exit_left = NULL;
	}
	else if (image->player_image == image->move_right)
	{
		image->player_image = image->player_with_exit_right;
		free(image->player_with_exit_left);
		image->player_with_exit_left = NULL;
	}
	else
	{
		image->player_image = image->player_with_exit_left;
		free(image->player_with_exit_right);
		image->player_with_exit_right = NULL;
	}
}

int	check_move_to_exit_bonus(t_data *image, int new_y, int new_x)
{
	if ((image->map->map_array[new_y][new_x] == 'E')
		&& !image->map->num_collectibles)
	{
		image->map->map_array[new_y][new_x] = 'P';
		image->map->map_array[image->player->y_player][image->player->x_player]
			= '0';
		change_player_image(image, new_x);
		image->game_over = 1;
	}
	else if ((image->map->map_array[new_y][new_x] == 'E')
		|| (image->map->map_array[new_y][new_x] == '1'))
		return (1);
	return (0);
}
