/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 21:39:15 by adebray           #+#    #+#             */
/*   Updated: 2015/08/04 14:35:36 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		size_buf(t_circ_buf *ptr)
{
	int	i;
	int	j;

	if (ptr->tail == ptr->head)
		return (CIRC_BUFSIZE - 1);
	else if (ptr->tail > ptr->head)
		return (ptr->tail - ptr->head);
	else
	{
		i = ptr->head;
		j = 0;
		while (i % (CIRC_BUFSIZE - 1) != ptr->tail)
		{
			i += 1;
			j += 1;
		}
		return (j);
	}
}

#include <stdio.h>

int		write_buf(t_circ_buf *ptr, char *mem, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		printf("%d -- %d\n", (i + ptr->head) % (CIRC_BUFSIZE - 1), i);
		ptr->buf[(i + ptr->head) % (CIRC_BUFSIZE - 1)] = mem[i];
		i += 1;
	}
	ptr->tail = (i + ptr->head) % (CIRC_BUFSIZE - 1);
	printf("return \n");
	return (i);
}

int		read_buf(char *str, t_circ_buf *ptr)
{
	int		i;
	int		j;

	if (ptr->tail > ptr->head)
		ft_strncpy(str, (ptr->buf + ptr->head), ptr->tail - ptr->head);
	else
	{
		i = ptr->head;
		j = 0;
		while (i % (CIRC_BUFSIZE - 1) != ptr->tail)
		{
			str[j] = ptr->buf[i % (CIRC_BUFSIZE - 1)];
			i += 1;
			j += 1;
		}
	}
	return (0);
}
