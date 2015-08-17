/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/17 18:06:57 by adebray           #+#    #+#             */
/*   Updated: 2015/08/17 18:46:12 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <irc.h>
#include <fcntl.h>

int main() {

	t_circ_buf	b;
	ft_bzero(&b, sizeof(b));

	printf("CIRC_BUFSIZE: %d\n\n", CIRC_BUFSIZE);

	size_t size = 12;

	char extract[CIRC_BUFSIZE];

	int fd;
	if ((fd = open("/dev/random", O_RDONLY)) == -1) {
		printf("Cant open random\n");
		return (0);
	}

	char str[size];
	read(fd, str, size);

	int i = 0;
	while (i < 42000) {
		printf("1 H:%d - T:%d: <%s>\n", b.head, b.tail, b.buf);
		write_buf(&b, str, LEN(str));
		printf("2 H:%d - T:%d: <%s>\n", b.head, b.tail, b.buf);
		ft_bzero(extract, CIRC_BUFSIZE);
		read_buf(extract, &b);
		printf("extract: %s\n", extract);
		if (LEN(extract) != size + 1)
			printf("ALERT\n");
		printf("3 H:%d - T:%d: <%s>\n", b.head, b.tail, b.buf);
		i += 1;
	}

    return 0;
}
