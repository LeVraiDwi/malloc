/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:16:48 by tcosse            #+#    #+#             */
/*   Updated: 2020/08/31 15:47:04 by tcosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j] && s[j] == c)
		j++;
	if (s[j])
		i++;
	while (s[j])
	{
		if (s[j++] == c)
		{
			while (s[j] == c)
				j++;
			if (!s[j])
				return (i);
			i++;
		}
	}
	return (i);
}

int	cleantab(char **tab, char *buf)
{
	free(tab);
	free(buf);
	return (0);
}

int	ft_create_buf(char **buf, char ***strtab, char const *s, char c)
{
	*buf = (char *)malloc(sizeof(char *) * ft_strlen(s));
	if (!s || !*buf)
		return (0);
	*strtab = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!*strtab)
		return (0);
	return (1);
}

int	ft_is_buff(char **strtab, char *buf, int *j)
{
	if (*buf)
	{
		strtab[*j] = ft_strdup(buf);
		if (!strtab[*j])
			return (cleantab(strtab, buf));
		*j = *j + 1;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	*buf;
	char	**strtab;

	j = 0;
	if (!ft_create_buf(&buf, &strtab, s, c))
		return (0);
	while (*s)
	{
		i = 0;
		while (*s && *s != c)
			buf[i++] = *s++;
		buf[i] = '\0';
		while (*s && *s == c)
			s++;
		if (!ft_is_buff(strtab, buf, &j))
			return (0);
	}
	strtab[j] = NULL;
	free(buf);
	return (strtab);
}
