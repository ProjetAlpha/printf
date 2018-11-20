/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_void.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 17:04:30 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 20:18:03 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"
#include "libft.h"
#include <stdio.h>


static	char	*set_zero(int n)
{
	char *dest;
	int i;

	i = 0;
	if (!(dest = malloc(sizeof(char) * n + 1)))
		return (NULL);
	while (i < n)
		dest[i++] = '0';
	dest[i] = '\0';
	return (dest);
}

static char *get_padding(unsigned long int n, char *str, t_info *info)
{
	int ret;
	int len;

	len = ft_strlen(str);
	info->t_len = 0;
	ret = 0;
	ret += 2;
	if (info->prec > 0 && info->is_prec != 0 && info->prec > len)
		info->t_len = info->width - ((info->prec - len) + len + ret);
	else if (info->width > len)
	{
		if (info->extra[ZERO] == ZERO)
			return (NULL);
		info->t_len = info->width - (len + ret);
	}
	if (info->t_len == 0)
		return (NULL);
	return (fill_str(info->t_len, ' '));
}

static char *set_prec(unsigned long int n, t_info *info, char *str)
{
	int len;
	char *ret;
	char *tmp;

	ret = ft_strnew(0);
	len = ft_strlen(str);
	if (info->prec > len)
	{
		if (info->prec >= 0 && info->is_prec > 0)
		{
			if ((tmp = set_zero(info->prec - len)) != NULL)
				ret = ft_strjoin(ret, tmp);	
		}
	}else if (info->prec == 0 && info->is_prec == 0 && info->width > len && info->extra[ZERO] == ZERO)
	{
		if ((tmp = set_zero(info->width - (len + 2))) != NULL)
				ret = ft_strjoin(ret, tmp);
	}
	return (ret);
}

char	*conv_void(unsigned long int n, t_info *info)
{
	char *str;
	int len;
	char *ret;
	char *tmp;
	info->u_arg = n;

	ret = ft_strnew(0);
	info->t_len = 0;

	str = conv_ubase(info, 16, get_nbr_len(info, 16, 1));
	len = ft_strlen(str);
	if (info->width > 0 && info->extra[MINUS] == 0 && info->width > len)
	{
		if ((tmp = get_padding(n, str, info)) != NULL)
			ret = ft_strjoin(ret, tmp);
	}
	ret = ft_strjoin(ret, "0x");
	if ((tmp = set_prec(n, info, str)) != NULL)
		ret = ft_strjoin(ret, tmp);
	if (len == 0)
		ret = ft_strjoin(ret, "0");
	else
		ret = ft_strjoin(ret, str);
	if (info->width > 0 && info->extra[MINUS] > 0)
	{
		if ((tmp = get_padding(n, str, info)) != NULL)
			ret = ft_strjoin(ret, tmp);
	}
	return (ret);
}
