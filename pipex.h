/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:47:49 by oel-berh          #+#    #+#             */
/*   Updated: 2022/04/05 01:06:16 by oel-berh         ###   ########.fr       */
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

char		**ft_split(char const *s, char c);
char		*ft_strjoin(char	*s1, char	*s2);
char		**path(char	**env);
int			search_path(char	**env);
void		parent(char **argv, char **env, int *end, int fd2);
void		child(char **argv, char **env, int *end, int fd1);
int			pipex(char **argv, char **env, int fd1, int fd2);
void		error(char *error, char *str);
int			ft_strlen(char *str);
void		free_tab(char **path);

#endif