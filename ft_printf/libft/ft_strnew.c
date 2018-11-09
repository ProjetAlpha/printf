/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 17:39:21 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 19:52:56 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*alloc;
	int		i;

	i = 0;
	if (!(alloc = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (size--)
		alloc[i++] = '\0';
	alloc[i] = '\0';
	return (alloc);
}
