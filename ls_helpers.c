/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:25:02 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/16 17:41:57 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	initialize_directory(t_directory *directory)
{
	directory->total = 0;
	directory->links_field = 0;
	directory->owner_field = 0;
	directory->group_field = 0;
	directory->size_field = 0;
	directory->first_file = NULL;
	directory->stat_info = NULL;
}

void	print_error_and_exit(char *directory_name)
{
	ft_printf("ft_ls: %s: ", directory_name);
	perror("");
	exit(0);
}

void	print_usage(void)
{
	ft_printf("usage: ft_ls [-alrRt] [file ...]\n");
}

/*
** Initializes the params structure
*/

void	initialize_params(t_params *params)
{
	params->a = 0;
	params->l = 0;
	params->r = 0;
	params->rr = 0;
	params->t = 0;
	params->file_param = NULL;
	params->multiple_folders = -1;
	return ;
}

char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*returnable;

	returnable = (char*)malloc(sizeof(char) * (ft_strlen(str1)
				+ ft_strlen(str2) + ft_strlen(str3)));
	returnable = ft_strjoin(str1, str2);
	returnable = ft_strjoin_frees1(returnable, str3);
	return (returnable);
}
