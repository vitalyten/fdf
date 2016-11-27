/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:26:37 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/27 13:54:02 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*ft_makemap(char *file, t_map *map)
{
	int		fd;
	int		y;
	char	*line;
	char	**split;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_showerr(1);
	map = ft_getdim(file, map);
	map->dots = (t_dot **)malloc(sizeof(t_dot *) * map->height);
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		map = ft_fillmap(split, map, y);
		ft_strdel(&line);
		free(split); // write function
		y++;
	}
	close(fd);
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 800, 800, "fdf");
	map->step = 20;
	return (map);
}

t_map	*ft_fillmap(char **data, t_map *map, int y)
{
	int		x;
	char	*clr;

	x = 0;
	map->dots[y] = (t_dot *)malloc(sizeof(t_dot) * map->width);
	while (*data)
	{
		map->dots[y][x].z = ft_atoi(*data);
		clr = ft_strstr(*data, "0x");
		map->dots[y][x].clr = (clr) ? ft_atoi_base(clr, 16) : 0;
		// map->dots[y][x].x = map->sq / 3 + x * 15 - y * 15;
		// map->dots[y][x].y = map->sq / 10 + y * 15 + x * 12 - map->dots[y][x].z * 2;
		map->dots[y][x].x = x;
		map->dots[y][x].y = y;
		data++;
		x++;
	}
	return (map);
}

t_map	*ft_getdim(char *file, t_map *map)
{
	int		fd;
	int		i;
	char	*str;
	char	**split;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_showerr(1);
	map->height = 0;
	map->width = 0;
	while (get_next_line(fd, &str) > 0)
	{
		map->height++;
		split = ft_strsplit(str, ' ');
		i = 0;
		while (split[i])
			i++;
		if (map->width < i)
			map->width = i;
		ft_strdel(&str);
	}
	map->sq = (map->width + map->height) / 2 * 30;
	close(fd);
	return (map);
}
