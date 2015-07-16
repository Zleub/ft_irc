/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 16:14:37 by adebray           #+#    #+#             */
/*   Updated: 2015/07/16 21:44:10 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

typedef struct sockaddr_in		t_sockin;
typedef struct s_network		t_network;
typedef struct s_client			t_client;

struct s_network
{
	int			fd;
	t_sockin	my_addr;
	fd_set		active_fd_set;
	fd_set		read_fd_set;
	fd_set		write_fd_set;
};

t_network		g_net;

#define CIRC_BUFSIZE 12

struct s_circ_buf
{
	char	buf[CIRC_BUFSIZE];
	int		head;
	int		tail;
};

int		write_buf(struct s_circ_buf *ptr, char *mem, int size)
{
	int		i = 0;

	while (i < size)
	{
		ptr->buf[(i + ptr->head) % (CIRC_BUFSIZE - 1)] = mem[i];
		i += 1;
	}
	ptr->head = (i + ptr->head) % (CIRC_BUFSIZE - 1);
	return i;
}

struct s_client
{
	int					id;
	struct sockaddr		addr;
	socklen_t			addr_size;
	struct s_circ_buf	buf;
};

t_client		g_clients[FD_SETSIZE];

void	debug_clients()
{
	for (int i = 0; i < FD_SETSIZE; i += 1)
	{
		if (g_clients[i].id != 0)
		{
			ft_printf("%d,\tH: %d,\tT: %d,\t: %s\n", i, g_clients[i].buf.head, g_clients[i].buf.tail, g_clients[i].buf.buf);
		}
	}
}

int		die(void)
{
	ft_printf("die function");
	exit(-1);
}

int		read_server(int fd)
{
	char	buf[255];
	int		n;

	ft_memset(buf, 0, 255);
	if (!(n = read(fd, buf, 254)))
	{
		ft_putstr("EXIT WITHOUT TEXT\n");
		return (0);
	}
	else if (n < 0)
	{
		ft_putstr("read flag 2\n");
		return (0);
	}
	else
	{
		ft_putstr("reading : \n\t");
		ft_putstr(buf);
		// ft_memcpy((g_clients[fd].buf.buf + g_clients[fd].buf.head), buf, n - 1);
		write_buf(&(g_clients[fd].buf), buf, n - 1);

		if (!ft_strcmp(buf, "debug\n"))
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
	g_clients[fd].id = fd;
	ft_printf("<-- NEW ENTRY %d -->\n", fd);
}

void	select_server(void)
{
	g_net.read_fd_set = g_net.active_fd_set;
	if (select (FD_SETSIZE, &(g_net.read_fd_set), NULL, NULL, NULL) < 0)
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
					g_clients[i].id = 0;
				}
			}
		}
	}
}

void	init_server(char *port)
{
	if ((g_net.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		die();
	ft_memset(&(g_net.my_addr), 0, sizeof(struct sockaddr_in));
	g_net.my_addr.sin_family = AF_INET;
	g_net.my_addr.sin_addr.s_addr = INADDR_ANY;
	g_net.my_addr.sin_port = htons(ft_atoi(port));
	if (bind(g_net.fd, (struct sockaddr *)&(g_net.my_addr), sizeof(struct sockaddr_in)) == -1)
		die();
	if (listen(g_net.fd, 0) == -1)
		die();
	FD_ZERO (&(g_net.active_fd_set));
	FD_SET (0, &(g_net.active_fd_set));
	g_clients[0].id = 1440;
	FD_SET (g_net.fd, &(g_net.active_fd_set));
	select_server();
}

int		main(int ac, char *av[])
{
	ft_memset(&g_net, 0, sizeof(g_net));
	ft_memset(&g_clients, 0, sizeof(g_clients));
	for (int i = 0; i < FD_SETSIZE; ++i)
	{
		g_clients[i].id = 0;
		g_clients[i].buf.head = 0;
		g_clients[i].buf.tail = 0;
	}
	if (ac == 2) {
		debug_clients();
		init_server(av[1]);
		while (42) {
			select_server();
			debug_clients();
		}
	}
	return (0);
}
