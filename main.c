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

void	err(char *s)
{
	ft_putendl(s);
	exit(42);
}

void	ft_set3to0(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int 	newlineseperators(char *tstr)
{
	if (tstr[0] != '\n' && tstr[4] == '\n' && tstr[9] == '\n' && tstr[14] == '\n'
		&& tstr[19] == '\n' && (tstr[20] == '\n' || tstr[20] == '\0'))
		return (1);
	else
		return (0);
	// else
	// {
	// 	if (tstr[0] != '\n' && tstr[4] == '\n' && tstr[9] == '\n' && tstr[14] == '\n'
	// 		&& tstr[19] == '\n' && (tstr[20] == '\n' || tstr[20] == '\0'))
	// 		return (1);
	// 	else
	// 		return (0);
	// }
}

int		neighborcheck(char *tstr, int index)
{
	int		cntneigh;

	cntneigh = 0;
	if ((index + 1) % 5 != 4)
	{
		if (tstr[index + 1] == '#') //right neighbor
			cntneigh++;
	}
	if (tstr[index - 1] != '\n')
	{
		if (tstr[index - 1] == '#') //left neighbor
			cntneigh++;
	}
	if (index + 5 < 20)
	{
		if (tstr[index + 5] == '#') //bot neighbor
			cntneigh++;
	}
	if (index - 5 >= 0)
	{
		if (tstr[index - 5] == '#') //top neighbor
			cntneigh++;
	}
	return (cntneigh); //return num of neighbors for this "#"
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
		if (tstr[i] == '.' || tstr[i] == '\n') //move thru "."
			i++;
		if (tstr[i] == '#') //find "#"
		{
			neighbors += neighborcheck(tstr, i); //count neighboring "#"(s)
			hash++; //count "#" = hash
			i++; //find next "#"
		}
	}
	if (hash == 4 && (neighbors == 6 || neighbors == 8))
		return (1); //found 4 "#"s with valid num of neighbors
	return (0); //did not find 4 "#"s or num of neighbors was off
}


int 	findlowx(char **grid)
{
	int 	x;
	int 	y;
	int 	lowx;

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

int 	findlowy(char **grid)
{
	int 	x;
	int 	y;
	int 	lowy;

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
	t_tetri		*new;
	int 		x;
	int 		y;
	int 		j;

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

void 	nxttet(t_tetri **bgnlst, t_tetri *lst)
{
	t_tetri 	*temp;

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

void 	reread(char *av)
{
	char	str[1];
	char	fstr[546];
	int 	i;
	int 	fdre;

	i = 0;
	fdre = open(av, O_RDONLY);
	if (fdre == -1)
		err("error");
	while (read(fdre, str, 1) != 0)
	{
		fstr[i] = str[0];
		i++;
	}
	i--;
	close(fdre);
	if (fstr[i] == '\n' && fstr[i - 1] == '\n')
		err("error");
}

t_tetri		*storetetri(char *av)
{
	t_tetri			*tetri;
	char			tstr[21];
	unsigned int	i;
	int				fd;
	int 			ret;

	i = 0;
	fd = open(av, O_RDONLY); //open file
	if (fd == -1)
		err("error");
	while ((ret = read(fd, tstr, 21))) //read 21 bytes at a time into tstr
	{
		if (ret < 20)
			err("error");
		if ((i == 26) || (newlineseperators(tstr) != 1))
			err("error");
		tstr[20] = '\0'; //sets newline at end of last 4 char of tetromino to '\0'
		if (!(tetricheck(tstr) == 1)) //check valid tetromino
			err("error");
		storepoints(&tetri, tstr, i); //store points & i which will determine letter for tetromino at the address of tetri
		i++; //next tetromino
	}
	close(fd);
	reread(av);
	if (i == 0)
	 	err("error");
	return (tetri);
}

int		tetcount(t_tetri **tetlst) // returns count of tetrominos (i)
{
	t_tetri		*lstp;
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

int		sizeup(t_tetri *lst) // takes total number of "#" and finds the sqrt rounded up for the smallest possible dimensions of our board that the tetrominos can fit within
{
	int		hashes;
	int		size;

	size = 1;
	hashes = (tetcount(&lst) * 4);
	while ((size * size) < hashes)
		size++;
	return (size);
}

char	**setboard(int size) // mallocs board and sets all spots to blank '.'s
{
	char	**board;
	int 	i;

	i  = 0;
	board = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		board[i] = ft_strnew(size);
		board[i] = ft_memset(board[i], '.', size);
		i++;
	}
	board[i] = 0;
	return (board);
}

void	printboard(char **board)
{
	int 	i;

	i = 0;
	while (board[i] != NULL)
	{
		ft_putendl(board[i]);
		i++;
	}
}

int 	tetfitsboard(int size, int c, int r, char **bored, t_tetri **lst)
{
	t_tetri 	*tet;
	int 		j;

	tet = *lst;
	j = 0;
	while (j < 4)
	{
		if (tet->y[j] + r >= size || tet->x[j] + c >= size)
			return (0);
		if (bored[tet->y[j] + r][tet->x[j] + c] == '\0')
			return (0);
		j++;
	}
	return (1);
}

int 	spotsvalid(int size, int c, int r, char **bored, t_tetri **lst)
{
	t_tetri 	*tet;
	int 		j;

	tet = *lst;
	j = 0;
	if (tetfitsboard(size, c, r, bored, &tet) != 1)
		return (0);
	while (j < 4)
	{
		if (bored[tet->y[j] + r][tet->x[j] + c] >= '1') 
			return (0);
		j++;
	}
	return (1);
}

void	placetet(int c, int r, char **bored, t_tetri **lst)
{
	t_tetri 	*tet;
	int 		j;
	//char		*str;

	//str = "1234";
	tet = *lst;
	j = 0;
	while (j < 4)
	{
		bored[tet->y[j] + r][tet->x[j] + c] = (char)tet->c; // needs to be 'A', '1' for testing
		j++;
	}
}

void	reset(int c, int r, char **bored, t_tetri **lst)
{
	t_tetri		*tet;
	int 		x;
	int 		y;
	int 		j;

	tet = *lst;
	j = 0;
	while (j < 4)
	{
		x = tet->x[j];
		y = tet->y[j];
		bored[r + y][c + x] = '.';
		j++;
	}
}

// void	placeat(int c, int r, char **bored)
// {
// 	bored[r][c] = '@';
// }

int 	fillthat(int size, int row, char **bored, t_tetri **bgnlst)
{
	t_tetri		*tmp;
	int 		col;

	tmp = *bgnlst;
	col = 0;
	if (tmp == NULL)
		return (1);
	while ((row < size)) // to make sure our tetromino is within the bounds of the board and to keep our start point above bottom of the board
	{
		// col = 0;
		// while ((spotsvalid(size, col, row, bored, &tmp) != 1) && (col < size)) // move thru col if not valid spot
		// 	col++;
		//if (col > size)
		//	col = 0;
		if ((spotsvalid(size, col, row, bored, &tmp) == 1) && (col < size))
		{
			placetet(col, row, bored, &tmp);
			if (fillthat(size, 0, bored, &tmp->next))
				return (1);
			reset(col, row, bored, &tmp);
		}
		row += (col < size) ? 0 : 1;
		col = (col < size) ? (col + 1) : 0;
		
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_tetri			*tmp; //tetromino storage
	char			**bored; //board to fill and print
	int 			minsqsize;
	int 			done;

	done = 0;
	if (argc != 2)
		err("usage: ./fillit target_file");
	tmp = storetetri(argv[1]); //store tetrominos in tmp after they are read
	if (!tmp)
		return (0);
	minsqsize = sizeup(tmp);
	while (!done)
	{
		bored = setboard(minsqsize);
		done = fillthat(minsqsize, 0, bored, &tmp);
		if (!done)
			minsqsize++;
	}
	printboard(bored);
	return (1);
}



















