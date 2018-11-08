/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_arg.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/29 18:40:27 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 14:14:52 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

int		is_extra_c(char c)
{
	return (c == '#' || c == '0' || c == '-' || c == '+' || c == ' ' || c == '%');
}

int		is_len_modif(char c)
{
	return (c == 'h' || c == 'l' || c == 'j' || c == 'z');
}

int		check_extra(char *str, t_info *info)
{
	int pos;
	int skip;
	char find[5];

	pos = 0;
	skip = 0;
	while (is_extra_c(*str))
	{
		if (pos <= 3)
		{	
			if (*str == '#' && find[0] != '#')
			{
				info->extra[pos] = H_TAG;
				find[0] = '#';
				pos++;
			}
			else if (*str == '0' && find[1] != '0')
			{
				info->extra[pos] = ZERO;
				find[1] = '0';
				pos++;
			}
			else if (*str == '-' && find[2] != '-')
			{
				info->extra[pos] = MINUS;
				find[2] = '-';
				pos++;
			}
			else if (*str == '+' && find[3] != '+')
			{
				info->extra[pos] = PLUS;
				find[3] = '+';
				pos++;
			}
			else if (*str == ' ' && find[4] != ' ')
			{
				info->extra[pos] = SPACE;
				find[3] = ' ';
				pos++;
			}
		}
		str++;
	}
	return (0);	
}

void	set_len_modif(char *str,  t_info *info)
{
	while (is_len_modif(*str))
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

int		is_flag(char c)
{
	int i;

	i = 0;
	while (FLAGS[i])
	{
		if (FLAGS[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	set_flags(char c, t_info *info)
{
	int i;

	i = 0;
	while (FLAGS[i])
	{
		if (FLAGS[i] == c)
			info->flag = allValues[i];
		i++;
	}
}


void	init_list(t_info *info)
{
	int i;

	i = 0;
	info->width = 0;
	info->prec = 0;
	info->length = 0;
	info->flag = 0;
	info->skip = 0;
	info->i_arg = 0;
	while (i <= 6)
		info->extra[i++] = 0;
	info->pos[0] = 0;
	info->pos[1] = 0;
	info->next = NULL;
}

int		is_empty(int *extra)
{
	int i;

	i = 0;
	while (i <= 6)
	{
		if (extra[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

int		count_flags(char *str, t_info *info)
{
	int count_flags;
	int index;
	int ret;
	char *begin;

	index = 0;
	begin = str;
	ret = 0;
	count_flags = 0;
	while (*str)
	{
		if (*str == '%')
		{
			//init_list(info);
			//info = malloc(sizeof(t_info));
			//if (*(str - 1) == '%')
			//info->extra[4] = PERCENT;
			// %%%    			--- Inc en dehors d une fonction : &str = **str => (*str)++;
			// si pas de flags, coupe la string entre pos begin et pos end. 
			// Mais si pourcent (extra_4), alors prend le en compte.
			// TODO : mieux handle les %.
			count_flags++;

			if (*str == '%' && *(str + 1) != '%')
			{
			//	count_flags++;
				info->pos[START] = &(*str) - begin;
				str++;
				check_extra(&(*str), info);
				while (is_extra_c(*str))
				{
					if (*str == '%' && *(str + 1) == '%')
						info->extra[PERCENT]++;
					str++;
				}
				while (ft_isdigit(*str))
				{
					info->width++;
					str++;
				}
				if (info->width > 0)
					info->width = ft_atoi(ft_strsub(begin, &(*str) - (begin + info->width), info->width));
				if (*str == '.')
				{
					str++;
					while (ft_isdigit(*str))
					{
						info->prec++;
						str++;
					}
				}
				if (info->prec > 0)
					info->prec = ft_atoi(ft_strsub(begin, &(*str) - (begin + info->prec), info->prec));
				set_len_modif(&(*str), info);
				if (info->length == HH || info->length == LL)
					str += 2;
				else if (info->length > 0)
					str++;
				set_flags(*str, info);
				if (info->flag > 0)
					str++;
				if (info->prec > 0 || info->width > 0 || !is_empty(info->extra))
					str--;
			}
			else if (*(str + 1) == '%')
			{
				info->pos[START] = &(*str) - begin;
				info->extra[PERCENT]++;
				str += 1;
			}
			info->pos[END] = &(*str) - begin;
			info->next = malloc(sizeof(t_info));
			info = info->next;
			init_list(info);
		}
		str++;
	}
	if (count_flags == 0)
		return (-1);
	return (count_flags);
}

void	print_struct(t_info *info)
{
	int i;

	while (info)
	{
		printf("WIDTH : %d | PREC : %d | LEN : %d | FLAG : %d | SKIP : %d\n\n", info->width, info->prec, info->length, info->flag,
				info->skip);
		i = 0;
		while (i < 6)
		{
			printf("EXTRA_%d : %d | ", i, info->extra[i]);
			i++;
		}
		printf("\n\n");
		printf("POS_BEGIN : %d | POS_END : %d\n\n", info->pos[0], info->pos[1]);
		info = info->next;
	}
}

char *get_type(int flag)
{
	if (flag == D || flag == LD || flag == 	I || flag == O
			|| flag == LO || flag == U || flag == LU || flag == X || flag == LX)
		return ("int");
	if (flag == S || flag == LS)
		return ("string");
	if (flag == C || flag == LC)
		return ("s_string");
	if (flag == P)
		return ("void");
	return (NULL);
}

t_info *get_info(int pos, t_info *info)
{
	int c_flags;

	c_flags = 0;
	while (info)
	{
		if (pos == c_flags)
			return (info);
		if (info->flag != 0)
			c_flags++;
		info = info->next;
	}
	return (NULL);
}

int		is_extra(int *extra, int id)
{
	int i;

	i = 0;	
	while (extra[i])
	{
		if (extra[i] == id)
			return (1);
		i++;
	}
	return (0);
}

char	*get_zero(t_info *info)
{
	int n;
	int i;
	char *res;

	if (info->width == 0)
		return (NULL);	
	n = info->width;
	i = 0;
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

long long int		get_nbr_len(int n, int base)
{
	int len;
	len = 0;
	while (n != 0)
	{
		len++;
		n /= base;
	}
	return (len);
}

int		conv_length(t_info *info)
{
	if (info->length == HH)
		return ((unsigned char)info->i_arg);	
	else if(info->length == H)
		return ((short int)info->i_arg);
	else if (info->length == L)
		return ((long int)info->i_arg);
	else if (info->length == LL)
		return ((long long int)info->i_arg);
	return (info->i_arg);
}

char	*conv_base(t_info *info, long long int base, int len)
{
	char *ret;
	int index;
	char c;
	int is_neg;
	long long int tmp;

	index = 0;
	is_neg = 0;
	conv_length(info);

	tmp = info->i_arg;
	if (info->flag == LX)
		c = 'A';
	else if (info->flag == X)
		c = 'a';
	if ((info->flag == X || info->flag == LX || info->flag == LO || info->flag == U || info->flag == LU
				|| info->flag == O) && tmp < 0)
	{	
		tmp = U_IM - info->i_arg *-1;
		if (!(ret = malloc(sizeof(char) * (get_nbr_len(tmp, base) + 1))))
			return (NULL);
	}
	else
	{
		if (tmp < 0)
			len++;
		if (!(ret = malloc(sizeof(char) *(len + 1))))
			return (NULL);
	}
	if (tmp < 0)
	{
		tmp *= -1;
		is_neg = 1;
	}
	while (tmp != 0)
	{
		if (base > 10 && tmp % base >= 10)
			ret[index] = (tmp % base - 10) + c;
		else
			ret[index] = tmp % base + '0';
		index++;
		tmp /= base;
	}
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
	//info->t_len += len;
	while (len-- != 0)
		res[i++] = c;
	res[i] = '\0';
	return (res);
}


/*char	*get_padding(t_info *info, int *extra)
{
	char *res;
	
	if (info->i_arg < 0)
		info->width--;
	printf(" RESSS : %d\n", info->width - (info->t_len + (info->prec - info->t_len)));
	if (!is_extra(info->extra, MINUS) && info->width > 0 && info->width > info->t_len + (info->prec - info->t_len))
		res = ft_strjoin(res, fill_str(info->width - (info->t_len + (info->prec - info->t_len)), ' '));
	if (info->i_arg < 0 && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO) && !(info->flag == U || info->flag == LU))
		res = ft_strjoin(res, "-");
	if (info->i_arg < 0)
		info->t_len--;
	if (info->prec > 0 && info->prec > info->t_len)
		res = ft_strjoin(res, fill_str(info->prec - info->t_len, '0'));
	//if (info->i_arg < 0)
		//info->t_len--;
	//if (is_extra(info->extra, MINUS) && info->width > 0 && info->width > info->t_len + (info->t_len - info->prec))
		//res = ft_strjoin(res, fill_str(info, info->t_len + (info->t_len - info->prec), ' '));
	return (res);
}*/

char *get_extra(int *extra, t_info *info)
{
	char *res;
	int base;
	int calc;

	calc = 0;
	base = get_base(info->flag);
	res = ft_strnew(0);
	info->t_len = 0;
	// TODO : besoin de convertir le nbre avant
	conv_length(info);
	if (base > 0)
		info->t_len += get_nbr_len(info->i_arg, base);
	//if (info->i_arg < 0)
		//info->width--;
	if (is_extra(extra, PLUS) && info->i_arg >= 0 && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO))
			calc += 1;
	if (((is_extra(extra, H_TAG) && info->flag == X) || (is_extra(extra, H_TAG) && info->flag == LX)))
			calc += 2;
	if ((info->flag == O || info->flag == LO) && info->prec == 0)
			calc+= 1;
	if (is_extra(extra, PLUS) && info->i_arg >= 0 && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO))
			calc += 1;
	if (is_extra(extra, SPACE) && info->i_arg > 0 && !is_extra(extra, PLUS) && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO))
			calc += 1;
	//if (info->prec == 0)
		//calc += 1;
	calc += info->t_len;
	if (!is_extra(info->extra, MINUS)) 
	{
		if (info->prec == 0 && !is_extra(extra, MINUS) && !is_extra(extra, ZERO))
		{
			printf("before calc 1 : %d\n", calc);

			calc = info->width - calc;
			printf("after calc 1 : %d\n", calc);
			//printf("width %d\n", info->width);
			if (calc > 0 && calc < info->width)
			{
				res = ft_strjoin(res, fill_str(calc, ' '));
			}
		}else if (info->prec > 0 && info->prec > calc)
		{
			if (info->prec == 1)
				calc = info->width - (info->prec + 1 + calc - get_nbr_len(info->i_arg, base));
			else
				calc = info->width - (info->prec + calc - get_nbr_len(info->i_arg, base));
			printf("calc 2 :  %d\n", calc);
			if (calc > 0 && calc < info->width)
				res = ft_strjoin(res, fill_str(calc, ' '));
		}else if (!is_extra(extra, ZERO))
		{
			calc = info->width - calc;
			if (calc > 0 && calc < info->width)
				res = ft_strjoin(res, fill_str(calc, ' '));
		}else if (is_extra(extra, ZERO) && info->prec == 0 && info->width == 0)
		{
			calc = info->width - calc;
			if (calc > 0 && calc < info->width)
			{
				res = ft_strjoin(res, fill_str(calc, ' '));
			}
		}else
		{
			calc -=info->t_len * 2;
		}
	}
	calc += info->t_len;
	//info->t_len += calc;
	if (info->i_arg < 0 && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO) && !(info->flag == U || info->flag == LU))
		res = ft_strjoin(res, "-");
	if (is_extra(extra, PERCENT))
		res = ft_strjoin(res, "%");
	if (is_extra(extra, PLUS) && info->i_arg >= 0 && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO))
	{
		res = ft_strjoin(res, "+");
		//info->t_len += 1;
	}
	if (is_extra(extra, SPACE) && info->i_arg > 0 && !is_extra(extra, PLUS) && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO))
	{
		res = ft_strjoin(res, " ");
		info->t_len += 1;
	}
	if (info->i_arg < 0 && !(info->flag == X || info->flag == LX) &&
			!(info->flag == O || info->flag == LO) && !(info->flag == U || info->flag == LU))
	{
		//res = ft_strjoin(res, "-");
		//info->t_len += 1;
	}
	if (((is_extra(extra, H_TAG) && info->flag == X) || (is_extra(extra, H_TAG) && info->flag == LX)))
	{
			if (info->i_arg != 0 && info->flag == X)
				res = ft_strjoin(res, "0x");
			if (info->i_arg != 0 && info->flag == LX)
				res = ft_strjoin(res, "0X");
			info->t_len += 2;
	}
	if (!is_extra(extra, MINUS) && is_extra(extra, H_TAG) && info->i_arg > 0 && (info->flag == O || info->flag == LO))
	{
		res = ft_strjoin(res, "0");
		calc-= 1;
	}
	printf("CCCC %d\n", calc);
	info->t_len = calc + get_nbr_len(info->i_arg, base);
	if (info->prec == 0 && !is_extra(extra, MINUS) && is_extra(extra, ZERO) && info->width > 0 && info->t_len < info->width)
	{
		//printf("CALLC : %d\n", info->t_len);

		//if (!((info->flag == X || info->flag == LX || info->flag == LO || info->flag == U || info->flag == LU
				//|| info->flag == O) && info->i_arg < 0))
		//if (info->width < info->t_len)
				
			res = ft_strjoin(res, get_zero(info));
	}
	//printf("CALC %d\n", calc);
	//if (info->i_arg < 0)
		//info->t_len--;
	if (info->prec > 0)
	{
		info->prec -= get_nbr_len(info->i_arg, base);
		if (info->prec > 0)
			res = ft_strjoin(res, fill_str(info->prec, '0'));
		calc += info->prec;
		info->t_len += info->prec;
	}
	conv_length(info);
	//printf("CALC %d\n", calc);
	if (info->flag > 0 && !(info->prec == 0 && info->i_arg == 0))
		res = ft_strjoin(res, conv_base(info, base, get_nbr_len(info->i_arg, base)));
	printf("CCCC %d\n", calc);
	if (is_extra(info->extra, MINUS) && info->width > 0 && calc <= info->width)
	{
		//if (
		//printf("CALC : %lld\n", info->width - (calc - get_nbr_len(info->i_arg, base)));
		//if (info->prec > 0)
			//calc--;
		res = ft_strjoin(res, fill_str(info->width - (calc - get_nbr_len(info->i_arg, base)), ' '));
	}
	return (res);
}	


char	*conv_int(int input, t_info *info)
{
	char *res;

	res = ft_strnew(0);
	info->i_arg = input;
	res = ft_strjoin(res, get_extra(info->extra, info));
	return (res);
	//TODO : gerer la width + la precision.
	//TODO : convertir + cast (length modifier).
}


char	*get_str(char *str, t_info *info)
{
	int begin;
	int end;
	int i;
	char *ret;

	begin = info->pos[START];
	end = info->pos[END];
	i = 0;
	if ((info->flag == 0) && end != 0)
	{
		if (!(ret = malloc(sizeof(char) * (end - begin) + 1)))
			return (NULL);
		while (str[begin] && begin <= end)
		{
			if (str[begin] == '%' && str[begin + 1] == '%')
			{
				ret[i++] = '%';
				begin++;
			}	
			else	
				ret[i++] = str[begin];
			begin++;	
		}
		ret[i] = '\0'; 
		return (ret);
	}
	return (NULL);	
}

char	*get_between_str(char *str, t_info *current, t_info *next)
{
	int start;
	int end;
	int i;
	char *ret;

	start = current->pos[END];
	end = next->pos[START];
	i = 0;
	if (end > 0 && start + 1 != end)
	{
		start++;
		if (!(ret = malloc(sizeof(char) * ((end - 1) - start) + 1)))
			return (NULL);
		while (str[start] && start <= end - 1)
		{
			ret[i++] = str[start];
			start++;
		}
		ret[i] = '\0';
		return (ret);
	}
	else if (end == 0)
	{
		if (!(ret = malloc(sizeof(char) * ft_strlen(str) - start)))
			return (NULL);
		if (current->flag && str[start + 1] == '\0' )
			start++;
		while (str[start])
		{
			ret[i++] = str[start];
			start++;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}


int	ft_printf(char *str, ...)
{
	int n;
	int i;
	char *type;
	long long int ret;
	t_info *info;
	char *tmp;
	va_list va;

	char *res;
	info = malloc(sizeof(t_info));
	init_list(info);
	res = ft_strnew(0);

	if ((n = count_flags(str, info)) == -1)
	{
		write(1, str, ft_strlen(str));
		return (ft_strlen(str));
	}
	va_start (va, str);
	i = 0;
	ret = 0;
	//print_struct(info);
	while (info)
	{
		if (i == 0 && info->pos[START] > 0)
			res = ft_strjoin(res, ft_strsub(str, 0, (str + info->pos[START]) - str));
		if ((tmp = get_str(str, info)) && is_empty(info->extra))
			res = ft_strjoin(res, tmp);
		if (!is_empty(info->extra) && info->flag == 0)
			res = ft_strjoin(res, get_extra(info->extra, info));
		if ((type = get_type(info->flag)))
		{
			if (ft_strcmp(type, "int") == 0)
			{
				ret = va_arg(va, long long int);
				info->i_arg = ret;
				conv_length(info);
				if (ret == 0)
				{
					res = ft_strjoin(res, get_extra(info->extra, info));
					res = ft_strjoin(res, "0");
				}
				else if ((tmp = conv_int(ret, info)))
					res = ft_strjoin(res, tmp);
			}else if (ft_strcmp(type, "string") == 0)
			{
				//res = ft_strjoin(res,
			}else if (ft_strcmp(type, "s_string") == 0)
			{
				
			}else if (ft_strcmp(type, "void") == 0)
			{

			}
		}
		if (info->next != NULL && (tmp = get_between_str(str, info, info->next)))
			res = ft_strjoin(res, tmp);
		info = info->next;
		i++;
	}
	va_end (va);
	write(1, res, ft_strlen(res));
	return (ft_strlen(res));
	//return (NULL);
}

int main(int ac, char **av)
{
	//char test[] = "coucou";
	long int test_d = 42;
	int test_o = 10;
	int test_k = -50;
	if (ac < 2)
		return (0);
	printf("\nMy printf\n");
	ft_printf(av[1], test_d, test_o, test_k);
	printf("\nREAL printf\n");
	printf(av[1], test_d, test_o, test_k);
}
