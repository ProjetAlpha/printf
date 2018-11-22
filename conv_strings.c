/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_strings.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/19 12:05:53 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 00:37:00 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"

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

char	*get_padding(char *str, t_info *info)
{
	int len;
	
	info->t_len = 0;
	len = (str == NULL) ? 6 : ft_strlen(str);
	if (info->extra[ZERO] == ZERO && info->width > 0 && info->extra[MINUS] != MINUS)
	{
		if (info->prec >= 0 && info->is_prec == 1 && info->prec < len)
			return (set_zero(info->width - (len - (len - info->prec))));
		else
			return (set_zero(info->width - len));
	}
	if (info->prec >= 0 && info->is_prec == 1 && info->prec < len)
		info->t_len = info->width - (len - (len - info->prec));
	else
		info->t_len = info->width - len;
	return (fill_str(info->t_len, ' '));
}

char	*conv_strings(char *str, t_info *info)
{
	char *ret;
	int len;
	char *s_prec;

	info->t_len = 0;
	ret = ft_strnew(0);
	len = (str == NULL) ? 6 : ft_strlen(str);
	if (info->width > 0 && info->extra[MINUS] == 0)
		ret = ft_strjoin(ret, get_padding(str, info));
	if (!(s_prec = malloc(sizeof(char) * (len - (len - info->prec) + 1))))
		return (NULL);
	if (info->prec >= 0 && info->is_prec > 0 && info->prec < len && str != NULL)
		ret = ft_strjoin(ret, ft_strncpy(s_prec, str, len - (len - info->prec)));
	else if (str != NULL)
		ret = ft_strjoin(ret, str);
	else if (str == NULL)
	{
		if (info->prec >= 0 && info->is_prec > 0 && info->prec < len)
			ret = ft_strjoin(ret, ft_strncpy(s_prec, "(null)", len - (len - info->prec)));
		else
			ret = ft_strjoin(ret, "(null)");
	}
	if (info->width > 0 && info->extra[MINUS] > 0)
		ret = ft_strjoin(ret, get_padding(str, info));
	return (ret);
}

char	*conv_char(int c, t_info *info)
{
	char *ret;
	info->prec = 0;
	char str[2];
	str[0] = c;
	str[1] = '\0';
	info->is_prec = 0;

	ret = ft_strnew(0);
	info->t_len = 0;
	if (info->flag == 0 && info->extra[ZERO] == ZERO)
	{
		ret = ft_strjoin(ret, set_zero(info->width - 1));
		ret = ft_strjoin(ret, str);
		info->t_len++;
		return (ret);
	}
	if (info->extra[ZERO] == ZERO && info->width > 0)
	{
		ret = ft_strjoin(ret, set_zero(info->width - 1));
		ret = ft_strjoin(ret, str);
		info->t_len++;
		return (ret);
	}
	if (info->width > 0 && info->extra[MINUS] == 0)
		ret = ft_strjoin(ret, fill_str(info->width - 1, ' '));
	ret = ft_strjoin(ret, str);
	if (info->width > 0 && info->extra[MINUS] > 0)
		ret = ft_strjoin(ret, fill_str(info->width - 1, ' '));
	if (c == 0 && info->extra[MINUS] == 0)
		info->t_len++;
	else if (c == 0 && info->extra[MINUS] > 0)
		info->t_len--;
	return (ret);
}
