/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcgover <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:12:36 by mmcgover          #+#    #+#             */
/*   Updated: 2016/11/08 11:12:37 by mmcgover         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			findlowx(char **grid)
{
	int		x;
	int		y;
	int		lowx;

	x = 0;
	y = 0;
	lowx = 3;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (grid[y][x] == '#')
			{
				if (lowx > x)
					lowx = x;
			}
			x++;
		}
		y++;
	}
	return (lowx);
}

int			findlowy(char **grid)
{
	int		x;
	int		y;
	int		lowy;

	x = 0;
	y = 0;
	lowy = 3;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (grid[y][x] == '#')
			{
				if (lowy > y)
					lowy = y;
			}
			x++;
		}
		y++;
	}
	return (lowy);
}

t_tetri		*newtet(char **grid, int lowx, int lowy, int i)
{
	t_tetri	*new;
	int		x;
	int		y;
	int		j;

	ft_set3to0(&x, &y, &j);
	if (!(new = malloc(sizeof(t_tetri))))
		return (NULL);
	new->c = (char)(i + 'A');
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (grid[y][x] == '#')
			{
				new->x[j] = x - lowx;
				new->y[j++] = y - lowy;
			}
			x++;
		}
		y++;
	}
	new->next = NULL;
	return (new);
}

void		nxttet(t_tetri **bgnlst, t_tetri *lst)
{
	t_tetri	*temp;

	temp = *bgnlst;
	while (temp->next)
		temp = temp->next;
	temp->next = lst;
}

void		storepoints(t_tetri **bgnlst, char *tstr, unsigned int i)
{
	char	**grid;

	grid = ft_strsplit(tstr, '\n');
	if (i == 0)
		*bgnlst = newtet(grid, findlowx(grid), findlowy(grid), i);
	else
		nxttet(bgnlst, newtet(grid, findlowx(grid), findlowy(grid), i));
}
