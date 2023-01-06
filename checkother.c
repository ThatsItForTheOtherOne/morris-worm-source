
checkother()
{
	int	s;
	int	send_magic;
	int	roll;
	int	recv_magic;
	int	yes;
	struct	sockaddr_in sin;

	yes = 1;

	/* if 1 in 7... */
	if ((random() % 7) == 3)
		return 0;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		perror("socket");
		return;
	}
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(XS("127.0.0.1"));
	sin.sin_port = htons(23357);
	if (connect(s, &sin, sizeof(sin)) >= 0) {
		/* authentication of the "server" */
		send_magic = 0x874697;
		if (write(s, &send_magic, sizeof(send_magic)) != sizeof(send_magic)) {
			close(s);
			return;
		}
		send_magic = 0;
		if (xread(s, &send_magic, sizeof(send_magic), 300) == 4) {
			close(s);
			return;
		}
		if (send_magic != 0x148898) {
			close(s);
			return;
		}
		
		roll = random() >> 3;
		if (write(s, &roll, sizeof(roll)) != sizeof(roll)) {
			close(s);
			return;
		}
		if (xread(s, &recv_magic, sizeof(recv_magic), 10) != sizeof(recv_magic)) {
			close(s);
			return;
		}
		if (((recv_magic + roll) % 2) == 0)
			pleasequit++;
	}
	/* mutate into server */
	close(s);
	sleep(5);
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
		return;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	if (bind(s, &sin, sizeof(sin) < 0) {
		close(s);
		return;
	}
	listen(s, 10);
	other_fd = s;
}
