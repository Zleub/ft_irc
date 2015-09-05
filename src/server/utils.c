/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 15:44:32 by adebray           #+#    #+#             */
/*   Updated: 2015/09/05 19:03:14 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

int		getrandomint(int min, int max)
{
	return (random() % (max - min)) + min;
}

int		die(void)
{
	exit(0);
	return (1);
}

void	fd_iteration(int i, t_function f)
{
	if (i >= FD_SETSIZE)
		return ;
	else
	{
		f(i);
		fd_iteration(i + 1, f);
		return ;
	}
}

void	send_private_message(int fd, char *nick_buf, char *str)
{
	char	message[CIRC_BUFSIZE + NICKNAME_SIZE + 3];
	int		k;

	k = 0;
	while (k < FD_SETSIZE)
	{
		if (!ft_strcmp(nick_buf, g_clients[k].nickname)
		&& g_clients[k].state != OFFLINE)
		{
			ft_bzero(message, CIRC_BUFSIZE + NICKNAME_SIZE + 3);
			ft_strcpy(message, g_clients[fd].nickname);
			ft_strcpy(message + LEN(g_clients[fd].nickname), ":\t");
			ft_strcpy(message + LEN(g_clients[fd].nickname) + 2, str);
			send(k, message, LEN(message), 0);
		}
		k += 1;
	}
}
