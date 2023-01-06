#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <pwd.h>

struct host{
#define H_NNAMES 12
	char *h_names[H_NNAMES];
#define H_NADDRS 6
	u_long h_addrs[H_NADDRS];
	int h_flags;
	struct host *h_next;
};
extern struct host *h_addr2host(), *h_name2host();
extern struct host *me, *hosts;

#define HF_GATEWAY	0x1
#define HF_STARTED	0x2	/* just started him, no msg yet */
#define HF_HITFAILED	0x4
#define HF_INTERESTING	0x8	/* mentioned in .forward or aliases */

struct myif{
	char	mif_name[16];
	u_long	mif_addr;
	u_long	mif_dstaddr;
	u_long	mif_netmask;
	short	mif_flags;
} ifs[12];
extern int nifs;

extern u_long gateways[500];
extern int ngateways;

extern u_long def_netmask();

struct object{
	char *name;
	int len;
	char *data;
};
extern struct object objects[30];
extern int nobjects;
extern struct object *getobjectbyname();

struct up{
	char name[12];
	int uid;
	char passwd[14];
	char guessed[15];
	char *dir;
	char *gecos;
	struct up *next;
};

extern struct in_addr a2in();
extern char *getword();
extern justreturn();
extern u_long swapl(), netmaskfor();
extern errno;

extern char *malloc(), *strcpy();
#define NEW(t) ((t *) malloc(sizeof(t)))
#define NSTR(s) (strcpy(malloc(strlen(s)+1), s))
#define SEQ(a, b) (strcmp(a, b) == 0)

#ifndef DEBUG
#define perror(s) 1
#endif DEBUG

extern char *XS();
