/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 18:00:08 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 12:12:51 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	int counter;

	counter = 0;
	while (n--)
	{
		(((unsigned char*)dest)[counter]) = (((unsigned char*)src)[counter]);
		if ((((unsigned char*)dest)[counter++]) == (unsigned char)c)
			return (((unsigned char*)dest + counter));
	}
	return (NULL);
}
