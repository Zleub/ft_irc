/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 21:40:40 by adebray           #+#    #+#             */
/*   Updated: 2015/07/17 21:41:20 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

int		die(void)
{
	ft_printf("die function");
	exit(-1);
}

void	debug_clients(void)
{
	for (int i = 0; i < FD_SETSIZE; i += 1)
	{
		if (g_clients[i].state != OFFLINE)
		{
			ft_printf("%d,\tH: %d,\tT: %d,\t: <%s>\n", i, g_clients[i].buf.head, g_clients[i].buf.tail, g_clients[i].buf.buf);
		}
	}
}
