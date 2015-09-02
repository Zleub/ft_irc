/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 20:26:39 by adebray           #+#    #+#             */
/*   Updated: 2015/09/02 17:32:01 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>
#include <curses.h>

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

void	write_header(void)
{
	int		i = 0;

	while (g_header[i])
	{
		mvprintw(i, (COLS / 2) - 21, g_header[i]);
		i += 1;
	}
}
