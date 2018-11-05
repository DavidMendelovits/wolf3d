/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:23:24 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/05 13:46:11 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

typedef struct 	s_point
{
	int			y;
	int			x;
}				t_point;

int				main(void)
{
	void		*mlx;
	void		*window;
	t_point		start;
	t_point		end;
	int			delta_x;
	int			delta_y;

	start.y = 10;
	start.x = 10;
	end.y = 100;
	end.x = 100;

	delta_x = end.x - start.x;
	delta_y = end.y - start.y;

	float		m = delta_y / delta_x;
	int			j = start.y;
	float		e = m - 1;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 1000, 1000, "newnew");
	for (int i = start.x; i < end.x; i++)
	{
		mlx_pixel_put(mlx, window, i, 10, 0xf8f8ff);
		if (e >= 0)
		{
			j += 1;
			e -= 1.0;
		}
		i += 1;
		e += m;
	}
	mlx_loop(mlx);
	return (0);
}
