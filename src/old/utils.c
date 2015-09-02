/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 21:40:40 by adebray           #+#    #+#             */
/*   Updated: 2015/08/16 16:35:15 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

char	*g_array[STATELEN] = {
	"OFFLINE",
	"PENDING",
	"ONLINE",
	"WRITING",
	"TRANSIT",
	"COMMAND"
};

int		die(void)
{
	printf("die function");
	exit(-1);
}

int		diewitherror(char *error)
{
	printf("%s", error);
	exit(-1);
}

int		textreturn(char *text, int ret)
{
	printf("%s", text);
	return (ret);
}

void	debug_clients(void)
{
	int i;

	i = 0;
	while (i < FD_SETSIZE)
	{
		if (g_clients[i].state != OFFLINE)
		{
			printf("%d, %s\tH: %d,\tT: %d,\t: <%s>\n",
				i,
				g_array[g_clients[i].state],
				g_clients[i].buf.head,
				g_clients[i].buf.tail,
				g_clients[i].buf.buf);
		}
		i += 1;
	}
}

void	debug_client(int fd)
{
	t_client	*c;

	c = &g_clients[fd];
	printf("[%d @ %s]-> %s, H:%d T:%d <----->\n%s - %s\n<----->\n",
		c->id,
		c->room,
		g_array[c->state],
		c->buf.head,
		c->buf.tail,
		c->nickname,
		c->buf.buf);
}
