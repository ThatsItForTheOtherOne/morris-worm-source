/*
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF THE UNIVERSITY
 * OF CALIFORNIA.  The copyright notice above does not evidence
 * any actual or intended publication of this source code.
 *
 * Redistribution in any form is explicitly denied unless prior
 * written permission is obtained from Michael Karels or an
 * authorized representative of the University.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef _TYPES_
typedef unsigned long u_long; /* XXX */
#endif

#define UNKNOWN		10 /* XXX for lengths of arrays of unknown size */

/*
 * Structure types, and field offsets and sizes
 */
struct interface {
	char	if_name[16];		/* 0x00 name */
	u_long	if_addr;		/* 0x10 outgoing IF address */
	u_long	if_dstaddr;		/* 0x14 dst addr if pt-to-pt */
	u_long	if_netmask;		/* 0x18 network mask */
	short	if_flags;		/* 0x1c flags */
};					/* sizeof = 0x20 = 1<<5 */

struct muck {
	char	name[16];		/* 0x00 */
	char	crypted[14];		/* 0x10 */
	char	passwd[18];		/* 0x1e */
	char	*home;			/* 0x30 */
	char	*gecos;			/* 0x34 */
	struct	muck *next;		/* 0x38 */
};					/* sizeof = 0x3c */

struct host {
	char	*name[12];		/* 0x00 */
	u_long	addrs[6];		/* 0x30 */
	int	flags;			/* 0x48 see below */
	struct	host *next;		/* 0x4c */
};					/* sizeof = 0x50 */

/* flags in host structure */
#define	H_GATEWAY	0x1		/* found via netstat -r -n */
#define	H_INFECTED	0x2		/* waithit says we wormed onto it */
#define	H_CANTHIT	0x4		/* tried and failed */
#define	H_EQUIVHOST	0x8		/* found via hosts.equiv or /.rhosts */

struct object {
	char	*name;			/* 0x00 */
	int	len;			/* 0x04 */
	char	*buf;			/* 0x08 */
};

/*
 * Typed functions
 */
char *XS();
char *crypt();
struct object *getobjectbyname();
struct host *h_name2host();
struct host *h_addr2host();
long random();
