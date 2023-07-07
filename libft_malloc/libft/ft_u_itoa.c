/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 08:20:51 by tcosse            #+#    #+#             */
/*   Updated: 2020/08/31 15:40:37 by tcosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	u_int_str(char *str, unsigned int n)
{
	*str-- = ((n % 10) + '0');
	n = n / 10;
	while (n)
	{
		*str-- = (n % 10) + '0';
		n = n / 10;
	}
}

unsigned int	size_u_num(unsigned int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_u_itoa(unsigned int n)
{
	unsigned int	l;
	char			*str;

	l = size_u_num(n);
	str = (char *)malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	u_int_str(str + l - 1, n);
	str[l] = '\0';
	return (str);
}
