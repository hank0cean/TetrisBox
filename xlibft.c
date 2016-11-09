/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlibft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 21:28:10 by chansen           #+#    #+#             */
/*   Updated: 2016/11/08 21:28:11 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		ft_putchar(str[i++]);
}

void	ft_putendl(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
		ft_putchar(str[i++]);
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
