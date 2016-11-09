/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 20:01:41 by chansen           #+#    #+#             */
/*   Updated: 2016/10/23 00:27:48 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct  s_spot
{
	int			size;
	int			col;
	int			row;
}				t_spot;

typedef struct			s_tetri
{
	char				*str;
	char				c;
	int					x[4];
	int					y[4];
	struct s_tetri		*next;
}						t_tetri;

char			**setboard(int size);

int				fillthat(int size, int row, char **board, t_tetri **bgnlst);

void			printboard(char **board);

void			storepoints(t_tetri **bgnlst, char *tstr, unsigned int i);

int				findlowx(char **grid);

int				findlowy(char **grid);

void			nxttet(t_tetri **bgnlst, t_tetri *lst);

int				reread(char *av);

void			err(char *s);

int				newlineseparators(char *tstr);

void			reset(int c, int r, char **board, t_tetri **lst);

void			ft_set3to0(int *a, int *b, int *c);

int				neighborcheck(char *tstr, int index);

int				tetricheck(char *tstr);

int				tetcount(t_tetri **tetlst);

int				tetfitsboard(t_spot *spot, char **b, t_tetri **lst);

int				spotsvalid(t_spot *spot, char **board, t_tetri **lst);

void			placetet(int c, int r, char **board, t_tetri **lst);

int				sizeup(t_tetri *lst);

t_tetri			*storetetri(char *av);

t_tetri			*newtet(char **grid, int lowx, int lowy, int i);

t_spot			*newspot(int size, int col, int row);

#endif
