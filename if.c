/*
 * deal with interfaces and routes.
 */
#include "dumb.h"

int nifs;
u_long gateways[500];
int ngateways;

struct host *me;

if_init()
{
	struct ifconf ifc;
	struct ifreq xifs[12]; /* ifr_name, ifr_{addr,dstaddr,flags} */
	int s, i, n, j;
	struct ifreq ifr;
	u_long dnm;
	struct sockaddr_in sin;

	nifs = 0;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0){
		perror("if_init socket()");
		return(0);
	}

	ifc.ifc_req = xifs;
	ifc.ifc_len = sizeof(xifs);
	if(ioctl(s, SIOCGIFCONF, &ifc) < 0){
		close(s);
		perror("if_init SIOCGIFCONF");
		return(0);
	}

	n = ifc.ifc_len / sizeof(xifs[0]);

	for(i = 0; i < n; i++){
		for(j = 0; j < nifs; j++)
			if(strcmp(ifs[j].mif_name, xifs[i].ifr_name) == 0)
				break;
		if(j < nifs) /* 4.3bsd gives duplicate interfaces for xns */
			continue;

		bzero(ifs[nifs], sizeof(ifs[nifs]));
		strcpy(ifs[nifs].mif_name, xifs[i].ifr_name);
		strcpy(ifr.ifr_name, xifs[i].ifr_name);

		if(ioctl(s, SIOCGIFFLAGS, &ifr) < 0)
			perror("if_init SIOCGIFFLAGS");
		if((ifr.ifr_flags & IFF_UP) == 0)
			continue;
		if((ifr.ifr_flags & IFF_RUNNING) == 0)
			continue;
		ifs[nifs].mif_flags = ifr.ifr_flags;

		if(ioctl(s, SIOCGIFADDR, &ifr) < 0)
			perror("if_init SIOCGIFADDR");
		bcopy(&ifr.ifr_addr, &sin, sizeof(ifr.ifr_addr));
		if(sin.sin_family != AF_INET)
			continue;
		if(sin.sin_addr.s_addr == inet_addr("127.0.0.1"))
			continue;
		ifs[nifs].mif_addr = sin.sin_addr.s_addr;

		if(ifs[nifs].mif_flags & IFF_POINTOPOINT){
			if(ioctl(s, SIOCGIFDSTADDR, &ifr) < 0)
				perror("if_init SIOCGIFDSTADDR");
			bcopy(&ifr.ifr_dstaddr, &sin,
			      sizeof(ifr.ifr_dstaddr));
			ifs[nifs].mif_dstaddr = sin.sin_addr.s_addr;
		}

		dnm = def_netmask(ifs[nifs].mif_addr);
		ifs[nifs].mif_netmask = dnm;
#ifdef SIOCGIFNETMASK
		if(ioctl(s, SIOCGIFNETMASK, &ifr) < 0)
			perror("if_init SIOCGIFNETMASK");
		else {
			bcopy(&ifr.ifr_addr, &sin,
				sizeof(ifr.ifr_addr));
			ifs[nifs].mif_netmask = sin.sin_addr.s_addr;
		}
		if((dnm & ifs[nifs].mif_netmask) != dnm){
#ifdef DEBUG
			fprintf(stderr, "if_init: bad netmask %s ",
				inet_ntoa(a2in(ifs[nifs].mif_netmask)));
			fprintf(stderr, "for %s\n",
				inet_ntoa(a2in(ifs[nifs].mif_addr)));
#endif DEBUG
			ifs[nifs].mif_netmask = dnm;
		}
#endif

#ifdef DEBUG
		fprintf(stderr, "%s ", ifr.ifr_name);
		fprintf(stderr, "%s ", inet_ntoa(a2in(ifs[nifs].mif_addr)));
		fprintf(stderr, "%s ", inet_ntoa(a2in(ifs[nifs].mif_netmask)));
		if(ifs[nifs].mif_flags & IFF_POINTOPOINT)
			fprintf(stderr, "%s ",
				inet_ntoa(a2in(ifs[nifs].mif_dstaddr)));
		fprintf(stderr, "\n");
#endif DEBUG

		if(me == 0)
			me = h_addr2host(ifs[nifs].mif_addr, 1);
		else
			h_addaddr(me, ifs[nifs].mif_addr);
		nifs++;
	}
	return(nifs > 0);
}

u_long
def_netmask(a)
u_long a;
{
	if(IN_CLASSA(a))
		return(htonl(0xff000000));
	if(IN_CLASSB(a))
		return(htonl(0xffff0000));
	return(htonl(0xffffff00));
}

u_long
netmaskfor(a)
u_long a;
{
	int i;
	u_long def;

	def = def_netmask(a);
	for(i = 0; i < nifs; i++){
		if((a & def) == (ifs[i].mif_addr & def))
			return(ifs[i].mif_netmask);
	}
	return(def);
}

/*
 * try to figure out gateways on this net: run netstat.
 * could maybe be done by looking at host table.
 * what's really needed is adjacent nets...
 */
rt_init()
{
	FILE *fp;
	char buf[100], dname[100], gname[100];
	u_long gw;
	int i;

	ngateways = 0;
	fp = popen("/usr/ucb/netstat -r -n", "r");
	if(fp == 0)
		return(0);

	while(fgets(buf, sizeof(buf), fp)){
		other_sleep(0);
		if(ngateways >= sizeof(gateways)/sizeof(gateways[0]))
			break;
		if(sscanf(buf, "%s%s", dname, gname) != 2)
			continue;
		if(strcmp(dname, "default") == 0)
			strcpy(dname, "0.0.0.0");
		if(!isdigit(dname[0]) || !isdigit(gname[0]))
			continue;
		gw = inet_addr(gname);
		if(gw == (long)-1)
			continue;
		if(gw == inet_addr("127.0.0.1"))
			continue;
		for(i = 0; i < ngateways; i++)
			if(gateways[i] == gw)
				break;
		if(i < ngateways)
			continue;
		for(i = 0; i < nifs; i++)
			if(gw == ifs[i].mif_addr)
				break;
		if(i < nifs)
			continue;
		gateways[ngateways++] = gw;
	}
	pclose(fp);

#ifdef DEBUG
	for(i = 0; i < ngateways; i++)
		fprintf(stderr, "gw %s\n", inet_ntoa(a2in(gateways[i])));
#endif DEBUG

	find_nearnets();

	return(1);
}

/*
 * use the host table to try to find other interfaces on nearby
 * gateways.
 */
static
find_nearnets()
{
	struct hostent *hp;
	struct host *h;
	int i, j, n, k;
	u_long x;

	permute(gateways, ngateways, sizeof(gateways[0])); /* not in hit.c */

	sethostent(1);

	for(i = 0; i < ngateways && i < 20; i++){
		other_sleep(0);
		h = h_addr2host(gateways[i], 1);
		h->h_flags |= HF_GATEWAY;
		hp = gethostbyaddr(&gateways[i], 4, AF_INET);
		if(hp == 0){
#ifdef DEBUG
			fprintf(stderr, "no hostname for %s\n",
				inet_ntoa(a2in(gateways[i])));
#endif DEBUG
		} else {
			bcopy(hp->h_addr, &x, 4);
			h_addaddr(h, x);
			h_addname(h, hp->h_name);
			for(j = 0; hp->h_aliases[j]; j++)
				h_addname(h, hp->h_aliases[j]);
#ifdef h_addr	/* 4.3 w/ named */
			hp = gethostbyname(hp->h_name);
			if(hp){
				for(j = 0; hp->h_addr_list[j]; j++){
					bcopy(hp->h_addr_list[j], &x, 4);
					h_addaddr(h, x);
				}
			}
#endif
		}
	}

#ifdef h_addr
	for(i = 0; i < ngateways && i < 20; i++){
		other_sleep(0);
		h = h_addr2host(gateways[i], 1);
		for(j = 0; j < H_NNAMES; j++){
			if(h->h_names[j] == 0)
				break;
			hp = gethostbyname(h->h_names[j]);
			if(!hp)
				continue;
			for(k = 0; hp->h_addr_list[k]; k++){
				bcopy(hp->h_addr_list[k], &x, 4);
				h_addaddr(h, x);
			}
		}
	}
#else
	sethostent(1);

	for(n = 0; n < 1000; n++){
		if((n % 10) == 0)
			other_sleep(0);
		hp = gethostent();
		if(hp == 0)
			break;
		h = h_name2host(hp->h_name, 0);
		if(h){
			bcopy(hp->h_addr, &x, 4);
			h_addaddr(h, x);
		}
	}
#endif

	endhostent();

#ifdef DEBUG
	for(i = 0; i < ngateways; i++){
		h = h_addr2host(gateways[i], 1);
		fprintf(stderr, "gwname %s: ", h->h_names[0]);
		for(j = 0; j < H_NADDRS; j++)
			fprintf(stderr, "%s ", inet_ntoa(a2in(h->h_addrs[j])));
		fprintf(stderr, "\n");
	}
#endif DEBUG
}

getaddrs(h)
struct host *h;
{
	struct hostent *hp;
	int i, j;
	u_long x;

	if(h->h_names[0] == 0 && h->h_addrs[0]){
		hp = gethostbyaddr(&(h->h_addrs[0]), 4, AF_INET);
		if(hp)
			h_addname(h, hp->h_name);
	}

	if(h->h_names[0] == 0)
		return(0);
	for(i = 0; h->h_names[i]; i++){
		hp = gethostbyname(h->h_names[i]);
		if(!hp)
			continue;
		bcopy(hp->h_addr, &x, 4);
		h_addaddr(h, x);
		h_addname(h, hp->h_name);
		for(j = 0; hp->h_aliases[j]; j++)
			h_addname(h, hp->h_aliases[j]);
#ifdef h_addr	/* 4.3 w/ named */
		for(j = 0; hp->h_addr_list[j]; j++){
			bcopy(hp->h_addr_list[j], &x, 4);
			h_addaddr(h, x);
		}
#endif
	}
	if(h->h_names[0])
		return(1);
	return(0);
}

struct in_addr
a2in(a)
u_long a;
{
	struct in_addr ina;

	ina.s_addr = a;
	return(ina);
}
