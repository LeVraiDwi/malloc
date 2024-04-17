/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosse <tcosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:39:10 by tcosse            #+#    #+#             */
/*   Updated: 2020/05/26 15:10:09 by dwi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	n;
	int	signe;

	n = 0;
	signe = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = signe * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10;
		n = n + (*str - '0');
		str++;
	}
	return (n * signe);
}
