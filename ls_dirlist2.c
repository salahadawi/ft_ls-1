/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirlist2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 10:23:24 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/17 11:45:42 by hlaineka         ###   ########.fr       */
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

	directory_elem = ft_lstend(first_directory);
	temp_directory = (t_directory*)directory_elem->content;
	temp_stat = (struct stat*)new_file->stat_info;
	if (params->l)
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

void	add_to_list(char *name, struct stat *stat_buf, t_params *params,
		t_list **first_directory)
{
	t_file			*new_file;
	char			*path_filename;
	char			*link_name;
	t_directory		*temp_dir;

	link_name = ft_strnew(2000);
	new_file = (t_file*)malloc(sizeof(t_file));
	new_file->stat_info = stat_buf;
	temp_dir = (t_directory*)(ft_lstend(*first_directory))->content;
	path_filename = ft_strjoin(temp_dir->name, name);
	if (readlink(path_filename, link_name, 2000) != -1)
	{
		new_file->name = ft_strjoin3(name, " -> ", link_name);
		new_file->is_link = 1;
	}
	else
	{
		new_file->name = ft_strdup(name);
		new_file->is_link = 0;
	}
	add_file(new_file, params, *first_directory);
	free(path_filename);
	free(link_name);
	free(new_file);
}

t_list	*read_argv(int argc, int i, t_params *params, char **argv)
{
	char		*directory_name;
	t_list		*first_directory;

	first_directory = NULL;
	if (i == argc)
	{
		directory_name = ft_strdup(".");
		read_directory(directory_name, params, &first_directory);
		free(directory_name);
	}
	while (argv[i])
	{
		params->multiple_folders++;
		directory_name = ft_strdup(argv[i++]);
		read_directory(directory_name, params, &first_directory);
		free(directory_name);
	}
	return (first_directory);
}

void	read_file(char *file_name, t_file *new_file, struct stat *stat_buf)
{
	char	*link_name;

	link_name = ft_strnew(2000);
	if (readlink(file_name, link_name, 2000) != -1)
	{
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
