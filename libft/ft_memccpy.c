/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 15:14:00 by tcosse            #+#    #+#             */
/*   Updated: 2020/06/01 18:24:24 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*d;
	const char	*s;
	char		ch;

	s = src;
	d = dest;
	ch = c;
	while (n--)
	{
		*d = *s++;
		if (*d++ == ch)
			return (d);
	}
	return (0);
}
