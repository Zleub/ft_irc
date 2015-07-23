/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/19 22:49:14 by adebray           #+#    #+#             */
/*   Updated: 2015/07/23 02:07:01 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

void	client_leave(int fd)
{
	close (fd);
	FD_CLR (fd, &(g_net.active_fd_set));
	ft_memset(&g_clients[fd], 0, sizeof(t_client));
}

int		client_write(int fd_talk, int fd_listen)
{
	char			str[CIRC_BUFSIZE + NICKNAME_SIZE + 3];
	struct s_client	*talker;

	talker = &g_clients[fd_talk];
	ft_bzero(str, CIRC_BUFSIZE + NICKNAME_SIZE + 3);
	if (FD_ISSET(fd_listen, &(g_net.write_fd_set)))
	{
		if (talker->state > PENDING && fd_listen != 0
			//&& fd_listen != fd_talk
			&& fd_listen != g_net.fd &&
			!strcmp(g_clients[fd_talk].room, g_clients[fd_listen].room))
		{
			if (talker->state == TRANSIT)
			{
				ft_strcpy(str, talker->nickname);
				ft_strcpy(str + LEN(talker->nickname), ":\t");
				read_buf(str + LEN(talker->nickname) + 2, &(talker->buf));
			}
			else
				read_buf(str, &(talker->buf));
			if (send(fd_listen, str, LEN(str), 0) == -1)
				diewitherror("send error\n");
		}
	}
	return (0);
}

int		client_read(int fd)
{
	char	buf[CIRC_BUFSIZE - 1];
	int		n;

	ft_memset(buf, 0, CIRC_BUFSIZE - 1);
	if (!(n = read(fd, buf, CIRC_BUFSIZE - 2)))
		return (textreturn("EXIT WITHOUT TEXT\n", 0));
	else if (n < 0)
		return (textreturn("read flag error\n", 0));
	else
	{
		if (n > CIRC_BUFSIZE - 1)
			ft_putendl("Too long message for buffer ...\n");
		write_buf(&(g_clients[fd].buf), buf, n);
		if (g_clients[fd].state == COMMAND || g_clients[fd].state == PENDING)
			;
		else if (g_clients[fd].state != TRANSIT &&
			g_clients[fd].state != WRITING)
			g_clients[fd].state = TRANSIT;
		else
			g_clients[fd].state = WRITING;
		// debug_client(fd);
		if (fd == 0 && !ft_strcmp(buf, "debug\n"))
			debug_clients();
		return (n);
	}
}
