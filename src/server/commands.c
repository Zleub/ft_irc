/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 21:09:56 by adebray           #+#    #+#             */
/*   Updated: 2015/08/10 01:31:54 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

int		get_size(char *str)
{
	int i;

	i = 0;
	while (!ft_isspace(str[i]))
		i += 1;
	return (i);
}

void	fill_array(char *str, char **str_array, int n)
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
			if (j < n)
				str_array[j] = ft_strndup(&str[i], get_size(&str[i]));
			j += 1;
		}
		i += 1;
	}
}

#define ONE_PARAM 1

int		nick_function(int fd, char *str)
{
	char *array[ONE_PARAM];

	ft_bzero(array, sizeof(array));
	fill_array(str, array, ONE_PARAM);
	if (array[0])
		ft_strncpy(g_clients[fd].nickname, array[0], NICKNAME_SIZE - 1);
	return (0);
}

int		join_function(int fd, char *str)
{
	char *array[ONE_PARAM];

	fill_array(str, array, ONE_PARAM);
	if (array[0]) {
		printf("join function %s\n", array[0]);
		ft_strncpy(g_clients[fd].room, array[0], ROOMNAME_SIZE - 1);
	}
	g_clients[fd].state = ONLINE;
	return (0);
}

int		leave_function(int fd, char *str)
{
	(void)str;
	ft_bzero(g_clients[fd].room, ROOMNAME_SIZE);
	g_clients[fd].state = PENDING;
	return (0);
}

int		function_test(int fd, char *str)
{
	printf("This is function_test with (%d)%s\n", fd, str);
	return (0);
}
