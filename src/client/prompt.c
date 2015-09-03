/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 13:11:18 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 13:30:43 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

int		command(char *buf)
{
	char	*tmp[2];
	int		cmp[2];

	if (!strncmp(buf, "/connect", 8))
	{
		ft_bzero(cmp, sizeof(cmp));
		while (buf[cmp[0]])
		{
			if (ft_isspace(buf[cmp[0]]) && !ft_isspace(buf[cmp[0] + 1]))
			{
				tmp[cmp[1]] = &buf[cmp[0] + 1];
				cmp[1] += 1;
			}
			if (ft_isspace(buf[cmp[0]]))
				buf[cmp[0]] = 0;
			cmp[0] += 1;
		}
		if (cmp[1] == 1)
			return (client_connect(tmp[0], 0));
		if (cmp[1] == 2)
			return (client_connect(tmp[0], ft_atoi(tmp[1])));
	}
	return (0);
}

void	prompt_erase(int *pos, char *str)
{
	if ((*pos) > 0)
	{
		(*pos) -= 1;
		mvwprintw(g_prompt, 1, (*pos) + 1, " ");
		wmove(g_prompt, 1, (*pos) + 1);
		str[(*pos)] = '\0';
	}
}

void	prompt_add(int *pos, char *str, char c)
{
	mvwprintw(g_prompt, 1, (*pos) + 1, "%c", c);
	str[(*pos)] = c;
	(*pos) += 1;
}

void	prompt_validation(int *pos, char *str)
{
	if (!command(str))
	{
		str[(*pos)] = 10;
		write(g_net.fd, str, LEN(str));
	}
	(*pos) = 0;
	ft_bzero(str, 1024);
	wclear(g_prompt);
	box(g_prompt, 0, 0);
	wmove(g_prompt, 1, 1);
}

void	prompt_work(void)
{
	static int	j;
	static char	str[1024];
	int			nbr;

	nbr = getch();
	if (nbr == 127)
		prompt_erase(&j, str);
	else if (nbr == 13)
		prompt_validation(&j, str);
	else
		prompt_add(&j, str, nbr);
}
