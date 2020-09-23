/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewtoend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:29:01 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/21 20:03:43 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../../includes/ft_ls.h"

/*
** Adds given content to the end of the list.
*/

void	ft_lstnewtoend(const void *content, size_t content_size,
		t_list **beginning)
{
	t_list	*newelem;
	t_list	*temp;
	//t_directory	*temp_dir;

	//ft_printf("!%s!", ((t_directory*)content)->name);
	newelem = ft_lstnew(content, content_size);
	//temp_dir = (t_directory*)newelem->content;
	//ft_printf("!%s!", temp_dir->name);
	temp = ft_lstend(*beginning);
	if (temp == NULL)
		*beginning = newelem;
	else
		ft_lstaddafter(temp, newelem);
	return ;
}
