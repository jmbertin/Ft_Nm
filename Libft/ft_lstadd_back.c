/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:44:07 by jbertin           #+#    #+#             */
/*   Updated: 2022/11/07 12:44:09 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp_list;

	if (new && alst)
	{
		if (!*alst)
		{
			*alst = new;
			return ;
		}
		tmp_list = ft_lstlast(*alst);
		tmp_list->next = new;
	}
}
