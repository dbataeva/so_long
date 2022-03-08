/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_rectangular(t_map_list *map)
{
	int	i;
	int	j;
	int	len_of_str_in_array;

	i = 0;
	if (map->map_array[0])
		j = ft_strlen(map->map_array[0]);
	while (map->map_array[i])
	{
		len_of_str_in_array = ft_strlen(map->map_array[i]);
		if (len_of_str_in_array != j)
			return (3);
		i++;
	}
	map->resolution_x = j;
	map->resolution_y = i;
	return (0);
}

int	check_map(t_map_list *map, t_player_list *player)
{
	if (check_rectangular(map) != 0)
		return (3);
	if (check_close_map(map->map_array) != 0)
		return (3);
	if (check_exit(map->map_array, 1, 1) != 0)
		return (3);
	if (check_player(map->map_array, player, 1, 1) != 0)
		return (3);
	if ((player->y_player == -1) || (player->x_player == -1))
		return (3);
	if (check_collectible(map, 1, 1) != 0)
		return (3);
	if (check_other_symbols(map->map_array, 0, 0) != 0)
		return (3);
	return (0);
}

int	work_with_struct(t_map_list *map, t_player_list *player, int fd, int gnl)
{
	int	i;

	if (gnl == -1)
	{
		close(fd);
		return (4);
	}
	map->map_array[map->count_str] = NULL;
	if (map->map_array[map->count_str - 1][0] == '\0')
		return (3);
	close(fd);
	i = check_map(map, player);
	if (i == 0)
		init(map, player, 0, 0);
	else
		return (3);
	return (i);
}

int	filling_lines(int n, int fd, t_map_list *map, t_player_list *player)
{
	int		i;
	int		gnl;

	if (n == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	map->map_array = (char **)malloc(sizeof(char *) * n + 1);
	if (!map->map_array)
		return (4);
	fd = open(map->argv, O_RDONLY);
	i = 0;
	gnl = get_next_line(fd, &map->map_array[i]);
	while (gnl > 0)
	{
		i++;
		gnl = get_next_line(fd, &map->map_array[i]);
	}
	n = work_with_struct(map, player, fd, gnl);
	return (n);
}
