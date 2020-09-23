/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_addtoend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:11:32 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/21 19:06:24 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstaddtoend(void *content, size_t content_size, t_list **beginning)
{
	t_list		*newelem;
	t_list		*temp;

	newelem = ft_lstnew(content, content_size);
	temp = ft_lstend(*beginning);
	if (temp == NULL)
		*beginning = newelem;
	else
		ft_lstaddafter(temp, newelem);
	return ;
}