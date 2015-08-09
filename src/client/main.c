/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 17:59:20 by adebray           #+#    #+#             */
/*   Updated: 2015/08/09 16:37:23 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <irc.h>
#include <curses.h>
#include <errno.h>

t_network		g_net;

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
		// printw("Connection at %s:%d failed\n", str, port);
		client_quit("HEREIAM");
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
//	printf("Connected to %s:%d\n", str, port);
	return (0);
}

void	fill_array(char *str, char **str_array)
{
	int i;
	int j;

	i = 2;
	j = 0;
	(void)str_array;
	while (i < (int)LEN(str))
	{
		if (ft_isspace(str[i - 1]) && !ft_isspace(str[i]))
		{
			if (j < 2)
				str_array[j] = ft_strndup(&str[i], get_size(&str[i]));
			j += 1;
		}
		i += 1;
	}
}

int		client_work(int fd)
{
	(void)fd;
	// char str[12];
	// getstr(str);
	// printw("'%s'\n", str);

	// char *buf_array[2];
	char buf[CIRC_BUFSIZE - 1];

	ft_bzero(buf, CIRC_BUFSIZE - 1);
	if (FD_ISSET (fd, &(g_net.read_fd_set)))
	{
		if (fd == 0) { // INPUT FORM NCURSES
			int nbr = getch();
			mvprintw(fd, 0, "%d: %d\n", fd, nbr);
		} else {
			int ret = read(fd, &buf, CIRC_BUFSIZE - 2);
			(void)ret;
			mvprintw(fd, 0, "%d: %s\n", fd, buf);
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

	WINDOW * local_win = newwin(0, 0, 10, 10);
	box(local_win, 0, 0);
	wrefresh(local_win);
	refresh();

	FD_SET (0, &(g_net.active_fd_set));

	if (argc == 3)
		client_connect(argv[1], ft_atoi(argv[2]));
	else if (argc == 2)
		client_connect(argv[1], 6667);

	// printw("%d\n", g_net.fd);
	printw("-> %d\n", write(g_net.fd, "/join test\n", 11));
	printw("-> %d\n", write(g_net.fd, "caca\n", 5));

	// client_quit(ft_itoa(g_net.fd));
	while (42) {
		// fflush(stdout);
		// fflush(stdin);
		refresh();
		select_client();
	}
	client_quit(NULL);
	return (0);
}
