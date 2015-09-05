/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 20:26:39 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 14:23:19 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

char *g_header[15] = {
	"                ,     :     ,\n",
	"          '.    ;    :    ;    ,`\n",
	"      '-.   '.   ;   :   ;   ,`   ,-`\n",
	"   \"-.   '-.  '.  ;  :  ;  ,`  ,-`   ,-\"\n",
	"      \"-.   '-. '. ; : ; ,` ,-`   ,-\"\n",
	" '\"--.   '\"-.  '-.'  '  `.-`  ,-\"`   ,--\"`\n",
	"      '\"--.  '\"-.   ...   ,-\"`  ,--\"`\n",
	"           '\"--.  .:::::.  ,--\"`\n",
	"------------------:::::::------------------\n",
	"                   ~~~~~\n",
	"                    ~~~\n",
	"                     ~\n",
	"\n",
	"           IRC SUNRISE WooOT\n",
	NULL
};

int		diewitherror(char *error)
{
	printf("%s", error);
	exit(-1);
}

int		get_size(char *str)
{
	int i;

	i = 0;
	while (!ft_isspace(str[i]))
		i += 1;
	return (i);
}

void	write_header(void)
{
	int		i;

	i = 0;
	while (g_header[i])
	{
		mvprintw(i, (COLS / 2) - 21, g_header[i]);
		i += 1;
	}
}

void	client_quit(char *str)
{
	if (g_net.fd != 0)
		close(g_net.fd);
	endwin();
	if (str != NULL)
		printf("%s\n", str);
	exit(0);
}

void	client_reset(void)
{
	if (g_net.fd != 0)
	{
		close(g_net.fd);
		g_net.fd = 0;
	}
}
