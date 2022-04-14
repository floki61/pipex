/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:38:20 by oel-berh          #+#    #+#             */
/*   Updated: 2022/04/12 21:50:55 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char	*argv, char **env, int *end, int fd1,int fd2,int j, int fd)
{
	char	**path1;
	char	**cmd;
	char	*cmd1;
	int		i;

	i = 0;
	close(end[0]);
	cmd = ft_split(argv, ' ');
	if(j != 1)
		dup2(end[1], STDOUT_FILENO);
	if(j == 0)
		dup2(fd1, STDIN_FILENO);
	else if(j == 2)
		dup2(fd, STDIN_FILENO);
	else
	{
		close(end[1]);
		dup2(fd, STDIN_FILENO);
		dup2(fd2, STDOUT_FILENO);
	}
	if (access(argv, F_OK) == 0)
		execve(argv, cmd, env);
	path1 = path(env);
	while (path1[i])
	{
		cmd1 = ft_strjoin(path1[i], "/");
		cmd1 = ft_strjoin(cmd1, cmd[0]);
		if (access(cmd1, F_OK) == 0)
			execve(cmd1, cmd, env);
		free(cmd1);
		i++;
	}
	error("zsh: command not found: ", argv);
	close(fd1);
	close(fd2);
	exit (0);
}

int	pipex(int   argc, char	**argv, char	**env, int fd1, int fd2)
{
	int		end[2];
	int		fd;
	int		pid;
    int     i;
    int     j;

    i = argc - 3;
    j = 2;
    while(i)
    {
		if (pipe(end) == -1)
			return (0);
	    pid = fork();
	    if (pid == -1)
		    perror("Fork: ");
	    else if (pid == 0 && i == argc - 3)
		    child(argv[j], env, end, fd1, fd2, 0, fd);
		else if (pid == 0 && i != 1)
			child(argv[j], env, end, fd1, fd2, 2, fd);
		else if(pid == 0 && i == 1)
		    	child(argv[j], env, end, fd1, fd2, 1, fd);
		else
		{
			while(waitpid(-1, NULL, 0) > 1)
			close(end[1]);
			fd = dup(end[0]);
			close(end[0]);
			j++;
			i--;
		}
    }
	return (0);
} 

int	main(int argc, char	**argv, char	**env)
{
	int	fd1;
	int	fd2;

	if (argc < 5)
		exit (0);
	if(!(strcmp(argv[1], "here_doc")))
		here_doc(argc, argv, env);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd2 < 0)
		exit (0);
	else if (fd1 < 0)
	{
		error("zsh: no such file or directory: ", argv[1]);
		exit (0);
	}
	pipex(argc, argv, env, fd1, fd2);
	return (0);
}