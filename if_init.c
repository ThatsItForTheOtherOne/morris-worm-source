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
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <string.h>
#include "types.h"

struct interface ifs[12];
struct host *me;
int nifs = 0;
u_long inet_addr();
u_long def_netmask();
u_long htonl();

/*
 * Initialise list of interfaces.  Return true iff some found.
 *
 * References to ifs[nifs].field below were improperly compiled (apparently
 * by a compiler bug), so that references to ifs[nifs] became references
 * to ifs[0].
 */
int
if_init()
{
	struct ifconf ifc;
	struct ifreq iflist[12];
	int s, i, n, j;
	struct ifreq ifr;
	u_long mask;
	struct sockaddr_in sin;
	u_long localaddr;

	/*
	 * Get list of interfaces.
	 */
	nifs = 0;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		return 0;
	ifc.ifc_req = iflist;
	ifc.ifc_len = sizeof(iflist);
	if (ioctl(s, SIOCGIFCONF, &ifc) < 0) {
		(void) close(s);
		return 0;
	}

	/*
	 * For all interfaces, if we do not already know about it,
	 * get its address, flags, etc.
	 */
	n = ifc.ifc_len / sizeof(struct ifreq);
	for (i = 0; i < n; i++) {
		/* see if we have it already */
		for (j = 0; j < nifs; j++)
			if (strcmp(ifs[j].if_name, iflist[i].ifr_name) == 0)
				break;
		if (j < nifs)		/* already have it */
			continue;

		/* prepare a new interface structure */
		/* there is an & missing here (programmer error) */
		/* bzero((char *)&ifs[nifs], sizeof(struct interface)); */
		bzero(ifs[nifs], sizeof(struct interface)); /* XXX */
		(void) strcpy(ifs[nifs].if_name, iflist[i].ifr_name);

		/* make sure this interface is up and running */
		(void) strcpy(ifr.ifr_name, iflist[i].ifr_name);
		if (ioctl(s, SIOCGIFFLAGS, &ifr) < 0)
			/*perror("ioctl SIOCGIFFLAGS")*/;
		if ((ifr.ifr_flags & IFF_UP) == 0)
			continue;
		if ((ifr.ifr_flags & IFF_RUNNING) == 0)
			continue;
		ifs[nifs].if_flags = ifr.ifr_flags;

		/* check the address: make sure it's IP and not localhost */
		if (ioctl(s, SIOCGIFADDR, &ifr) < 0)
			/*perror("ioctl SIOGCIFADDR")*/;
		bcopy((char *)&ifr.ifr_addr, (char *)&sin, sizeof(sin));
		if (sin.sin_family != AF_INET)
			continue;
		localaddr = inet_addr(XS("127.0.0.1"));
		if (sin.sin_addr.s_addr == localaddr)
			continue;
		ifs[nifs].if_addr = sin.sin_addr.s_addr;

		/* pick up remote p-to-p address, netmask */
		if (ifs[nifs].if_flags & IFF_POINTOPOINT) {
			if (ioctl(s, SIOCGIFDSTADDR, &ifr) < 0)
				/*perror("ioctl SIOCGIFDSTADDR")*/;
			bcopy((char *)&ifr.ifr_dstaddr, (char *)&sin, 16);
			ifs[nifs].if_dstaddr = sin.sin_addr.s_addr;
		}
		mask = def_netmask(ifs[nifs].if_addr);
		ifs[nifs].if_netmask = mask;
		if (ioctl(s, SIOCGIFNETMASK, &ifr) >= 0) {
			bcopy((char *)&ifr.ifr_addr, (char *)&sin, 16);
			ifs[nifs].if_netmask = sin.sin_addr.s_addr;
		}
		if ((mask & ifs[nifs].if_netmask) != mask)
			ifs[nifs].if_netmask = mask;

		/* if we haven't found an address for ourselves, install one */
		if (me == 0)
			me = h_addr2host(ifs[nifs].if_addr, 1);
		else
			h_addaddr(me, ifs[nifs].if_addr);
		nifs++;
	}
	return nifs > 0;
}

/* guess a netmask based on A/B/C address class */
u_long
def_netmask(addr)
	u_long addr;
{

	if (IN_CLASSA(addr))
		return htonl(IN_CLASSA_NET);
	if (IN_CLASSB(addr))
		return htonl(IN_CLASSB_NET);
	return htonl(IN_CLASSC_NET);
}

/* in addition to A/B/C class, find out if we are attached to the network
   that this host is on and see if there is a more specific netmask */
u_long
netmaskfor(addr)
	u_long addr;
{
	int i;
	u_long mask;

	mask = def_netmask(addr);
	for (i = 0; i < nifs; i++)
		if ((addr & mask) == (ifs[i].if_addr & mask))
			return ifs[i].if_netmask;
	return mask;
}

/* next: rt_init */
