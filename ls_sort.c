/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:16:25 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/16 20:00:45 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		sort_dir_name(t_list *a, t_list *b)
{
	t_directory	*a_dir;
	t_directory	*b_dir;

	a_dir = (t_directory*)a->content;
	b_dir = (t_directory*)b->content;
	if (ft_strcmp(a_dir->name, b_dir->name) < 0)
		return (TRUE);
	return (FALSE);
}

int		sort_file_name(t_list *a, t_list *b)
{
	t_file	*a_file;
	t_file	*b_file;

	a_file = (t_file*)a->content;
	b_file = (t_file*)b->content;
	if (ft_strcmp(a_file->name, b_file->name) < 0)
		return (TRUE);
	return (FALSE);
}

int		sort_dir_time(t_list *a, t_list *b)
{
	t_directory	*a_dir;
	t_directory	*b_dir;

	a_dir = (t_directory*)a->content;
	b_dir = (t_directory*)b->content;
	if (!ft_strequ(a_dir->name, ""))
		return (FALSE);
	if (!ft_strequ(b_dir->name, ""))
		return (TRUE);
	if (a_dir->stat_info->st_mtime > b_dir->stat_info->st_mtime)
		return (TRUE);
	if (a_dir->stat_info->st_mtime == b_dir->stat_info->st_mtime)
	{
		if (a_dir->stat_info->st_mtimespec.tv_nsec
		> b_dir->stat_info->st_mtimespec.tv_nsec)
			return (TRUE);
		if (a_dir->stat_info->st_mtimespec.tv_nsec
		== b_dir->stat_info->st_mtimespec.tv_nsec
		&& ft_strcmp(a_dir->name, b_dir->name) < 0)
			return (TRUE);
	}
	return (FALSE);
}

int		sort_file_time(t_list *a, t_list *b)
{
	t_file	*a_file;
	t_file	*b_file;

	a_file = (t_file*)a->content;
	b_file = (t_file*)b->content;
	if (a_file->stat_info->st_mtime > b_file->stat_info->st_mtime)
		return (TRUE);
	if (a_file->stat_info->st_mtime == b_file->stat_info->st_mtime)
	{
		if (a_file->stat_info->st_mtimespec.tv_nsec
		> b_file->stat_info->st_mtimespec.tv_nsec)
			return (TRUE);
		if (a_file->stat_info->st_mtimespec.tv_nsec
		== b_file->stat_info->st_mtimespec.tv_nsec
		&& ft_strcmp(a_file->name, b_file->name) < 0)
			return (TRUE);
	}
	return (FALSE);
}

void	reverse_lists(t_list **first_directory)
{
	t_list		*temp_dir_list;
	t_directory	*temp_directory;

	if (!*first_directory)
		return ;
	temp_dir_list = *first_directory;
	temp_directory = (t_directory*)temp_dir_list->content;
	if (ft_strequ(temp_directory->name, "") && temp_dir_list->next)
		temp_dir_list->next = ft_lst_reverse(&temp_dir_list->next);
	else
		ft_lst_reverse(first_directory);
	temp_dir_list = *first_directory;
	while (temp_dir_list)
	{
		temp_directory = (t_directory*)temp_dir_list->content;
		ft_lst_reverse(&temp_directory->first_file);
		temp_dir_list = temp_dir_list->next;
	}
}
