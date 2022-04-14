/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:41:16 by oel-berh          #+#    #+#             */
/*   Updated: 2022/04/12 17:59:49 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**path(char **env)
{
	int		i;
	char	**path;
	char	**equal;

	i = search_path(env);
	equal = ft_split(env[i], '=');
	path = ft_split(equal[1], ':');
	free_tab(equal);
	return (path);
}

int	search_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!(strncmp(env[i], "PATH", 4)))
			return (i);
		i++;
	}
	return (0);
}

void	error(char *error, char *str)
{
	write(2, error, ft_strlen(error));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	free_tab(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
}
char	*ft_substr(char *s, int start, int len)
{
	char	*c;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	if (s[0] == '\0' || start > ft_strlen(s))
	{
		c = malloc(1 * sizeof(char));
		if (!c)
			return (NULL);
		c[0] = '\0';
		return (c);
	}
	c = (char *)malloc((len + 1) * sizeof(char));
	if (!c)
		return (NULL);
	while (s[start] && len > 0)
	{
		c[j++] = s[start++];
		len--;
	}
	c[j] = '\0';
	return (c);
}
