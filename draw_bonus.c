/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	where_start_draw(t_data *image, int *i, int *j)
{
	*j = image->player->x_player - (image->width / 2) / 64;
	if (*j < 0)
		*j = 0;
	if (*j > (image->map->resolution_x - image->width / 64))
		*j = image->map->resolution_x - image->width / 64;
	*i = image->player->y_player - (image->height / 2) / 64;
	if (*i < 0)
		*i = 0;
	if (*i > (image->map->resolution_y - image->height / 64))
		*i = image->map->resolution_y - image->height / 64;
	return ;
}

void	get_image(char cellar, t_data *image, int x, int y)
{
	if (cellar == '0')
		mlx_put_image_to_window(image->mlx, image->mlx_win, image->back, x, y);
	else if (cellar == '1')
		mlx_put_image_to_window(image->mlx, image->mlx_win, image->wall, x, y);
	else if (cellar == 'C')
		mlx_put_image_to_window(image->mlx, image->mlx_win, image->collectible,
			x, y);
	else if (cellar == 'E')
		mlx_put_image_to_window(image->mlx, image->mlx_win, image->exit, x, y);
	else if (cellar == 'P')
		mlx_put_image_to_window(image->mlx, image->mlx_win, image->player_image,
			x, y);
	else if (cellar == 'H')
		get_image_continue(image, x, y);
	return ;
}

void	init_int(int *i, int *j, t_data *image)
{
	*i = 0;
	*j = 0;
	if (image->flag_big_map)
		where_start_draw(image, i, j);
	return ;
}

void	string_put(t_data *image)
{
	if (image->number_of_movements)
		string_movements_put(image, NULL, NULL);
	if (image->game_over == 1)
		mlx_string_put(image->mlx, image->mlx_win, image->width / 2 - 8,
			image->height / 2, 0xdb5000, "WIN!");
	else if (image->game_over == 2)
		mlx_string_put(image->mlx, image->mlx_win, image->width / 2 - 12,
			image->height / 2, 0xdb5000, "LOOSE!");
	return ;
}

int	draw(t_data *image, int old_j, int x, int y)
{
	int	i;
	int	j;

	init_int(&i, &j, image);
	old_j = j;
	while (image->map->map_array[i])
	{
		j = old_j;
		x = 0;
		while (image->map->map_array[i][j])
		{
			get_image(image->map->map_array[i][j], image, x, y);
			x += 64;
			j++;
		}
		i++;
		y += 64;
	}
	string_put(image);
	return (0);
}
