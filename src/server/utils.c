/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 15:44:32 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 14:46:13 by adebray          ###   ########.fr       */
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
