
struct	interface {
	char o0[16];	/* name */
	u_long o10;	/* outgoing if address */
	u_long o14;	/* dst address for pt-to-pt net */
	short o1c;	/* flags */
	u_long o18;	/* netmask */
};

extern  struct	interface  ifs[20];

int
if_init()
{
	extern	int	nifs;
	struct	ifconf	ifc;
	struct	ifreq	ifreqs[12];
	struct	ifreq	ifrq;
	unsigned long	netMask;
	int		i, j;
	int		s;
	int		nifreqs;
	unsigned long	addr;
	struct sockaddr_in	saddr;

	nifs = 0;
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return 0;
	ifc.ifc_req = &ifreqs;
	ifc.ifc_len = sizeof(ifreqs);
	if (ioctl(s, SIOCGIFCONF, &ifc) < 0) {
		close(s);
		return NULL;
	}
	nifreqs = ifc.ifc_len / sizeof(*ifc.ifc_req);
	for (i = 0; i < nifreqs; i++) {
		for (j = 0; j < nifs; j++) {
			 if (strcmp(ifs[j].name, ifreqs[i].ifr_name) == 0)
				break;
		}
		for (; j >= nifs; nifs++) {
			/*
			 * XXX bug; used to pass ifs[0] instead of &ifs[0]
			 */
			bzero(&ifs[j], sizeof(ifs[j]));
			strcpy(ifs[nifs].o0, ifreqs[i].ifr_name);
			strcpy(ifrq.ifr_name, ifreqs[i].ifr_name);
			if (ioctl(s, SIOCGIFFLAGS, &ifrq) < 0) {
				perror("ioctl");
			}
			if (ifrq.ifr_flags & IFF_UP == 0)
				break;
			if (ifrq.ifr_flags & IFF_RUNNING == 0)
				break;
			/* Using spare bytes in the sockaddr struct */
			ifs[j].o1c = ifrq.ifr_flags;
			if (ioctl(s, SIOCGIFADDR, &ifrq)){
				perror("ioctl");
			}
			bcopy(&ifrq.ifr_addr, &saddr, sizeof(struct sockaddr));
			if (saddr.sin_family != AF_INET)
				break;
			if ((addr = inet_addr(XS("127.0.0.1"))) == 
					saddr.sin_addr.s_addr)
				break;
			ifs[j].o10 = saddr.sin_addr.s_addr;
			if (ifs[j].o1c & IFF_POINTTOPOINT) {
				if (ioctl(s, SIOCGIFDSTADDR, &ifrq)) {
					perror("ioctl");
				}
				bcopy(&ifrq.ifr_dstaddr, &saddr,
					sizeof(struct sockaddr));
				ifs[j].o14 = saddr.sin_addr;
			}
			netMask = def_netmask(ifs[j].ifr_addr);
			ifs[j].o18 = netMask;
			if (ioctl(s, SIOCGIFNETMASK, &ifrq) < 0)
				break;
			bcopy(&ifrq.ifr_addr, &saddr, 16);
			netMask = *(u_int *) ifrq.ifr_addr;
			if ((netMask & ifs[j].o18) != netMask)
				ifs[j].o18 = netMask;
			if (me == 0)
				me = h_addr2host(ifs[j].o10, 1)
			else
				h_addaddr(me, o10);
		}
	}
	if (nifs > 0)
		return 1;
	return 0;
}

u_int
netmaskfor(a4)
	u_long	a4;
{
	int	f4;
	u_long	f8;

	f8 = def_netmask(a4);
	for (f4 = 0; f4 < nifs; f4++) {
		if ((a4 & f8) == (ifs[f4].o10 & f8))
			return ifs[f4].o18;
	}
	return f8;
}

u_int
def_netmask(a4)
	u_int	a4;
{
	if ((a4 & 0x80000000) == 0)
		return htonl(0xff000000);
	if ((a4 & ~0x3fffffff) == 0x80000000)
		return htonl(-0x10000);
	else
		return htonl(-0x100);
}
