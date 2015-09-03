/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 17:59:20 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 13:28:38 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

void	ft_signal(int sig)
{
	printf("signal : %d\n", sig);
	client_quit(NULL);
}

void	init(void)
{
	signal(SIGWINCH, &ft_signal);
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	timeout(0);
	ft_bzero(&g_net, sizeof(g_net));
	FD_SET(0, &(g_net.active_fd_set));
	g_prompt = newwin(5, COLS, LINES - 5, 0);
	box(g_prompt, 0, 0);
	wmove(g_prompt, 1, 1);
}

int		main(int argc, char **argv)
{
	init();
	write_header();
	if (argc == 3)
		client_connect(argv[1], ft_atoi(argv[2]));
	else if (argc == 2)
		client_connect(argv[1], 6667);
	while (42)
	{
		refresh();
		wrefresh(g_prompt);
		select_client();
	}
	client_quit(NULL);
	return (0);
}
