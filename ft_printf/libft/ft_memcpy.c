/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 17:13:45 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 19:29:41 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d_conv;
	char	*s_conv;
	int		counter;

	counter = 0;
	d_conv = (char *)dest;
	s_conv = (char *)src;
	while (n--)
	{
		d_conv[counter] = s_conv[counter];
		counter++;
	}
	return (dest);
}
