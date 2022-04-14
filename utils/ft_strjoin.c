/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-berh <oel-berh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:38:50 by oel-berh          #+#    #+#             */
/*   Updated: 2022/04/14 01:14:23 by oel-berh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char	*s1, char	*s2)
{
	char	*ret;
	int		i;
	int		str1;
	int		str2;
	int		strr1;

	i = -1;
	str1 = ft_strlen(s1);
	str2 = ft_strlen(s2);
	ret = (char *) malloc(sizeof(char) * (str1 + str2 + 1));
	if (s1) {
		while (s1[++i])
			ret[i] = s1[i];
	}
	strr1 = str1;
	i = 0;
	while (s2[i])
	{
		ret[str1] = s2[i];
		i++;
		str1++;
	}
	ret[strr1 + str2] = '\0';
	free(s1);
	return (ret);
}
