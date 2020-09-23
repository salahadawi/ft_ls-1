/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:25:02 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/23 18:39:25 by hlaineka         ###   ########.fr       */
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
	directory->error_message = NULL;
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

void	handle_file_error(char *file_name, t_params *params, t_list **first_directory)
{
	t_file	*new_file;
	char	*error_message;
	char	*error_str;

	error_message = ft_strjoin("ft_ls: ", file_name);
	error_message = ft_strjoin_frees1(error_message, ": ");
	error_str = ft_strdup(strerror(errno));
	error_message = ft_strjoin_frees1(error_message, error_str);
	new_file = (t_file*)malloc(sizeof(t_file));
	new_file->error_message = ft_strdup(error_message);
	new_file->name = ft_strdup(file_name);
	new_file->is_link = FALSE;
	new_file->stat_info = NULL;
	add_file(new_file, params, *first_directory);
	free(error_message);
	free(error_str);
}

void	handle_dir_error(char *directory_name, t_list **first_directory)
{
	char		*error_message;
	t_directory	*new_directory;
	char		*error_str;

	error_message = ft_strjoin("ft_ls: ", directory_name);
	error_message = ft_strjoin_frees1(error_message, ": ");
	error_str = ft_strdup(strerror(errno));
	error_message = ft_strjoin_frees1(error_message, error_str);
	new_directory = (t_directory*)malloc(sizeof(t_directory));
	initialize_directory(new_directory);
	new_directory->name = ft_strdup(directory_name);
	new_directory->stat_info = NULL;
	new_directory->error_message = ft_strdup(error_message);
	ft_lstnewtoend(new_directory, sizeof(t_directory), first_directory);
	free(error_message);
}