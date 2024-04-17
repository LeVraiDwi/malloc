/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 15:35:14 by tcosse            #+#    #+#             */
/*   Updated: 2020/05/26 15:05:32 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (d < s)
		while (n--)
			*d++ = *s++;
	else if (d > s)
	{
		s += n - 1;
		d += n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}
