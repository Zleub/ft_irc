/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 16:14:37 by adebray           #+#    #+#             */
/*   Updated: 2015/07/19 08:25:56 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

struct timeval		g_timeout = {
	2,
	500000
};

int		read_server(int fd)
{
	char	buf[CIRC_BUFSIZE - 1];
	int		n;

	ft_memset(buf, 0, CIRC_BUFSIZE - 1);
	if (!(n = read(fd, buf, CIRC_BUFSIZE - 2)))
		return textReturn("EXIT WITHOUT TEXT\n", 0);
	else if (n < 0)
		return textReturn("read flag error\n", 0);
	else
	{
		if (n > CIRC_BUFSIZE - 1)
			ft_putendl("Too long message for buffer ...\n");

		write_buf(&(g_clients[fd].buf), buf, n);

		if (g_clients[fd].state != TRANSIT && g_clients[fd].state != WRITING)
			g_clients[fd].state = TRANSIT;
		else
			g_clients[fd].state = WRITING;

		if (!ft_strcmp(buf, "debug\n") || !ft_strcmp(buf, "debug"))
			debug_clients();
		return (n);
	}
}

void	accept_server(void)
{
	int		fd;

	fd = 0;
	if ((fd = accept(g_net.fd, &(g_clients[fd].addr), &(g_clients[fd].addr_size))) == -1)
		die();
	FD_SET(fd, &(g_net.active_fd_set));
	g_clients[fd].state = ONLINE;
	g_clients[fd].id = g_net.client_nbr++;
	ft_strcpy(g_clients[fd].nickname, "guest_");
	ft_strcpy(g_clients[fd].nickname + 6, ft_itoa(g_net.client_nbr));
	printf("<-- NEW ENTRY %d -->\n", fd);
}

void	do_i_have_something_to_do(int fd)
{
	// write(1, ( g_clients[fd].buf.buf + g_clients[fd].buf.head ), g_clients[fd].buf.tail - g_clients[fd].buf.head);
	if (g_clients[fd].buf.buf[g_clients[fd].buf.head] == '/') {
		printf("I got a command : %s\n", &g_clients[fd].buf.buf[g_clients[fd].buf.head]);
		// g_clients[fd].buf.head = g_clients[fd].buf.tail - g_clients[fd].buf.head;
	}
}

void	select_server(void)
{
	g_net.read_fd_set = g_net.active_fd_set;
	g_net.write_fd_set = g_net.active_fd_set;
	if (select (FD_SETSIZE, &(g_net.read_fd_set), &(g_net.write_fd_set), NULL, &g_timeout) < 0)
		die();

	for (int i = 0; i < FD_SETSIZE; ++i)
	{
		if (FD_ISSET (i, &(g_net.read_fd_set)))
		{
			if (i == g_net.fd)
				accept_server();
			else
			{
				if (!read_server(i))
				{
					close (i);
					FD_CLR (i, &(g_net.active_fd_set));
					ft_memset(&g_clients[i], 0, sizeof(t_client));
				}
				else
				{
					int alloc_size = 0;
					char *str = NULL;

					do_i_have_something_to_do(i);
					for(int j = 0; j <= FD_SETSIZE; j++) {
						// send to everyone!
						if (FD_ISSET(j, &(g_net.write_fd_set))) {
							// except the listener and ourselves
							if (j != 0 && j != i && j != g_net.fd) {

								// debug_client(i);

								if (g_clients[i].state == TRANSIT)
								{
									alloc_size = size_buf(&(g_clients[i].buf)) + LEN(g_clients[i].nickname) + 3;
									str = (char*)malloc(alloc_size);
									ft_bzero(str, alloc_size);
									// printf("< -- >\n");
									// debug_clients();
									// printf("log malloc size : (%d)%d\n", size_buf(&(g_clients[i].buf)), alloc_size);
									ft_strcpy(str, g_clients[i].nickname);
									ft_strcpy(str + LEN(g_clients[i].nickname), ":\t");

									read_buf(str + LEN(g_clients[i].nickname) + 2, &(g_clients[i].buf));
								}
								else
								{
									alloc_size = size_buf(&(g_clients[i].buf));
									str = (char*)malloc(size_buf(&(g_clients[i].buf)));
									ft_bzero(str, size_buf(&(g_clients[i].buf)) + 1);

									read_buf(str, &(g_clients[i].buf));
								}


								// ft_strndup((g_clients[i].buf.buf + g_clients[i].buf.head), g_clients[i].buf.tail - g_clients[i].buf.head);
								if (send(j, str, LEN(str), 0) == -1) {
									printf("send error\n");
								}
							}
						}
					}

					// int test = 0;
					// while (test < alloc_size)
					// {
					// 	if (str[test] == '\n')
					// 		g_clients[i].state = ONLINE;

					// 	test += 1;
					// }
					int index = g_clients[i].buf.tail - 1;
					if (index == -1)
						index = CIRC_BUFSIZE - 2;

					printf("%s -- %d[%c]\n", g_clients[i].buf.buf, index, g_clients[i].buf.buf[index]);

					if (g_clients[i].buf.buf[index] == '\n')// && size_buf(&(g_clients[i].buf)) != CIRC_BUFSIZE - 2)
						g_clients[i].state = ONLINE;
					g_clients[i].buf.head = g_clients[i].buf.tail;

				}
			}
		}
	}
}

void	init_server(char *port)
{
	if ((g_net.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		die();
	___bzero(&(g_net.my_addr), sizeof(struct sockaddr_in));
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
