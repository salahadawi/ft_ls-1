/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:27:33 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/25 13:17:30 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
** Creates and adds a directory to the list of directories to be printed.
*/

void		add_directory(char *directory_name, t_list **first_directory,
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
** Reads the stat struct of a file and handles errors
*/

static void	read_stat(char *directory_name, t_params *params,
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

/*
** Whenever there is the parameter -R, recursively calls on read_directory
** to read all the subdirectories.
*/

static void	recursive_caller(t_params *params, t_list **first_directory)
{
	t_file		*temp_file;
	t_list		*temp_file_list;
	t_directory	*last_directory;
	char		*path;
	char		*tmp;

	tmp = NULL;
	last_directory = (t_directory*)ft_lstend(*first_directory)->content;
	if (ft_strequ(last_directory->name, "") || !last_directory->stat_info)
		return ;
	temp_file_list = last_directory->first_file;
	path = last_directory->name;
	while (temp_file_list)
	{
		temp_file = (t_file*)temp_file_list->content;
		if (temp_file->is_dir && !ft_strequ(temp_file->name, ".")
		&& !ft_strequ(temp_file->name, "./")
		&& !ft_strequ(temp_file->name, "..")
		&& !ft_strequ(temp_file->name, "../") && temp_file->stat_info)
		{
			tmp = ft_strjoin(path, temp_file->name);
			read_directory(tmp, params,
			first_directory, 0);
			free(tmp);
		}
		temp_file_list = temp_file_list->next;
	}
}

/*
** Opens the directory stream and adds that directory to the data
** structure. Continues to read the directory stream and saves all the
** files in the directory to the data structure
*/

static void	read_dirp(struct stat *dir_stat, char *directory_name,
			t_params *params, t_list **first_directory)
{
	DIR				*dirp;
	struct dirent	*dirent_buf;

	dirp = opendir(directory_name);
	if (dirp == NULL)
	{
		if (errno == 20)
		{
			if (handle_file_param(directory_name, first_directory, params))
			{
				free(dir_stat);
				return ;
			}
		}
		handle_dir_error(directory_name, first_directory);
		free(dir_stat);
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

/*
** Reads the stat struct of the directory and handles errors.
** Call a function to read the directory stream and recursive
** function, when needed
*/

void		read_directory(char *directory_name, t_params *params,
			t_list **first_directory, int caller)
{
	struct stat		*stat_buf;
	char			*new_name;

	new_name = NULL;
	stat_buf = (struct stat*)malloc(sizeof(struct stat));
	if (-1 == lstat(directory_name, stat_buf))
	{
		handle_dir_error(directory_name, first_directory);
		free(stat_buf);
		return ;
	}
	if (S_ISLNK(stat_buf->st_mode))
	{
		if (caller && params->l)
			handle_file_param(directory_name, first_directory, params);
		free(stat_buf);
		return ;
	}
	if (ft_strlast(directory_name) != '/')
		new_name = ft_str_char_join('/', directory_name);
	else
		new_name = ft_strdup(directory_name);
	read_dirp(stat_buf, new_name, params, first_directory);
	free(new_name);
	if (params->rr && !S_ISLNK(stat_buf->st_mode))
		recursive_caller(params, first_directory);
}
