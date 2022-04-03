
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int fd[2];
  int id;
  if(pipe(fd) == -1)
    return (0);
  if((id = fork()) == -1)
    return (0);
  if (id == 0)
  {
    close(fd[0]);
    int x;
    printf("input a number : ");
    scanf("%d", &x);
    write(fd[1], &x, sizeof(int));
    close(fd[1]);
  }
  else
  {
    close(fd[1]);
    int y;
    read(fd[0], &y, sizeof(int));
    close(fd[0]);
    printf("got from child process %d\n", y);

  }
  return (0);
}