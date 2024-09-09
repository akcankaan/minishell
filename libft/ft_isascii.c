/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehakcan <mehakcan@student.42.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:31:19 by mehakcan          #+#    #+#             */
/*   Updated: 2024/09/09 12:31:19 by mehakcan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	ft_isascii(int x)
{
	if (x <= 127 && x >= 0)
		return (1);
	return (0);
}
