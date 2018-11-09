/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 18:20:51 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 21:05:31 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dest;
	int		len;
	int		counter;

	counter = 0;
	len = 0;
	if (s)
	{
		len = ft_strlen(s);
		if (!(dest = (char*)malloc(sizeof(char) * len + 1)))
			return (NULL);
		while (*s)
			dest[counter++] = f((char)*s++);
		dest[counter] = '\0';
		return (dest);
	}
	return ("\0");
}
