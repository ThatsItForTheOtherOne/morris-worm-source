#include "dumb.h"

int other_fd = -1, pleasequit;
#define PORT 23357

checkother()
{
	int s, x, mine, his, yes = 1;
	struct sockaddr_in sin;

	if((random() % 7) == 3){
#ifdef DEBUG
		fprintf(stderr, "checkother not bothering\n");
#endif DEBUG
		return;
	}

	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0)
		return;

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(PORT);

	if(connect(s, &sin, sizeof(sin)) < 0){
		close(s);
		goto gronk;
	}

	x = 8865431;
	if(write(s, &x, 4) != 4){
		close(s);
		return;
	}

	x = 0;
	if(xread(s, &x, 4, 300) != 4){
		close(s);
		return;
	}

	if(x != 1345688){
		close(s);
		return;
	}

	mine = random() >> 3;
	if(write(s, &mine, 4) != 4){
		close(s);
		return;
	}

	if(xread(s, &his, 4, 10) != 4){
		close(s);
		return;
	}

	if(((mine + his) % 2) == 0){
#ifdef DEBUG
		fprintf(stderr, "checkother exiting\n");
#endif DEBUG
		pleasequit++;
	}

	close(s);

gronk:
#ifdef DEBUG
	fprintf(stderr, "checkother grabbing the port\n");
#endif DEBUG
	sleep(5);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0)
		return;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

	if(bind(s, &sin, sizeof(sin)) < 0){
		close(s);
		return;
	}
	listen(s, 10);

	other_fd = s;
}

other_sleep(tm)
{
	int n, mask, t0, t1;
	struct timeval tv;

	if(other_fd < 0){
		if(tm)
			sleep(tm);
		return;
	}

	do{
		if(other_fd < 0)
			return;
		mask = 1 << other_fd;
		if(tm < 0)
			tm = 0;
		tv.tv_sec = tm;
		tv.tv_usec = 0;
		if(tm)
			time(&t0);
		n = select(other_fd + 1, &mask, 0, 0, &tv);
		if(n < 0)
			sleep(1);
		if(mask)
			other_doit();
		if(tm){
			time(&t1);
			tm -= (t1 - t0);
		}
	} while(tm > 0);
}

static
other_doit()
{
	int s, len, x, mine, his;
	struct sockaddr_in from;

	len = sizeof(from);
	s = accept(other_fd, &from, &len);

	if(s < 0)
		return;

	x = 1345688;
	if(write(s, &x, 4) != 4){
		close(s);
		return;
	}

	if(xread(s, &x, 4, 10) != 4){
		close(s);
		return;
	}
	if(x != 8865431){
		close(s);
		return;
	}

	mine = random() >> 3;
	if(write(s, &mine, 4) != 4){
		close(s);
		return;
	}

	if(xread(s, &his, 4, 10) != 4){
		close(s);
		return;
	}

	close(s);
	if(from.sin_addr.s_addr != inet_addr("127.0.0.1"))
		return;

	if(((mine + his) % 2) != 0){
		close(other_fd);
		other_fd = -1;
#ifdef DEBUG
		fprintf(stderr, "other_doit exiting\n");
#endif DEBUG
		pleasequit++;
	}

	return;
}

xread(fd, buf, n, tmo)
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
		i++;
	}
	return(i);
}
