/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 16:14:37 by adebray           #+#    #+#             */
/*   Updated: 2015/08/03 08:36:29 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

struct timeval		g_timeout = {
	0,
	5000
};

void	accept_server(void)
{
	char	*tmp;
	int		fd;

	fd = 0;
	if ((fd = accept(g_net.fd, &(g_clients[fd].addr),
		&(g_clients[fd].addr_size))) == -1)
		die();
	FD_SET(fd, &(g_net.active_fd_set));
	g_clients[fd].state = PENDING;
	g_clients[fd].id = g_net.client_nbr++;
	ft_strcpy(g_clients[fd].nickname, "guest_");
	tmp = ft_itoa(g_net.client_nbr);
	ft_strcpy(g_clients[fd].nickname + 6, tmp);
	free(tmp);
	printf("<-- NEW ENTRY %d -->\n", fd);
}

void	do_business(int fd_talker)
{
	int state;
	int index;

	state = g_clients[fd_talker].state;
	if (do_i_have_something_to_do(fd_talker))
		fd_diteration(fd_talker, 0, &client_write);
	index = g_clients[fd_talker].buf.tail - 1;
	if (index == -1)
		index = CIRC_BUFSIZE - 2;
	if (g_clients[fd_talker].state == COMMAND && state == PENDING)
		g_clients[fd_talker].state = state;
	else if (g_clients[fd_talker].state > PENDING
		&& g_clients[fd_talker].buf.buf[index] == '\n')
		g_clients[fd_talker].state = ONLINE;
	g_clients[fd_talker].buf.head = g_clients[fd_talker].buf.tail;
}

int		do_i_have_something_to_read(int fd)
{
	if (FD_ISSET (fd, &(g_net.read_fd_set)))
	{
		if (fd == g_net.fd)
			accept_server();
		else
		{
			if (!client_read(fd))
				client_leave(fd);
			else
				do_business(fd);
		}
	}
	return (0);
}

void	select_server(void)
{
	g_net.read_fd_set = g_net.active_fd_set;
	g_net.write_fd_set = g_net.active_fd_set;
	if (select (FD_SETSIZE, &(g_net.read_fd_set), &(g_net.write_fd_set),
		NULL, &g_timeout) < 0)
		die();
	fd_iteration(0, &do_i_have_something_to_read);
}

void	init_server(char *port)
{
	if ((g_net.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		die();
	ft_bzero(&(g_net.my_addr), sizeof(struct sockaddr_in));
	g_net.my_addr.sin_family = AF_INET;
	g_net.my_addr.sin_addr.s_addr = INADDR_ANY;
	g_net.my_addr.sin_port = htons(ft_atoi(port));
	if (bind(g_net.fd, (struct sockaddr *)&(g_net.my_addr),
		sizeof(struct sockaddr_in)) == -1)
		die();
	if (listen(g_net.fd, 0) == -1)
		die();
	FD_ZERO (&(g_net.active_fd_set));
	FD_ZERO (&(g_net.write_fd_set));
	FD_ZERO (&(g_net.read_fd_set));
	FD_SET (g_net.fd, &(g_net.active_fd_set));
	FD_SET (0, &(g_net.active_fd_set));
	g_clients[0].state = ONLINE;
	select_server();
}

void	__test(int sig)
{
	char s[2];
	int i;

	i = 0;
	s[0] = 4;
	s[1] = '\n';
	(void)sig;
	while (i < FD_SETSIZE)
	{
		if ( FD_ISSET(i, &(g_net.write_fd_set)) )
			send(i, s, 2, 0);
		i += 1;
	}
	close(g_net.fd);
	exit(0);
}

int		main(int ac, char *av[])
{
	ft_memset(&g_net, 0, sizeof(g_net));
	ft_memset(&g_clients, 0, sizeof(g_clients));
	signal(SIGINT, &__test);
	if (ac < 2)
		init_server("6667");
	else if (ac < 3)
		init_server(av[1]);
	while (42) {
		// debug_clients();
		select_server();
	}
	return (0);
}
