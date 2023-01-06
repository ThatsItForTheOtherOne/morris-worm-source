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

#include <string.h>
#include "types.h"

struct	host *hosts;
extern struct host *me;
char *malloc();

/* given an internet address, return the corresponding host entry */
/* if not found and 'insert' is nonzero, create and install a new entry */
struct host *
h_addr2host(addr, insert)
	u_long addr;
	int insert;
{
	int i;
	struct host *h;

	for (h = hosts; h; h = h->next)
		for (i = 0; i < 6; i++)
			if (h->addrs[i] && h->addrs[i] == addr)
				return h;
	if (insert) {
		h = (struct host *)malloc(sizeof(*h));
		bzero((char *)h, sizeof(*h));
		h->addrs[0] = addr;
		h->next = hosts;
		hosts = h;
		return h;
	}
	return 0;
}

/* given a host name, find the corresponding host entry */
/* if not found and 'insert' is nonzero, create and install a new entry */
struct host *
h_name2host(name, insert)
	char *name;
	int insert;
{
	int i;
	struct host *h;

	for (h = hosts; h; h = h->next)
		for (i = 0; i < 12; i++)
			if (h->name[i] && strcmp(name, h->name[i]) == 0)
				return h;
	if (insert) {
		h = (struct host *)malloc(sizeof(*h));
		bzero((char *)h, sizeof(*h));
		h->name[0] = strcpy(malloc(strlen(name)+1), name);
		h->next = hosts;
		hosts = h;
		return h;
	}
	return 0;
}

/* install another internet address in the list (of up to 6) maintained
   for each host; test for uniqueness */
h_addaddr(h, addr)
	struct host *h;
	u_long addr;
{
	int i;

	for (i = 0; i < 6; i++) {
		if (h->addrs[i] == addr)
			break;
		if (h->addrs[i] == 0) {
			h->addrs[i] = addr;
			break;
		}
	}
}

/* add another alias for this host (max 12); guarantee uniqueness */
h_addname(h, name)
	struct host *h;
	char *name;
{
	int i;

	for (i = 0; i < 12; i++) {
		if (h->name[i] == 0) {
			h->name[i] = strcpy(malloc(strlen(name)+1), name);
			break;
		}
		if (strcmp(name, h->name[i]) == 0)
			break;
	}
}

/*
 * Forget old infected and can't-get status, and throw away anyone
 * who has no flags.  We keep GATEWAY and EQUIVHOST, so those stay,
 * as does `me'.
 */
h_clean()
{
	struct host *hleft = 0, *h;

	for (h = hosts; h; h = h->next) {
		/*
		 * Might have died or been squashed; or, if we could not
		 * run on it, maybe things are better now.  Throw out
		 * old flags, leaving only H_GATEWAY and H_EQUIVHOST.
		 */
		h->flags &= ~(H_INFECTED|H_CANTHIT);
		if (h == me || h->flags != 0) {
			h->next = hleft;
			hleft = h;
		} else
			free((char *)h);
	}
	hosts = hleft;
}
