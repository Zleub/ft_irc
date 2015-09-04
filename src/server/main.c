/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 11:48:35 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 14:58:39 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

void	init(char *port)
{
	int option;

	if ((g_net.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		die();
	ft_bzero(&(g_net.my_addr), sizeof(struct sockaddr_in));
	g_net.my_addr.sin_family = AF_INET;
	g_net.my_addr.sin_addr.s_addr = INADDR_ANY;
	g_net.my_addr.sin_port = htons(ft_atoi(port));
	option = 1;
	if (setsockopt(g_net.fd, SOL_SOCKET, SO_REUSEADDR, &option,
		sizeof(option)) < 0)
		die();
	if (bind(g_net.fd, (struct sockaddr *)&(g_net.my_addr),
		sizeof(struct sockaddr_in)) == -1)
		die();
	if (listen(g_net.fd, 0) == -1)
		die();
	FD_ZERO(&(g_net.active_fd_set));
	FD_ZERO(&(g_net.write_fd_set));
	FD_ZERO(&(g_net.read_fd_set));
	FD_SET(g_net.fd, &(g_net.active_fd_set));
}

struct timeval		g_timeout = {
	0,
	5000
};

int		run(void)
{
	g_net.read_fd_set = g_net.active_fd_set;
	g_net.write_fd_set = g_net.active_fd_set;
	if (select(FD_SETSIZE, &(g_net.read_fd_set), &(g_net.write_fd_set),
		NULL, &g_timeout) < 0)
		die();
	fd_iteration(0, &read_fd);
	return (0);
}

void	test(int sig)
{
	char	s[2];
	int		i;

	i = 3;
	s[0] = 4;
	s[1] = 10;
	(void)sig;
	while (i < FD_SETSIZE)
	{
		close(i);
		i += 1;
	}
	close(g_net.fd);
	exit(0);
}

int		main(int ac, char *av[])
{
	ft_bzero(&g_net, sizeof(g_net));
	ft_bzero(&g_clients, sizeof(g_clients));
	signal(SIGINT, &test);
	if (ac < 2)
		init("6667");
	else if (ac < 3)
		init(av[1]);
	while (42)
		run();
	return (0);
}
