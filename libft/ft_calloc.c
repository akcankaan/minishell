/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecer <iecer@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:31:11 by mehakcan          #+#    #+#             */
/*   Updated: 2024/09/09 12:51:09 by iecer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t c, size_t s)
{
	char	*ptr;

	ptr = malloc(c * s);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, s * c);
	return (ptr);
}
