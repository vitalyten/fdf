/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 22:47:45 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/28 22:49:05 by vtenigin         ###   ########.fr       */
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

void	ft_linex(t_dot a, t_dot b, t_map *map)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	x;
	int	y;

	x1 = a.x;
	x2 = b.x;
	y1 = a.y - (a.z * (sin(map->r1) + sin(map->r2)));
	y2 = b.y - (b.z * (sin(map->r1) + sin(map->r2)));
	if (x1 > x2)
	{
		ft_swap(&x1, &x2);
		ft_swap(&y1, &y2);
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

void	ft_liney(t_dot a, t_dot b, t_map *map)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	x;
	int	y;

	x1 = a.x;
	x2 = b.x;
	y1 = a.y - (a.z * (sin(map->r1) + sin(map->r2)));
	y2 = b.y - (b.z * (sin(map->r1) + sin(map->r2)));
	if (y1 > y2)
	{
		ft_swap(&x1, &x2);
		ft_swap(&y1, &y2);
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

void	ft_drawline(t_dot a, t_dot b, t_map *map)
{
	int	y1;
	int	y2;

	a = ft_rot(a, map);
	b = ft_rot(b, map);
	y1 = a.y - (a.z * (sin(map->r1) + sin(map->r2)));
	y2 = b.y - (b.z * (sin(map->r1) + sin(map->r2)));
	if (ft_abs(a.x  - b.x) > ft_abs(y1 - y2))
		ft_linex(a, b, map);
	else
		ft_liney(a, b, map);
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