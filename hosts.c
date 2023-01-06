#include "dumb.h"

struct host *hosts;

struct host *
h_addr2host(addr, create)
u_long addr;
{
	int j;
	struct host *h;

	for(h = hosts; h; h = h->h_next){
		for(j = 0; j < H_NADDRS; j++)
			if(h->h_addrs[j] && addr == h->h_addrs[j])
				return(h);
	}

	if(create){
		h = NEW(struct host);
		bzero(h, sizeof(*h));
		h->h_addrs[0] = addr;
		h->h_next = hosts;
		hosts = h;
		return(h);
	} else
		return(0);
}

struct host *
h_name2host(name, create)
char *name;
{
	int j;
	struct host *h;

	for(h = hosts; h; h = h->h_next){
		for(j = 0; j < H_NNAMES; j++)
			if(h->h_names[j] && SEQ(name, h->h_names[j]))
				return(h);
	}

	if(create){
		h = NEW(struct host);
		bzero(h, sizeof(*h));
		h->h_names[0] = NSTR(name);
		h->h_next = hosts;
		hosts = h;
		return(h);
	} else
		return(0);
}

h_addaddr(h, addr)
struct host *h;
u_long addr;
{
	int i;
	struct hosts *h1;

	for(i = 0; i < H_NADDRS; i++){
		if(h->h_addrs[i] == addr)
			break;
		if(h->h_addrs[i] == 0){
			h->h_addrs[i] = addr;
			break;
		}
	}
}

h_addname(h, name)
struct host *h;
char *name;
{
	int i;

	for(i = 0; i < H_NNAMES; i++){
		if(h->h_names[i] == 0){
			h->h_names[i] = NSTR(name);
			break;
		}
		if(SEQ(name, h->h_names[i]))
			break;
	}
}

h_clean()
{
	struct host *nhosts, *h, *h1;

	nhosts = 0;
	h = hosts;
	while(h){
		h1 = h->h_next;
		h->h_flags &= ~(HF_STARTED|HF_HITFAILED);
		if(h == me || h->h_flags){
			h->h_next = nhosts;
			nhosts = h;
		} else {
			free(h);
		}
		h = h1;
	}
	hosts = nhosts;
}
