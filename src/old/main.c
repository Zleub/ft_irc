/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 16:14:37 by adebray           #+#    #+#             */
/*   Updated: 2015/08/17 19:46:03 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

// struct timeval		g_timeout = {
// 	0,
// 	5000
// };
//
// void	accept_server(void)
// {
// 	char	*tmp;
// 	int		fd;
//
// 	fd = 0;
// 	if ((fd = accept(g_net.fd, &(g_clients[fd].addr),
// 		&(g_clients[fd].addr_size))) == -1)
// 		die();
// 	FD_SET(fd, &(g_net.active_fd_set));
// 	g_clients[fd].state = PENDING;
// 	g_clients[fd].id = g_net.client_nbr++;
// 	ft_strcpy(g_clients[fd].nickname, "guest_");
// 	tmp = ft_itoa(g_net.client_nbr);
// 	ft_strcpy(g_clients[fd].nickname + 6, tmp);
// 	free(tmp);
// 	printf("<-- NEW ENTRY %d -->\n", fd);
// }
//
// void	do_business(int fd_talker)
// {
// 	printf("do_business: %d\n", fd_talker);
// 	if (do_i_have_something_to_do(fd_talker)) {
// 		// fd_diteration(fd_talker, 0, &client_write);
//
// 		char str[CIRC_BUFSIZE + NICKNAME_SIZE + 3];
// 		ft_bzero(str, CIRC_BUFSIZE + NICKNAME_SIZE + 3);
// 		// read_buf(str, &(g_clients[fd_talker].buf));
// 		ft_strcpy(str, g_clients[fd_talker].nickname);
// 		ft_strcpy(str + LEN(g_clients[fd_talker].nickname), ":\t");
// 		read_buf(str + LEN(g_clients[fd_talker].nickname) + 2, &(g_clients[fd_talker].buf));
//
// 		int i = 0;
// 		while (i < FD_SETSIZE) {
// 			client_write(fd_talker, i, str);
// 			i += 1;
// 		}
// 	}
// }
//
// int		do_i_have_something_to_read(int fd)
// {
// 	if (FD_ISSET (fd, &(g_net.read_fd_set)))
// 	{
// 		if (fd == g_net.fd)
// 			accept_server();
// 		else if (g_clients[fd].buf.tail - g_clients[fd].buf.head == 0)
// 		{
// 			if (!client_read(fd))
// 				client_leave(fd);
// 			// else {
// 			// 	do_business(fd);
// 			// }
// 		}
// 	}
// 	return (0);
// }
//
// void	select_server(void)
// {
// 	g_net.read_fd_set = g_net.active_fd_set;
// 	g_net.write_fd_set = g_net.active_fd_set;
// 	if (select (FD_SETSIZE, &(g_net.read_fd_set), &(g_net.write_fd_set),
// 		NULL, &g_timeout) < 0)
// 		die();
// 	fd_iteration(0, &do_i_have_something_to_read);
//
// 	int i = 0;
// 	while (i < FD_SETSIZE) {
// 		if (g_clients[i].buf.tail - g_clients[i].buf.head != 0) {
// 			do_business(i);
// 		}
// 		i += 1;
// 	}
// }
//
// void	init_server(char *port)
// {
// 	if ((g_net.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
// 		die();
// 	ft_bzero(&(g_net.my_addr), sizeof(struct sockaddr_in));
// 	g_net.my_addr.sin_family = AF_INET;
// 	g_net.my_addr.sin_addr.s_addr = INADDR_ANY;
// 	g_net.my_addr.sin_port = htons(ft_atoi(port));
//
// 	int option = 1;
// 	if(setsockopt(g_net.fd,SOL_SOCKET,(SO_REUSEADDR), &option, sizeof(option)) < 0)
// 		die();
//
// 	if (bind(g_net.fd, (struct sockaddr *)&(g_net.my_addr),
// 		sizeof(struct sockaddr_in)) == -1)
// 		die();
// 	if (listen(g_net.fd, 0) == -1)
// 		die();
// 	FD_ZERO (&(g_net.active_fd_set));
// 	FD_ZERO (&(g_net.write_fd_set));
// 	FD_ZERO (&(g_net.read_fd_set));
// 	FD_SET (g_net.fd, &(g_net.active_fd_set));
// 	FD_SET (0, &(g_net.active_fd_set));
// 	g_clients[0].state = ONLINE;
// 	select_server();
// }
//
// void	__test(int sig)
// {
// 	char s[2];
// 	int i;
//
// 	i = 3;
// 	s[0] = 4;
// 	s[1] = 10;
// 	(void)sig;
// 	printf("Im here\n");
// 	while (i < FD_SETSIZE)
// 	{
// 		// write(i, s, 2);
// 		close(i);
// 		i += 1;
// 	}
// 	close(g_net.fd);
// 	exit(0);
// }

// int		main(int ac, char *av[])
// {
// 	ft_memset(&g_net, 0, sizeof(g_net));
// 	ft_memset(&g_clients, 0, sizeof(t_client) * FD_SETSIZE);
// 	signal(SIGINT, &__test);
// 	if (ac < 2)
// 		init_server("6667");
// 	else if (ac < 3)
// 		init_server(av[1]);
// 	while (42) {
// 		// debug_client(0);
// 		// debug_clients();
// 		select_server();
// 	}
// 	return (0);
// }

int		main(int ac, char *av[])
{
	printf("caca\n");
	return (0);
}
