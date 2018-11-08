/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 19:19:05 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 21:06:32 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	char	*dest;

	if (s1 && s2)
	{
		i = 0;
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		if (!(dest = (char *)malloc(sizeof(char) * s1_len + s2_len + 1)))
			return (NULL);
		while (*s1)
			dest[i++] = *s1++;
		while (*s2)
			dest[i++] = *s2++;
		dest[i] = '\0';
		return (dest);
	}
	return ("\0");
}
