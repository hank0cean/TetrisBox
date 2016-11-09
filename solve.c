/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 21:07:57 by chansen           #+#    #+#             */
/*   Updated: 2016/11/08 21:08:01 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_spot	*newspot(int size, int col, int row)
{
	t_spot		*new;

	if (!(new = malloc(sizeof(t_spot))))
		return (NULL);
	new->size = size;
	new->col = col;
	new->row = row;
	return (new);
}

int		tetcount(t_tetri **tetlst)
{
	t_tetri	*lstp;
	int		i;

	i = 0;
	lstp = *tetlst;
	while (lstp != NULL)
	{
		lstp = lstp->next;
		i++;
	}
	return (i);
}

int		tetfitsboard(t_spot *spot, char **b, t_tetri **lst)
{
	t_tetri	*tet;
	int		j;

	tet = *lst;
	j = 0;
	while (j < 4)
	{
		if (tet->y[j] + spot->row >= spot->size
			|| tet->x[j] + spot->col >= spot->size)
			return (0);
		if (b[tet->y[j] + spot->row][tet->x[j] + spot->col] == '\0')
			return (0);
		j++;
	}
	return (1);
}

int		spotsvalid(t_spot *spot, char **b, t_tetri **lst)
{
	t_tetri	*tet;
	int		j;

	tet = *lst;
	j = 0;
	if (tetfitsboard(spot, b, &tet) != 1)
		return (0);
	while (j < 4)
	{
		if (b[tet->y[j] + spot->row][tet->x[j] + spot->col] >= '1')
			return (0);
		j++;
	}
	return (1);
}

void	placetet(int c, int r, char **board, t_tetri **lst)
{
	t_tetri	*tet;
	int		j;

	tet = *lst;
	j = 0;
	while (j < 4)
	{
		board[tet->y[j] + r][tet->x[j] + c] = (char)tet->c;
		j++;
	}
}
