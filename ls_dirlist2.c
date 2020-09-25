/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirlist2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 10:23:24 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/25 11:57:39 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
** Creates a new file to be added to the list of files on a directory.
** Calls a function to do the adding.
*/

void		add_to_list(struct dirent *dirent_buf, struct stat *stat_buf,
			t_params *params, t_list **first_directory)
{
	t_file			*new_file;
	char			*path_filename;
	char			*link_name;
	t_directory		*temp_dir;

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

/*
** Checks if the given file is a link, and if so, changes the name accordingly
*/

void		read_link(char *file_name, t_file *new_file, struct stat *stat_buf)
{
	char	*link_name;
	int		i;

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

/*
** helper function to handle_file_param
*/

static void	add_new_dir(t_list **first_directory, t_file *new_file,
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

/*
** Helper function to handle_file_param
*/

void		find_dir_add_file(t_list **first_directory, t_file *new_file,
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

/*
** Handles a file parameter and adds it to the data structure. The stat
** struct of t_directory structure where file params are saved is set
** to NULL as well as the name of the directory to "" (empty string).
*/

int			handle_file_param(char *file_name, t_list **first_directory,
			t_params *params)
{
	struct stat	*stat_buf;
	t_file		*new_file;

	if (ft_strlast(file_name) == '/')
		file_name = ft_str_realloc(file_name, 0, ft_strlen(file_name) - 1);
	stat_buf = (struct stat*)malloc(sizeof(struct stat));
	if (-1 == lstat(file_name, stat_buf))
	{
		print_error(file_name);
		free(stat_buf);
		return (0);
	}
	new_file = (t_file*)malloc(sizeof(t_file));
	read_link(file_name, new_file, stat_buf);
	find_dir_add_file(first_directory, new_file, params);
	free(new_file);
	return (1);
}
