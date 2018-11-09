/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:03:04 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/19 14:56:36 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*ptr2;

	if (size != 0 && ptr)
	{
		if (!(ptr2 = malloc(1)))
			return (0);
		ft_memdel(&ptr);
		return (ptr2);
	}
	if (!(ptr2 = malloc(size)))
		return (0);
	if (ptr)
	{
		ft_memcpy(ptr2, ptr, size);
		ft_memdel(&ptr);
	}
	return (ptr2);
}
