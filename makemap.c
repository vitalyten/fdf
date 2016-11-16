/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:26:37 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/14 16:40:48 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*ft_makemap(char *file, t_map *map)
{
	int		fd;
	int		i;
	char	*str;
	char	**split;

	fd = open(file, O_RDONLY);
	map = ft_getdim(file, map);
	map->data = (int **)malloc(sizeof(int *) * map->height);
	i = 0;
	while (get_next_line(fd, &str) > 0)
	{
		split = ft_strsplit(str, ' ');
		map->data[i] = ft_fillmap(split, map);
		ft_strdel(&str);
		i++;
	}
	close(fd);
	return (map);
}

int		*ft_fillmap(char **data, t_map *map)
{
	int	*arr;
	int	i;

	i = 0;
	arr = (int *)malloc(sizeof(int) * map->width);
	while (*data)
	{
		arr[i] = ft_atoi(*data);
		data++;
		i++;
	}
	return (arr);
}

t_map	*ft_getdim(char *file, t_map *map)
{
	int		fd;
	int		i;
	char	*str;
	char	**split;

	fd = open(file, O_RDONLY);
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
