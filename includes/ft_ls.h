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

typedef struct	s_params
{
	int		a;
	int		l;
	int		rr;
	int		r;
	int		t;
	int		total;
	int		multiple_params;
	int		links_field;
	int		owner_field;
	int		group_field;
	int		size_field;
	char	*full_directory;
	char	*file_name;
}				t_params;

typedef struct	s_data
{
	char		*name;
	struct stat	*info;
}				t_data;


#endif
