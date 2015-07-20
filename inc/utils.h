/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 19:36:00 by adebray           #+#    #+#             */
/*   Updated: 2015/07/20 06:55:16 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define LEN(x) ft_strlen(x)

typedef struct s_read		t_read;

struct						s_read
{
	int						size;
	int						index;
	int						fd;
	char					*read;
	struct s_read			*next;
};

# define CIRC_BUFSIZE 12

typedef struct s_circ_buf	t_circ_buf;

struct						s_circ_buf
{
	char					buf[CIRC_BUFSIZE];
	int						head;
	int						tail;
};

#endif
