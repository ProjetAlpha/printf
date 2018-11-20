/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/13 14:42:44 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 22:08:48 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"

int		get_base(int flag)
{
	if (flag == D || flag == LD || flag == U || flag == LU || flag == I)
		return (10);
	if (flag == O || flag == LO)
		return (8);
	if (flag == X || flag == LX)
		return (16);
	return (0);
}

void	conv_length(t_info *info)
{
	if ((info->flag == D || info->flag == I) && info->length == 0)
		info->i_arg = (info->i_arg >= 0 || info->i_arg <= 0) ? (int)info->i_arg : 0;
	else if ((info->flag == U || info->flag == X || info->flag == LX || info->flag == O) && info->length == 0)
		info->i_arg = (unsigned int)info->i_arg;
	else if ((info->flag == LU || info->flag == LO || info->flag == LD))
		info->i_arg = ((unsigned long)info->i_arg);
	else if (info->length == HH && !(info->flag == U || info->flag == O ||
				info->flag == LO || info->flag == LU || info->flag == LD))
		info->i_arg  = (char)info->i_arg;
	else if(info->length == H && !(info->flag == U || info->flag == O || info->flag == LO
				|| info->flag == LU || info->flag == LD))
		info->i_arg = info->i_arg <= 0 ? ((unsigned short int)info->i_arg): (short int)info->i_arg;
	else if (info->length == L || info->length == Z || info->length == LL || info->length == J)
		info->i_arg = (unsigned long long)info->i_arg;
}

void	conv_ulength(t_info *info)
{
	if ((info->flag == U || info->flag == X || info->flag == LX || info->flag == O) && info->length == 0)
		info->u_arg = (unsigned int)info->u_arg;
	else if (info->length == HH && !(info->flag == U || info->flag == O ||
				info->flag == LO || info->flag == LU || info->flag == LD))
		info->u_arg = (unsigned char)info->u_arg;
	else if(info->length == H && !(info->flag == U || info->flag == O || info->flag == LO
				|| info->flag == LU || info->flag == LD))
		info->u_arg = (unsigned short int)info->u_arg;
	else if (info->length == L || info->length == Z || info->length == LL || info->length == J)
		info->u_arg = (unsigned long long)info->u_arg;
}

int		is_valid(char c)
{
	if  (is_extra_c(c) || is_flag(c) || ft_isdigit(c) || is_len_modif(c) || c == '.')
	   		return (1);
	return (0);	
}


void	check_end(char *str, char **curr_str, t_info *info)
{
	int len;
	char *tmp;

	len = 0;
	/*if (*str && *str != '%' && info->stop == 0)
	{
		info->stop = 1;
		info->c_len++;
		if (!(tmp = conv_char(*str, info)))
			write(1, tmp, 
		//write(1, "%", 1);
		(*curr_str)++;
	}*/
	if (*str && !is_valid(*str) && info->stop == 0)
	{
		info->stop = 1;
		if ((tmp = conv_char(*str, info)) != NULL)
		{
			len = ft_strlen(tmp);
			write(1, tmp, len);
			info->c_len+= len;
		}else
			info->c_len++;
		(*curr_str)++;
	}
}

int		check_extra(char **curr_str, char *str, t_info *info)
{
	while (*str && is_extra_c(*str))
	{
		if (*str == '#')
			info->extra[H_TAG] = H_TAG;
		else if (*str == '0')
			info->extra[ZERO] = ZERO;
		else if (*str == '-')
			info->extra[MINUS] = MINUS;
		else if (*str == '+')
			info->extra[PLUS] = PLUS;
		else if (*str == ' ')
			info->extra[SPACE] = SPACE;
		(*curr_str)++;
		str++;
	}
	check_end(str, curr_str, info); 
	return (0);
}

void	set_len_modif(char *str, t_info *info)
{
	while (*str && is_len_modif(*str))
	{
		if (*str == 'h' && *(str + 1) != 'h')
			info->length = H;
		else if (*str == 'l' && *(str + 1) != 'l')
			info->length = L;
		else if (*str == 'h' && *(str + 1) == 'h')
			info->length = HH;
		else if (*str == 'l' && *(str + 1) == 'l')
			info->length = LL;
		else if (*str == 'j')
			info->length = J;
		else if (*str == 'z')
			info->length = Z;
		if (info->length > 0)
			break;
		str++;
	}
}
