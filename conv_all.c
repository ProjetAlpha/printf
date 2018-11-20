/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_digit.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/14 16:40:21 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 22:00:41 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

char	*conv_uint(unsigned long input, t_info *info)
{
	char *res;

	res = ft_strnew(0);
	info->u_arg = input;
	conv_ulength(info);
	if (info->flag == X || info->flag == LX)
		res = ft_strjoin(res, conv_hexa(info->extra, info));
	if (info->flag == O || info->flag == LO)
		res = ft_strjoin(res, conv_o(info->extra, info));
	if (info->flag == U || info->flag == LU || info->flag == LD)
		res = ft_strjoin(res, conv_un(info->extra, info));
	return (res);
}

char	*conv_int(long long int input, t_info *info)
{
	char *res;

	res = ft_strnew(0);
	info->i_arg = input;
	conv_length(info);
	res = ft_strjoin(res, conv_basic(info->extra, info));
	return (res);
}

char	*conv_flags(t_info *info, va_list args, char **curr_str, char *str)
{
	if (info->flag == D || info->flag == I)
		return (conv_int(va_arg(args, long long int), info));
	if (info->flag == LX || info->flag == LU
			|| info->flag == LD || info->flag == U
			|| info->flag == X || info->flag == O || info->flag == LO
			|| info->length == Z || info->length == LL || info->length == J)
		return (conv_uint(va_arg(args, unsigned long int), info));
	if (info->flag == LS || info->flag == S)
		return (conv_strings(va_arg(args, char *), info));
	else if (info->flag == C || info->flag == LC)
		return (conv_char(va_arg(args, int), info));
	else if (info->flag == P)
		return (conv_void((unsigned long int)va_arg(args, void *), info));
	return (NULL);
}
