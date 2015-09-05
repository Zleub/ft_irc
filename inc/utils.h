/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 19:36:00 by adebray           #+#    #+#             */
/*   Updated: 2015/08/17 19:09:25 by adebray          ###   ########.fr       */
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

#endif
