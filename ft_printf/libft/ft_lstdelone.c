/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstdelone.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 16:23:06 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 18:51:49 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list *delete;

	delete = *alst;
	if (alst)
	{
		del(delete->content, ft_strlen((char *)delete->content));
		free(*alst);
		*alst = NULL;
	}
}
