/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 13:05:23 by adebray           #+#    #+#             */
/*   Updated: 2015/09/03 13:13:43 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <libft.h>
# include <irc.h>
# include <curses.h>
# include <errno.h>

# define CONNECT(X, Y) connect(X, (struct sockaddr *)&(Y), sizeof(Y))

WINDOW			*g_prompt;

void			client_quit(char *str);
void			client_reset();
void			prompt_erase(int *pos, char *str);
void			prompt_add(int *pos, char *str, char c);
void			prompt_validation(int *pos, char *str);
void			prompt_work(void);
int				client_connect(char *str, int port);
int				client_work(int fd);
void			select_client(void);

#endif
