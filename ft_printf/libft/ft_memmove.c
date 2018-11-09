/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 19:31:13 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 20:09:28 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*conv_d;
	unsigned char	*conv_s;
	size_t			index;

	conv_d = (unsigned char *)dest;
	conv_s = (unsigned char*)src;
	index = 0;
	if (conv_s > conv_d)
	{
		while (n--)
		{
			*(conv_d + index) = *(conv_s + index);
			index++;
		}
	}
	else
	{
		index = n - 1;
		while (n--)
		{
			*(conv_d + index) = *(conv_s + index);
			index--;
		}
	}
	return (dest);
}
