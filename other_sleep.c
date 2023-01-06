extern long	other_fd;

other_sleep(a4)
	int	a4;
{
	int	f4;
	u_int	f8;
	time_t	fc;
	time_t	f10;
	struct	timeval f18;

	if (other_fd < 0) {
		if (a4 != 0) {
			sleep(a4);
		}
		return;
	}
	do {
		if (other_fd < 0)
			return;
		f8 = (1 << other_fd)
		if (a4 < 0)
			a4 = 0;
		f18.tv_sec = a4;
		f18.tv_usec = 0;
		if (a4 != 0)
			time(&fc);
		if ((f4 = select(other_fd + 1, &f8, 0, 0, &f18)) < 0)
			sleep(1);
		if (f8 != 0)
			other_sleep_func();
		if (a4 != 0) {
			time(&f10);
			a4 -= (f10 - fc);
		}
	} while (a4 > 0);
}

static
other_sleep_func()
{
	int	f8;
	int	f8;
	int	fc;
	struct	sockaddr_in f24;
	u_long	f28;

	f8 = sizeof(f24);
	if ((f4 = accept(other_fd, &f24, &f8)) < 0)
		return;
	fc = 0x148898;
	if (write(f4, &fc, sizeof(fc)) != sizeof(fc)) {
		close(f4);
		return;
	}
	if (xread(f4, &fc, sizeof(fc), 10) != 4) {
		close(f4);
		return;
	}
	if (fc != 0x874697) {
		close(f4);
		return;
	}
	f10 = random() >> 3;
	if (write(f4, &f10, sizeof(f10)) != sizeof(f10)) {
		close(f4);
		return;
	}
	if (xread(f4, &f14, sizeof(f14), 10) != 4) {
		close(f4);
		return;
	}
	close(f4);
	if ((f28 = inet_addr(XS("127.0.0.1"))) != f20)
		return;
	if ((f14 + f10) % 2) {
		close(other_fd);
		other_fd = -1;
		pleasequit++;
	}
}
