/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/13 16:10:02 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 22:00:14 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

void	check_digit(char **curr_str, char *str, t_info *info)
{
	check_end(str, curr_str, info);
	while (*str && ft_isdigit(*str) && info->stop == 0)
	{
		info->width = info->width * 10 + (*str - '0');	
		(*curr_str)++;
		str++;
	}
	check_end(str, curr_str, info);
}

void	check_prec(char **curr_str, char *str, t_info *info)
{
	check_end(str, curr_str, info);
	if (*str && *str == '.' && info->stop == 0)
	{
		info->is_prec = 1;
		str++;
		(*curr_str)++;
		while (*str && ft_isdigit(*str) && info->stop == 0)
		{
			info->prec = info->prec * 10 + (*str - '0');
			(*curr_str)++;
			str++;
		}	
	}
	check_end(str, curr_str, info);
}

void	set_all_flags(char **curr_str, char *str, t_info *info)
{
	if (info->stop == 0)
		set_len_modif(str, info);
	if ((info->length == HH || info->length == LL) && info->stop == 0)
	{
		(*curr_str)+=2;
		str+=2;
	}
	else if (info->length > 0 && info->stop == 0)
	{
		(*curr_str)++;
		str++;
	}
	if (info->stop == 0)
		set_flags(*str, info);
	if (info->flag != 0 && info->stop == 0)
	{
		set_flags(*str, info);
		(*curr_str)++;
		str++;
	}
}

t_info	*init_list(void)
{
	t_info *info;
	int i;
	i = 0;
	info = malloc(sizeof(t_info));
	info->width = 0;
	info->prec = 0;
	info->length = 0;
	info->u_arg = 0;
	info->flag = 0;
	info->skip = 0;
	info->stop = 0;
	info->c_len = 0;
	info->i_arg = 0;
	info->is_prec = 0;
	while (i <= 6)
		info->extra[i++] = 0;
	info->pos[0] = 0;
	info->pos[1] = 0;
	info->next = NULL;
	return (info);
}

void	free_lst(t_info *info)
{
	while (info)
	{
		free(info);
		info = info->next;
	}
}

int		parse_str(char *str, t_info *info, va_list args)
{
	char *tmp;
	int c_len;

	c_len = 0;
	while (*str)
	{
		while (*str && *str != '%')
		{
			c_len++;
			write(1, str++, 1);
		}
		if (*str == '%')
		{
			info->stop = 0;
			str++;
			check_extra(&str, &(*str), info);
			check_digit(&str, &(*str), info);
			check_prec(&str, &*(str), info);
			set_all_flags(&str, &*(str), info);
			if ((tmp = conv_flags(info, args, &str, str)))
			{
				if (info->flag == C)
				{
					if (info->t_len == 1)
					{
						write(1, tmp, ft_strlen(tmp) + info->t_len);
						c_len+= 1;
					}
					else if (info->t_len == -1)
					{
						write(1, "\0", 1);
						c_len+=1;
						write(1, tmp, ft_strlen(tmp));
					}else
						write(1, tmp, ft_strlen(tmp));

				}
				else
					write(1, tmp, ft_strlen(tmp));
				c_len+= ft_strlen(tmp);
				free(tmp);
			}
			if (info->c_len > 0)
				c_len += info->c_len;
			info->next = init_list();
			info = info->next;
		}
	}
	free_lst(info);
	return (c_len);
}

int		ft_printf(const char *str, ...)
{
	t_info *info;

	info = init_list();
	va_list va;
	va_start(va, str);
	return (parse_str((char*)str, info, va));
	//va_end(va);
	//return (0);
}

/*int main(void)
{
	//char test_1[] = "%% %%% %%% % %";
	//char test_2[] = "\nME : |% 20.12ld et % 05D% 4.8hi !|\n";
	char test_3[] = "|%3.1d| : 3.1\n\n";

	int dtr;
	dtr = 7;
	//printf("\nRE : |% 20.12ld et % 05D% 4.8hi !|\n", 0x11ffaa147, 24, (short)-2345);
	//printf("\n PRINTF : |%1.4s| et |%-6.8s| et |%4.2s| \n", str, str, str);
	ft_printf(test_3, dtr);
	printf("\n drintf : |%+-20.d|\n", 0);
	printf("|%d|\n", dtr);
	ft_printf("|%d|\n\n", dtr);
	printf("|%1d| : 1\n", dtr);
	ft_printf("|%1d| : 1\n\n", dtr);
	printf("|%2d| : 2\n", dtr);
	ft_printf("|%2d| : 2\n\n", dtr);
	printf("|%3d| : 3\n", dtr);
	ft_printf("|%3d| : 3\n\n", dtr);
	printf("|%.0d| : .0\n", dtr);
	ft_printf("|%.0d| : .0\n\n", dtr);
	printf("|%.1d| : .1\n", dtr);
	ft_printf("|%.1d| : .1\n\n", dtr);
	printf("|%.2d| : .2\n", dtr);
	ft_printf("|%.2d| : .2\n\n", dtr);
	printf("|%.3d| : .3\n", dtr);
	ft_printf("|%.3d| : .3\n\n", dtr);
	printf("|%1.0d| : 1.0\n", dtr);
	ft_printf("|%1.0d| : 1.0\n\n", dtr);
	printf("|%1.1d| : 1.1\n", dtr);
	ft_printf("|%1.1d| : 1.1\n\n", dtr);
	printf("|%1.2d| : 1.2\n", dtr);
	ft_printf("|%1.2d| : 1.2\n\n", dtr);
	printf("|%1.3d| : 1.3\n", dtr);
	ft_printf("|%1.3d| : 1.3\n\n", dtr);
	printf("|%1.4d| : 1.4\n", dtr);
	ft_printf("|%1.4d| : 1.4\n\n", dtr);
	printf("|%2.0d| : 2.0\n", dtr);
	ft_printf("|%2.0d| : 2.0\n\n", dtr);
	printf("|%2.1d| : 2.1\n", dtr);
	ft_printf("|%2.1d| : 2.1\n\n", dtr);
	printf("|%2.2d| : 2.2\n", dtr);
	ft_printf("|%2.2d| : 2.2\n\n", dtr);
	printf("|%2.3d| : 2.3\n", dtr);
	ft_printf("|%2.3d| : 2.3\n\n", dtr);
	printf("|%2.4d| : 2.4\n", dtr);
	ft_printf("|%2.4d| : 2.4\n\n", dtr);
	printf("|%3.0d| : 3.0\n", dtr);
	ft_printf("|%3.0d| : 3.0\n\n", dtr);
	printf("|%3.1d| : 3.1\n", dtr);
	ft_printf("|%3.1d| : 3.1\n\n", dtr);
	printf("|%3.2d| : 3.2\n", dtr);
	ft_printf("|%3.2d| : 3.2\n\n", dtr);
	printf("|%3.3d| : 3.3\n", dtr);
	ft_printf("|%3.3d| : 3.3\n\n", dtr);
	printf("|%3.4d| : 3.4\n", dtr);
	ft_printf("|%3.4d| : 3.4\n\n", dtr);
	printf("|%4.0d| : 4.0\n", dtr);
	ft_printf("|%4.0d| : 4.0\n\n", dtr);
	printf("|%4.1d| : 4.1\n", dtr);
	ft_printf("|%4.1d| : 4.1\n\n", dtr);
	printf("|%4.2d| : 4.2\n", dtr);
	ft_printf("|%4.2d| : 4.2\n\n", dtr);
	printf("|%4.3d| : 4.3\n", dtr);
	ft_printf("|%4.3d| : 4.3\n\n", dtr);
	printf("|%4.4d| : 4.4\n", dtr);
	ft_printf("|%4.4d| : 4.4\n\n", dtr);

	printf("\n__0 FLAGS__\n\n");

	printf("|%0.0d| : .0\n", dtr);
	ft_printf("|%0.0d| : .0\n\n", dtr);
	printf("|%0.1d| : .1\n", dtr);
	ft_printf("|%0.1d| : .1\n\n", dtr);
	printf("|%0.2d| : .2\n", dtr);
	ft_printf("|%0.2d| : .2\n\n", dtr);
	printf("|%0.3d| : .3\n", dtr);
	ft_printf("|%0.3d| : .3\n\n", dtr);
	printf("|%01.0d| : 1.0\n", dtr);
	ft_printf("|%01.0d| : 1.0\n\n", dtr);
	printf("|%01.1d| : 1.1\n", dtr);
	ft_printf("|%01.1d| : 1.1\n\n", dtr);
	printf("|%01.2d| : 1.2\n", dtr);
	ft_printf("|%01.2d| : 1.2\n\n", dtr);
	printf("|%01.3d| : 1.3\n", dtr);
	ft_printf("|%01.3d| : 1.3\n\n", dtr);
	printf("|%01.4d| : 1.4\n", dtr);
	ft_printf("|%01.4d| : 1.4\n\n", dtr);
	printf("|%02.0d| : 2.0\n", dtr);
	ft_printf("|%02.0d| : 2.0\n\n", dtr);
	printf("|%02.1d| : 2.1\n", dtr);
	ft_printf("|%02.1d| : 2.1\n\n", dtr);
	printf("|%02.2d| : 2.2\n", dtr);
	ft_printf("|%02.2d| : 2.2\n\n", dtr);
	printf("|%02.3d| : 2.3\n", dtr);
	ft_printf("|%02.3d| : 2.3\n\n", dtr);
	printf("|%02.4d| : 2.4\n", dtr);
	ft_printf("|%02.4d| : 2.4\n\n", dtr);
	printf("|%03.0d| : 3.0\n", dtr);
	ft_printf("|%03.0d| : 3.0\n\n", dtr);
	printf("|%03.1d| : 3.1\n", dtr);
	ft_printf("|%03.1d| : 3.1\n\n", dtr);
	printf("|%03.2d| : 3.2\n", dtr);
	ft_printf("|%03.2d| : 3.2\n\n", dtr);
	printf("|%03.3d| : 3.3\n", dtr);
	ft_printf("|%03.3d| : 3.3\n\n", dtr);
	printf("|%03.4d| : 3.4\n", dtr);
	ft_printf("|%03.4d| : 3.4\n\n", dtr);

	printf("|%#15.4d| : 15.4\n", dtr);
	ft_printf("|%#15.4d| : 15.4\n\n", dtr);

	printf("|%02d| : 02\n", dtr);
	ft_printf("|%02d| : 02\n\n", dtr);

	printf("|%03d| : 02\n", dtr);
	ft_printf("|%03d| : 02\n\n", dtr);

	printf("|%#05d| : #05\n", dtr);
	ft_printf("|%#05d| : #05\n\n", dtr);

	printf("|%#014d| : #014\n", dtr);
	ft_printf("|%#014d| : #014\n\n", dtr);

	printf("|%#-+10d| : -+8\n", dtr);
	ft_printf("|%#-+10d| : -+8\n\n", dtr);

	printf("|%#- 10d| : -\' \'9\n", dtr);
	ft_printf("|%#- 10d| : -\' \'9\n\n", dtr);

	printf("|%#-10d| : -10\n", dtr);
	ft_printf("|%#-10d| : -10\n\n", dtr);

	printf("|%#+0.d, %.5d| : 3. .5\n", 0, 0);
	ft_printf("|%#+0.d, %.5d| : 3. .5\n\n", 0, 0);

	printf("|%#08d| : 8 \n", 7);
	ft_printf("|%#08d| : 8\n\n", 7);

	printf("|%04d|\n", 71);
	ft_printf("|%04d|\n\n", 71);
	//printf("|%c| : noflag\n", str);
	//ft_printf("|%c| : noflag\n\n", str);

	printf("|%1d| : 1\n", dtr);
	ft_printf("|%1d|: 1\n\n", dtr);

	//printf("|%5c| : 5\n", str);
	//ft_printf("|%5c|: 5\n\n", str);

	printf("|%15d| : 15\n", dtr);
	ft_printf("|%15d| : 15\n\n", dtr);

	printf("|%-15d| : -15.15\n", dtr);
	ft_printf("|%-15d| : -15.15\n\n", dtr);
	//parse_str(test_2, info);
}*/
