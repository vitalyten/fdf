/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 15:16:58 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/28 22:49:00 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_swap(int	*a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int		ft_abs(int	n)
{
	return((n > 0) ? n : -n);
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

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac == 2)
	{
		map = (t_map *)malloc(sizeof(t_map));
		map = ft_makemap(av[1], map);
		ft_printmap(map); // print matrix
		ft_drawmap(map);
		mlx_key_hook(map->win, key_fun, map);
		mlx_loop(map->mlx);
	}
	else
		ft_putstr("Usage: ./fdf \"filename\"\n");
	return (0);
}
