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

extern int errno;
extern struct host *me;

/*
 * Make a port to which the (given) other host can connect.
 * Choose a random number for verification.
 * Store the file descriptor through afd, the port through
 * aport, the magic number through amagic, and my canonical
 * host address (as far as otherhost is concerned) through
 * amyaddr.
 *
 * Return 1 for success, 0 for failure.
 */
int
makemagic(otherhost, amyaddr, aport, amagic, afd)
	struct host *otherhost;
	u_long *amyaddr;
	int *aport;
	long *amagic;
	int *afd;
{
	int s, i, sz;
	struct sockaddr_in addr, myaddr;

	/* choose magic number */
	*amagic = random() & 0x00ffffff;

	/*
	 * Set myaddr to my primary address; then try to
	 * connect to his telnet port so that we can see
	 * what my canonical address is as far as he is concerned.
	 */
	bzero((char *)&myaddr, sizeof(myaddr));
	myaddr.sin_addr.s_addr = me->addrs[0];
	for (i = 0; i < 6; i++) {
		if (otherhost->addrs[i] == 0)
			continue;
		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s < 0)
			return 0;
		bzero((char *)&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(23);	/* telnet */
		addr.sin_addr.s_addr = otherhost->addrs[i];
		errno = 0;
		if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) != -1) {
			/* made it; get canonical address */
			sz = sizeof(myaddr);
			(void) getsockname(s, (struct sockaddr *)&myaddr, &sz);
			(void) close(s);
			break;
		} else
			(void) close(s);
	}
	*amyaddr = myaddr.sin_addr.s_addr;

	/* try (up to 1024 times!) to get a socket for him */
	for (i = 0; i < 1024; i++) {
		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s < 0)
			return 0;
		bzero((char *)&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(random() % 32767);
		if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) != -1) {
			/* got it */
			(void) listen(s, 10);
			*aport = addr.sin_port;
			*afd = s;
			return 1;
		}
		(void) close(s);
	}
	/* no luck */
	return 0;
}
