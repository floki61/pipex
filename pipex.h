/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:47:49 by oel-berh          #+#    #+#             */
/*   Updated: 2022/04/15 05:40:44 by oel-berh         ###   ########.fr       */
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
# include <stdlib.h>

typedef struct s_node
{
	int	fd;
	int	fd1;
	int	fd2;
	int	data;
	int	argc;
	int	j;
}	t_node;

void		dup_files(char **argv, int *end, t_node *files);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char	*s1, char	*s2);
char		*get_next_line(int fd);
char		**path(char	**env);
int			search_path(char	**env);
void		child(char	**argv, char **env, int *end, t_node *files);
void		parent(int *i, int *end, t_node *files);
int			pipex(int argc, char	**argv, char	**env, t_node *files);
void		error(char *error, char *str);
int			ft_strlen(char *str);
char		*ft_substr(char *s, int start, int len);
void		free_tab(char **path);
void		parent2(char	**argv, char	**env, int *end, int fd);
void		ft_putstr_fd(char *s, int fd);
void		child2(char	**argv, char **env, int *end, int fd);
void		here_doc(int argc, char **argv, char	**env);
void		read_from_0(char *limitter, int fd);

#endif