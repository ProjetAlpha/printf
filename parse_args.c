/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_arg.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/29 18:40:27 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 16:44:45 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>


char *get_extra(int *extra, t_info *info)
{
	char *res;
	int base;
	int calc;

	calc = 0;
	base = get_base(info->flag);
	res = ft_strnew(0);
	info->t_len = 0;
	if (base > 0)
		info->t_len += get_nbr_len(info, base);
	if (info->i_arg < 0 || (info->flag == 0 && info->is_prec == 0 && info->prec == 0 && !is_extra(extra, SPACE)))
		info->width--;
	if (info->i_arg == 0 && is_extra(extra, ZERO) && info->width > 0 && !(info->flag == O || info->flag == LO))
		calc += 1;
	if (((is_extra(extra, H_TAG) && info->flag == X) || (is_extra(extra, H_TAG) && info->flag == LX)))
			calc += 2;
	if ((info->flag == O || info->flag == LO) && is_extra(extra, H_TAG))
			calc+= 1;
	if (is_extra(extra, PLUS) && info->i_arg > 0 && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO) && info->flag)
			calc += 1;
	if (is_extra(extra, SPACE) && info->i_arg > 0 && !is_extra(extra, PLUS) && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO) && info->flag && info->prec == 0 && info->is_prec == 0)
			calc += 1;
	if (is_extra(extra, SPACE) && info->i_arg >= 0 && !is_extra(extra, PLUS) && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO) && !(info->flag == U || info->flag == LU) && info->flag)
	{
		res = ft_strjoin(res, " ");
		info->t_len += 1;
	}
	calc += info->t_len;
	if (!is_extra(info->extra, MINUS)) 
	{

		if (info->prec == 0 && !is_extra(extra, MINUS) && !is_extra(extra, ZERO) && info->flag)
		{
			calc = info->width - calc;
			if (calc > 0 && calc < info->width)
				res = ft_strjoin(res, fill_str(calc, ' '));
		}else if (info->prec > 0 && info->flag)
		{
			if (info->prec == 1)
				calc = info->width - 1 - (info->prec + calc +  - get_nbr_len(info, base));
			else
				calc = info->width - (info->prec + calc - get_nbr_len(info, base));
			if (calc > 0 && calc < info->width)
				res = ft_strjoin(res, fill_str(calc, ' '));
		}else if (!is_extra(extra, ZERO) && info->flag)
		{
			calc = info->width - calc;
			if (calc > 0 && calc < info->width)
				res = ft_strjoin(res, fill_str(calc, ' '));
		}else if (is_extra(extra, ZERO) && info->prec == 0 && info->is_prec && info->flag)
		{
			calc = info->width - calc;
			if (calc > 0 && calc < info->width)
				res = ft_strjoin(res, fill_str(calc, ' '));
		}else if (info->width > 0 && info->flag == 0 && !is_extra(extra, ZERO))
			res = ft_strjoin(res, fill_str(info->width, ' '));
		else
			calc -=info->t_len * 2;
	}
	if (!is_extra(info->extra, MINUS))
		calc += info->t_len;
	info->t_len += calc;
	if (info->i_arg < 0 && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO) && !(info->flag == U || info->flag == LU))
		res = ft_strjoin(res, "-");
	if (is_extra(extra, PLUS) && info->i_arg >= 0 && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO) && !(info->flag == U || info->flag == LU) && info->flag)
	{
		res = ft_strjoin(res, "+");
		info->t_len += 1;
	}
	if (is_extra(extra, SPACE) && info->i_arg > 0 && !is_extra(extra, PLUS) && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO))
		info->t_len += 1;
	if (info->i_arg < 0 !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO) && !(info->flag == U || info->flag == LU))
	{
		res = ft_strjoin(res, "-");
		info->t_len += 1;
	}
	if (((is_extra(extra, H_TAG) && info->flag == X) || (is_extra(extra, H_TAG) && info->flag == LX)))
	{
			if (info->i_arg != 0 && info->flag == X)
				res = ft_strjoin(res, "0x");
			if (info->i_arg != 0 && info->flag == LX)
				res = ft_strjoin(res, "0X");
			info->t_len += 2;
	}
	if (info->i_arg > 0 && (info->flag == O || info->flag == LO) && is_extra(extra, H_TAG))
	{
		res = ft_strjoin(res, "0");
		if (is_extra(extra, H_TAG) && info->prec > 0 && info->flag)
			info->prec--;
	}
	info->t_len = calc + get_nbr_len(info, base);
	if ((info->prec == 0 || info->flag == 0) && !is_extra(extra, MINUS) && is_extra(extra, ZERO) && info->width > 0 && info->t_len < info->width)
			res = ft_strjoin(res, get_zero(info));
	if (info->prec > 0 && info->flag)
	{
		info->prec -= get_nbr_len(info, base);
		if (info->i_arg == 0)
			info->prec -= 1;
		if (info->prec > 0 && info->is_prec == 1)
			res = ft_strjoin(res, fill_str(info->prec, '0'));
			calc += info->prec;
		info->t_len += info->prec;
	}
	if (info->flag > 0 && !(info->prec == 0 && info->i_arg == 0))
		res = ft_strjoin(res, conv_base(info, base, get_nbr_len(info, base)));	
	if (is_extra(info->extra, MINUS) && info->width > 0)
		res = ft_strjoin(res, fill_str(info->width - calc, ' '));
	return (res);
}	


char	*conv_int(long long int input, t_info *info)
{
	char *res;

	res = ft_strnew(0);
	info->i_arg = input;
	conv_length(info); 
	if (info->i_arg == 0 && info->is_prec == 0)
	{
		res = ft_strjoin(res, get_extra(info->extra, info));
		return (res = ft_strjoin(res, "0"));
	}
	res = ft_strjoin(res, get_extra(info->extra, info));
	return (res);
}


int		ft_printf(const char *str, ...)
{
	char *conv;
	conv = (char *)str;
	t_info *info;
	va_list va;
	char *res;
	
	info = malloc(sizeof(t_info));
	init_list(info);
	res = ft_strnew(0);
/*	if ((n = count_flags(conv, info)) == -1)
		return (escape_str(conv));*/
	va_start (va, str);
// va_arg(va, long long int);	
	write(1, res, ft_strlen(res));
	return (ft_strlen(res));
	//return (NULL);
}
