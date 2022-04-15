/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:38:20 by oel-berh          #+#    #+#             */
/*   Updated: 2022/04/15 05:41:00 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char	**argv, char **env, int *end, t_node *files)
{
	char	**path1;
	char	**cmd;
	char	*cmd1;
	int		i;

	i = 0;
	close(end[0]);
	cmd = ft_split(argv[files->j], ' ');
	dup_files(argv, end, files);
	if (access(argv[files->j], F_OK) == 0)
		execve(argv[files->j], cmd, env);
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
	error("zsh: command not found: ", argv[files->j]);
	close(files->fd1);
	close(files->fd2);
	exit (0);
}

void	parent(int *i, int *end, t_node *files)
{
	if (*i == 1)
	{
		while (waitpid (-1, NULL, 0) > 1)
			;
	}
	close(end[1]);
	files->fd = dup(end[0]);
	close(end[0]);
	files->j = files->j + 1;
	(*i)--;
}

int	pipex(int argc, char	**argv, char	**env, t_node	*files)
{
	int		end[2];
	int		pid;
	int		i;

	i = argc - 3;
	files->argc = argc - 3;
	files->j = 2;
	while (i)
	{
		files->data = i;
		if (pipe(end) == -1)
			return (0);
		pid = fork();
		if (pid == -1)
			perror("Fork");
		else if (pid == 0)
			child(argv, env, end, files);
		else
			parent(&i, end, files);
	}
	return (0);
}

int	main(int argc, char	**argv, char	**env)
{
	t_node	*files;

	files = malloc(sizeof(t_node));
	if (argc < 5)
		exit (0);
	if (!(strcmp(argv[1], "here_doc")))
		here_doc(argc, argv, env);
	files->fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (files->fd2 < 0)
		exit (0);
	pipex(argc, argv, env, files);
	return (0);
}
