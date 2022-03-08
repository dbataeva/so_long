/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 10:32:33 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 17:54:23 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	if_error(int number, t_map_list *map, int i)
{
	if (number == 1)
		write(2, "Error\nof number of arguments\n", 29);
	else if (number == 2)
		write(2, "Error\nof opening\n", 17);
	else if (number == 3)
		write(2, "Error\nof configurations or map\n", 31);
	else if (number == 4)
		write(2, "Error\nof memory\n", 16);
	else if (number == 5)
		write(2, "Error\nof image\n", 15);
	else if (number == 6)
		write(2, "Error\nof second argument\n", 25);
	else if (number == 7)
		write(2, "Error\nof first argument\n", 24);
	if (map->map_array)
	{
		while (map->map_array[i])
		{
			free(map->map_array[i]);
			i++;
		}
		free(map->map_array);
	}
	return (1);
}

int	check_argvs(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		return (1);
	len = ft_strlen(argv[1]) - 1;
	if ((argv[1][len] != 'r') || (argv[1][len - 1] != 'e') ||
						(argv[1][len - 2] != 'b') || (argv[1][len - 3] != '.'))
		return (7);
	return (0);
}

int	check_numbers_of_strings(int fd, int n)
{
	char	*ptr;
	char	buf[1024];
	int		rd;

	rd = read(fd, buf, 1023);
	while (rd > 0)
	{
		buf[rd] = '\0';
		ptr = buf;
		ptr = ft_strchr(ptr, '\n');
		while (ptr)
		{
			ptr++;
			n++;
			ptr = ft_strchr(ptr, '\n');
		}
		rd = read(fd, buf, 1023);
	}
	if (rd < 0)
	{
		write(2, "Error\nof reading\n", 17);
		return (-1);
	}
	return (n);
}

void	init_structs(t_map_list *map, t_player_list *player, char *argv)
{
	map->map_array = NULL;
	map->argv = argv;
	player->x_player = -1;
	player->y_player = -1;
	return ;
}

int	main(int argc, char **argv)
{
	int				fd;
	int				n;
	t_map_list		map;
	t_player_list	player;

	init_structs(&map, &player, argv[1]);
	n = check_argvs(argc, argv);
	if (n != 0)
		return (if_error(n, &map, 0));
	fd = open(argv[1], O_RDONLY);
	if (fd < 1)
		return (if_error(2, &map, 0));
	n = check_numbers_of_strings(fd, 1);
	if (n < 3)
	{
		close(fd);
		if (n == -1)
			return (if_error(8, &map, 0));
		return (if_error(3, &map, 0));
	}
	map.count_str = n;
	n = filling_lines(n, fd, &map, &player);
	if (n != 0)
		return (if_error(n, &map, 0));
	return (0);
}
