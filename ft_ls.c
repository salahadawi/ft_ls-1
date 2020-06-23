/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 10:42:34 by hlaineka          #+#    #+#             */
/*   Updated: 2020/06/22 12:28:26 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	*getowner(struct stat *buffer)
{
	struct passwd	*user_info;

	if ((user_info = getpwuid(buffer->st_uid)))
		return (ft_strdup(user_info->pw_name));
	else
		return(ft_strdup(""));
}

char	*getgroup(struct stat *buffer)
{
	struct group	*group_info;

	if ((group_info = getgrgid(buffer->st_gid)))
		return (group_info->gr_name);
	else
		return(ft_strdup(""));	
}
void		check_field_width(struct stat *info, t_params *params)
{
	if (ft_define_length(info->st_nlink) > params->links_field)
		params->links_field = ft_define_length(info->st_nlink);
	if ((int)ft_strlen(getowner(info)) > params->owner_field)
		params->owner_field = ft_strlen(getowner(info));
	if ((int)ft_strlen(getgroup(info)) > params->group_field)
		params->group_field = ft_strlen(getgroup(info));
	if (ft_define_length(info->st_size) > params->size_field)
		params->size_field = ft_define_length(info->st_size);
	params->total = params->total + info->st_blocks;
}

struct stat		*read_file_stat(char *name)
{	
	struct stat		*returnable;

	returnable = (struct stat*)malloc(sizeof(struct stat));
	returnable = NULL;
	if (-1 == stat(name, returnable))
	{
		ft_printf("ft_ls: %s: ", name);
		perror("");
		exit(0);
	}
	return(returnable);
}

void	read_file_info(char *name, t_params *params, t_list **first_printable)
{	
	t_data			*file_data;
	char			*temp;
	
	file_data = (t_data*)malloc(sizeof(t_data));
	file_data->info = (struct stat*)malloc(sizeof(struct stat));
	file_data->name = ft_strdup(name);
	temp = ft_strjoin(params->full_directory, file_data->name);
	file_data->info = read_file_stat(temp);
	free(temp);
	check_field_width(file_data->info, params);
	ft_lstnewtoend(file_data, sizeof(t_data), first_printable);
}

void		read_directory(DIR *dirp, t_params *params, t_list **first_printable, t_list **first_directory)
{
	struct dirent 	*dirent_buf;

	while ((NULL != (dirent_buf = readdir(dirp))))
	{
		if (params->a || dirent_buf->d_name[0] != '.')
		{
			read_file_info(dirent_buf->d_name, params, first_printable);
			if (dirent_buf->d_type == DT_DIR && params->rr && !ft_strequ(dirent_buf->d_name, ".") && !ft_strequ(dirent_buf->d_name, "./") && !ft_strequ(dirent_buf->d_name, "..") && !ft_strequ(dirent_buf->d_name, "../"))
			{
				ft_lstnewtoend(dirent_buf->d_name, ft_strlen(dirent_buf->d_name) + 1, first_directory);
			}
		}
	}
	return ;
}

char	*get_modes(struct stat *buffer)
{
	char	*returnable;

	returnable = ft_strset('-', 10);
	if (S_ISDIR(buffer->st_mode))
		returnable[0] = 'd';
	if (buffer->st_mode & S_IRUSR)
		returnable[1] = 'r';
	if (buffer->st_mode & S_IWUSR)
		returnable[2] = 'w';
	if (buffer->st_mode & S_IXUSR)
		returnable[3] = 'x';
	if (buffer->st_mode & S_IRGRP)
		returnable[4] = 'r';
	if (buffer->st_mode & S_IWGRP)
		returnable[5] = 'w';
	if (buffer->st_mode & S_IXGRP)
		returnable[6] = 'x';
	if (buffer->st_mode & S_IROTH)
		returnable[7] = 'r';
	if (buffer->st_mode & S_IWOTH)
		returnable[8] = 'w';
	if (buffer->st_mode & S_IXOTH)
		returnable[9] = 'x';
	return(returnable);
}

char	*gettime(struct stat *buffer)
{
	time_t	timestamp;
	char	*returnable;
	int		i;
	int		w;
	int		k;

	i = 0;
	w = 0;
	k = 0;
	timestamp = buffer->st_mtime;
	returnable = ft_strdup(ctime(&timestamp));
	returnable = ft_str_realloc(returnable, 4, 12);
	return(returnable);

}

void	print_l(char *file_name, struct stat *buffer, t_params *params)
{
	char	*temp;

	temp = get_modes(buffer);
	ft_printf("%s  ", temp);
	free(temp);
	ft_printf("%*d ", params->links_field, buffer->st_nlink);
	ft_printf("%*s  ", params->owner_field, getowner(buffer));
	ft_printf("%*s  ", params->group_field, getgroup(buffer));
	ft_printf("%*d ", params->size_field, buffer->st_size);
	temp = gettime(buffer);
	ft_printf("%s ", temp);
	free (temp);
	ft_printf("%s\n", file_name);
	//free (file_name);
	return ;
}

void	print_output(t_list *first_printable, char *directory_name, t_params *params)
{
	t_data			*temp;
	t_list			*temp_list;

	if ((params->rr && !(ft_strequ(directory_name, "./"))) || params->multiple_params)
		ft_printf("%s:\n", directory_name);
	if (params->l)
		ft_printf("total %d\n", params->total);
	while (first_printable)
	{
		temp = (t_data*)first_printable->content;
		if (params->l)
			print_l(temp->name, temp->info, params);
		else
			ft_printf("%s\n", temp->name);
		//first_printable = first_printable->next;
		temp_list = first_printable->next;
		free(temp->name);
		free(temp->info);
		free(first_printable->content);
		free(first_printable);
		first_printable = temp_list;
	}
	if (params->rr || params->multiple_params)
		ft_printf("\n");
}

int		sort_content_string(t_list *a, t_list *b)
{
	if (ft_strcmp((char*)a->content, (char*)b->content) < 0)
		return TRUE;
	return FALSE;
}

void	sort_directory(t_list **first_directory)
{
	ft_lst_merge_sort(first_directory, &sort_content_string);
}

int		sort_stat_name(t_list *a, t_list *b)
{
	t_data	*a_data;
	t_data	*b_data;

	a_data = (t_data*)a->content;
	b_data = (t_data*)b->content;
	if (ft_strcmp(a_data->name, b_data->name) < 0)
		return TRUE;
	return FALSE;
}

int		sort_stat_time(t_list *a, t_list *b)
{
	t_data	*a_data;
	t_data	*b_data;

	a_data = (t_data*)a->content;
	b_data = (t_data*)b->content;
	if (a_data->info->st_mtime > b_data->info->st_mtime)
		return TRUE;
	if (a_data->info->st_mtime == b_data->info->st_mtime)
	{
		if (ft_strcmp(a_data->name, b_data->name) < 0)
			return TRUE;
	}
	return FALSE;
}

void	sort_files(t_list **first_printable, t_params *params)
{
	if (params->t)
		ft_lst_merge_sort(first_printable, &sort_stat_time);
	else
		ft_lst_merge_sort(first_printable, &sort_stat_name);
}

int		print_folder(char *directory_name, t_params *params, t_list *first_directory)
{
	t_list			*first_printable;
	DIR				*dirp;
	t_list			*temp;
	
	params->total = 0;
	dirp = opendir(directory_name);
	if (dirp == NULL && params->multiple_params)
	{
		read_file_info(directory_name, params, &first_printable);
		if (first_directory)
			first_directory = first_directory->next;
	}
	else if (dirp == NULL)
	{
		ft_printf("ft_ls: %s: ", directory_name);
		perror( "" );
		exit(0);
	}
	else
	{
		first_printable = NULL;
		if (ft_strlast(directory_name) != '/')
			directory_name = ft_str_char_join('/', directory_name);
		params->full_directory = ft_strdup(directory_name);
		read_directory(dirp, params, &first_printable, &first_directory);
		sort_directory(&first_directory);
		sort_files(&first_printable, params);
	}
	print_output(first_printable, directory_name, params);
	while (first_directory)
	{
		if (params->rr)
			print_folder(ft_strjoin(directory_name, (char*)first_directory->content), params, first_directory->next);
		else
			print_folder(ft_str_char_join('/', (char*)first_directory->content), params, first_directory->next);
		temp = first_directory->next;
		//free(first_directory->content); tuplafree??
		free(first_directory);
		first_directory = temp;
	}
	closedir(dirp);
	//free(directory_name);
	return (1);
}

void	initialize_params(t_params *params)
{
	params->a = 0;
	params->l = 0;
	params->r = 0;
	params->rr = 0;
	params->t = 0;
	params->multiple_params = -1;
	params->links_field = 0;
	params->owner_field = 0;
	params->group_field = 0;
	params->size_field = 0;
	return ;
}

void	print_usage()
{
	ft_printf("usage: ft_ls [-alrRt] [file ...]\n");
}

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

int		main(int argc, char **argv)
{
	char		*directory_name;
	int			i;
	t_params	*params;
	t_list		*first_directory;
	int			temp_argc;

	temp_argc = argc;
	first_directory = NULL;
	params = (t_params*)malloc(sizeof(t_params));
	initialize_params(params);
	i = 1;
	while (argv[i] && argv[i][0] == '-')
		read_params(argv[i++], params);
	if (!argv[i])
		directory_name = ft_strdup(".");
	else
	{
		while (argv[i])
		{
			directory_name = ft_strdup(argv[i]);
			ft_lstnewtoend(directory_name, ft_strlen(argv[i]) + 1, &first_directory);
			i++;
			params->multiple_params++;
			//free(directory_name);
		}
		sort_directory(&first_directory);
		directory_name = ft_strdup((char*)first_directory->content);
		first_directory = first_directory->next;
	}
	//ft_printf("%s", first_directory->content);
	print_folder(directory_name, params, first_directory);
	//while(1);
	return(0);
}