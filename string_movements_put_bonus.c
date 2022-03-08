/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_monements_put_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*y_player_coordinates_to_str(t_data *image, int y_player, char **str_y,
char **str_x)
{
	char	*num_mov;

	*str_y = ft_itoa(y_player);
	if (!*str_y)
	{
		free(*str_x);
		if_exit(image, 1);
	}
	num_mov = ft_itoa(image->number_of_movements);
	if (!num_mov)
	{
		free(*str_x);
		if_exit(image, 1);
	}
	return (num_mov);
}

void	x_player_coordinates_to_str(t_data *image, int x_player, char **str_x)
{
	*str_x = ft_itoa(x_player);
	if (!*str_x)
		if_exit(image, 1);
	return ;
}

void	free_two_char(char **first, char **second, int flag_exit, t_data *image)
{
	if (first)
		free(*first);
	if (second)
		free(*second);
	if (flag_exit)
		if_exit(image, 1);
	return ;
}

void	string_movements_put(t_data *image, char *str, char *ptr)
{
	char	*str_x;
	char	*str_y;
	char	*num_mov;

	x_player_coordinates_to_str(image, image->player->x_player, &str_x);
	num_mov = y_player_coordinates_to_str(image, image->player->y_player,
			&str_y, &str_x);
	ptr = ft_strjoin(num_mov, " movement to x=");
	free(num_mov);
	if (!ptr)
		free_two_char(&str_x, &str_y, 1, image);
	str = ft_strjoin(ptr, str_x);
	free_two_char(&ptr, &str_x, 0, image);
	if (!str)
		free_two_char(&str_y, NULL, 1, image);
	ptr = ft_strjoin(str, ", y=");
	free(str);
	if (!ptr)
		free_two_char(&str_y, NULL, 1, image);
	str = ft_strjoin(ptr, str_y);
	free_two_char(&ptr, &str_y, 0, image);
	if (!str)
		if_exit(image, 1);
	mlx_string_put(image->mlx, image->mlx_win, 0, 10, 0x000000, str);
	free(str);
}
