#include "includes/ft_ls.h"

int		print_folder(char *directory_name)
{
	DIR				*dirp;
	struct dirent 	*dirent_buf;
	t_list			*first;
	
	first = NULL;
	dirp = opendir(directory_name);
	if (dirp == NULL)
	{
		ft_printf("trying to open: %s .", directory_name);
		perror( "" );
		exit(0);
	}
	while ((NULL != (dirent_buf = readdir(dirp))))
	{
		if (dirent_buf->d_name[0] != '.')
		{
			ft_printf("%s\n", dirent_buf->d_name);
			if (dirent_buf->d_type == DT_DIR)
				ft_lstnewtoend(dirent_buf->d_name, ft_strlen(dirent_buf->d_name), &first);
		}
	}
	directory_name = ft_str_char_join('/', directory_name);
	ft_printf("\n");
	while (first)
	{
		print_folder(ft_strjoin(directory_name, first->content));
		first = first->next;
	}
	closedir(dirp);
	return (1);
}

int		main(int argc, char **argv)
{
	char			*directory_name;

	if (argc > 1)
		directory_name = ft_strdup(argv[1]);
	else
		directory_name = ft_strdup(".");
	print_folder(directory_name);
	return(0);
}