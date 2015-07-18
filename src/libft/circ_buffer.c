/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 21:39:15 by adebray           #+#    #+#             */
/*   Updated: 2015/07/18 03:35:24 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

int		size_buf(struct s_circ_buf *ptr)
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

int		write_buf(struct s_circ_buf *ptr, char *mem, int size)
{
	int		i = 0;

	while (i < size)
	{
		ptr->buf[(i + ptr->head) % (CIRC_BUFSIZE - 1)] = mem[i];
		i += 1;
	}
	ptr->tail = (i + ptr->head) % (CIRC_BUFSIZE - 1);
	return i;
}

int		read_buf(char *str, struct s_circ_buf *ptr)
{
	int		i;
	int		j;
//	ft_strncpy(str + LEN(g_clients[i].nickname) + 2, (g_clients[i].buf.buf + g_clients[i].buf.head), g_clients[i].buf.tail - g_clients[i].buf.head);
	// ft_printf("THIS IS READING ACCESS from %d to %d\n", ptr->head, ptr->tail);
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
