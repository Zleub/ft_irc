/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 14:38:26 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 14:50:03 by adebray          ###   ########.fr       */
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

void	debug_client(t_client *c)
{
	printf("%d\t| %s\tH: %d,\tT: %d,\t: <%s>\n",
		c->id,
		g_array[c->state],
		c->buf.head,
		c->buf.tail,
		c->buf.buf);
}

void	debug_clients(void)
{
	int i;

	i = 0;
	while (i < FD_SETSIZE)
	{
		if (g_clients[i].state != OFFLINE)
			debug_client(&g_clients[i]);
		i += 1;
	}
}

void	client_leave(int fd)
{
	printf("<--- CLIENT LEAVE %d --->\n", fd);
	close(fd);
	FD_CLR(fd, &(g_net.active_fd_set));
	ft_memset(&g_clients[fd], 0, sizeof(t_client));
}

int		client_read(int index)
{
	int		n;
	char	buf[CIRC_BUFSIZE + 1];

	printf("Reading %d\n", index);
	ft_bzero(buf, CIRC_BUFSIZE + 1);
	n = 0;
	if ((n = read(index, buf, CIRC_BUFSIZE)) < 1)
		return (0);
	else
	{
		write_buffer(&g_clients[index].buf, buf);
		printf("Msg size: %d\n", n);
		return (n);
	}
}

int		client_write(int fd_talk, int fd_listen, char *str)
{
	struct s_client	*talker;

	talker = &g_clients[fd_talk];
	if (FD_ISSET(fd_listen, &(g_net.write_fd_set)))
	{
		if (talker->state > PENDING && fd_listen != 0
			&& fd_listen != g_net.fd
			&& !strcmp(g_clients[fd_talk].room, g_clients[fd_listen].room))
		{
			printf("BROADCAST: I read %zu chars\n", LEN(str));
			if (send(fd_listen, str, LEN(str), 0) == -1)
				die();
		}
	}
	return (0);
}
