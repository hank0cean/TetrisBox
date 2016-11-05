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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char const *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
		ft_putchar(s[i++]);
}


void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
	return ;
}

void	*ft_memalloc(size_t size)
{
	char	*mem;

	mem = (void *)malloc(size);
	if (!(mem))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}


static char		*word_builder(char const *str, char c, unsigned int *index)
{
	unsigned	i;
	unsigned	start;
	unsigned	end;
	char		*word;

	i = *index;
	while (str[i] == c && str[i] != '\0')
		i++;
	start = i;
	while (str[i] != c && str[i] != '\0')
		i++;
	end = i;
	*index = i;
	word = ft_strnew(end - start);
	i = 0;
	while (start < end)
	{
		word[i] = str[start];
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	unsigned	i;
	unsigned	j;
	unsigned	words;
	char		**rtn;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	i = 0;
	j = 0;
	rtn = (char**)malloc(sizeof(char*) * (words + 1));
	if (!rtn)
		return (NULL);
	while (i < words)
	{
		rtn[i] = word_builder(s, c, &j);
		i++;
	}
	rtn[i] = 0;
	return (rtn);
}


void	ft_putendl(char const *s)
{
	ft_putstr(s);
	ft_putchar('\n');
}


void	*ft_memset(void *b, int c, size_t len)
{
	char *d;

	d = b;
	if (len)
	{
		while (len--)
		{
			*d++ = (unsigned char)c;
		}
	}
	return (b);
}

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)ft_memalloc(size + 1);
	if (!(str))
		return (NULL);
	ft_bzero(str, size);
	return (str);
}


void	err(char *s)
{
	ft_putendl(s);
	exit(42);
}

int 	newlineseperators(char *tstr)
{
	if (tstr[0] != '\n' && tstr[4] == '\n' && tstr[9] == '\n' && tstr[14] == '\n'
		&& (tstr[19] == '\n' || tstr[19] == '\0'))
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

	neighbors = 0;
	hash = 0;
	i = 0;
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

t_tetri		*newtet(char **grid, int i)
{
	t_tetri		*new;
	int 		x;
	int 		y;
	int 		j;

	x = 0;
	y = 0;
	j = 0;
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
				new->x[j] = x;
				new->y[j++] = y;
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
		*bgnlst = newtet(grid, i);
	else
		nxttet(bgnlst, newtet(grid, i));
}

	// while (y < 4)
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

t_tetri		*storetetri(char *av)
{
	t_tetri			*tetri;
	char			tstr[21];
	unsigned int	i;
	int				fd;

	i = 0;
	fd = open(av, O_RDONLY); //open file
	if (fd == -1)
		(err("error: failed to open file"));
	while (read(fd, tstr, 21)) //read 21 bytes at a time into tstr
	{
		if (i == 26)
			err("error: too many tetrominoes");
		if (!(newlineseperators(tstr) == 1))
			err("error: bad seperating newline");
		tstr[19] = '\0'; //sets newline at end of last 4 char of tetromino to '\0'
		if (!(tetricheck(tstr) == 1)) //check valid tetromino
			err("error: tetromino format off");
		storepoints(&tetri, tstr, i); //store points & i which will determine letter for tetromino at the address of tetri
		i++; //next tetromino
	}
	close(fd);
	if (i == 0)
	 	(err(""));
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

	size = 1;
	hashes = (tetcount(&lst) * 4);
	while ((size * size) < hashes)
		size++;
	return (size);
}

char	**setboard(int size)
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

int		main(int argc, char **argv)
{
	t_tetri			*tmp; //tetromino storage
	char			**bored; //board to fill and print

	if (argc != 2)
		err("usage: ./fillit target_file");
	tmp = storetetri(argv[1]); //store tetrominos in tmp after they are read
	if (!tmp)
		return (0);
	bored = setboard(sizeup(tmp));
	// while (!done)
	// {
	// 	bored = setboard(sizeup(tmp));
	// }
	printboard(bored);
}

















