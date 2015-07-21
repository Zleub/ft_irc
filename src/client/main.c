/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 17:59:20 by adebray           #+#    #+#             */
/*   Updated: 2015/07/21 10:03:33 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <irc.h>
#include <errno.h>

t_network		g_net;

struct timeval		g_timeout = {
	0,
	5000
};

int		diemsg(char *str)
{
	printf("error: %s | %s\n", str, strerror(errno));
	exit(-1);
}

int		client_work(int fd)
{
	char buf[1024];

	ft_bzero(buf, 1024);
	if (FD_ISSET (fd, &(g_net.read_fd_set)))
	{
		read(fd, &buf, 1024);
		printf("read: %s\n", buf);
		ft_bzero(buf, 1024);
	}
	return (0);
}

void	select_client(void)
{
	g_net.read_fd_set = g_net.active_fd_set;
	g_net.write_fd_set = g_net.active_fd_set;
	if (select (FD_SETSIZE, &(g_net.read_fd_set), &(g_net.write_fd_set), NULL, &g_timeout) < 0)
		diemsg("select");

	fd_iteration(0, &client_work);
}

int		main(void)
{

	ft_bzero(&g_net, sizeof(g_net));
	if ((g_net.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		diemsg("socket");
	g_net.my_addr.sin_family = AF_INET;
	g_net.my_addr.sin_addr.s_addr = INADDR_ANY;
	g_net.my_addr.sin_port = htons(ft_atoi("4242"));
	if (connect(g_net.fd, (struct sockaddr *)&(g_net.my_addr), sizeof(g_net.my_addr)) == -1)
		diemsg("connect");
	FD_SET (g_net.fd, &(g_net.active_fd_set));
	FD_SET (0, &(g_net.active_fd_set));
	while (42)
		select_client();
	return (0);
}
