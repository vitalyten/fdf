/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:26:37 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/02 14:19:40 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_showerr(int code)
{
	if (code == 1)
		ft_putstr("Can't open file.\n");
	exit(-1);
}

t_map	*ft_initmap(t_map *map)
{
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 2000, 1000, "fdf");
	map->r1 = -0.5;
	map->r2 = 0.5;
	map->r3 = -0.4;
	map->step = 20;
	map->scale = 2;
	map->offx = 500;
	map->offy = 200;
	return (map);
}

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
		free(split);
		y++;
	}
	close(fd);
	map = ft_initmap(map);
	return (map);
}

t_map	*ft_fillmap(char **data, t_map *map, int y)
{
	int	x;

	x = 0;
	map->dots[y] = (t_dot *)malloc(sizeof(t_dot) * map->width);
	while (*data)
	{
		map->dots[y][x].z = ft_atoi(*data);
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
	close(fd);
	return (map);
}
