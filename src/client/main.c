/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 17:59:20 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 12:09:43 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <irc.h>
#include <curses.h>
#include <errno.h>

t_network		g_net;
WINDOW			*prompt = NULL;

struct timeval		g_timeout = {
	0,
	5000
};

void	client_quit(char *str)
{
	if (g_net.fd != 0)
		close(g_net.fd);
	endwin();
	if (str != NULL)
		printf("%s\n", str);
	exit (0);
}

int		client_connect(char *str, int port)
{
	if (!ft_strcmp(str, "localhost"))
		str = "127.0.0.1";
	if (!port)
		port = 6667;
	if ((g_net.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		client_quit("socket");
	g_net.my_addr.sin_family = AF_INET;
	g_net.my_addr.sin_addr.s_addr = inet_addr(str);
	g_net.my_addr.sin_port = htons(port);
	if (connect(g_net.fd, (struct sockaddr *)&(g_net.my_addr),
		sizeof(g_net.my_addr)) == -1)
	{
//		INFO MANAGEMENT
		printw("Connection at %s:%d failed\n", str, port);
		if (g_net.fd != 0)
		{
			close(g_net.fd);
			g_net.fd = 0;
		}
		return (0);
	}
	// client_quit(ft_itoa(g_net.fd));
	FD_SET (g_net.fd, &(g_net.active_fd_set));

//	INFO MANAGEMENT
	printf("Connected to %s:%d\n", str, port);
	return (1);
}

int		command(char *buf)
{
	if (!strncmp(buf, "/connect", 8))
	{
		int i = 0;
		int j = 0;
		char *tmp[2];

		while (buf[i])
		{
			if (ft_isspace(buf[i]) && !ft_isspace(buf[i + 1]))
			{
				tmp[j] = &buf[i + 1];
				j += 1;
			}
			if (ft_isspace(buf[i]))
				buf[i] = 0;
			i += 1;
		}
		if (j == 2)
			return client_connect(tmp[0], 0);
		if (j == 3)
			return client_connect(tmp[0], ft_atoi(tmp[1]));
	}
	return (0);
}

int		client_work(int fd)
{
	static int i;
	static int j;
	static char str[1024];
	char buf[CIRC_BUFSIZE - 1];

	ft_bzero(buf, CIRC_BUFSIZE - 1);
	if (FD_ISSET (fd, &(g_net.read_fd_set)))
	{
		if (fd == 0)
		{
			int nbr = getch();

			if (nbr == 127)
			{
				if (j > 0)
				{
					j -= 1;
					mvwprintw(prompt, 1, j + 1, " ");
					wmove(prompt, 1, j + 1);
					str[j] = '\0';
				}
			}
			else
			{
				mvwprintw(prompt, 1, j + 1, "%c", nbr);
				str[j] = nbr;
				j += 1;
			}
			if (nbr == 13)
			{
				if (!command(str))
				{
					str[j - 1] = 10;
					write(g_net.fd, str, LEN(str));
				}
				j = 0;
				ft_bzero(str, 1024);
				wclear(prompt);
				box(prompt, 0, 0);
				wmove(prompt, 1, 1);
			}
		}
		else
		{
			int ret = read(fd, &buf, CIRC_BUFSIZE - 2);
			if (ret == 0)
				client_quit(NULL);
			mvprintw(i, 0, "%s\n", buf);
			i = (i + 1) % (LINES - 6);
		}
	}

	return (0);
}

void	select_client(void)
{
	g_net.read_fd_set = g_net.active_fd_set;
	g_net.write_fd_set = g_net.active_fd_set;
	if (select (FD_SETSIZE, &(g_net.read_fd_set), NULL, NULL, &g_timeout) < 0)
		diewitherror("select");
	fd_iteration(0, &client_work);
}

void	ft_signal(int sig)
{
	printf("signal : %d\n", sig);
	client_quit(NULL);
}

int		main(int argc, char **argv)
{
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	timeout(0);

	write_header();
	ft_bzero(&g_net, sizeof(g_net));

	FD_SET (0, &(g_net.active_fd_set));

	if (argc == 3)
		client_connect(argv[1], ft_atoi(argv[2]));
	else if (argc == 2)
		client_connect(argv[1], 6667);

	signal(SIGWINCH, &ft_signal);
	prompt = newwin(5, COLS, LINES - 5, 0);
	box(prompt, 0, 0);

	wmove(prompt, 1, 1);
	while (42) {
		refresh();
		wrefresh(prompt);
		select_client();
	}
	client_quit(NULL);
	return (0);
}
