/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 15:25:35 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 11:57:22 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	s_tmp;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	s_tmp = size;
	while (*dest && size-- > 0)
		dest++;
	if (s_tmp < dst_len)
		return (src_len + s_tmp);
	while (*src && size-- > 1)
		*dest++ = *src++;
	while (*src)
		src++;
	*dest = '\0';
	return (dst_len + src_len);
}
