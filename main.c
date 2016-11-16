/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:16:58 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/14 16:40:53 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // norm

void ft_fdf(char *file)
{
	t_map *map;
	int	i;
	int	j;

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
}

int	main(int ac, char **av)
{
	if (ac == 2)
		ft_fdf(av[1]);
	return (0);
}


// {
// 	void *mlx;
// 	void *win;
// 	int x;
// 	int y;
// 	unsigned int color = 0xffffff;

// 	mlx = mlx_init();
// 	win = mlx_new_window(mlx, 1000, 1000, "fdf");
// 	y = 50;
// 	while (y < 950)
// 	{
// 		x = 50;
// 		while (x < 950)
// 		{
// 			if (x % 33 && y % 2)
// 			{
// 				// mlx_pixel_put(mlx, win, x, y, color--);
// 				if (color == 0)
// 					color = 0xffffff;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_key_hook(win, key_fun, 0);
// 	mlx_loop(mlx);
// 	return(0);
// }

// int	key_fun(int key, void *mlx, void *win)
// {
// 	printf("key #%d\n", key);
// 	mlx_pixel_put(mlx, win, key, key, 0xffffff);
// 	return (0);
// }