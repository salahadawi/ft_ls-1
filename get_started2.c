# include "includes/ft_ls.h"

char	*check_filetype(struct stat *buffer)
{
	char	*returnable;

	if (S_ISREG(buffer->st_mode))
		returnable = ft_strdup("File");
	if (S_ISBLK(buffer->st_mode))
		returnable = ft_strdup("Block special file");
	if (S_ISCHR(buffer->st_mode))
		returnable = ft_strdup("Character special file");
	if (S_ISDIR(buffer->st_mode))
		returnable = ft_strdup("Directory");
	if (S_ISFIFO(buffer->st_mode))
		returnable = ft_strdup("FIFO file");
	if (S_ISLNK(buffer->st_mode))
		returnable = ft_strdup("Symbolic link");
	if (S_ISSOCK(buffer->st_mode))
		returnable = ft_strdup("Socket");
	return(returnable);
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
		returnable[5] = 'x';
	if (buffer->st_mode & S_IXGRP)
		returnable[6] = 'w';
	if (buffer->st_mode & S_IROTH)
		returnable[7] = 'r';
	if (buffer->st_mode & S_IWOTH)
		returnable[8] = 'w';
	if (buffer->st_mode & S_IXOTH)
		returnable[9] = 'x';
	return(returnable);
}

char	*getowner(struct stat *buffer)
{
	struct passwd	*user_info;

	user_info = (struct passwd*)malloc(sizeof(struct passwd));
	user_info = getpwuid(buffer->st_uid);
	return (user_info->pw_name);
}

char	*getgroup(struct stat *buffer)
{
	struct group	*group_info;

	group_info = (struct group*)malloc(sizeof(struct group));
	group_info = getgrgid(buffer->st_gid);
	return (group_info->gr_name);
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

int		main(int argc, char **argv)
{
	char			*file_name;
	struct stat		*buffer;
	char			*file_path;
	
	if (argc == 2)
	{
		buffer = (struct stat*)malloc(sizeof(struct stat));
		file_name = ft_strdup(argv[1]);
		file_path = ft_strjoin("./", file_name);
		if (-1 == stat(file_name, buffer))
		{
			ft_printf("Trying to print info on %s: ", file_name);
			perror("");
			exit(0);
		}
		ft_printf("Name: %s\n", file_name);
		ft_printf("Type: %s\n", check_filetype(buffer));
		ft_printf("Modes: %s\n", get_modes(buffer));
		ft_printf("Number of links: %d\n", buffer->st_nlink);
		ft_printf("Owner: %s\n", getowner(buffer));
		ft_printf("Group: %s\n", getgroup(buffer));
		ft_printf("Size: %d bytes\n", buffer->st_size);
		ft_printf("Last modification date: %s\n", gettime(buffer));

		
	}
	return (1);
}