/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:16:58 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/20 16:31:22 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // norm

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

void ft_fdf(char *file)
{
	t_map	*map;
	void	*mlx;
	void	*win;
	int		x;
	int		y;

	float x1;
	float y1;
	float x2;
	float y2;
	float xl;
	float yl;
	unsigned int col = 0xffffff;

	
	map = (t_map *)malloc(sizeof(t_map));
	map = ft_makemap(file, map);
	mlx = mlx_init();

	win = mlx_new_window(mlx, map->sq, map->sq, "fdf");

	ft_printmap(map);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			mlx_pixel_put(mlx, win, map->dots[y][x].x, map->dots[y][x].y, col);

			xl = (float)(map->dots[y][x].x - 1);
			x1 = (float)map->dots[y][x].x;
			y1 = (float)map->dots[y][x].y;
			while (y + 1 < map->height && xl > map->dots[y + 1][x].x)
			{
				x2 = (float)map->dots[y + 1][x].x;
				y2 = (float)map->dots[y + 1][x].y;
				yl = ((xl - x1) / (x2 - x1)) * (y2 - y1) + y1;
				mlx_pixel_put(mlx, win, (int)(xl + 0.5), (int)(yl + 0.5), col);
				xl--;
			}
			xl = (float)(map->dots[y][x].x + 1);
			while (x + 1 < map->width && xl < map->dots[y][x + 1].x)
			{
				x2 = (float)map->dots[y][x + 1].x;
				y2 = (float)map->dots[y][x + 1].y;
				yl = ((xl - x1) / (x2 - x1)) * (y2 - y1) + y1;
				mlx_pixel_put(mlx, win, (int)(xl + 0.5), (int)(yl + 0.5), col);
				xl++;
			}
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


	// y = 0;
	// while (y < map->height)
	// {
	// 	x = 0;
	// 	dots[y] = (t_dot *)malloc(sizeof(t_dot) * map->width);
	// 	while (x < map->width)
	// 	{
	// 		dots[y][x].x = 1500 + x * 1 - y * 15;
	// 		dots[y][x].y = -1000 + y * 1 + x * 12 - map->data[y][x] * 2;
	// 		// dots[y][x].x = 200 + x * 15 - y * 15;
	// 		// dots[y][x].y = 100 + y * 15 + x * 12 - map->data[y][x] * 2;
	// 		x++;
	// 	}
	// 	y++;
	// }

// int	key_fun(int key, void *mlx, void *win)
// {
// 	printf("key #%d\n", key);
// 	mlx_pixel_put(mlx, win, key, key, 0xffffff);
// 	return (0);
// }