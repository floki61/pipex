#include "pipex.h"

char **path(char **argv,char **env)
{
	int i;
	int	j = 0;
	char **path;
	char **equal;

	i = search_path(argv, env);
	equal = ft_split(env[i],'=');
	path = ft_split(equal[1],':');
	return (path);
}

int		search_path(char **argv,char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		if(!(strncmp(env[i], "PATH", 4)))
			return (i);
		i++;
	}
	return (0);
}