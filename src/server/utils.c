/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 21:40:40 by adebray           #+#    #+#             */
/*   Updated: 2015/07/23 01:03:47 by adebray          ###   ########.fr       */
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
			printf("%d,\tH: %d,\tT: %d,\t: <%s>\n",
				i,
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
	printf("[%d]-> %s |%s - %s|\n",
		c->id,
		g_array[c->state],
		c->nickname,
		c->buf.buf);
}
