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
#include <netdb.h>
#include "types.h"

/*
 * Fill in names and addresses for the given host.
 * Return 1 if we found at least one name.
 */
int
getaddrs(h)
	struct host *h;
{
	struct hostent *hp;
	int i, j;
	u_long addr;

	if (h->name[0] == 0 && h->addrs[0] != INADDR_ANY) {
		hp = gethostbyaddr((char *)&h->addrs[0], sizeof(u_long), AF_INET);
		if (hp != 0)
			h_addname(h, hp->h_name);
	}
	if (h->name[0] == 0)
		return 0;
	for (i = 0; h->name[i] != 0; i++) {
		hp = gethostbyname(h->name[i]);
		if (hp == 0)
			continue;
		bcopy(hp->h_addr, (char *)&addr, sizeof(addr));
		h_addaddr(h, addr);
		h_addname(h, hp->h_name);
		for (j = 0; hp->h_aliases[j] != 0; j++)
			h_addname(h, hp->h_aliases[j]);
		for (j = 0; hp->h_addr_list[j] != 0; j++) {
			bcopy(hp->h_addr_list[j], (char *)&addr, sizeof(addr));
			h_addaddr(h, addr);
		}
	}
	if (h->name[0] != 0)
		return 1;
	return 0;
}
