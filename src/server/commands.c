/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 21:09:56 by adebray           #+#    #+#             */
/*   Updated: 2015/09/05 18:37:59 by adebray          ###   ########.fr       */
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
	char message[ROOMNAME_SIZE + 10];
	char *array[ONE_PARAM];

	ft_bzero(array, sizeof(array));
	fill_array(str, array, ONE_PARAM);
	if (array[0] != NULL && strcmp("", array[0]))
	{
		ft_bzero(g_clients[fd].room, ROOMNAME_SIZE);
		ft_strncpy(g_clients[fd].room, array[0], ROOMNAME_SIZE - 1);
		ft_bzero(message, NICKNAME_SIZE + 10);
		ft_strcpy(message, "Joined: ");
		ft_strcpy(message + 8, g_clients[fd].room);
		ft_strcpy(message + 8 + LEN(g_clients[fd].room), "\n");
		send(fd, message, LEN(message), 0);
		free(array[0]);
		g_clients[fd].state = ONLINE;
	}
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
		if (g_clients[i].state == ONLINE &&
			!ft_strcmp(g_clients[i].room, g_clients[fd].room))
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
	char	nick_buf[NICKNAME_SIZE + 1];
	int		i;
	int		j;

	i = 0;
	ft_bzero(nick_buf, NICKNAME_SIZE + 1);
	while (str[i] && ((ft_isspace(str[i - 1]) && !ft_isspace(str[i])) == 0))
		i += 1;
	j = 0;
	while (str[i] && !ft_isspace(str[i + j]))
	{
		nick_buf[j] = str[i + j];
		j += 1;
	}
	while (str[i] && ft_isspace(str[i + j]))
		i += 1;
	if (strcmp(str + i + j, ""))
		send_private_message(fd, nick_buf, str + i + j);
	return (1);
}
