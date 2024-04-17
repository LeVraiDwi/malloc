/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 18:11:05 by tcosse            #+#    #+#             */
/*   Updated: 2020/05/14 20:24:46 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	int_str(char *str, long n)
{
	*str-- = ((n % 10) + '0');
	n = n / 10;
	while (n)
	{
		*str-- = (n % 10) + '0';
		n = n / 10;
	}
}

int	size_num(long n)
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

char	*ft_itoa(int n)
{
	int		l;
	long	i;
	char	*str;

	i = (long)n;
	l = size_num(i);
	if (i < 0)
	{
		str = (char *)malloc(sizeof(char) * (l + 2));
		if (!str)
			return (NULL);
		i = i * (-1);
		*str++ = '-';
	}
	else
	{
		str = (char *)malloc(sizeof(char) * (l + 1));
		if (!str)
			return (NULL);
	}
	int_str(str + l - 1, i);
	str[l] = '\0';
	if (n < 0)
		return (str - 1);
	return (str);
}
