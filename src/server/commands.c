/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 21:09:56 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 18:16:25 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>
#define ONE_PARAM 1

int		nick_function(int fd, char *str)
{
	char *array[ONE_PARAM];

	ft_bzero(array, sizeof(array));
	fill_array(str, array, ONE_PARAM);
	if (array[0])
		ft_strncpy(g_clients[fd].nickname, array[0], NICKNAME_SIZE - 1);
	free(array[0]);
	return (1);
}

int		join_function(int fd, char *str)
{
	char *array[ONE_PARAM];

	ft_bzero(array, sizeof(array));
	fill_array(str, array, ONE_PARAM);
	if (array[0])
	{
		// printf("join function %s\n", array[0]);
		ft_strncpy(g_clients[fd].room, array[0], ROOMNAME_SIZE - 1);
	}
	free(array[0]);
	g_clients[fd].state = ONLINE;
	return (1);
}

int		leave_function(int fd, char *str)
{
	(void)str;
	ft_bzero(g_clients[fd].room, ROOMNAME_SIZE);
	g_clients[fd].state = PENDING;
	return (1);
}

int		who_function(int fd, char *str)
{
	int		i;
	char	buf[NICKNAME_SIZE + 1];

	(void)fd;
	(void)str;
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (g_clients[i].state == ONLINE && !ft_strcmp(g_clients[i].room, g_clients[fd].room))
		{
			ft_bzero(buf, NICKNAME_SIZE + 1);
			ft_strcpy(buf, g_clients[i].nickname);
			buf[LEN(buf)] = '\n';
			send(fd, buf, LEN(buf), 0);
		}
		i = i + 1;
	}
	return (1);
}

int		msg_function(int fd, char *str)
{
	char	message[CIRC_BUFSIZE + NICKNAME_SIZE + 3];
	char	nick_buf[NICKNAME_SIZE + 1];
	int		i;
	int		j;
	int		k;

	i = 0;
	ft_bzero(nick_buf, NICKNAME_SIZE + 1);
	while ((ft_isspace(str[i - 1]) && !ft_isspace(str[i])) == 0)
		i += 1;
	j = 0;
	while (!ft_isspace(str[i + j]))
	{
		nick_buf[j] = str[i + j];
		j += 1;
	}
	while (ft_isspace(str[i + j]))
		i += 1;

	printf("Server-side, msg function: %d to %s <%s>\n", fd, nick_buf, str + i + j);
	k = 0;
	while (k < FD_SETSIZE)
	{
		if (!ft_strcmp(nick_buf, g_clients[k].nickname) && g_clients[k].state != OFFLINE)
		{
			ft_bzero(message, CIRC_BUFSIZE + NICKNAME_SIZE + 3);
			ft_strcpy(message, g_clients[fd].nickname);
			ft_strcpy(message + LEN(g_clients[fd].nickname), ":\t");
			ft_strcpy(message + LEN(g_clients[fd].nickname) + 2, str + i + j);

			send(k, message, LEN(message), 0);
		}
		k += 1;
	}

	return (1);
}
