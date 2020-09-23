/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:27:33 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/23 18:22:04 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	add_new_dir(t_list **first_directory, t_file *new_file,
		t_params *params)
{
	t_directory	*temp_directory;

	temp_directory = (t_directory*)malloc(sizeof(t_directory));
	initialize_directory(temp_directory);
	temp_directory->name = ft_strdup("");
	if (params->l)
		check_field_width(new_file->stat_info, temp_directory);
	ft_lstnewtoend(new_file, sizeof(t_file), &temp_directory->first_file);
	ft_lstnewtoend(temp_directory, sizeof(t_directory), first_directory);
	free(temp_directory);
}

void	find_dir_add_file(t_list **first_directory, t_file *new_file,
		t_params *params)
{
	t_directory	*temp_directory;
	t_list		*temp_dir_list;

	temp_directory = NULL;
	temp_dir_list = *first_directory;
	while (temp_dir_list)
	{
		temp_directory = (t_directory*)temp_dir_list->content;
		if (ft_strequ(temp_directory->name, ""))
			break ;
		temp_dir_list = temp_dir_list->next;
	}
	if (temp_dir_list == NULL)
		add_new_dir(first_directory, new_file, params);
	else
	{
		if (params->l)
			check_field_width(new_file->stat_info, temp_directory);
		ft_lstnewtoend(new_file, sizeof(t_file), &temp_directory->first_file);
	}
}

int		handle_file_param(char *file_name, t_list **first_directory,
		t_params *params)
{
	struct stat	*stat_buf;
	t_file		*new_file;

	if (ft_strlast(file_name) == '/')
		file_name = ft_strsub_freestr(file_name, 0, ft_strlen(file_name) - 1);
	stat_buf = (struct stat*)malloc(sizeof(struct stat));
	if (-1 == lstat(file_name, stat_buf))
	{
		print_error(file_name);
		return (0);
	}
	new_file = (t_file*)malloc(sizeof(t_file));
	read_file(file_name, new_file, stat_buf);
	find_dir_add_file(first_directory, new_file, params);
	free(new_file);
	return (1);
}

void	read_stat(char *directory_name, t_params *params,
		t_list **first_directory, struct dirent *dirent_buf)
{
	struct stat		*stat_buf;
	char			*path_filename;

	stat_buf = (struct stat*)malloc(sizeof(struct stat));
	path_filename = ft_strjoin(directory_name, dirent_buf->d_name);
	if (-1 == lstat(path_filename, stat_buf))
	{
		handle_file_error(dirent_buf->d_name, params, first_directory);
		free(path_filename);
		free(stat_buf);
		return ;
	}
	add_to_list(dirent_buf, stat_buf, params, first_directory);
	free(path_filename);
}

void	read_dirp(struct stat *dir_stat, char *directory_name, t_params *params,
		t_list **first_directory)
{
	DIR				*dirp;
	struct dirent	*dirent_buf;

	dirp = opendir(directory_name);
	if (dirp == NULL)
	{
		if (errno == 20)
		{
			if (handle_file_param(directory_name, first_directory, params))
				return ;
		}
		handle_dir_error(directory_name, first_directory);
		return ;
	}
	add_directory(directory_name, first_directory, dir_stat);
	while (NULL != (dirent_buf = readdir(dirp)))
	{
		if (params->a || dirent_buf->d_name[0] != '.')
			read_stat(directory_name, params, first_directory, dirent_buf);
	}
	closedir(dirp);
}
