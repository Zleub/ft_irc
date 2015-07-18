/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 21:40:40 by adebray           #+#    #+#             */
/*   Updated: 2015/07/18 22:21:58 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

int		die(void)
{
	printf("die function");
	exit(-1);
}

int		dieWithError(char *error)
{
	printf("%s", error);
	exit(-1);
}

int		textReturn(char *text, int ret)
{
	printf("%s", text);
	return (ret);
}

void	debug_clients(void)
{
	for (int i = 0; i < FD_SETSIZE; i += 1)
	{
		if (g_clients[i].state != OFFLINE)
		{
			printf("%d,\tH: %d,\tT: %d,\t: <%s>\n", i, g_clients[i].buf.head, g_clients[i].buf.tail, g_clients[i].buf.buf);
		}
	}
}

char	*g_array[STATELEN] = {
	"OFFLINE",
	"ONLINE",
	"PENDING",
	"WRITING",
	"TRANSIT"
};

void	debug_client(int fd)
{
	t_client	*c;

	c = &g_clients[fd];
	printf("[%d]-> %s |%s - %s|\n", c->id, g_array[c->state], c->nickname, c->buf.buf);
}
