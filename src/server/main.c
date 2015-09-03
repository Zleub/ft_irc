/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 11:48:35 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 12:22:53 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

void	init(char *port)
{
	if ((g_net.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		die();
	ft_bzero(&(g_net.my_addr), sizeof(struct sockaddr_in));
	g_net.my_addr.sin_family = AF_INET;
	g_net.my_addr.sin_addr.s_addr = INADDR_ANY;
	g_net.my_addr.sin_port = htons(ft_atoi(port));

	int option = 1;
	if(setsockopt(g_net.fd,SOL_SOCKET,(SO_REUSEADDR), &option, sizeof(option)) < 0)
		die();

	if (bind(g_net.fd, (struct sockaddr *)&(g_net.my_addr),
		sizeof(struct sockaddr_in)) == -1)
		die();
	if (listen(g_net.fd, 0) == -1)
		die();

	FD_ZERO (&(g_net.active_fd_set));
	FD_ZERO (&(g_net.write_fd_set));
	FD_ZERO (&(g_net.read_fd_set));
	FD_SET (g_net.fd, &(g_net.active_fd_set));
	// FD_SET (0, &(g_net.active_fd_set));
	// g_clients[0].state = ONLINE;
}

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

char	*g_array[STATELEN] = {
	"OFFLINE",
	"PENDING",
	"ONLINE",
	"WRITING",
	"TRANSIT",
	"COMMAND"
};

void	debug_client(t_client *c) {
	printf("%d\t| %s\tH: %d,\tT: %d,\t: <%s>\n",
		c->id,
		g_array[c->state],
		c->buf.head,
		c->buf.tail,
		c->buf.buf
	);

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

int		write_buffer(t_circ_buf *buf, char str[CIRC_BUFSIZE])
{
	int j = 0;

	while (str[j] && j < CIRC_BUFSIZE)
	{
		buf->buf[buf->tail] = str[j];
		buf->tail = (buf->tail + 1) % CIRC_BUFSIZE;
		j = j + 1;
	}
	return (j);
}

int		read_buffer(t_circ_buf *buf, char str[CIRC_BUFSIZE])
{

	if (buf->head == buf->tail)
	{
		int	i = 0;
		while (i < CIRC_BUFSIZE)
		{
			int index = (buf->head + i) % CIRC_BUFSIZE;
			str[i] = buf->buf[index];
			i = i + 1;
		}

	}
	else
	{
		int	i = 0;
		while (buf->head != buf->tail)
		{
			str[i] = buf->buf[buf->head];
			buf->head = (buf->head + 1) % CIRC_BUFSIZE;
			i = i + 1;
		}
	}
	return (0);
}

int		getrandomint(int min, int max)
{
	return (random() % (max - min)) + min;
}

struct timeval		g_timeout = {
	0,
	5000
};

void	client_leave(int fd)
{
	printf("<--- CLIENT LEAVE %d --->\n", fd);
	close (fd);
	FD_CLR (fd, &(g_net.active_fd_set));
	ft_memset(&g_clients[fd], 0, sizeof(t_client));
}

int		client_read(int index)
{
	int n;
	char buf[CIRC_BUFSIZE + 1];

	printf("Reading %d\n", index);
	ft_bzero(buf, CIRC_BUFSIZE + 1);
	n = 0;
	if ((n = read(index, buf, CIRC_BUFSIZE)) < 1)
		return (0);
	else
	{
		write_buffer(&g_clients[index].buf, buf);
		printf("Msg size: %d\n", n);
		return n;
	}
}

int		client_write(int fd_talk, int fd_listen, char *str)
{
	// char			str[CIRC_BUFSIZE + NICKNAME_SIZE + 3];
	struct s_client	*talker;

	talker = &g_clients[fd_talk];
	// ft_bzero(str, CIRC_BUFSIZE + NICKNAME_SIZE + 3);
	if (FD_ISSET(fd_listen, &(g_net.write_fd_set)))
	{
		// printf("client_write fd_talk: %d, fd_listen: %d\n", fd_talk, fd_listen);
		if (talker->state > PENDING && fd_listen != 0
			// && fd_listen != fd_talk
			&& fd_listen != g_net.fd
			&& !strcmp(g_clients[fd_talk].room, g_clients[fd_listen].room))
		{
			// ft_strcpy(str, talker->nickname);
			// ft_strcpy(str + LEN(talker->nickname), ":\t");
			// read_buffer(&(talker->buf), str + LEN(talker->nickname) + 2);

			printf("BROADCAST: I read %zu chars\n", LEN(str));
			if (send(fd_listen, str, LEN(str), 0) == -1)
				die();
		}
	}
	return (0);
}

#define COMMAND_SETSIZE 5

t_command	g_commands[COMMAND_SETSIZE] = {
	{"nick", &nick_function},
	{"join", &join_function},
	{"leave", &leave_function},
	{"who", &function_test},
	{"msg", &function_test},
};

int		do_command(int fd, char *str)
{
	int i;

	i = 0;
	// printf("do_command call : %d, <%s>\n", fd, str);
	while (i < COMMAND_SETSIZE)
	{
		if (!ft_strncmp(str + 1, g_commands[i].id, LEN(g_commands[i].id)))
			return g_commands[i].f(fd, str);
		i += 1;
	}
	return (0);
}

int		do_token(int index, char *token)
{
	printf("token for %d: <%s>#%zu\n", index, token, LEN(token));
	if (!do_command(index, token) && LEN(token) != 0)
	{
		int i = 0;

		char str[CIRC_BUFSIZE + NICKNAME_SIZE + 3];
		ft_bzero(str, CIRC_BUFSIZE + NICKNAME_SIZE + 3);
		// read_buf(str, &(g_clients[fd_talker].buf));
		ft_strcpy(str, g_clients[index].nickname);
		ft_strcpy(str + LEN(g_clients[index].nickname), ":\t");
		ft_strcpy(str + LEN(g_clients[index].nickname) + 2, token);

		// str[LEN(str)] = '\n';
		// read_buffer(&(g_clients[index].buf), str + LEN(g_clients[index].nickname) + 2);

		while (i < FD_SETSIZE) {
			client_write(index, i, str);
			i += 1;
		}
	}
	return (0);
}


int		do_business(int index)
{
	char buf[CIRC_BUFSIZE + 1];
	ft_bzero(buf, CIRC_BUFSIZE + 1);

	read_buffer(&g_clients[index].buf, buf);

	printf("LENCHECK(%zu)\n", LEN(buf));

	int i = 0;
	while (buf[i])
	{
		if (i == 0)
			do_token(index, &buf[i]);
		if (buf[i] == '\n' && !ft_isspace(buf[i + 1]))
			do_token(index, &buf[i + 1]);
		i += 1;
	}
	// printf("I got something to do for %d: <%s>\n", index, buf);
	return (0);
}

int		read_fd(int index)
{
	if (FD_ISSET (index, &(g_net.read_fd_set)))
	{
		if (index == g_net.fd)
			accept_server();
		else // if (g_clients[index].buf.tail - g_clients[index].buf.head == 0)
		{
			if (!client_read(index))
				client_leave(index);
			else
				do_business(index);
		}
		debug_clients();
	}
	return (0);
}

int		run(void)
{
	g_net.read_fd_set = g_net.active_fd_set;
	g_net.write_fd_set = g_net.active_fd_set;
	if (select (FD_SETSIZE, &(g_net.read_fd_set), &(g_net.write_fd_set), NULL, &g_timeout) < 0)
		die();
	fd_iteration(0, &read_fd);
	return (0);
}

void	__test(int sig)
{
	char s[2];
	int i;

	i = 3;
	s[0] = 4;
	s[1] = 10;
	(void)sig;
	printf("Im here\n");
	while (i < FD_SETSIZE)
	{
		// write(i, s, 2);
		close(i);
		i += 1;
	}
	close(g_net.fd);
	exit(0);
}

int		main(int ac, char *av[])
{
	(void)ac;
	(void)av;

	ft_bzero(&g_net, sizeof(g_net));
	ft_bzero(&g_clients, sizeof(g_clients));
	signal(SIGINT, &__test);
	if (ac < 2)
		init("6667");
	else if (ac < 3)
		init(av[1]);
	while (42) {
		run();
	}

	// g_clients[0].id = 10;
	// write_buffer(&g_clients[0].buf, "LONG INIT CHIA\t\t");
	//
	// char str[CIRC_BUFSIZE + 1];
	// ft_bzero(str, CIRC_BUFSIZE + 1);
	//
	//
	// debug_client(&g_clients[0]);
	// read_buffer(&g_clients[0].buf, str);
	// printf("%s\n", str);
	//
	// size_t i;
	// char stuff[CIRC_BUFSIZE];
	// for (i = 0; i < CIRC_BUFSIZE; i++) {
	// 	stuff[i] = getrandomint(65, 90);
	// }
	// write_buffer(&g_clients[0].buf, stuff);
	//
	// debug_client(&g_clients[0]);
	// read_buffer(&g_clients[0].buf, str);
	// printf("%s\n", str);
	return (0);
}
