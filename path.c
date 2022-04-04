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
	free_path(equal);
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

void	error(char *error,char *str)
{
	write(2, error, ft_strlen(error));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}
void	free_path(char **path)
{
	int i;

	i = 0;
	while(path[i])
	{
		free(path[i]);
		i++;
	}
}