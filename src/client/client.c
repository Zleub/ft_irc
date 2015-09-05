/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 13:13:02 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 17:01:34 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

struct timeval	g_timeout = {
	0,
	5000
};

int		client_connect(char *str, int port)
{
	client_reset();
	if (!ft_strcmp(str, "localhost"))
		str = "127.0.0.1";
	if (!port)
		port = 6667;
	if ((g_net.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		client_quit("socket");
	g_net.my_addr.sin_family = AF_INET;
	g_net.my_addr.sin_addr.s_addr = inet_addr(str);
	g_net.my_addr.sin_port = htons(port);
	if (CONNECT(g_net.fd, g_net.my_addr) == -1)
	{
		printw("Connection at %s:%d failed\n", str, port);
		client_reset();
		return (0);
	}
	FD_SET(g_net.fd, &(g_net.active_fd_set));
	printw("Connected to %s:%d\n", str, port);
	return (1);
}

int		client_work(int fd)
{
	static int	i;
	int			j;
	char		buf[CIRC_BUFSIZE - 1];
	char		**tmp;

	ft_bzero(buf, CIRC_BUFSIZE - 1);
	if (FD_ISSET(fd, &(g_net.read_fd_set)))
	{
		if (fd == 0)
			prompt_work();
		else
		{
			if ((read(fd, &buf, CIRC_BUFSIZE - 2)) == 0)
				client_quit(NULL);
			tmp = ft_strsplit(buf, '\n');
			j = 0;
			while (tmp[j])
			{
				mvprintw(i, 0, "%s\n", tmp[j]);
				j = j + 1;
				i = (i + 1) % (LINES - 6);
			}
		}
	}
	return (0);
}

void	select_client(void)
{
	g_net.read_fd_set = g_net.active_fd_set;
	g_net.write_fd_set = g_net.active_fd_set;
	if (select(FD_SETSIZE, &(g_net.read_fd_set), NULL, NULL, &g_timeout) < 0)
		diewitherror("select");
	fd_iteration(0, &client_work);
}
