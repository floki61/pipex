#include <stdio.h>  
int main(int argc, char * argv[], char * envp[]) 
{ 
    unsigned short i; 
  
    for(i = 0; envp[i] != NULL; i++) 
    { 
        printf("%s\n", envp[i]); 
    }
  
    return 0; 
}
// void child(int *fd, char **argv)
// {
//     close(fd[0]);
//     int x;
//     printf("input a number : ");
//     scanf("%d", &x);
//     dup2(fd[1], 1);
//     close(fd[1]);
//     printf("fwfwerfwe");
//     write(fd[1], &x, sizeof(int));
// }
// void    parent(int *fd, char **argv)
// {
//     close(fd[1]);
//     int y;
//     dup2(fd[0], 0);
//     close(fd[0]);
//     read(0, &y, sizeof(int));
//     char p[10];
//     read(0,p,9);
//     printf("got from child process %d %s\n", y, p);

// }
// int main(int argc,char **argv,char **env)
// {
//     int fd[2];
//     int pid;
//     if(pipe(fd) == -1)
//         return (0);
    
//     pid = fork();
//     if (pid == -1)
//         return (0);
//     else if(pid == 0)
//         child(fd, argv);
//     else
//         parent(fd, argv); 
// }
