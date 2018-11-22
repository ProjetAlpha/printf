/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_hex.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 20:38:59 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 21:01:08 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
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

static	char *get_padding(unsigned long int n, t_info *info, int len)
{
	int ret;
	char *dest;

	ret = 0;
	dest = ft_strnew(0);
	info->t_len = 0;
	if ((info->prec == 0 && info->is_prec == 1) && n == 0)
		len--;
	if (info->extra[H_TAG] == H_TAG && info->u_arg != 0 && info->prec != 0)
		ret+=2;
	if (info->prec > 0 && info->is_prec != 0 && info->prec > len)
		info->t_len = info->width - ((info->prec - len) + len + ret);
	else if (info->width > len)
	{
		if (info->extra[ZERO] == ZERO && info->extra[MINUS] != MINUS && info->prec == 0 && info->is_prec == 0)
			return (NULL);
		info->t_len = info->width - (len + ret);
	}
	if (info->t_len == 0)
		return (NULL);
	return (fill_str(info->t_len, ' '));
}

static char *set_prec(unsigned long int n, t_info *info, int len)
{
	char *ret;
	char *tmp;
	int diff;

	diff = 0;
	ret = ft_strnew(0);
	if (info->extra[H_TAG] == H_TAG && n != 0 && info->prec >= 0 && info->is_prec > 0)
				len-=2;
	if (info->prec > len)
	{
		if (info->prec >= 0 && info->is_prec > 0)
		{
			if((tmp = set_zero(info->prec - (len + diff))) != NULL)
				ret = ft_strjoin(ret, tmp);
		}
	}else if (info->prec == 0 && info->is_prec == 0 && info->width > len
			&& info->extra[ZERO] == ZERO && info->extra[MINUS] != MINUS)
	{
		if ((tmp = set_zero(info->width - (len + diff))) != NULL)
			ret = ft_strjoin(ret, tmp);
	}
	return (ret);
}

char 	*conv_hexa(int *extra, t_info *info)
{
	char *ret;
	char *tmp;
	int i_len;

	i_len = get_nbr_len(info, 16, 1);
	//printf(" \nbefore Len : %d\n\n", i_len);
	if (info->u_arg == 0)
		i_len++;
	if (info->extra[H_TAG] == H_TAG && info->u_arg != 0)
		i_len+=2;
	//printf(" \nafter Len : %d\n\n", i_len);
	ret = ft_strnew(0);
	if (info->width > 0 && info->extra[MINUS] != MINUS && info->width > i_len)
	{
		if ((tmp = get_padding(info->u_arg, info, i_len)) != NULL)
			ret = ft_strjoin(ret, tmp);
	}
	if (info->extra[H_TAG] && info->u_arg != 0 && info->flag == X)
		ret = ft_strjoin(ret, "0x");
	if (info->extra[H_TAG] && info->u_arg != 0 && info->flag == LX)
		ret = ft_strjoin(ret, "0X");
	if ((tmp = set_prec(info->u_arg, info, i_len)) != NULL)
		ret = ft_strjoin(ret, tmp);
	if (info->u_arg == 0 && !(info->is_prec > 0 && info->prec == 0))
		ret = ft_strjoin(ret, "0");
	if (info->u_arg != 0)
		ret = ft_strjoin(ret, conv_ubase(info, 16, i_len));
	if (info->width > 0 && info->extra[MINUS] == MINUS)
	{
		if ((tmp = get_padding(info->u_arg, info, i_len)) != NULL)
			ret = ft_strjoin(ret, tmp);
	}
	return (ret);
}
