/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 16:44:56 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 19:34:30 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *list;

	if (alst)
	{
		list = *alst;
		while (list)
		{
			del(list->content, ft_strlen((char*)list->content));
			free(list);
			list = list->next;
		}
		*alst = NULL;
	}
}
