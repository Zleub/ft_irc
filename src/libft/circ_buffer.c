/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 21:39:15 by adebray           #+#    #+#             */
/*   Updated: 2015/08/17 18:51:10 by adebray          ###   ########.fr       */
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

int		write_buf(t_circ_buf *ptr, char *mem, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		ptr->buf[(i + ptr->head) % (CIRC_BUFSIZE - 1)] = mem[i];
		i += 1;
	}
	ptr->tail = (i + ptr->head) % (CIRC_BUFSIZE - 1);
	return (i);
}

#include <stdio.h>

int		read_buf(char *str, t_circ_buf *ptr)
{
	int		i;
	int		j;
	int		n;

	n = 0;
	// printf("readbuff head: %d, tail:%d\n", ptr->head, ptr->tail);
	while (ptr->buf[ptr->head + n] != '\n' && n != ptr->tail) {
		// printf("n: %d\n", n);
		n = (n + 1) % (CIRC_BUFSIZE - 1);
	}
	// printf("readbuff 2\n");
	if (n < ptr->tail - ptr->head)
	{
		ft_strncpy(str, (ptr->buf + ptr->head), n + 1);
		ptr->head += n + 1;
		// printf("1\n");
		return (n);
	}
	if (ptr->tail > ptr->head)
	{
		ft_strncpy(str, (ptr->buf + ptr->head), ptr->tail - ptr->head);
		ptr->head = ptr->tail;
		// printf("2\n");
		return (ptr->tail - ptr->head);
	}
	else
	{
		i = ptr->head;
		j = 0;
		while (i % (CIRC_BUFSIZE - 1) != ptr->tail && ptr->buf[i % (CIRC_BUFSIZE - 1)] != '\n')
		{
			// printf("-> %d\n", j);
			str[j] = ptr->buf[i % (CIRC_BUFSIZE - 1)];
			i += 1;
			j += 1;
		}
	}
	if (ptr->buf[i % (CIRC_BUFSIZE - 1)] == '\n') {
		str[j + 1] = '\n';
		ptr->head = (i + 1) % (CIRC_BUFSIZE - 1);
	}
	else
		ptr->head = i % (CIRC_BUFSIZE - 1);

	// printf("3\n");
	return (i % (CIRC_BUFSIZE - 1));
}
