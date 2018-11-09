/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 19:28:39 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 21:02:25 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static char		*i_trim(const char *s, int space, int len)
{
	char	*dest;
	int		index;
	int		res;

	index = 0;
	res = 0;
	while (is_space(s[len - 1]))
	{
		index++;
		len--;
	}
	res = ft_strlen(s) - (index + space);
	if (!(dest = (char*)malloc(sizeof(char) * res + 1)))
		return (NULL);
	index = 0;
	while (index < res)
	{
		dest[index] = s[index + space];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char			*ft_strtrim(char const *s)
{
	int space;
	int len;

	space = 0;
	len = 0;
	if (s)
	{
		len = ft_strlen(s);
		while (is_space(s[space]))
			space++;
		if (s[space] == '\0')
			return (ft_strnew(1));
		if (space == 0 && !is_space(s[len - 1]))
			return (ft_strdup(s));
		return (i_trim(s, space, len));
	}
	return (NULL);
}
