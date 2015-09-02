/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/02 15:44:32 by adebray           #+#    #+#             */
/*   Updated: 2015/09/02 16:32:15 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

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
