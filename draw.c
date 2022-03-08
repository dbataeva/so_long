/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	return ;
}

void	init_int(int *i, int *j)
{
	*i = 0;
	*j = 0;
	return ;
}

int	draw(t_data *image, int old_j, int x, int y)
{
	int	i;
	int	j;

	init_int(&i, &j);
	if (image->flag_big_map)
		where_start_draw(image, &i, &j);
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
	if (image->game_over)
		mlx_string_put(image->mlx, image->mlx_win, image->width / 2 - 8,
			image->height / 2, 0xdb5000, "WIN!");
	return (0);
}

void	ft_free(int i, t_data *image)
{
	if (image->map->map_array)
	{
		while (image->map->map_array[i])
		{
			free(image->map->map_array[i]);
			i++;
		}
		free(image->map->map_array);
	}
	if (image->mlx)
		free(image->mlx);
	if (image->mlx_win)
		free(image->mlx_win);
	if (image->back)
		free(image->back);
	if (image->collectible)
		free(image->collectible);
	if (image->player_image)
		free(image->player_image);
	if (image->exit)
		free(image->exit);
	if (image->wall)
		free(image->wall);
	return ;
}
