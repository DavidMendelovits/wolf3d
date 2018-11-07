/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:24:11 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/06 16:52:12 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

# define USAGE "wolf3d -> Usage:\n./wolf3d [map]\n"
# define MAP_ERROR "Invalid Map!\n"
typedef struct		s_point
{
	double				x;
	double				y;
}					t_point;

typedef struct		s_map
{
	int				width;
	int				height;
	char			**map;
	t_point			start;
}					t_map;

typedef struct		s_player
{
	t_point			position;
	t_point			direction;
	t_point			plane;

}
#endif
