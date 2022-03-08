/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_textures_continue(int fd)
{
	fd = open("textures/move_left64.xpm", O_RDONLY);
	if (fd < 0)
		return (3);
	close(fd);
	fd = open("textures/dolphin_and_exit64.xpm", O_RDONLY);
	if (fd < 0)
		return (3);
	close(fd);
	fd = open("textures/exit_left64.xpm", O_RDONLY);
	if (fd < 0)
		return (3);
	close(fd);
	return (0);
}

void	xpm_file_to_image_continue(t_data *image, int width, int height)
{
	if (!image->player_with_exit_right || (width != 64) || (height != 64))
		if_exit(image, 2);
	image->player_with_exit_left = mlx_xpm_file_to_image(image->mlx,
			"textures/exit_left64.xpm", &width, &height);
	if (!image->player_with_exit_left || (width != 64) || (height != 64))
		if_exit(image, 2);
	image->enemy = mlx_xpm_file_to_image(image->mlx, "textures/enemy64.xpm",
			&width, &height);
	if (!image->enemy || (width != 64) || (height != 64))
		if_exit(image, 2);
	image->move_left = mlx_xpm_file_to_image(image->mlx,
			"textures/move_left64.xpm", &width, &height);
	if (!image->move_left || (width != 64) || (height != 64))
		if_exit(image, 2);
	return ;
}

void	get_image_continue(t_data *image, int x, int y)
{
	if (!(image->number_of_movements % 2))
		mlx_put_image_to_window(image->mlx, image->mlx_win, image->enemy, x, y);
	else
		mlx_put_image_to_window(image->mlx, image->mlx_win, image->back, x, y);
	return ;
}

void	ft_free_bonus(int i, t_data *image)
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
	if (image->exit)
		free(image->exit);
	if (image->wall)
		free(image->wall);
	if (image->move_right)
		free(image->move_right);
	return ;
}
