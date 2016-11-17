/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 11:50:50 by vtenigin          #+#    #+#             */
/*   Updated: 2016/11/14 15:23:02 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>

typedef struct	s_map
{
	int			height;
	int			width;
	int			**data;
}				t_map;

t_map	*ft_makemap(char *file, t_map *map);
int		*ft_fillmap(char **data, t_map *map);
t_map	*ft_getdim(char *file, t_map *map);
void	ft_fdf(char *file);

#endif