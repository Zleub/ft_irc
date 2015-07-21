/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 16:14:37 by adebray           #+#    #+#             */
/*   Updated: 2015/07/21 09:14:32 by adebray          ###   ########.fr       */
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
	if ((fd = accept(g_net.fd, &(g_clients[fd].addr), &(g_clients[fd].addr_size))) == -1)
		die();
	FD_SET(fd, &(g_net.active_fd_set));
	g_clients[fd].state = ONLINE;
	g_clients[fd].id = g_net.client_nbr++;
	ft_strcpy(g_clients[fd].nickname, "guest_");
	tmp = ft_itoa(g_net.client_nbr);
	ft_strcpy(g_clients[fd].nickname + 6, tmp);
	free(tmp);
	printf("<-- NEW ENTRY %d -->\n", fd);
}

int		do_i_have_something_to_do(int fd)
{
	char		test[COMMAND_BUFSIZE];

	if (g_clients[fd].buf.buf[g_clients[fd].buf.head] == '/' && g_clients[fd].state != WRITING && g_clients[fd].state != COMMAND)
	{
		ft_bzero(test, COMMAND_BUFSIZE);
		g_clients[fd].state = COMMAND;
	}
	// write(1, ( g_clients[fd].buf.buf + g_clients[fd].buf.head ), g_clients[fd].buf.tail - g_clients[fd].buf.head);
	if (g_clients[fd].state == COMMAND) {
		if (LEN(test) == 0)
			read_buf(test, &g_clients[fd].buf);
		else
			read_buf(&test[LEN(test)], &g_clients[fd].buf);
		printf("I got a command : %s\n", test);
		// g_clients[fd].buf.head = g_clients[fd].buf.tail;
		return (0);
	}
	return (1);
}

void	do_business(int fd_talker)
{
	if (do_i_have_something_to_do(fd_talker))
		fd_diteration(fd_talker, 0, &client_write);

	int index = g_clients[fd_talker].buf.tail - 1;
	if (index == -1)
		index = CIRC_BUFSIZE - 2;

	if (g_clients[fd_talker].buf.buf[index] == '\n')// && size_buf(&(g_clients[i].buf)) != CIRC_BUFSIZE - 2)
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
			else {
				// debug_client(fd);
				do_business(fd);
			}
		}
	}
	return (0);
}

void	select_server(void)
{
	g_net.read_fd_set = g_net.active_fd_set;
	g_net.write_fd_set = g_net.active_fd_set;
	if (select (FD_SETSIZE, &(g_net.read_fd_set), &(g_net.write_fd_set), NULL, &g_timeout) < 0)
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
	if (bind(g_net.fd, (struct sockaddr *)&(g_net.my_addr), sizeof(struct sockaddr_in)) == -1)
		die();
	if (listen(g_net.fd, 0) == -1)
		die();
	FD_ZERO (&(g_net.active_fd_set));
	FD_SET (g_net.fd, &(g_net.active_fd_set));
	FD_SET (0, &(g_net.active_fd_set));
	g_clients[0].state = ONLINE;
	select_server();
}

int		main(int ac, char *av[])
{
	ft_memset(&g_net, 0, sizeof(g_net));
	ft_memset(&g_clients, 0, sizeof(g_clients));
	for (int i = 0; i < FD_SETSIZE; ++i)
	{
		g_clients[i].id = 0;
		g_clients[i].state = OFFLINE;
		g_clients[i].buf.head = 0;
		g_clients[i].buf.tail = 0;
	}
	if (ac == 2) {
		debug_clients();
		init_server(av[1]);
		while (42) {
			select_server();
			// printf("tik\n");
			// debug_clients();
		}
	}
	return (0);
}
