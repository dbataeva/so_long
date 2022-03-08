/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_close_map_exit_player_collectible_other_symbo:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_close_map(char **line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && (line[i][j] == '1'))
		j++;
	if (line[i][j] != '\0')
		return (3);
	while (line[i])
		i++;
	i--;
	j = 0;
	while (line[i] && (line[i][j] == '1'))
		j++;
	if (line[i][j] != '\0')
		return (3);
	i = 0;
	while (line[i] && (line[i][0] == '1') && (line[i][ft_strlen(line[i]) - 1]
			== '1'))
		i++;
	if (line[i])
		return (3);
	return (0);
}

int	check_exit(char **line, int i, int j)
{
	int	num_exits;

	num_exits = 0;
	while (line[i])
	{
		j = 1;
		while (line[i][j])
		{
			if (line[i][j] == 'E')
				num_exits++;
			j++;
		}
		i++;
	}
	if (num_exits == 0)
		return (3);
	return (0);
}

int	check_player(char **line, t_player_list *player, int i, int j)
{
	while (line[i])
	{
		j = 1;
		while (line[i][j])
		{
			if (line[i][j] == 'P')
			{
				if (player->y_player == -1)
					player->y_player = i;
				else
					return (3);
				j = 0;
				while (line[i][j] && (line[i][j] != 'P'))
					j++;
				if (player->x_player == -1)
					player->x_player = j;
				else
					return (3);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_collectible(t_map_list *map, int i, int j)
{
	map->num_collectibles = 0;
	while (map->map_array[i])
	{
		j = 1;
		while (map->map_array[i][j])
		{
			if (map->map_array[i][j] == 'C')
				map->num_collectibles++;
			j++;
		}
		i++;
	}
	if (map->num_collectibles == 0)
		return (3);
	return (0);
}

int	check_other_symbols(char **line, int i, int j)
{
	while (line[i])
	{
		j = 1;
		while (line[i][j])
		{
			if ((line[i][j] == '1') || (line[i][j] == '0')
					|| (line[i][j] == 'P') || (line[i][j] == 'E')
					|| (line[i][j] == 'C'))
				j++;
			else if (line[i][j])
				return (3);
		}
		i++;
	}
	return (0);
}
