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
#include <netinet/in.h>
#include "types.h"

int other_fd = -1;
int pleasequit;
unsigned long inet_addr();

checkother()
{
	int	s;
	long	send_magic;
	long	roll;
	long	recv_magic;
	int	yes;
	struct	sockaddr_in sin;

	yes = 1;

	/* if 1 in 7, skip it */
	if (random() % 7 == 3)
		return;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		perror("socket");
		return;
	}
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(XS("127.0.0.1"));
	sin.sin_port = htons(23357);
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) >= 0) {
		/* authentication of the "server" */
		send_magic = 0x874697;
		if (write(s, (char *)&send_magic, sizeof(send_magic)) !=
		    sizeof(send_magic)) {
			(void) close(s);
			return;
		}
		send_magic = 0;
		if (xread(s, (char *)&send_magic, sizeof(send_magic), 300) ==
		    sizeof(send_magic)) {
			(void) close(s);
			return;
		}
		if (send_magic != 0x148898) {
			(void) close(s);
			return;
		}
		
		/* randomly select whether client or server will exit */
		roll = random() >> 3;
		if (write(s, (char *)&roll, sizeof(roll)) != sizeof(roll)) {
			(void) close(s);
			return;
		}
		if (xread(s, (char *)&recv_magic, sizeof(recv_magic), 10) !=
		    sizeof(recv_magic)) {
			(void) close(s);
			return;
		}
		if (((recv_magic + roll) % 2) == 0)
			/* we lost */
			pleasequit++;
	}
	(void) close(s);
	sleep(5);

	/* open another socket at the same address so we can serve too */
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		return;
	(void) setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		(void) close(s);
		return;
	}
	(void) listen(s, 10);
	other_fd = s;
}
