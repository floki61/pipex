/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 22:41:07 by oel-berh          #+#    #+#             */
/*   Updated: 2022/04/15 05:11:45 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child2(char	**argv, char **env, int *end, int fd)
{
	char	**path1;
	char	**cmd;
	char	*cmd1;
	int		i;

	i = 0;
	close(end[0]);
	cmd = ft_split(argv[3], ' ');
	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	if (access(argv[3], F_OK) == 0)
		execve(argv[3], cmd, env);
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
	error("zsh: command not found: ", argv[3]);
	close(fd);
	exit (0);
}

void	parent2(char	**argv, char	**env, int *end, int fd)
{
	char	**path1;
	char	**cmd2;
	char	*cmd;
	int		i;

	i = 0;
	close(end[1]);
	cmd2 = ft_split(argv[4], ' ');
	dup2(end[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	if (access(argv[4], F_OK) == 0)
		execve(argv[4], cmd2, env);
	path1 = path(env);
	while (path1[i])
	{
		cmd = ft_strjoin(path1[i], "/");
		cmd = ft_strjoin(cmd, cmd2[0]);
		if (access(cmd, F_OK) == 0)
			execve(cmd, cmd2, env);
		free(cmd);
		i++;
	}
	error("zsh: command not found: ", argv[4]);
	close(fd);
	exit(127);
}

void	here_doc(int argc, char **argv, char	**env)
{
	t_node	*files;
	int		pid;
	int		end[2];

	files = malloc(sizeof(t_node));
	files->fd1 = open("/tmp/.fd", O_CREAT | O_RDWR, 0777);
	files->fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (files->fd2 < 0 || files->fd1 < 0 || pipe(end) == -1)
		exit (0);
	read_from_0(argv[2], files->fd1);
	pid = fork();
	if (pid == -1)
		perror("Fork");
	else if (pid == 0)
	{
		files->fd1 = open("/tmp/.fd", O_RDONLY);
		child2(argv, env, end, files->fd1);
	}
	waitpid(-1, NULL, 0);
	files->fd1 = dup(end[0]);
	unlink("/tmp/.fd");
	parent2(argv, env, end, files->fd2);
	exit(0);
}
