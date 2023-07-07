/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:06:34 by tcosse            #+#    #+#             */
/*   Updated: 2020/05/25 13:52:51 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t l)
{
	unsigned int	len_dest;
	unsigned int	len_src;

	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	dest = dest + len_dest;
	if (l > len_dest)
	{
		l = l - len_dest - 1;
		if (l)
			while (l-- && *src)
				*dest++ = *src++;
		*dest = '\0';
		return (len_dest + len_src);
	}
	return (l + len_src);
}
