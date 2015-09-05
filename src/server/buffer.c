/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 14:40:10 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 14:48:53 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

int		write_buffer(t_circ_buf *buf, char str[CIRC_BUFSIZE])
{
	int j;

	j = 0;
	while (str[j] && j < CIRC_BUFSIZE)
	{
		buf->buf[buf->tail] = str[j];
		buf->tail = (buf->tail + 1) % CIRC_BUFSIZE;
		j = j + 1;
	}
	return (j);
}

int		read_buffer(t_circ_buf *buf, char str[CIRC_BUFSIZE])
{
	int i;
	int index;

	if (buf->head == buf->tail)
	{
		i = 0;
		while (i < CIRC_BUFSIZE)
		{
			index = (buf->head + i) % CIRC_BUFSIZE;
			str[i] = buf->buf[index];
			i = i + 1;
		}
	}
	else
	{
		i = 0;
		while (buf->head != buf->tail)
		{
			str[i] = buf->buf[buf->head];
			buf->head = (buf->head + 1) % CIRC_BUFSIZE;
			i = i + 1;
		}
	}
	return (0);
}
