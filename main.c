/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:16:58 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/28 15:23:10 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot	ft_rot(t_dot a, t_map *map)
{
	t_dot	b;
	double	tempx;
	double	tempy;
	double	tempz;

	a.x *= map->step;
	a.y *= map->step;
	a.z *= map->scale;
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
	// Rotation around the Y axis
	// tempx = (double)a.x * cos(map->r2) - (double)a.z * sin(map->r2);
	// tempz = (double)a.x * sin(map->r2) + (double)a.z * cos(map->r2);
	// // Rotation around the X axis
	// b.z = (int)(tempz * cos(map->r1) - (double)a.y * sin(map->r1));
	// tempy = tempz * sin(map->r1)  + (double)a.y * cos(map->r1);
	// // Rotation around the Z axis
	// b.x = (int)(tempx * cos(map->r3) + tempy * sin(map->r3));
	// b.y = (int)(tempy * cos(map->r3) - tempx * sin(map->r3));
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
	int temp;

	a = ft_rot(a, map);
	b = ft_rot(b, map);
	x1 = a.x;
	y1 = a.y - (a.z * (sin(map->r1) + sin(map->r2)));
	x2 = b.x;
	y2 = b.y - (b.z * (sin(map->r1) + sin(map->r2)));
	if (abs(x1  - x2) > abs(y1 - y2))
	{
		if (x1 > x2)
		{
			temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		x = x1;
		y = y1;
		while (x < x2)
		{
			mlx_pixel_put(map->mlx, map->win, x + map->offx, y + map->offy, 0xffffff);
			x++;
			y = (double)((double)(x - x1) / (double)(x2 - x1)) * (y2 - y1) + y1;
		}
	}
	else
	{
		if (y1 > y2)
		{
			temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
		x = x1;
		y = y1;
		while (y < y2)
		{
			mlx_pixel_put(map->mlx, map->win, x + map->offx, y + map->offy, 0xffffff);
			y++;
			x = (double)((double)(y - y1) / (double)(y2 - y1)) * (x2 - x1) + x1;
		}
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

void	ft_keyrot(int keycode, t_map *map)
{
	if (keycode == 12)
		map->r3 += (M_PI / 36);
	if (keycode == 14)
		map->r3 -= (M_PI / 36);
	if (keycode == 13)
		map->r1 += (M_PI / 36);
	if (keycode == 1)
		map->r1 -= (M_PI / 36);
	if (keycode == 0)
		map->r2 += (M_PI / 36);
	if (keycode == 2)
		map->r2 -= (M_PI / 36);
}

int		key_fun(int keycode, t_map *map)
{
	printf("key = %d\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode >= 0 && keycode <= 14)
		ft_keyrot(keycode, map);
	if (keycode == 27)
		map->step -= 1;
	if (keycode == 24)
		map->step += 1;
	if (keycode == 121)
		map->scale -= 1;
	if (keycode == 116)
		map->scale += 1;
	if (keycode == 123)
		map->offx -= 5;
	if (keycode == 124)
		map->offx += 5;
	if (keycode == 126)
		map->offy -= 5;
	if (keycode == 125)
		map->offy += 5;
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
