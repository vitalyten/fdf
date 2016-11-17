/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:16:58 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/16 22:57:29 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // norm

void ft_fdf(char *file)
{
	t_map *map;
	t_dot **dots;
	int	i;
	int	j;
	void *mlx;
	void *win;
	int x;
	int y;
	int xl;
	int yl;
	unsigned int color = 0xffffff;

	map = (t_map *)malloc(sizeof(t_map));
	map = ft_makemap(file, map);
	i = 0;
	printf("width = %d height = %d\n", map->width, map->height);
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("%2d ", map->data[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	dots = (t_dot **)malloc(sizeof(t_dot *) * map->height);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		dots[y] = (t_dot *)malloc(sizeof(t_dot) * map->width);
		while (x < map->width)
		{
			dots[y][x].x = 150 + x * 10 - y * 11;
			dots[y][x].y = 100 + y * 10 + x * 8 - map->data[y][x];
			x++;
		}
		y++;
	}
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "fdf");
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			mlx_pixel_put(mlx, win, dots[y][x].x, dots[y][x].y, color);
			xl = dots[y][x].x;
			yl = dots[y][x].y;
			while (y + 1 < map->height && xl < dots[y + 1][x].x && yl < dots[y + 1][x].y)
			{

			}
			// mlx_pixel_put(mlx, win, 150 + x * 10 - y * 11, 100 + y * 10 + x * 8 - map->data[y][x], color);
			x++;
		}
		y++;
	}
	// mlx_key_hook(win, key_fun, 0);
	mlx_loop(mlx);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		ft_fdf(av[1]);
	return (0);
}




// int	key_fun(int key, void *mlx, void *win)
// {
// 	printf("key #%d\n", key);
// 	mlx_pixel_put(mlx, win, key, key, 0xffffff);
// 	return (0);
// }