/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 19:59:15 by chansen           #+#    #+#             */
/*   Updated: 2016/10/22 23:07:49 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	error(char *s)
{
	ft_putendl(s);
	return (NULL);
}

int		neighborcheck(char *s, int index)
{
	int		cntneigh;

	cntneigh = 0;
	if ((i + 1) % 5 != 4)
	{
		if (s[i + 1] == '#') //right neighbor
			cntneigh++;
	}
	if (s[i - 1] != '\n')
	{
		if (s[i - 1] == '#') //left neighbor
			cntneigh++;
	}
	if (i + 5 < 20)
	{
		if (s[i + 5] == '#') //bot neighbor
			cntneigh++;
	}
	if (i - 5 >= 0)
	{
		if (s[i - 5] == '#') //top neighbor
			cntneigh++;
	}
	return (cntneigh); //return num of neighbors for this "#"
}

void		tetricheck(char *ts)
{
	int		hash;
	int		neighbors;
	int		i;

	neighbors = 0;
	hash = 0;
	i = 0;
	while (ts[i] != '\0')
	{
		if (ts[i] != '.' || ts[i] != '#')
			return (0);
		while (ts[i] == '.') //move thru "."
			i++;
		if (ts[i] == '#') //find "#"
		{
			neighbors = neighborcheck(ts, i); //count neighboring "#"
			hash++; //count "#" = hash
			i++; //find next "#"
		}
		if (hash == 3 && (neighbors == 6 || neighbors == 8))
			return (1); //found 4 "#"s with valid num of neighbors
	}
	return (0); //did not find 4 "#"s or num of neighbors was off
}

t_tetri		storetetri(char *av)
{
	t_tetri			*tetri;
	char			tstr[21];
	unsigned int	i;
	int				fd;

	i = 0;
	fd = open(av, O_RDONLY); //open file
	if (fd == -1)
		return (error("error: failed to open file"));
	while (read(fd, tstr, 21)) //read 21 bytes at a time into tstr
	{
		if (i == 26)
			return (error("error: too many tetrominoes"));
		tstr[20] = '\0'; //sets end of tetromino to '\0'
		if (!(tetricheck(tstr))) //check valid tetromino
			return (error("error: tetromino format off"));

		i++; //next tetromino
	}
}

int		main(int argc, char **argv)
{
	t_tetri		*tmp;
	char		**bored;
	
	if (argc != 2)
		return (error("usage: ./fillit target_file"));
	tmp = storetetri(argv[1]); //store tetrominos in tmp after they are read
	if (!tmp)
		return (error(""));

		
}

