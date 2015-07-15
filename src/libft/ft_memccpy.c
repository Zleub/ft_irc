/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 00:23:42 by adebray           #+#    #+#             */
/*   Updated: 2015/01/03 18:39:47 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	unsigned char	*tmp2;

	tmp2 = (unsigned char*)s2;
	if (c < 0)
		c *= -1;
	while (n--)
	{
		if (*tmp2 == c)
		{
			*(unsigned char*)s1++ = *tmp2++;
			return (s1);
		}
		*(unsigned char*)s1++ = *tmp2++;
	}
	return (NULL);
}
