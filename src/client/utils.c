/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 20:26:39 by adebray           #+#    #+#             */
/*   Updated: 2015/07/22 20:32:24 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

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
	printf("                ,     :     ,\n");
	printf("          '.    ;    :    ;    ,`\n");
	printf("      '-.   '.   ;   :   ;   ,`   ,-`\n");
	printf("   \"-.   '-.  '.  ;  :  ;  ,`  ,-`   ,-\"\n");
	printf("      \"-.   '-. '. ; : ; ,` ,-`   ,-\"\n");
	printf(" '\"--.   '\"-.  '-.'  '  `.-`  ,-\"`   ,--\"`\n");
	printf("      '\"--.  '\"-.   ...   ,-\"`  ,--\"`\n");
	printf("           '\"--.  .:::::.  ,--\"`\n");
	printf("------------------:::::::------------------\n");
	printf("                   ~~~~~\n                    ~~~\n");
	printf("                     ~\n");
	printf("\n");
	printf("           IRC SUNRISE WooOT\n");
}
