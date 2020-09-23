/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:15:51 by hlaineka          #+#    #+#             */
/*   Updated: 2020/05/19 09:16:21 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
** Creates a new string where it combines the two strings given as parameters
*/

char	*ft_strjoin(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	w;
	char			*returnable;

	if (s1 && s2)
	{
		if (NULL != (returnable = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		{
			i = 0;
			w = 0;
			while (s1[i] != '\0')
			{
				returnable[i] = s1[i];
				i++;
			}
			while (s2[w] != '\0')
				returnable[i++] = s2[w++];
			returnable[i] = '\0';
			return (returnable);
		}
	}
	return (NULL);
}
