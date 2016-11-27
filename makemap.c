/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:16:58 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/26 23:54:19 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // norm

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

int	ft_max(int a, int b)
{
	return ((a > b) ? a : b);
}

int	ft_min(int a, int b)
{
	return ((a < b) ? a : b);
}

t_dot	ft_rot(t_dot a)
{
	t_dot	b;
	float	r1 = 0;
	float	r2 = 0;
	float	r3 = 0.5;
	double	tempx;
	double	tempy;
	double	tempz;

	a.x *= 20;
	a.y *= 20;
	a.x += 50;
	a.y += 300;
	// r1 = the angle of rotation around the X axis, r2 is around the Y, and r3 is the Z.
	// Rotation around the Y axis
	tempx = (double)a.x * cos(r2) - (double)a.z * sin(r2);
	tempz = (double)a.x * sin(r2) + (double)a.z * cos(r2);
	// Rotation around the X axis
	b.z = (int)(tempz * cos(r1) - (double)a.y * sin(r1));
	tempy = tempz * sin(r1)  + (double)a.y * cos(r1);
	// Rotation around the Z axis
	b.x = (int)(tempx * cos(r3) + tempy * sin(r3));
	b.y = (int)(tempy * cos(r3) - tempx * sin(r3));
	return(b);
}

void	ft_drawline(t_dot a, t_dot b, t_map *map)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	x;
	int	y;

	a = ft_rot(a);
	b = ft_rot(b);
	x1 = ft_min(a.x, b.x);
	x2 = ft_max(a.x, b.x);
	y1 = (x1 == a.x) ? a.y - a.z : b.y - b.z;
	y2 = (x2 == b.x) ? b.y - b.z : a.y - a.z;
	
	x = x1;
	y = y1;

	if (x1 != x2)
		while (x <= x2)
		{

			mlx_pixel_put(map->mlx, map->win, x, y, 0xffffff);
			x++;
			y = ((x - x1) / (x2 - x1)) * (y2 - y1) + y1;
		}
	// else
	// {
	// 	y1 = ft_min(y1, y2);
	// 	y2 = ft_max(y1, y2);
	// 	y = y1;
	// 	while (y <= y2)
	// 	{
	// 		mlx_pixel_put(map->mlx, map->win, x, y, 0xffffff);
	// 		y++;
	// 	}
	// }

}

void	ft_fdf(char *file)
{
	t_map	*map;
	int x;
	int y;

	map = (t_map *)malloc(sizeof(t_map));
	map = ft_makemap(file, map);

	ft_printmap(map); // print matrix
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (y + 1 < map->height)
				ft_drawline(map->dots[y][x], map->dots[y + 1][x], map);
			if (x + 1 < map->width)
				ft_drawline(map->dots[y][x], map->dots[y][x + 1], map);
			// mlx_pixel_put(mlx, win, map->dots[y][x].x, map->dots[y][x].y, col);

			// xl = (float)(map->dots[y][x].x - 1);
			// x1 = (float)map->dots[y][x].x;
			// y1 = (float)map->dots[y][x].y;
			// while (y + 1 < map->height && xl > map->dots[y + 1][x].x)
			// {
			// 	x2 = (float)map->dots[y + 1][x].x;
			// 	y2 = (float)map->dots[y + 1][x].y;
			// 	yl = ((xl - x1) / (x2 - x1)) * (y2 - y1) + y1;
			// 	mlx_pixel_put(mlx, win, (int)(xl + 0.5), (int)(yl + 0.5), col);
			// 	xl--;
			// }
			// xl = (float)(map->dots[y][x].x + 1);
			// while (x + 1 < map->width && xl < map->dots[y][x + 1].x)
			// {
			// 	x2 = (float)map->dots[y][x + 1].x;
			// 	y2 = (float)map->dots[y][x + 1].y;
			// 	yl = ((xl - x1) / (x2 - x1)) * (y2 - y1) + y1;
			// 	mlx_pixel_put(mlx, win, (int)(xl + 0.5), (int)(yl + 0.5), col);
			// 	xl++;
			// }
			x++;
		}
		y++;
	}
	// mlx_key_hook(win, key_fun, 0);
	mlx_loop(map->mlx);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		ft_fdf(av[1]);
	else
		ft_putstr("Usage: ./fdf \"filename\"\n");
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

// void ft_fdf(char *file)
// {
// 	t_map	*map;
// 	void	*mlx;
// 	void	*win;
// 	int		x;
// 	int		y;

// 	float x1;
// 	float y1;
// 	float x2;
// 	float y2;
// 	float xl;
// 	float yl;
// 	unsigned int col = 0xffffff;


// 	map = (t_map *)malloc(sizeof(t_map));
// 	map = ft_makemap(file, map);
// 	mlx = mlx_init();

// 	win = mlx_new_window(mlx, map->sq, map->sq, "fdf");

// 	ft_printmap(map);
// 	y = 0;
// 	while (y < map->height)
// 	{
// 		x = 0;
// 		while (x < map->width)
// 		{
// 			mlx_pixel_put(mlx, win, map->dots[y][x].x, map->dots[y][x].y, col);

// 			xl = (float)(map->dots[y][x].x - 1);
// 			x1 = (float)map->dots[y][x].x;
// 			y1 = (float)map->dots[y][x].y;
// 			while (y + 1 < map->height && xl > map->dots[y + 1][x].x)
// 			{
// 				x2 = (float)map->dots[y + 1][x].x;
// 				y2 = (float)map->dots[y + 1][x].y;
// 				yl = ((xl - x1) / (x2 - x1)) * (y2 - y1) + y1;
// 				mlx_pixel_put(mlx, win, (int)(xl + 0.5), (int)(yl + 0.5), col);
// 				xl--;
// 			}
// 			xl = (float)(map->dots[y][x].x + 1);
// 			while (x + 1 < map->width && xl < map->dots[y][x + 1].x)
// 			{
// 				x2 = (float)map->dots[y][x + 1].x;
// 				y2 = (float)map->dots[y][x + 1].y;
// 				yl = ((xl - x1) / (x2 - x1)) * (y2 - y1) + y1;
// 				mlx_pixel_put(mlx, win, (int)(xl + 0.5), (int)(yl + 0.5), col);
// 				xl++;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	// mlx_key_hook(win, key_fun, 0);
// 	mlx_loop(mlx);
// }