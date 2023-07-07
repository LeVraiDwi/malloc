/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 19:03:08 by tcosse            #+#    #+#             */
/*   Updated: 2020/05/27 17:28:51 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(unsigned int nmemb, size_t size)
{
	void	*alloc;
	int		count;

	count = nmemb * size;
	alloc = malloc(count);
	if (!alloc)
		return (0);
	ft_bzero(alloc, count);
	return (alloc);
}
