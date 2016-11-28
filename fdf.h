/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 11:50:50 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/27 18:56:16 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h> // remove

typedef struct	s_dot
{
	int			x;
	int			y;
	int			z;
	int			clr;
}				t_dot;

typedef struct	s_map
{
	void		**mlx;
	void		**win;
	int			height;
	int			width;
	int			sq;
	int			step;
	double		r1;
	double		r2;
	double		r3;
	t_dot		**dots;
}				t_map;

t_map	*ft_makemap(char *file, t_map *map);
t_map	*ft_fillmap(char **data, t_map *map, int y);
t_map	*ft_getdim(char *file, t_map *map);
void	ft_fdf(char *file);
void	ft_showerr(int code);
void	ft_printmap(t_map *map);

#endif