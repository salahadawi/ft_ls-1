/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 11:53:03 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/17 11:46:09 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	print_all(t_params *params, t_list *first_directory)
{
	t_directory		*temp_directory;
	t_list			*temp_dirlist;
	char			*directory_name;

	temp_dirlist = first_directory;
	while (temp_dirlist)
	{
		temp_directory = (t_directory*)temp_dirlist->content;
		if (!ft_strequ(temp_directory->name, ""))
			directory_name = ft_strsub(temp_directory->name, 0,
			ft_strlen(temp_directory->name) - 1);
		if ((params->rr || (params->multiple_folders > -1)) && temp_dirlist
		!= first_directory)
			ft_printf("%s:\n", directory_name);
		if (params->l && !ft_strequ(temp_directory->name, ""))
			ft_printf("total %d\n", temp_directory->total);
		print_filelist(params, temp_directory);
		if (params->rr || params->multiple_folders > 0)
			ft_printf("\n");
		temp_dirlist = temp_dirlist->next;
		params->multiple_folders--;
		if (!ft_strequ(temp_directory->name, ""))
			free(directory_name);
	}
}

void	sort_directories(t_list **first_directory, t_params *params)
{
	t_list		*temp_dir_list;
	t_directory	*temp_directory;

	if (params->t)
		ft_lst_merge_sort(first_directory, &sort_dir_time);
	else
		ft_lst_merge_sort(first_directory, &sort_dir_name);
	temp_dir_list = *first_directory;
	while (temp_dir_list)
	{
		temp_directory = (t_directory*)temp_dir_list->content;
		if (params->t)
			ft_lst_merge_sort(&temp_directory->first_file, &sort_file_time);
		else
			ft_lst_merge_sort(&temp_directory->first_file, &sort_file_name);
		temp_dir_list = temp_dir_list->next;
	}
	if (params->r)
		reverse_lists(first_directory);
}

/*
** Opens the dirent stream on the given directory name after parsing the
** name with "/" if necessary. Calls on a function to save the stat and
** name info on a while loop while reading. Calls on itself recursively
** when ever there is R flag given to read all subdirectories as well.
*/

void	read_directory(char *directory_name, t_params *params,
		t_list **first_directory)
{
	struct stat		*stat_buf;

	stat_buf = (struct stat*)malloc(sizeof(struct stat));
	if (-1 == lstat(directory_name, stat_buf))
	{
		print_error(directory_name);
		free(stat_buf);
		return ;
	}
	if (params->multiple_folders != -1 && params->l
	&& S_ISLNK(stat_buf->st_mode))
	{
		handle_file_param(directory_name, first_directory, params);
		free(stat_buf);
		return ;
	}
	if (ft_strlast(directory_name) != '/')
		directory_name = ft_str_char_join('/', directory_name);
	read_dirp(stat_buf, directory_name, params, first_directory);
	free(directory_name);
}

/*
** reads the given input string, and sets params structure values
** accordingly
*/

void	read_params(char *input, t_params *params)
{
	int		i;

	i = 1;
	while (input[i] != '\0')
	{
		if (input[i] == 'a')
			params->a = 1;
		else if (input[i] == 'l')
			params->l = 1;
		else if (input[i] == 'r')
			params->r = 1;
		else if (input[i] == 'R')
			params->rr = 1;
		else if (input[i] == 't')
			params->t = 1;
		else
		{
			ft_printf("ft_ls: illegal option -- %c\n", input[i]);
			print_usage();
			exit(0);
		}
		i++;
	}
}

/*
** Reads all the params that the program has been given, and adds them
** to relative data structures. Send the list to sorting and printing
** functions and then closes the program.
*/

int		main(int argc, char **argv)
{
	int			i;
	t_params	*params;
	t_list		*first_directory;

	params = (t_params*)malloc(sizeof(t_params));
	initialize_params(params);
	i = 1;
	while (i < argc && argv[i][0] == '-')
		read_params(argv[i++], params);
	first_directory = read_argv(argc, i, params, argv);
	sort_directories(&first_directory, params);
	print_all(params, first_directory);
	return (0);
}
