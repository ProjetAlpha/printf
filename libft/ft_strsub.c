/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 19:01:47 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 21:03:29 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	counter;
	char	*dest;

	counter = 0;
	if (s)
	{
		if (!(dest = (char*)malloc(sizeof(char) * len + 1)))
			return (NULL);
		while (counter < len)
		{
			dest[counter] = s[start];
			start++;
			counter++;
		}
		dest[counter] = '\0';
		return (dest);
	}
	return ("\0");
}
