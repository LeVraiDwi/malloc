/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:45:36 by tcosse            #+#    #+#             */
/*   Updated: 2020/06/16 15:47:32 by tcosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

const char	*start_cut(char const *s1, char const *set)
{
	int	flag;

	flag = 1;
	while (flag && *s1)
	{
		flag = 0;
		if (in_set(*s1, set))
		{
			s1++;
			flag = 1;
		}
	}
	return (s1);
}

int	size_str(char const *s1, char const *set)
{
	int	flag;
	int	i;

	i = 0;
	flag = 1;
	while (s1[i])
		i++;
	while (flag)
	{
		flag = 0;
		if (in_set(s1[--i], set))
			flag = 1;
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	i;
	unsigned int	l;

	if (!s1 || !set)
		return (0);
	l = 0;
	s1 = start_cut(s1, set);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	i = size_str(s1, set);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	while (*s1 && i--)
		str[l++] = *s1++;
	str[l] = '\0';
	return (str);
}
