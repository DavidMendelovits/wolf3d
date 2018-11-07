/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:23:24 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/07 14:35:49 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void			new_mlx(void)
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
		mlx_pixel_put(mlx, window, i, j, 0xf8f8ff);
		if (e >= 0)
		{
			j += 1;
			e -= 1.0;
		}
		i += 1;
		e += m;
	}
	mlx_loop(mlx);

}

t_map			*init_map(void)
{
	t_map				*map;

	map = (t_map *)malloc(sizeof(*map));
	map->width = 0;
	map->height = 0;
	map->map = NULL;
	map->start.x = 0;
	map->start.y = 0;
	return (map);
}

int				read_validate_first_line(t_map **map, int fd)
{
	char				*line;
	char				*tmp;
	char				**args;

	line = NULL;
	get_next_line(fd, &line);
	tmp = replace_char(line, 'x', ' ');
	args = ft_strsplit(tmp);
	ft_print_strings(args);
	if (ptr_count(args) != 2)
	{
		printf("ptr_count = %d\n", ptr_count(args));
		return (0);
	}
	(*map)->width = ft_atoi(args[0]);
	(*map)->height = ft_atoi(args[1]);
	return (1);
}

int				validate_line(char *line, t_map **map)
{
	int					p;
	static int 			line_num = 0;

	p = 0;
	while (line[p])
	{
		if (line[p] == 'S')
		{
			(*map)->start.x = p;
			(*map)->start.y = line_num;
		}
		else if (line[p] != '0' && line[p] != '1')
		{
			return (0);
		}
		p += 1;
	}
	line_num += 1;
	if (p != (*map)->width)
		return (0);
	return (1);
}

int				validate_map(t_map **map, int fd)
{
	char				*line;
	char				**map_;
	int					p;

	line = NULL;
	map_ = (char **)malloc(sizeof(char *) * ((*map)->height + 1));
	p = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (!validate_line(line, map))
			return (0);
		map_[p] = ft_strdup(line);
		p += 1;
		free(line);
		line = NULL;
	}
	map_[p] = NULL;
	printf("start at [%f][%f]\n", (*map)->start.y, (*map)->start.x);
	ft_print_strings(map_);
	return (1);
}

t_map			*read_validate_map(char *filename)
{
	t_map				*map;
	int					fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = init_map();
	
	if (!read_validate_first_line(&map, fd))
		return (NULL);
	printf("map->width = %d\nmap->height = %d\n", map->width, map->height);
	if (!validate_map(&map, fd))
		return (NULL);
	return (map);
}

t_player		*init_player(t_map *map)
{
	t_player			*player;

	player = malloc(sizeof(*player));
	player->position.y = map->start.y;
	player->position.x = map->start.x;
	player->direction.x = -1;
	player->direction.y = 0;
	return (player);
}

t_mlx			*init(void)
{
	t_mlx				*m;

	m = malloc(sizeof(*m));
	m->mlx = mlx_init();
	m->size.x = 1000;
	m->size.y = 1000;
	return (m);
}

void			color_pixel(t_mlx *m, int x, int y, int color)
{
	m->img_int[y * m->size_line + x * m->bpp] = color;
	m->img_int[y * m->size_line + x * m->bpp + 1] = color >> 8;
	m->img_int[y * m->size_line + x * m->bpp + 2] = color >> 16;
}

void			new_image(t_mlx *m, int color)
{
	m->img_ptr = mlx_new_image(m->mlx, 1000, 1000);
	m->img_int = mlx_get_data_addr(m->img_ptr, &m->bpp, &m->size_line, &m->endian); 
	m->bpp /= 8;
	printf("img address -> %p\n", m->img_int);
	printf("size_line = %d\n", m->size_line);
	printf("bpp = %d\n", m->bpp);
	m->color = mlx_get_color_value(m->mlx, color);
	printf("color value = %u\n", m->color);
	printf("size.x = %f\nsize.y = %f\n", m->size.x, m->size.y);
	for (int i = 0; i < m->size.y; i++)
	{
		for (int j = 0; j < m->size.x; j++)
		{
			color_pixel(m, j, i, m->color);
		}
	}
	mlx_put_image_to_window(m->mlx, m->window, m->img_ptr, 0, 0);
}

void			new_background(t_mlx *m)
{
	static int				color = 0xfffafa;

	new_image(m, color);
	color += 10;
}

int				key_press_hook(int keycode, t_mlx *m)
{
	printf("keycode = %d\n", keycode);
	if (keycode == 53)
		exit(1);
	if (keycode == 49)
	{
		new_background(m);
	}
	if (m->mlx)
		printf("-----------------\n");
	return (0);
}

void			set_hooks(t_mlx *m)
{
	mlx_hook(m->window, 2, 0, key_press_hook, m);
//	mlx_hook(m->window, 6, 0, mouse_motion_hook, m);
}

void			screenplay(void)
{
	t_mlx				*m;

	m = init();
	m->window = mlx_new_window(m->mlx, 1000, 1000, "newnew");
//	new_image(m);
	set_hooks(m);
	mlx_loop(m->mlx);
}

void			wolf3d(char *mapname)
{
	t_map				*map;
//	t_player			*player;
	

	map = read_validate_map(mapname);
	if (!map)
	{
		write(2, MAP_ERROR, sizeof(MAP_ERROR));
		return ;
	}
//	player = init_player(map);
	screenplay();
}

int				main(int argc, char **argv)
{
	if (argc == 2)
	{
		wolf3d(argv[1]);
	}
	else
	{
		write(2, USAGE, sizeof(USAGE));
	}
//	new_mlx();
	return (0);
}
