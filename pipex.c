#include "pipex.h"

void child(char **argv,char **env,int *end,int fd1)
{
	char **path1;
	char **cmd;
	char *cmd1;
	int i;

	i = 0;
	close(end[0]);
	cmd = ft_split(argv[2], ' ');
    dup2(fd1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	path1 = path(argv,env);
	while(path1[i])
	{
		cmd1 = ft_strjoin(path1[i], "/");
		cmd1 = ft_strjoin(cmd1,cmd[0]);
		if(access(cmd1,F_OK) == 0)
		{	
			while(1);
			execve(cmd1,cmd,env);
		}
		free(cmd1);
		i++;
	}
	error("zsh: command not found: ",argv[2]);
	close(fd1);
}
void    parent(char **argv,char **env,int *end,int fd2)
{
	char **path1;
	char **cmd2;
	char *cmd;
	int i;

	i = 0;
	close(end[1]);
	cmd2 = ft_split(argv[3], ' ');
    dup2(end[0], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	path1 = path(argv,env);
	while(path1[i])
	{
		cmd = ft_strjoin(path1[i], "/");
		cmd = ft_strjoin(cmd,cmd2[0]);
		if(access(cmd,F_OK) == 0)
		{
			execve(cmd,cmd2,env);
		}
		i++;
		free(cmd);
	}
	error("zsh: command not found: ",argv[3]);
	close(fd2);
	exit(127);
}
int	pipex(char **argv,char **env,int fd1,int fd2)
{
	int end[2];
    int pid;

    if(pipe(end) == -1)
        return (0);
    pid = fork();
    if (pid == -1)
        perror("Fork: ");
    else if(pid == 0)
        child(argv, env,end,fd1);	//infile cmd1
    else
        parent(argv,env,end,fd2); 	//outfile cmd2
	printf("ok");
	return (0);
}

int		main(int argc,char **argv,char **env)
{
	int fd1;
	int fd2;
	int i;

	if(argc != 5)
		exit (0);
	fd1 = open(argv[1],O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR, 0644);
	if(fd2 < 0)
		exit (0);
	else if (fd1 < 0)
	{
		error("zsh: no such file or directory: ",argv[1]);
		exit (0);
	}
	pipex(argv,env,fd1,fd2);
	return (0);
}
