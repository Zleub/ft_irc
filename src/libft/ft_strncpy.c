/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 00:27:13 by adebray           #+#    #+#             */
/*   Updated: 2015/01/03 20:23:21 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	while (s2[i] != '\0' && i < n)
	{
		s1[i] = s2[i];
		++i;
	}
	while (i < n)
		s1[i++] = '\0';
	return (s1);
}
