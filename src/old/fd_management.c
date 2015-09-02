/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 00:29:25 by adebray           #+#    #+#             */
/*   Updated: 2015/07/20 00:30:53 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <irc.h>

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

void	fd_diteration(int i, int j, t_dfunction f)
{
	if (j >= FD_SETSIZE)
		return ;
	else
	{
		f(i, j);
		fd_diteration(i, j + 1, f);
		return ;
	}
}
