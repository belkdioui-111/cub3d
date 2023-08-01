/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:33:58 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/07/31 23:39:54 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	calcul_width_height_the_map(char **map, t_map *mapp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j] != '\n' && map[i][j] != '\0')
			j++;
		i++;
	}
	mapp->i = i;
	mapp->j = j;
}



t_map	*init_map(t_global *glob, int check)
{
	t_map	*map;
	int		i;
	int		j;

	map = malloc(sizeof(t_map));
	if (!map)
		exit(1);
	calcul_width_height_the_map(glob->ele->map, map);
	map->x_p_move = 0;
	map->y_p_move = 0;
	map->rot_pl = glob->rot_pl;
	map->w = width_map;
	map->h = height_map;
	map->w_sq = 10;
	map->h_sq = 10;
	map->data = glob->mlx_cub->data2;
	glob->data = glob->mlx_cub->data;
	return (map);
}

void	set_textures(t_global *glob)
{
	int		i;
	char	*path;

	i = 0;
	glob->textures = malloc(sizeof(t_data_tex) * 4);
	while (i < 4)
	{
		if(i == 0)
			path = ft_strdup(glob->ele->no);
		if(i == 1)
			path = ft_strdup(glob->ele->so);
		if(i == 2)
			path = ft_strdup(glob->ele->we);
		if(i == 3)
			path = ft_strdup(glob->ele->ea);
		glob->textures[i].img = mlx_xpm_file_to_image(glob->mlx_cub->mlx_ptr, path, &glob->textures[i].wid, &glob->textures[i].hei);
    	glob->textures[i].addr = mlx_get_data_addr(glob->textures[i].img, &glob->textures[i].bits_per_pixel, &glob->textures[i].line_length, &glob->textures[i].endian);
		free(path);
		i++;
	}
}

t_global	*init_global(t_global *glob, int ac, char **av)
{
	glob->mlx_cub = init_mlx();
	glob->ele = get_map(ac, av, glob);
	glob->map = init_map(glob, 1);
	set_textures(glob);
	return (glob);
}
