/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:31:29 by mehakcan          #+#    #+#             */
/*   Updated: 2024/09/09 12:31:29 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdlib.h>

static int	calc(int n)
{
	int	x;

	x = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		x++;
	while (n != 0)
	{
		n /= 10;
		x++;
	}
	return (x);
}

char	*ft_itoa(int nbr)
{
	long	temp;
	char	*str;
	int		x;

	temp = nbr;
	x = calc(temp);
	str = malloc(x + 1);
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		temp *= -1;
	}
	str[x] = '\0';
	while (x--)
	{
		str[x] = temp % 10 + '0';
		temp /= 10;
	}
	if (nbr < 0)
		str[0] = '-';
	return (str);
}
