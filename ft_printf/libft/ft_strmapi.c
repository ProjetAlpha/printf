/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 18:42:17 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 21:05:04 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	int				len;
	unsigned int	counter;

	counter = 0;
	len = 0;
	if (s)
	{
		len = ft_strlen(s);
		if (!(dest = (char*)malloc(sizeof(char) * len + 1)))
			return (NULL);
		while (s[counter])
		{
			dest[counter] = f(counter, (char)s[counter]);
			counter++;
		}
		dest[counter] = '\0';
		return (dest);
	}
	return ("\0");
}
