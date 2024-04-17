/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:18:06 by tcosse            #+#    #+#             */
/*   Updated: 2020/06/10 17:23:03 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t l)
{
	int	i;

	if (!*little)
		return ((char *)big);
	while (*big && l)
	{
		i = 0;
		while (big[i] && big[i] == little[i] && l - i)
			i++;
		if (!little[i])
			return ((char *)big);
		big++;
		l--;
	}
	return (0);
}
