/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:26:37 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/27 19:35:12 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_showerr(int code)
{
	if (code == 1)
		ft_putstr("Can't open file.\n");
	exit(-1);
}

void	ft_printmap(t_map *map)  // remove
{
	int	i;
	int	j;

	i = 0;
	printf("width = %d height = %d\n", map->width, map->height);
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("%2d ", map->dots[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
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
		free(split); // write function
		y++;
	}
	close(fd);
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 800, 800, "fdf");
	map->r1 = -0.1;
	map->r2 = -0.7;
	map->r3 = 0.5;
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
