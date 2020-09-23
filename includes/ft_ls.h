/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:15:23 by hlaineka          #+#    #+#             */
/*   Updated: 2020/09/23 17:36:40 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <errno.h>

typedef struct	s_file
{
	char		*name;
	int			is_link;
	struct stat	*stat_info;
	int			is_dir;
	char		*error_message;

}				t_file;

typedef struct	s_directory
{
	int			total;
	int			links_field;
	int			owner_field;
	int			group_field;
	int			size_field;
	t_list		*first_file;
	char		*name;
	struct stat	*stat_info;
	char		*error_message;
}				t_directory;

typedef struct	s_params
{
	int			a;
	int			l;
	int			rr;
	int			r;
	int			t;
	t_file		*file_param;
	int			multiple_folders;
}				t_params;

typedef struct	s_data
{
	char		*name;
	struct stat	*info;
}				t_data;

void			read_directory(char	*directory_name, t_params *params,
				t_list **first_directory, int caller);
void			read_dirp(struct stat *dir_stat, char *directory_name,
				t_params *params, t_list **first_directory);
char			*getowner(struct stat *buffer);
char			*getgroup(struct stat *buffer);
char			*get_modes(struct stat *buffer, char *filename, char *directory,
				int is_link);
char			*gettime(struct stat *buffer);
void			print_l(char *file_name, struct stat *buffer,
				t_directory *directory, int is_link);
int				sort_dir_name(t_list *a, t_list *b);
int				sort_dir_time(t_list *a, t_list *b);
int				sort_file_name(t_list *a, t_list *b);
int				sort_file_time(t_list *a, t_list *b);
void			reverse_lists(t_list **first_directory);
void			initialize_directory(t_directory *directory);
void			print_usage(void);
void			initialize_params(t_params *params);
void			check_field_width(struct stat *info,
				t_directory *directory_info);
void			add_file(t_file *new_file, t_params *params,
				t_list *first_directory);
void			add_directory(char *directory_name, t_list **first_directory,
				struct stat *stat_buf);
void			add_to_list(struct dirent *dirent_buf, struct stat *stat_buf,
				t_params *params, t_list **first_directory);
void			find_dir_add_file(t_list **first_directory, t_file *new_file,
				t_params *params);
int				handle_file_param(char *file_name, t_list **first_directory,
				t_params *params);
void			check_field_width(struct stat *info,
				t_directory *directory_info);
void			print_filelist(t_params *params, t_directory *directory);
char			*ft_strjoin3(char *str1, char *str2, char *str3);
void			print_error(char *directory_name);
void			read_file(char *file_name, t_file *new_file,
				struct stat *stat_buf);
t_list			*read_argv(int argc, int i, t_params *params, char **argv);
void			handle_dir_error(char *directory_name, t_list **first_directory);
void			handle_file_error(char *file_name, t_params *params, t_list **first_directory);
void			recursive_caller(t_params *params, t_list **first_directory);

#endif
