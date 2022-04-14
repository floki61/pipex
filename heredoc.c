#include "pipex.h"

void	noname(char *limitter, int fd)
{
	char *instruction = NULL;
	// int	i;
	write(2, "->\n", 3);
	// i = ft_strlen(limitter) - 1;
	instruction = get_next_line(0);
	if (instruction)	
		instruction[ft_strlen(instruction) - 1] = '\0';

	while(instruction)
	{
		if(strcmp(limitter,instruction) == 0)
		{
			close(0);
			close(fd);
			return ;
		}
		ft_putstr_fd(instruction,fd);
		ft_putstr_fd("\n", fd);
		free(instruction);
		instruction = get_next_line(0);
		instruction[ft_strlen(instruction) - 1] = '\0';
	}  
}
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
	error("zsh: command not found: ", argv[2]);
	close(fd);
	exit (0);
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


void	parent2(char	**argv, char	**env, int *end, int fd)
{
	char	**path1;
	char	**cmd2;
	char	*cmd;
	int		i;

	i = 0;
	close(end[1]);
	write(2, "parent\n",7);
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
	error("zsh: command not found: ", argv[3]);
	close(fd);
	exit(127);
}
void here_doc(int	argc,char **argv, char	**env)
{
	int fd1;
	int fd2;
	int pid;
	int end[2];

	fd1 = open(argv[2],	 O_CREAT | O_RDWR | O_TRUNC, 0644);
	fd2	= open(argv[argc - 1], O_CREAT | O_RDWR , 0644);
	if(fd2 < 0 || fd1 < 0)
		exit (0);
	if (pipe(end) == -1)
		exit (0);
	
	noname(argv[2], fd1);
	pid = fork();
	if(pid == -1)
		perror("Fork");
	else if(pid == 0)
	{
		// printf("hey\n");
		// printf("hey\n");
		fd1 = open(argv[2], O_RDONLY);
		child2(argv, env, end, fd1);
	}
	else
	{
		waitpid(-1, NULL, 0);
		fd1 = dup(end[0]);
		parent2(argv, env, end, fd2);
	}
	exit(0);
}