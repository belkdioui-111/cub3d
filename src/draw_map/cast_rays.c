/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kdio <bel-kdio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:19:10 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/07/24 16:51:48 by bel-kdio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	check_greater_or_less_in_part_horiz(t_mlx *mlx_cub, t_cast_ray *ca_ray)
{
	if (ca_ray->ra > PI)
	{
		ca_ray->ry = ((mlx_cub->y_p / 50) * 50) - 0.0001;
		ca_ray->rx = (mlx_cub->y_p - ca_ray->ry) * \
				ca_ray->atan + (float)mlx_cub->x_p;
		ca_ray->yo = -50;
		ca_ray->xo = -ca_ray->yo * ca_ray->atan;
	}
	if (ca_ray->ra < PI)
	{
		ca_ray->ry = ((mlx_cub->y_p / 50) * 50) + 50;
		ca_ray->rx = (mlx_cub->y_p - ca_ray->ry) * \
			ca_ray->atan + (float)mlx_cub->x_p;
		ca_ray->yo = 50;
		ca_ray->xo = -ca_ray->yo * ca_ray->atan;
	}
	if (ca_ray->ra == 0 || ca_ray->ra == (float)PI)
	{
		ca_ray->rx = (float)mlx_cub->x_p;
		ca_ray->ry = (float)mlx_cub->y_p;
		ca_ray->dof = mlx_cub->w / 50;
	}
}

void	check_horiental(t_mlx *mlx_cub, t_cast_ray *ca_ray)
{
	ca_ray->dof = 0;
	ca_ray->atan = -1 / tan(ca_ray->ra);
	check_greater_or_less_in_part_horiz(mlx_cub, ca_ray);
	while (ca_ray->dof < mlx_cub->w / 50)
	{
		ca_ray->mx = (int)(ca_ray->rx / 50);
		ca_ray->my = (int)(ca_ray->ry / 50);
		if (ca_ray->mx >= 0 && ca_ray->mx < mlx_cub->w / 50 \
			&& ca_ray->my >= 0 && ca_ray->my < mlx_cub->h
			/ 50 && mlx_cub->ele->map[ca_ray->my][ca_ray->mx] == '1')
		{
			ca_ray->dof = mlx_cub->w / 50;
			ca_ray->hx = ca_ray->rx;
			ca_ray->hy = ca_ray->ry;
			ca_ray->dish = calc_dist(mlx_cub->x_p, mlx_cub->y_p, \
				ca_ray->rx, ca_ray->ry);
		}
		else
		{
			ca_ray->rx += ca_ray->xo;
			ca_ray->ry += ca_ray->yo;
			ca_ray->dof += 1;
		}
	}
}

void	check_greater_or_less_in_part_verti(t_mlx *mlx_cub, t_cast_ray *ca_ray)
{
	if (ca_ray->ra > (M_PI / 2) && ca_ray->ra < ((3 * M_PI) / 2))
	{
		ca_ray->rx = ((mlx_cub->x_p / 50) * 50) - 0.0001;
		ca_ray->ry = (mlx_cub->x_p - ca_ray->rx) * \
			ca_ray->ntan + (float)mlx_cub->y_p;
		ca_ray->xo = -50;
		ca_ray->yo = -ca_ray->xo * ca_ray->ntan;
	}
	if (ca_ray->ra < (M_PI / 2) || ca_ray->ra > ((3 * M_PI) / 2))
	{
		ca_ray->rx = ((mlx_cub->x_p / 50) * 50) + 50;
		ca_ray->ry = (mlx_cub->x_p - ca_ray->rx) * \
			ca_ray->ntan + (float)mlx_cub->y_p;
		ca_ray->xo = 50;
		ca_ray->yo = -ca_ray->xo * ca_ray->ntan;
	}
	if (ca_ray->ra == 0 || ca_ray->ra == (float)PI)
	{
		ca_ray->rx = (float)mlx_cub->x_p;
		ca_ray->ry = (float)mlx_cub->y_p;
		ca_ray->dof = mlx_cub->w / 50;
	}
}

void	check_vertical(t_mlx *mlx_cub, t_cast_ray *ca_ray)
{
	ca_ray->dof = 0;
	ca_ray->ntan = -tan(ca_ray->ra);
	check_greater_or_less_in_part_verti(mlx_cub, ca_ray);
	while (ca_ray->dof < mlx_cub->w / 50)
	{
		ca_ray->mx = (int)(ca_ray->rx / 50);
		ca_ray->my = (int)(ca_ray->ry / 50);
		if (ca_ray->mx >= 0 && ca_ray->mx < mlx_cub->w / 50 && \
			ca_ray->my >= 0 && ca_ray->my < mlx_cub->h
			/ 50 && mlx_cub->ele->map[ca_ray->my][ca_ray->mx] == '1')
		{
			ca_ray->dof = mlx_cub->w / 50;
			ca_ray->vx = ca_ray->rx;
			ca_ray->vy = ca_ray->ry;
			ca_ray->disv = calc_dist(mlx_cub->x_p, mlx_cub->y_p, \
				ca_ray->rx, ca_ray->ry);
		}
		else
		{
			ca_ray->rx += ca_ray->xo;
			ca_ray->ry += ca_ray->yo;
			ca_ray->dof += 1;
		}
	}
}

void	cast_rays(t_mlx *mlx_cub)
{
	mlx_cub->cast_ray = init_strcut_cast_ray(mlx_cub);
	while (mlx_cub->cast_ray->rays < mlx_cub->cast_ray->num_of_rays)
	{
		mlx_cub->cast_ray->dish = 100000000;
		mlx_cub->cast_ray->disv = 100000000;
		check_horiental(mlx_cub, mlx_cub->cast_ray);
		check_vertical(mlx_cub, mlx_cub->cast_ray);
		set_the_min_pos(mlx_cub);
		draw_line(mlx_cub, mlx_cub->x_p, mlx_cub->y_p);
		mlx_cub->cast_ray->ra += mlx_cub->cast_ray->dr;
		if (mlx_cub->cast_ray->ra > 2 * PI)
			mlx_cub->cast_ray->ra -= 2 * PI;
		if (mlx_cub->cast_ray->ra < 0)
			mlx_cub->cast_ray->ra += 2 * PI;
		mlx_cub->cast_ray->rays++;
	}
}