/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 14:48:54 by tcosse            #+#    #+#             */
/*   Updated: 2020/06/25 16:04:01 by tcosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	if (n == 0)
		return (0);
	c1 = *s1;
	c2 = *s2;
	while (n-- && *s1 && *s2)
	{
		if (c1 != c2)
			return (c1 - c2);
		if (n)
		{
			s1++;
			s2++;
		}
		c1 = *s1;
		c2 = *s2;
	}
	return (c1 - c2);
}
