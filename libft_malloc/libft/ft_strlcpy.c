/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 15:46:24 by tcosse            #+#    #+#             */
/*   Updated: 2020/05/25 13:52:02 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t l)
{
	int	count;

	if (!dest || !src)
		return (0);
	count = 0;
	while (src[count])
		count++;
	if (l)
	{
		while (*src && l-- > 1)
		{
			*dest++ = *src++;
		}
		*dest = 0;
	}
	return (count);
}
