/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_basic.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 15:39:31 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 23:40:26 by thbrouss    ###    #+. /#+    ###.fr     */
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

static	char *get_padding(int n, t_info *info, int len)
{
	int ret;
	char *dest;

	ret = 0;
	dest = ft_strnew(0);
	info->t_len = 0;
	if ((info->prec == 0 && info->is_prec == 1) && n == 0)
		len--;
	if (info->extra[SPACE] == SPACE && info->extra[PLUS] != PLUS && n >= 0)
		ret++;
	if (info->extra[PLUS] == PLUS && n >= 0)
		ret++;
	if (n < 0)
		len++;
	if (info->prec > 0 && info->is_prec != 0 && info->prec > len)
	{
		if (n < 0)
			info->t_len = (info->width - 1) - ((info->prec - len) + len + ret);
		else
			info->t_len = info->width - ((info->prec - len) + len + ret); 
	}
	else if (info->width > len)
	{
		if (info->extra[ZERO] == ZERO && info->extra[MINUS] != MINUS)
			return (NULL);
		info->t_len = info->width - (len + ret);
	}
	if (info->t_len == 0)
		return (NULL);
	return (fill_str(info->t_len, ' '));
}

static char *set_prec(int n, t_info *info, int len)
{
	char *ret;
	char *tmp;
	int diff;

	diff = 0;
	ret = ft_strnew(0);
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
		if (info->extra[SPACE] == SPACE && info->extra[PLUS] != PLUS && n >= 0)
			diff++;
		if (info->extra[PLUS] == PLUS && n >= 0)
			diff++;
		if (n < 0)
			diff++;
		if ((tmp = set_zero(info->width - (len + diff))) != NULL)
			ret = ft_strjoin(ret, tmp);
	}
	return (ret);
}

char 	*conv_basic(int *extra, t_info *info)
{
	char *ret;
	char *tmp;
	int i_len;

	i_len = get_nbr_len(info, 10, 0);
	if (info->i_arg == 0)
		i_len++;
	ret = ft_strnew(0);
	if (info->extra[SPACE] == SPACE && info->extra[PLUS] != PLUS && info->i_arg >= 0)
		ret = ft_strjoin(ret, " ");
	if (info->width > 0 && info->extra[MINUS] != MINUS && info->width > i_len)
	{
		if ((tmp = get_padding(info->i_arg, info, i_len)) != NULL)
			ret = ft_strjoin(ret, tmp);
	}
	if (info->extra[PLUS] == PLUS && info->i_arg >= 0)
		ret = ft_strjoin(ret, "+");
	if (info->i_arg < 0)
		ret = ft_strjoin(ret, "-");
	if ((tmp = set_prec(info->i_arg, info, i_len)) != NULL)
		ret = ft_strjoin(ret, tmp);
	if (info->i_arg == 0 && !(info->is_prec > 0 && info->prec == 0))
		ret = ft_strjoin(ret, "0");
	if (info->i_arg != 0)
		ret = ft_strjoin(ret, conv_base(info, 10, i_len));
	if (info->width > 0 && info->extra[MINUS] == MINUS)
	{
		if ((tmp = get_padding(info->i_arg, info, i_len)) != NULL)
			ret = ft_strjoin(ret, tmp);
	}
	return (ret);
}
