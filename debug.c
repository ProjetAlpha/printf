/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/13 15:59:29 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/14 17:46:14 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

void	print_struct(t_info *info)
{
	int i;

	while (info)
	{
		printf("WIDTH : %d | PREC : %d | LEN : %d | FLAG : %d | SKIP : %d\n\n",
				info->width, info->prec, info->length, info->flag,
				info->skip);
		i = 0;
		while (i < 8)
		{
			printf("EXTRA_%d : %d | ", i, info->extra[i]);
			i++;
		}
		printf("\n\n");
		printf("POS_BEGIN : %d | POS_END : %d\n\n", info->pos[0], info->pos[1]);
		info = info->next;
	}
}
