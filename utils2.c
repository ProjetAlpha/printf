/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/13 15:50:35 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 07:18:08 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

t_values		g_allvalues[] =
{
		S, LS, P, D, LD,
			I, O, LO, U, LU,
				X, LX, C, LC, F, LF
};

int		get_nbr_len(t_info *info, int base, int type)
{
	int len;
	unsigned long long tmp_2;
	long long int tmp;
	
	len = 0;
	tmp = 0;
	tmp_2 = 0;
	if (type == 0)
	{
		tmp = ABS(info->i_arg);
		while (tmp != 0)
		{
			len++;
			tmp /= base;
		}
	}
	else if (type == 1)
	{
		tmp_2 = ABS(info->u_arg);
		while (tmp_2 != 0)
		{
			len++;
			tmp_2 /= base;
		}
	}
	return (len);
}


char	*conv_ubase(t_info *info, int base, int len)
{
	char *ret;
	int index;
	char c;
	unsigned long tmp;
	index = 0;

	tmp = ABS(info->u_arg);
	if (info->flag == LX)
		c = 'A';
	else if (info->flag == X || info->flag == P)
		c = 'a';
	if (!(ret = malloc(sizeof(char) *(len + 1))))
		return (NULL);
	while (tmp != 0)
	{
		if (base > 10 && tmp % base >= 10)
			ret[index] = (tmp % base - 10) + c;
		else if (tmp % base < 10)
			ret[index] = tmp % base + '0';
		index++;
		tmp /= base;
	}
	ret[index] = '\0';
	return (ft_strrev(ret));
}

char	*conv_base(t_info *info, int base, int len)
{
	char *ret;
	int index;
	char c;
	unsigned long tmp;
	index = 0;

	tmp = ABS(info->i_arg);
	if (info->flag == LX)
		c = 'A';
	else if (info->flag == X)
		c = 'a';
	if (!(ret = malloc(sizeof(char) *(len + 1))))
		return (NULL);
	if ((unsigned long long)tmp == 0)
		return (NULL);
	while (tmp != 0)
	{
		if (base > 10 && tmp % base >= 10)
			ret[index] = (tmp % base - 10) + c;
		else if (tmp % base < 10)
			ret[index] = tmp % base + '0';
		index++;
		tmp /= base;
	}
	ret[index] = '\0';
	return (ft_strrev(ret));
}

char *fill_str(int len, char c)
{
	char *res;
	int i;

	i = 0;
	if (len < 0)
		return (NULL);
	if (!(res = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len-- != 0)
		res[i++] = c;
	res[i] = '\0';
	return (res);
}

void	set_flags(char c, t_info *info)
{
	int i;

	i = 0;
	while (FLAGS[i])
	{
		if (FLAGS[i] == c)
			info->flag = g_allvalues[i];
		i++;
	}
}

char	*get_zero(t_info *info)
{
	long long int n;
	int i;
	char *res;

	if (info->width == 0)
		return (NULL);
	n = info->width;
	i = 0;
	if (info->i_arg == 0)
		;
	if (n > info->t_len)
		n -= info->t_len;
	else
		return (NULL);
	if (n > 0)
	{
		if (!(res = malloc(sizeof(char) * n + 1)))
			return (NULL);
	}else
		return (NULL);
	info->t_len += n;
	while (n-- != 0)
		res[i++] = '0';
	res[i] = '\0';
	return (res);
}
