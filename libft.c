/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 21:15:53 by chansen           #+#    #+#             */
/*   Updated: 2016/11/08 21:15:55 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)ft_memalloc(size + 1);
	if (!(str))
		return (NULL);
	ft_bzero(str, size);
	return (str);
}

char	*word_builder(char const *str, char c, unsigned int *index)
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

char	**ft_strsplit(char const *s, char c)
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
