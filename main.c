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

char		**setboard(int size)
{
	char	**board;
	int		i;

	i = 0;
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

void		printboard(char **board)
{
	int		i;

	i = 0;
	while (board[i] != NULL)
	{
		ft_putendl(board[i]);
		i++;
	}
}

int			fillthat(int size, int row, char **bored, t_tetri **bgnlst)
{
	t_tetri	*tmp;
	t_spot	*spot;
	int		col;

	tmp = *bgnlst;
	col = 0;
	spot = newspot(size, col, row);
	if (tmp == NULL)
		return (1);
	while ((spot->row < spot->size))
	{
		if ((spotsvalid(spot, bored, &tmp) == 1) && (spot->col < spot->size))
		{
			placetet(spot->col, spot->row, bored, &tmp);
			if (fillthat(spot->size, 0, bored, &tmp->next))
				return (1);
			reset(spot->col, spot->row, bored, &tmp);
		}
		spot->row += (spot->col < spot->size) ? 0 : 1;
		spot->col = (spot->col < spot->size) ? (spot->col + 1) : 0;
	}
	return (0);
}

t_tetri		*storetetri(char *av)
{
	t_tetri			*tetri;
	char			tstr[21];
	unsigned int	i;
	int				fd;
	int				ret;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		err("error");
	while ((ret = read(fd, tstr, 21)))
	{
		if ((ret < 20) || (i == 26) || (newlineseparators(tstr) != 1))
			err("error");
		tstr[20] = '\0';
		if (!(tetricheck(tstr) == 1))
			err("error");
		storepoints(&tetri, tstr, i);
		i++;
	}
	close(fd);
	if (i == 0 || !(reread(av)))
		err("error");
	return (tetri);
}

int			main(int argc, char **argv)
{
	t_tetri			*tmp;
	char			**bored;
	int				minsqsize;
	int				done;

	done = 0;
	if (argc != 2)
		err("usage: ./fillit target_file");
	tmp = storetetri(argv[1]);
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
