/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrchr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 14:53:18 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 13:02:22 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int memo;
	unsigned int counter;

	memo = 0;
	counter = 0;
	while (s[counter])
	{
		if (c == s[counter])
			memo = counter;
		counter++;
	}
	if (c == '\0' && c == s[counter])
		memo = counter;
	if (c == 0 && c != s[counter])
		return ("\0");
	else if (memo == 0 && c == s[0])
		return ((char *)s + memo);
	else if (memo)
		return ((char *)s + memo);
	return (NULL);
}
