/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:19:03 by tcosse            #+#    #+#             */
/*   Updated: 2020/05/25 11:45:10 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	l1;
	unsigned int	l2;

	l1 = 0;
	l2 = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[l1])
		l1++;
	while (s2[l2])
		l2++;
	l1 += l2 + 1;
	str = (char *)malloc(sizeof(char *) * l1);
	if (!str)
		return (0);
	l1 = 0;
	while (*s1)
		str[l1++] = *s1++;
	while (*s2)
		str[l1++] = *s2++;
	str[l1] = '\0';
	return (str);
}
