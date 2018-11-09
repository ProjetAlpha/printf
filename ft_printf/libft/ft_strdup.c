/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 12:09:52 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 12:19:30 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dest;

	len = 0;
	while (s[len])
		len++;
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	len = 0;
	while (s[len])
	{
		dest[len] = s[len];
		len++;
	}
	dest[len] = '\0';
	return (dest);
}
