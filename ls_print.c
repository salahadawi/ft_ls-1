/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:13:13 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/16 20:08:20 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	*get_sattr(struct stat *buffer, char *filename, char *directory,
		char *returnable)
{
	char	*name_buf;
	char	*path_name;

	name_buf = NULL;
	path_name = ft_strjoin(directory, filename);
	returnable[10] = listxattr(path_name, name_buf, 0, 0) ? '@' : ' ';
	if (buffer->st_mode & S_ISUID)
		returnable[3] = (buffer->st_mode & S_IXUSR) ? 's' : 'S';
	if (buffer->st_mode & S_ISGID)
		returnable[6] = (buffer->st_mode & S_IXGRP) ? 's' : 'S';
	if (buffer->st_mode & S_ISVTX)
		returnable[9] = (buffer->st_mode & S_IXOTH) ? 't' : 'T';
	free(path_name);
	return (returnable);
}

char	get_filetype(struct stat *buffer)
{
	char	c;

	if (S_ISREG(buffer->st_mode))
		c = '-';
	else if (S_ISDIR(buffer->st_mode))
		c = 'd';
	else if (S_ISBLK(buffer->st_mode))
		c = 'b';
	else if (S_ISCHR(buffer->st_mode))
		c = 'c';
	else if (S_ISFIFO(buffer->st_mode))
		c = 'p';
	else if (S_ISLNK(buffer->st_mode))
		c = 'l';
	else if (S_ISSOCK(buffer->st_mode))
		c = 's';
	else
		c = '?';
	return (c);
}

char	*get_modes(struct stat *buffer, char *filename, char *directory,
		int is_link)
{
	char	*returnable;

	returnable = ft_strset('-', 11);
	returnable[0] = get_filetype(buffer);
	if (is_link)
		returnable[0] = 'l';
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
	return (get_sattr(buffer, filename, directory, returnable));
}

char	*gettime(struct stat *buffer)
{
	time_t	timestamp;
	char	*returnable;
	char	*year_now;
	time_t	seconds;
	char	*temp_year;

	seconds = time(NULL);
	year_now = ft_strdup(ctime(&seconds));
	year_now = ft_str_realloc(year_now, 19, 5);
	timestamp = buffer->st_mtime;
	returnable = ft_strdup(ctime(&timestamp));
	temp_year = ft_strsub(returnable, 19, 5);
	if (ft_strequ(temp_year, year_now))
		returnable = ft_str_realloc(returnable, 4, 12);
	else
	{
		returnable = ft_str_realloc(returnable, 4, 7);
		returnable = ft_strjoin_frees1(returnable, temp_year);
	}
	free(temp_year);
	free(year_now);
	return (returnable);
}

void	print_l(char *file_name, struct stat *buffer, t_directory *directory,
		int is_link)
{
	char	*temp;

	temp = get_modes(buffer, file_name, directory->name, is_link);
	ft_printf("%s ", temp);
	free(temp);
	ft_printf("%*d ", directory->links_field, buffer->st_nlink);
	ft_printf("%-*s  ", directory->owner_field, getowner(buffer));
	ft_printf("%-*s  ", directory->group_field, getgroup(buffer));
	ft_printf("%*d ", directory->size_field, buffer->st_size);
	temp = gettime(buffer);
	ft_printf("%s ", temp);
	free(temp);
	ft_printf("%s\n", file_name);
	return ;
}
