/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 22:47:45 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/02 11:02:12 by vtenigin         ###   ########.fr       */
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
	tempx = (double)a.x * cos(map->r2) - (double)a.z * sin(map->r2);
	tempz = (double)a.x * sin(map->r2) + (double)a.z * cos(map->r2);
	b.z = (int)(tempz * cos(map->r1) - (double)a.y * sin(map->r1));
	tempy = tempz * sin(map->r1) + (double)a.y * cos(map->r1);
	b.x = (int)(tempx * cos(map->r3) + tempy * sin(map->r3));
	b.y = (int)(tempy * cos(map->r3) - tempx * sin(map->r3));
	return (b);
}

void	ft_linex(t_dot a, t_dot b, t_map *map)
{
	int		y1;
	int		y2;
	t_dot	cur;

	if (a.x > b.x)
	{
		cur = a;
		a = b;
		b = cur;
	}
	y1 = a.y - (a.z * (sin(map->r1) + sin(map->r2)));
	y2 = b.y - (b.z * (sin(map->r1) + sin(map->r2)));
	cur.x = a.x;
	cur.y = y1;
	while (cur.x < b.x)
	{
		mlx_pixel_put(map->mlx, map->win,
						cur.x + map->offx, cur.y + map->offy, 0xffffff);
		cur.x++;
		cur.y = (double)((double)(cur.x - a.x) / (double)(b.x - a.x))
			* (y2 - y1) + y1;
	}
}

void	ft_liney(t_dot a, t_dot b, t_map *map)
{
	int		y1;
	int		y2;
	t_dot	cur;

	y1 = a.y - (a.z * (sin(map->r1) + sin(map->r2)));
	y2 = b.y - (b.z * (sin(map->r1) + sin(map->r2)));
	if (y1 > y2)
	{
		ft_swap(&y1, &y2);
		cur = a;
		a = b;
		b = cur;
	}
	cur.x = a.x;
	cur.y = y1;
	while (cur.y < y2)
	{
		mlx_pixel_put(map->mlx, map->win,
						cur.x + map->offx, cur.y + map->offy, 0xffffff);
		cur.y++;
		cur.x = (double)((double)(cur.y - y1) / (double)(y2 - y1))
				* (b.x - a.x) + a.x;
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
	if (ft_abs(a.x - b.x) > ft_abs(y1 - y2))
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
