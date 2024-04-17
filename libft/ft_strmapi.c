/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 13:51:49 by tcosse            #+#    #+#             */
/*   Updated: 2020/05/25 11:45:58 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	i = 0;
	if (!s || !f)
		return (0);
	str = ft_strdup(s);
	if (!str)
		return (str);
	while (str[i])
	{
		str[i] = (*f)(i, str[i]);
		i++;
	}
	return (str);
}
