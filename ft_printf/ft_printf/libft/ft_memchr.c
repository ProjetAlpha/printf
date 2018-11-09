/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 20:10:14 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 20:04:34 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *dest;

	dest = (unsigned char *)s;
	while (n-- != 0)
	{
		if (*dest == (unsigned char)c)
			return (dest);
		dest++;
	}
	return (NULL);
}
