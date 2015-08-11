/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 21:07:13 by adebray           #+#    #+#             */
/*   Updated: 2015/08/10 15:54:20 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

#define COMMAND_SETSIZE 5

t_command	g_commands[COMMAND_SETSIZE] = {
	{"nick", &nick_function},
	{"join", &join_function},
	{"leave", &leave_function},
	{"who", &function_test},
	{"msg", &function_test},
};

int		do_i_have_something_to_do(int fd)
{
	static char		test[COMMAND_BUFSIZE];

	if (g_clients[fd].buf.buf[g_clients[fd].buf.head] == '/'
		&& g_clients[fd].state != WRITING && g_clients[fd].state != COMMAND)
	{
		ft_bzero(test, COMMAND_BUFSIZE);
		g_clients[fd].state = COMMAND;
	}
	if (g_clients[fd].state == COMMAND)
	{
		int nbr;

		nbr = 0;
		printf("CACATEST\n");
		if (LEN(test) == 0)
			nbr = read_buf(test, &g_clients[fd].buf);
		else
			nbr = read_buf(&test[LEN(test)], &g_clients[fd].buf);

		printf("COMMAND: I read %d chars <%s>\n", nbr, test);
		g_clients[fd].buf.head = nbr + 1;
		if (test[LEN(test) - 1] == '\n')
			do_command(fd, test);
		return (0);
	}
	return (1);
}

int		do_command(int fd, char *str)
{
	int i;

	i = 0;
	printf("do_command call : %d, <%s>\n", fd, str);
	while (i < COMMAND_SETSIZE)
	{
		if (!ft_strncmp(str + 1, g_commands[i].id, LEN(g_commands[i].id)))
			g_commands[i].f(fd, str);
		i += 1;
	}
	return (0);
}
