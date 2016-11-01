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

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct s_tetri	t_tetri;

struct					s_tetri
{
	char	*str;
	char	c;
	int		x[4];
	int		y[4];
	struct s_tetri		*next;
};

#endif
