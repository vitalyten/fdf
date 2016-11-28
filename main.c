/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:16:58 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/27 19:35:35 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_max(int a, int b)
{
	return ((a > b) ? a : b);
}

int	ft_min(int a, int b)
{
	return ((a < b) ? a : b);
}

t_dot	ft_rot(t_dot a, t_map *map)
{
	t_dot	b;
	double	tempx;
	double	tempy;
	double	tempz;

	a.x *= map->step;
	a.y *= map->step;
	a.x += (map->width * 2);
	a.y += (map->width * 2);
	// r1 = the angle of rotation around the X axis, r2 is around the Y, and r3 is the Z.
	// Rotation around the Y axis
	tempx = (double)a.x * cos(map->r2) - (double)a.z * sin(map->r2);
	tempz = (double)a.x * sin(map->r2) + (double)a.z * cos(map->r2);
	// Rotation around the X axis
	b.z = (int)(tempz * cos(map->r1) - (double)a.y * sin(map->r1));
	tempy = tempz * sin(map->r1)  + (double)a.y * cos(map->r1);
	// Rotation around the Z axis
	b.x = (int)(tempx * cos(map->r3) + tempy * sin(map->r3));
	b.y = (int)(tempy * cos(map->r3) - tempx * sin(map->r3));
	return(b);
}

void	ft_drawline(t_dot start, t_dot finish, t_map *map)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	x;
	int	y;
	t_dot temp;
	t_dot a;
	t_dot b;


	a = ft_rot(start, map);
	b = ft_rot(finish, map);
	if (a.x > b.x)
	{
		temp = a;
		a = b;
		b = temp;
	}
	x1 = a.x;
	y1 = a.y - a.z;
	x2 = b.x;
	y2 = b.y - b.z;

	x = x1;
	y = y1;
	while (x < x2)
	{
		mlx_pixel_put(map->mlx, map->win, x, y, 0xffffff);
		x++;
		y = (double)((double)(x - x1) / (double)(x2 - x1)) * (y2 - y1) + y1;
	}
}

void	ft_drawmap(t_map *map)
{
	int x;
	int y;

	mlx_clear_window(0, map->win);
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
			x++;
		}
		y++;
	}
}

int				key_fun(int keycode, t_map *map)
{
	printf("key = %d\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode == 12)
		map->r2 += 0.1;
	if (keycode == 14)
		map->r2 -= 0.1;
	if (keycode == 13)
		map->r1 += 0.1;
	if (keycode == 1)
		map->r1 -= 0.1;
	if (keycode == 0)
		map->r2 += 0.1;
	if (keycode == 2)
		map->r2 -= 0.1;
	ft_drawmap(map);
	return (0);
}



void	ft_fdf(char *file)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	map = ft_makemap(file, map);

	ft_printmap(map); // print matrix
	ft_drawmap(map);
	mlx_key_hook(map->win, key_fun, map);
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
