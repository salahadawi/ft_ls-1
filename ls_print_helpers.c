/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:45:59 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/23 12:37:55 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
** Checks the max field width for all the colums when printing with -l
*/

void	check_field_width(struct stat *info, t_directory *directory_info)
{
	if (ft_define_length(info->st_nlink) > directory_info->links_field)
		directory_info->links_field = ft_define_length(info->st_nlink);
	if ((int)ft_strlen(getowner(info)) > directory_info->owner_field)
		directory_info->owner_field = ft_strlen(getowner(info));
	if ((int)ft_strlen(getgroup(info)) > directory_info->group_field)
		directory_info->group_field = ft_strlen(getgroup(info));
	if (ft_define_length(info->st_size) > directory_info->size_field)
		directory_info->size_field = ft_define_length(info->st_size);
	directory_info->total = directory_info->total + info->st_blocks;
}

void	print_filelist(t_params *params, t_directory *directory)
{
	t_file	*temp_file;
	t_list	*temp_list;

	temp_list = directory->first_file;
	while (temp_list)
	{
		temp_file = (t_file*)temp_list->content;
		if (params->l)
			print_l(temp_file->name, temp_file->stat_info, directory,
			temp_file->is_link);
		//else if (!temp_file->stat_info)
		//	ft_printf("%s\n", temp_file->error_message);
		else
			ft_printf("%s\n", temp_file->name);
		temp_list = temp_list->next;
	}
}

void	print_error(char *directory_name)
{
	ft_printf("ft_ls: %s: ", directory_name);
	perror("");
}

char	*getowner(struct stat *buffer)
{
	struct passwd	*user_info;

	if ((user_info = getpwuid(buffer->st_uid)))
		return (user_info->pw_name);
	else
		return (ft_itoa(buffer->st_uid));
}

char	*getgroup(struct stat *buffer)
{
	struct group	*group_info;

	if ((group_info = getgrgid(buffer->st_gid)))
		return (group_info->gr_name);
	else
		return (ft_itoa(buffer->st_gid));
}
