/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:47:49 by oel-berh          #+#    #+#             */
/*   Updated: 2022/04/12 22:23:46 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
#include <stdlib.h>

char		**ft_split(char const *s, char c);
char		*ft_strjoin(char	*s1, char	*s2);
char        *get_next_line(int fd);
char		**path(char	**env);
int			search_path(char	**env);
void        child(char	*argv, char **env, int *end, int fd1,int fd2,int j, int fd);
int	        pipex(int   argc, char	**argv, char	**env, int fd1, int fd2);
void		error(char *error, char *str);
int			ft_strlen(char *str);
char        *ft_substr(char *s, int start, int len);
void		free_tab(char **path);
void	parent2(char	**argv, char	**env, int *end, int fd);
void	ft_putstr_fd(char *s, int fd);
void	child2(char	**argv, char **env, int *end, int fd);
void    here_doc(int	argc,char **argv, char	**env);
char    *limitter(char *str);
void	noname(char *limitte, int fd);
#endif