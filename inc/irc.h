/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 19:30:18 by adebray           #+#    #+#             */
/*   Updated: 2015/07/20 17:53:15 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_H
# define IRC_H

# include <libft.h>
# include <stdio.h>
# include <netinet/ip.h>
# include <arpa/inet.h>

typedef struct sockaddr_in		t_sockin;
typedef struct s_network		t_network;
typedef struct s_client			t_client;

struct							s_network
{
	int							fd;
	int							client_nbr;
	t_sockin					my_addr;
	fd_set						active_fd_set;
	fd_set						read_fd_set;
	fd_set						write_fd_set;
};

t_network						g_net;

enum							e_state
{
	OFFLINE,
	ONLINE,
	PENDING,
	WRITING,
	TRANSIT,
	COMMAND,
	STATELEN
};

# define NICKNAME_SIZE 10

struct							s_client
{
	int							id;
	int							state;
	char						nickname[NICKNAME_SIZE];
	struct sockaddr				addr;
	socklen_t					addr_size;
	struct s_circ_buf			buf;
};

t_client						g_clients[FD_SETSIZE];

int								die(void);
int								diewitherror(char *error);

int								textreturn(char *text, int ret);
void							debug_clients(void);
void							debug_client(int fd);

void							client_leave(int fd);
int								client_write(int fd_talker, int fd_listener);
int								client_read(int fd);

typedef int						(*t_function)(int);
typedef int						(*t_dfunction)(int, int);

void							fd_iteration(int i, t_function f);
void							fd_diteration(int i, int j, t_dfunction f);

#endif
