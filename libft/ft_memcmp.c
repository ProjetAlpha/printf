/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 20:27:42 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 12:20:17 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *s_one;
	unsigned char *s_two;

	s_one = (unsigned char*)s1;
	s_two = (unsigned char*)s2;
	while (n--)
	{
		if (*s_one != *s_two)
			return (*s_one - *s_two);
		s_one++;
		s_two++;
	}
	return (0);
}
