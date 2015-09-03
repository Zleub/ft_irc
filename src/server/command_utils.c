/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 14:26:28 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 17:46:36 by adebray          ###   ########.fr       */
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

#define COMMAND_SETSIZE 5

t_command	g_commands[COMMAND_SETSIZE] = {
	{"nick", &nick_function},
	{"join", &join_function},
	{"leave", &leave_function},
	{"who", &who_function},
	{"msg", &msg_function},
};

int		do_command(int fd, char *str)
{
	int i;

	i = 0;
	while (i < COMMAND_SETSIZE)
	{
		if (!ft_strncmp(str + 1, g_commands[i].id, LEN(g_commands[i].id)))
			return (g_commands[i].f(fd, str));
		i += 1;
	}
	return (0);
}
