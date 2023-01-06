struct	host *hosts;

struct host {
	char *name[12];			/* names */
	struct in_addr addrs[6];	/* addresses */
	int	flags;
	struct host *next;		/* next */
};

struct host *
h_name2host(name, insert)
	char	*name;
	int	insert;
{
	int	f4;
	struct	host *f8;

	for (f8 = hosts; f8 != 0; f8 = f8->o4c)
		for (f4 = 0; f4 < 12; f4++)
			if (f8->o0[f4] != 0 && strcmp(name, f8->o0[f4]) == 0)
				return f8;
	if (insert == 0)
		return 0;
	f8 = (struct host *) malloc(sizeof(*f8));
	bzero(f8, sizeof(*f8));
	f8->o0[0] = strcpy(malloc(strlen(name)+1), name);
	f8->o4c = hosts;
	hosts = f8;
	return f8;
}

struct host *
h_addr2host(addr, insert)
	struct in_addr addr;
	int insert;
{
	int	f4;
	struct	host *f8;

	for (f8 = hosts; f8 != 0; f8 = f8->o4c)
		for (f4 = 0; f4 < 6; f4++)
			if (f8->o30[f4].s_addr != INADDR_ANY &&
			    f8->o30[f4].s_addr == addr.s_addr)
				return f8;
	if (insert) {
		f8 = (struct host *)malloc(sizeof(*f8));
		bzero(f8, sizeof(*f8));
		f8->o30[0] = addr;
		f8->o4c = hosts;
		hosts = f8;
		return f8;
	}
	return 0;
}

h_addaddr(a4, a8)
	struct host *a4;
	struct in_addr a8;
{
	int	f4;

	for (f4 = 0; f4 < 6; f4++) {
		if (a4->o30[f4].s_addr == a8.s_addr)
			return;
		if (a4->o30[f4].s_addr == INADDR_ANY) {
			a4->o30[f4] = a8;
			return;
		}
	}
}

h_addname(a4, name)
	struct host *a4;
	char *name;
{
	int f4;

	for (f4 = 0; f4 < 12; f4++) {
		if (a4->o0[f4] == 0) {
			a4->o0[f4] = strcpy(malloc(strlen(name)+1), name);
			return;
		}
		if (strcmp(name, a4->o0[f4]) == 0)
			return;
	}
}

h_clean()
{
	struct host *f4 = 0;
	struct host *f8;

	for (f8 = hosts; f8 != 0; f8 = f8->o4c) {
		f8->o48 &= ~(bit(1)|bit(2));
		if (f8 == me || f8->o48 != 0) {
			f8->o4c = f4;
			f4 = f8;
		} else
			free(f8);
	}
	hosts = f4;
}

int
getaddrs(a4)
	struct host *a4;
{
	struct	hostent	*f4;
	int	f8;
	int	fc;
	u_long	f10;

	if ((a4->name[0] == 0) && (a4->addrs[0].s_addr != 0) &&
			((f4 = gethostbyaddr(&a4->addrs[0],4,AF_INET)) != 0)) {
		h_addname(a4, f4->h_name);
	}
	if (a4->name[0] == 0)
		return 0;
	for (f8 = 0; a4->name[f8] != 0; f8++) {
		if ((f4 = gethostbyname(a4->name[f8])) == 0)
			continue;
		bcopy(&f4->h_addr, &f10, sizeof(u_long));
		h_addaddr(a4, f10);
		h_addname(a4, f4->h_name);
		for (fc = 0; f4->h_aliases[fc] != 0; fc++) {
			h_addname(a4, f4->h_aliases[fc]);
		}
		for (fc = 0; f4->h_addr_list[fc] != 0; fc++) {
			bcopy(f4->h_addr_list[fc], &f10, sizeof(u_long));
			h_addaddr(a4, f10);
		}
	}
	if (a4->name[0] != 0)
		return 1;
	return 0;
}
