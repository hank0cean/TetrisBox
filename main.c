/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 19:59:15 by chansen           #+#    #+#             */
/*   Updated: 2016/10/28 13:05:54 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "./../libft/libft.h"
#include <stdio.h>

int	err(char *s)
{
	ft_putendl(s);
	return (NULL);
}

int 	newlineseperators(char *str)
{
	if (str[0] != '\n' && str[5] == '\n' && str[10] == '\n' && str[15] == '\n'
		&& (str[20] == '\n' || str[20] == '\0'))
		return (1);
	else
		return (0);
}

int		neighborcheck(char *s, int index)
{
	int		cntneigh;

	cntneigh = 0;
	if ((index + 1) % 5 != 4)
	{
		if (s[index + 1] == '#') //right neighbor
			cntneigh++;
	}
	if (s[index - 1] != '\n')
	{
		if (s[index - 1] == '#') //left neighbor
			cntneigh++;
	}
	if (index + 5 < 20)
	{
		if (s[index + 5] == '#') //bot neighbor
			cntneigh++;
	}
	if (index - 5 >= 0)
	{
		if (s[index - 5] == '#') //top neighbor
			cntneigh++;
	}
	return (cntneigh); //return num of neighbors for this "#"
}

int		tetricheck(char *ts)
{
	int		hash;
	int		neighbors;
	int		i;

	neighbors = 0;
	hash = 0;
	i = 0;
	while (ts[i] != '\0')
	{
		if (ts[i] != '.' && ts[i] != '#' && ts[i] != '\n')
			return (0);
		if (ts[i] == '.' || ts[i] == '\n') //move thru "."
			i++;
		if (ts[i] == '#') //find "#"
		{
			neighbors += neighborcheck(ts, i); //count neighboring "#"(s)
			hash++; //count "#" = hash
			i++; //find next "#"
		}
	}
	if (hash == 4 && (neighbors == 6 || neighbors == 8))
		return (1); //found 4 "#"s with valid num of neighbors
	return (0); //did not find 4 "#"s or num of neighbors was off
}

void		storepoints(t_tetri **bgnlst, char *str, unsigned int i)
{
	char	**grid;
	int 	x;
	int 	y;
	int 	j;

	j = 0;
	x = 0;
	y = 0;
	grid = ft_strsplit(str, '\n');
	if (i == 0)
		*bgnlst = newtet(find_x(grid), find_y(grid));
	else
		*bgnlst = nxttet(i, find_x(grid), find_y(grid));
	// while(y < 4)
	// {
	// 	x = 0;
	// 	while (x < 4)
	// 	{
	// 		if (grid[y][x] == '.')
	// 			x++;
	// 		if (grid[y][x] == '#')
	// 		{
	// 			bgnlst->x[j] = x;
	// 			bgnlst->y[j] = y;
	// 			j++;
	// 			x++;
	// 		}
	// 	}
	// 	y++;
	// }
}

t_tetri		*storetetri(char *av)
{
	t_tetri			*tetri;
	char			tstr[21];
	unsigned int	i;
	int				fd;

	i = 0;
	fd = open(av, O_RDONLY); //open file
	if (fd == -1)
		return (err("error: failed to open file"));
	while (read(fd, tstr, 21)) //read 21 bytes at a time into tstr
	{
		if (i == 26)
			return (err("error: too many tetrominoes"));
		if (newlineseperators(tstr) == 1)
			tstr[20] = '\0'; //sets newline at end of last 4 char of tetromino to '\0'
		else
			return (err("error: bad seperating newline"));
		if (!(tetricheck(tstr) == 1)) //check valid tetromino
			return (err("error: tetromino format off"));
		storepoints(&tetri, tstr, i); //store points of tetri & i which will determine letter for tetromino
		i++; //next tetromino
	}
	if (i == 0)
		return (err(""));
	close(fd);
	return (tetri);
}

int		tetcount(t_tetri **tetlst)
{
	t_tetri		*lstp;
	int		i;

	i = 0;
	lstp = *tetlst;
	while (lstp->next)
	{
		lstp = lstp->next;
		i++;
	}
	return (i);
}

int		sizeup(t_tetri *lst)
{
	int		hashes;
	int		size;

	hashes = (tetcount(&lst) * 4);
	
}

int		main(int argc, char **argv)
{
	t_tetri			*tmp; //tetromino storage
	//char			**bored; //board to fill and print
	//unsigned int	minsqsize;

	if (argc != 2)
		return (err("usage: ./fillit target_file"));
	tmp = storetetri(argv[1]); //store tetrominos in tmp after they are read
	if (!tmp)
		return (0);
	printf("%d\n", tmp->next->x[0]);
	printf("%d\n", tmp->next->y[0]);
	//minsqsize = sizeup(tmp);

}

