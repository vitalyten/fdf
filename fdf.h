/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 11:50:50 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/02 11:12:14 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>

typedef struct	s_dot
{
	int			x;
	int			y;
	int			z;
}				t_dot;

typedef struct	s_map
{
	void		**mlx;
	void		**win;
	int			height;
	int			width;
	int			sq;
	int			step;
	float		scale;
	int			offx;
	int			offy;
	double		r1;
	double		r2;
	double		r3;
	t_dot		**dots;
}				t_map;

int				key_fun(int keycode, t_map *map);
void			ft_keyrot(int keycode, t_map *map);
int				ft_abs(int	n);
void			ft_swap(int	*a, int *b);
void			ft_drawmap(t_map *map);
void			ft_drawline(t_dot a, t_dot b, t_map *map);
void			ft_liney(t_dot a, t_dot b, t_map *map);
void			ft_linex(t_dot a, t_dot b, t_map *map);
t_dot			ft_rot(t_dot a, t_map *map);
t_map			*ft_getdim(char *file, t_map *map);
t_map			*ft_fillmap(char **data, t_map *map, int y);
t_map			*ft_makemap(char *file, t_map *map);
t_map			*ft_initmap(t_map *map);
void			ft_printmap(t_map *map);
void			ft_showerr(int code);

#endif
