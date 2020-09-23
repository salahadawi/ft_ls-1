/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirlist2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 10:23:24 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/23 16:31:03 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
** Adds a file to the last directory of the list.
*/

void	add_file(t_file *new_file, t_params *params, t_list *first_directory)
{
	t_list		*directory_elem;
	t_directory	*temp_directory;
	struct stat	*temp_stat;

	ft_printf("add_file");
	directory_elem = ft_lstend(first_directory);
	temp_directory = (t_directory*)directory_elem->content;
	temp_stat = (struct stat*)new_file->stat_info;
	if (params->l && temp_stat)
		check_field_width(temp_stat, temp_directory);
	ft_lstnewtoend(new_file, sizeof(t_file), &(temp_directory->first_file));
}

/*
** Creates and dds a directory to the list of directories to be printed.
*/

void	add_directory(char *directory_name, t_list **first_directory,
		struct stat *stat_buf)
{
	t_directory	*new_directory;

	ft_printf("add_directory");
	new_directory = (t_directory*)malloc(sizeof(t_directory));
	initialize_directory(new_directory);
	new_directory->name = ft_strdup(directory_name);
	new_directory->stat_info = stat_buf;
	ft_lstnewtoend(new_directory, sizeof(t_directory), first_directory);
	free(new_directory);
}

/*
** Creates a new file to be added to the list of files on a directory.
** Calls a function to do the adding.
*/

void	add_to_list(struct dirent *dirent_buf, struct stat *stat_buf, t_params *params,
		t_list **first_directory)
{
	t_file			*new_file;
	char			*path_filename;
	char			*link_name;
	t_directory		*temp_dir;

	ft_printf("add_to_list");
	link_name = ft_strnew(2000);
	new_file = (t_file*)malloc(sizeof(t_file));
	new_file->stat_info = stat_buf;
	temp_dir = (t_directory*)(ft_lstend(*first_directory))->content;
	path_filename = ft_strjoin(temp_dir->name, dirent_buf->d_name);
	if (readlink(path_filename, link_name, 2000) != -1)
	{
		new_file->name = ft_strjoin3(dirent_buf->d_name, " -> ", link_name);
		new_file->is_link = 1;
	}
	else
	{
		new_file->name = ft_strdup(dirent_buf->d_name);
		new_file->is_link = 0;
	}
	new_file->is_dir = (dirent_buf->d_type == DT_DIR) ? 1 : 0;
	add_file(new_file, params, *first_directory);
	free(path_filename);
	free(link_name);
	free(new_file);
}

void	read_file(char *file_name, t_file *new_file, struct stat *stat_buf)
{
	char	*link_name;
	int		i;

	ft_printf("read_file");
	link_name = ft_strnew(2000);
	if ((i = readlink(file_name, link_name, 2000)) != -1)
	{
		link_name[i] = '\0';
		new_file->name = ft_strjoin3(file_name, " -> ", link_name);
		new_file->is_link = 1;
	}
	else
	{
		new_file->name = ft_strdup(file_name);
		new_file->is_link = 0;
	}
	new_file->stat_info = stat_buf;
	free(link_name);
}

void	read_directory(char *directory_name, t_params *params,
		t_list **first_directory, int caller)
{
	struct stat		*stat_buf;
	//char			*link_name;
	//int				i;

	ft_printf("read_directory !%s!\n", directory_name);
	stat_buf = (struct stat*)malloc(sizeof(struct stat));
	if (-1 == lstat(directory_name, stat_buf))
	{
		ft_printf("!!dir error!!");
		handle_dir_error(directory_name, first_directory);
		//free(stat_buf);
		return ;
	}
	if (caller && params->l && S_ISLNK(stat_buf->st_mode))
	{
		ft_printf("!!file param!!");
		handle_file_param(directory_name, first_directory, params);
		//free(stat_buf);
		return ;
	}
	if (S_ISLNK(stat_buf->st_mode))
	{	
		ft_printf("!!is link!!");
		free(stat_buf);
		return;
		//link_name = ft_strnew(2000);
		//i = readlink(directory_name, link_name, 2000);
		//link_name[i] = '\0';
		//free(directory_name);
		//directory_name = ft_strdup(link_name);
		//free(link_name);
	}
	if (ft_strlast(directory_name) != '/')
		directory_name = ft_str_char_join('/', directory_name);
	read_dirp(stat_buf, directory_name, params, first_directory);
	//free(directory_name);
	if (params->rr && !S_ISLNK(stat_buf->st_mode))
		recursive_caller(params, first_directory);
}

void	recursive_caller(t_params *params, t_list **first_directory)
{
	t_file		*temp_file;
	t_list		*temp_file_list;
	t_directory	*last_directory;
	char		*path;

	ft_printf("recursive_caller");
	last_directory = (t_directory*)ft_lstend(*first_directory)->content;
	if (ft_strequ(last_directory->name, "") || !last_directory->stat_info)
		return;
	temp_file_list = last_directory->first_file;
	path = last_directory->name;
	while (temp_file_list)
	{
		temp_file = (t_file*)temp_file_list->content;
		if (temp_file->is_dir && !ft_strequ(temp_file->name, ".")
		&& !ft_strequ(temp_file->name, "./") && !ft_strequ(temp_file->name, "..")
		&& !ft_strequ(temp_file->name, "../") && temp_file->stat_info)
			read_directory(ft_strjoin(path, temp_file->name), params,
			first_directory, 0);
		temp_file_list = temp_file_list->next;
	}
}
