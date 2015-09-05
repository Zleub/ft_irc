/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 14:53:16 by adebray           #+#    #+#             */
/*   Updated: 2015/09/05 16:37:39 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

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
	// printf("<-- NEW ENTRY %d -->\n", fd);
}

int		do_token(int index, char *token)
{
	int		i;
	char	str[CIRC_BUFSIZE + NICKNAME_SIZE + 3];

	printf("token for %d: <%s>#%zu\n", index, token, LEN(token));
	if (token[LEN(token) - 1] != '\n')
	{
		g_clients[index].buf.head -= LEN(token);
		return (0);
	}
	if (!do_command(index, token) && LEN(token) != 0)
	{
		i = 0;
		ft_bzero(str, CIRC_BUFSIZE + NICKNAME_SIZE + 3);
		ft_strcpy(str, g_clients[index].nickname);
		ft_strcpy(str + LEN(g_clients[index].nickname), ":\t");
		ft_strcpy(str + LEN(g_clients[index].nickname) + 2, token);
		while (i < FD_SETSIZE)
		{
			client_write(index, i, str);
			i += 1;
		}
	}
	return (0);
}

int		do_business(int index)
{
	int		i;
	char	buf[CIRC_BUFSIZE + 1];

	ft_bzero(buf, CIRC_BUFSIZE + 1);
	read_buffer(&g_clients[index].buf, buf);
	i = 0;
	while (buf[i])
	{
		if (i == 0)
			do_token(index, &buf[i]);
		if (buf[i] == '\n' && !ft_isspace(buf[i + 1]))
			do_token(index, &buf[i + 1]);
		i += 1;
	}
	return (0);
}

int		read_fd(int index)
{
	if (FD_ISSET(index, &(g_net.read_fd_set)))
	{
		if (index == g_net.fd)
			accept_server();
		else
		{
			if (!client_read(index))
				client_leave(index);
			else
				do_business(index);
		}
		// debug_clients();
	}
	return (0);
}
