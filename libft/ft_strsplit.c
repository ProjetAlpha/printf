/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 14:08:13 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 12:07:37 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		ft_c_count(char *s, char c, int k)
{
	int c_count;

	c_count = 0;
	while (s[k] && s[k] != c)
	{
		c_count++;
		k++;
	}
	return (c_count);
}

static int		ft_w_count(char *s, char c)
{
	int w_count;
	int index;

	index = 0;
	w_count = 0;
	while (s[index])
	{
		while (s[index] && s[index] == c)
			index++;
		if (s[index] == '\0')
			return (w_count);
		if ((index > 0 && s[index - 1] == c) || (index == 0 && s[index] != c))
			w_count++;
		index++;
	}
	return (w_count);
}

static char		**ft_do_split(int w_count, char **dest, char *s, char c)
{
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	while (i < w_count)
	{
		while (s[k] && s[k] == c)
			k++;
		dest[i] = (char *)malloc(sizeof(char) * ft_c_count((char*)s, c, k) + 1);
		j = 0;
		while (s[j + k] && j < ft_c_count((char*)s, c, k) && s[j + k] != c)
		{
			dest[i][j] = (char)(s[j + k]);
			j++;
		}
		while (s[k] && s[k] != c)
			k++;
		dest[i][j] = '\0';
		i++;
	}
	dest[i] = ((void*)0);
	return (dest);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**dest;
	int		w_count;

	if (s)
	{
		w_count = ft_w_count((char*)s, c);
		if (!(dest = (char **)malloc(sizeof(char *) * w_count + 1)))
			return (NULL);
		return (ft_do_split(w_count, dest, (char*)s, c));
	}
	return (NULL);
}
