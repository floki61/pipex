/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 05:02:18 by oel-berh          #+#    #+#             */
/*   Updated: 2022/04/15 05:36:38 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	dup_files(char **argv, int *end, t_node *files)
{
	if (files->j == 2)
	{
		files->fd1 = open(argv[1], O_RDONLY);
		if (files->fd1 < 0)
		{
			error("zsh: no such file or directory: ", argv[1]);
			exit (0);
		}
	}
	if (files->data != 1)
		dup2(end[1], STDOUT_FILENO);
	if (files->data == files->argc)
		dup2(files->fd1, STDIN_FILENO);
	else if (files->data != 1)
		dup2(files->fd, STDIN_FILENO);
	else
	{
		close(end[1]);
		dup2(files->fd, STDIN_FILENO);
		dup2(files->fd2, STDOUT_FILENO);
	}
}

void	read_from_0(char *limitter, int fd)
{
	char	*instruction;

	instruction = NULL;
	ft_putstr_fd ("pipe heredoc> ", 0);
	instruction = get_next_line(0);
	if (instruction)
		instruction[ft_strlen(instruction) - 1] = '\0';
	while (instruction)
	{
		if (strcmp(limitter, instruction) == 0)
		{
			close(0);
			close(fd);
			return ;
		}
		ft_putstr_fd(instruction, fd);
		ft_putstr_fd("\n", fd);
		free(instruction);
		ft_putstr_fd ("pipe heredoc> ", 0);
		instruction = get_next_line(0);
		if (instruction)
			instruction[ft_strlen(instruction) - 1] = '\0';
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write (fd, &s[i], 1);
			i++;
		}
	}
}
