/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	if_exit(t_data *image, int out)
{
	ft_free(0, image);
	if (out == 0)
		exit (0);
	if (out == 1)
		write(2, "Error\nof memory\n", 16);
	if (out == 2)
		write(2, "Error\nof texture\n", 17);
	if (out == 3)
		write(2, "Error\nof opening\n", 17);
	exit(1);
	return (0);
}

int	check_textures(int fd)
{
	fd = open("textures/fon64.xpm", O_RDONLY);
	if (fd < 0)
		return (3);
	close (fd);
	fd = open("textures/dolphin64.xpm", O_RDONLY);
	if (fd < 0)
		return (3);
	close(fd);
	fd = open("textures/shell64.xpm", O_RDONLY);
	if (fd < 0)
		return (3);
	close(fd);
	fd = open("textures/exit64.xpm", O_RDONLY);
	if (fd < 0)
		return (3);
	close(fd);
	fd = open("textures/wall64.xpm", O_RDONLY);
	if (fd < 0)
		return (3);
	close(fd);
	return (0);
}

void	xpm_file_to_image(t_data *image, int width, int height)
{
	image->wall = mlx_xpm_file_to_image(image->mlx, "textures/wall64.xpm",
			&width, &height);
	if (!image->wall || (width != 64) || (height != 64))
		if_exit(image, 2);
	image->back = mlx_xpm_file_to_image(image->mlx, "textures/fon64.xpm",
			&width, &height);
	if (!image->back || (width != 64) || (height != 64))
		if_exit(image, 2);
	image->collectible = mlx_xpm_file_to_image(image->mlx,
			"textures/shell64.xpm", &width, &height);
	if (!image->collectible || (width != 64) || (height != 64))
		if_exit(image, 2);
	image->exit = mlx_xpm_file_to_image(image->mlx, "textures/exit64.xpm",
			&width, &height);
	if (!image->exit || (width != 64) || (height != 64))
		if_exit(image, 2);
	image->player_image = mlx_xpm_file_to_image(image->mlx,
			"textures/dolphin64.xpm", &width, &height);
	if (!image->player_image || (width != 64) || (height != 64))
		if_exit(image, 2);
	image->player_with_exit = mlx_xpm_file_to_image(image->mlx,
			"textures/dolphin_and_exit64.xpm", &width, &height);
	if (!image->player_with_exit || (width != 64) || (height != 64))
		if_exit(image, 2);
	return ;
}

void	new_window(t_data *image)
{
	image->mlx_win = NULL;
	image->back = NULL;
	image->collectible = NULL;
	image->player_image = NULL;
	image->player_with_exit = NULL;
	image->exit = NULL;
	image->wall = NULL;
	image->mlx_win = mlx_new_window(image->mlx, image->width, image->height,
			"./so_long");
	if (!image->mlx_win)
		if_exit(image, 1);
	if (check_textures(0) != 0)
		if_exit(image, 3);
	xpm_file_to_image(image, 0, 0);
	draw(image, 0, 0, 0);
	mlx_hook(image->mlx_win, 2, 1L << 0, key_press, image);
	mlx_hook(image->mlx_win, 33, 0L, if_exit, image);
	mlx_loop(image->mlx);
	return ;
}

void	init(t_map_list *map, t_player_list *player, int width_pixels,
int height_pixels)
{
	t_data	image;

	image.player = player;
	image.map = map;
	image.game_over = 0;
	image.flag_big_map = 0;
	image.mlx = mlx_init();
	image.number_of_movements = 0;
	mlx_get_screen_size(image.mlx, &image.width, &image.height);
	width_pixels = image.width / 64 - 1;
	height_pixels = image.height / 64 - 1;
	image.width = image.map->resolution_x * 64;
	image.height = 64 * image.map->resolution_y;
	if (image.map->resolution_x >= width_pixels)
	{
		image.width = 64 * width_pixels;
		image.flag_big_map = 1;
	}
	if (image.map->resolution_y >= height_pixels)
	{
		image.height = 64 * height_pixels;
		image.flag_big_map = 1;
	}
	new_window(&image);
}
