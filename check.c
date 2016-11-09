/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmcgover <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:11:57 by mmcgover          #+#    #+#             */
/*   Updated: 2016/11/08 11:11:59 by mmcgover         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		reread(char *av)
{
	char	str[1];
	char	fstr[546];
	int		i;
	int		fdre;

	i = 0;
	fdre = open(av, O_RDONLY);
	if (fdre == -1)
		return (0);
	while (read(fdre, str, 1) != 0)
	{
		fstr[i] = str[0];
		i++;
	}
	i--;
	close(fdre);
	if (fstr[i] == '\n' && fstr[i - 1] == '\n')
		return (0);
	return (1);
}

int		sizeup(t_tetri *lst)
{
	int		hashes;
	int		size;

	size = 1;
	hashes = (tetcount(&lst) * 4);
	while ((size * size) < hashes)
		size++;
	return (size);
}

int		newlineseparators(char *tstr)
{
	if (tstr[0] != '\n' && tstr[4] == '\n' && tstr[9] == '\n' && tstr[14] ==
		'\n' && tstr[19] == '\n' && (tstr[20] == '\n' || tstr[20] == '\0'))
		return (1);
	else
		return (0);
}

int		neighborcheck(char *tstr, int index)
{
	int		cntneigh;

	cntneigh = 0;
	if ((index + 1) % 5 != 4)
	{
		if (tstr[index + 1] == '#')
			cntneigh++;
	}
	if (tstr[index - 1] != '\n')
	{
		if (tstr[index - 1] == '#')
			cntneigh++;
	}
	if (index + 5 < 20)
	{
		if (tstr[index + 5] == '#')
			cntneigh++;
	}
	if (index - 5 >= 0)
	{
		if (tstr[index - 5] == '#')
			cntneigh++;
	}
	return (cntneigh);
}

int		tetricheck(char *tstr)
{
	int		hash;
	int		neighbors;
	int		i;

	ft_set3to0(&hash, &neighbors, &i);
	while (tstr[i] != '\0')
	{
		if (tstr[i] != '.' && tstr[i] != '#' && tstr[i] != '\n')
			return (0);
		if (tstr[i] == '.' || tstr[i] == '\n')
			i++;
		if (tstr[i] == '#')
		{
			neighbors += neighborcheck(tstr, i);
			hash++;
			i++;
		}
	}
	if (hash == 4 && (neighbors == 6 || neighbors == 8))
		return (1);
	return (0);
}
