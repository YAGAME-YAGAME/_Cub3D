/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:23:39 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/30 18:15:09 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					x;
	unsigned long long	t;

	i = 0;
	x = 1;
	t = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			x = -x;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		t = (t * 10) + (str[i] - 48);
		i++;
	}
	return ((int)(t * x));
}
