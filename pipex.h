#ifndef PIPEX_H
#define	PIPEX_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

char		**ft_split(char const *s, char c);
char	    *ft_strjoin(char	*s1, char	*s2);
char        **path(char **argv,char **env);
int		    search_path(char **argv,char **env);
void        parent(char **argv,char **env,int *end,int fd2);
void        child(char **argv,char **env,int *end,int fd1);
int	        pipex(char **argv,char **env,int fd1,int fd2);

#endif