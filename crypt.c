#include "types.h"

/* Some comments in here are adapted from an article by Matt Bishop */

/* The e[] array is the same as the original but every element
   has been decremented by one */
/* A comment from the original about another array:
   'For some reason, they give a 0-origin index, unlike everything else.' */
char E[48]; /* BSS */
long E_L[8][16]; /* BSS */
long E_H[8][16]; /* BSS */
static char e[] = {
	31, 0, 1, 2, 3, 4,
	3, 4, 5, 6, 7, 8,
	7, 8, 9, 10, 11, 12,
	11, 12, 13, 14, 15, 16,
	15, 16, 17, 18, 19, 20,
	19, 20, 21, 22, 23, 24,
	23, 24, 25, 26, 27, 28,
	27, 28, 29, 30, 31, 0,
};

/* Compute an encrypted password from a cleartext key and a salt. */
/* This private version of crypt() contains several significant departures
   from the original. */
char *
crypt(key, salt) /* 420c */
	char *key, *salt;
{
	static char iobuf[16];
	static long block[2];	/* original has block[66] */
	register int i, j, c;
	int temp, temp2;

	/* equivalent to block[i] loop in original */
	block[0] = 0;
	block[1] = 0;

	/* this initialization appears in setkey() in the original */
	for (i = 0; i < 48; ++i)
		E[i] = e[i];

	/* here we pack the bits into two words instead of spreading
	   them out through 64 words as the original does */
	for (i = 0; (c = *key) && i < 32; ++key) {
		for (j = 0; j < 7; ++j, ++i) {
			temp2 = (c >> (6 - j)) & 01;
			block[0] |= temp2 << (31 - i);
		}
		++i;
	}
	for (i = 0; (c = *key) && i < 32; ++key) {
		for (j = 0; j < 7; ++j, ++i) {
			temp2 = (c >> (6 - j)) & 01;
			block[1] |= temp2 << (31 - i);
		}
		++i;
	}

	/* this replaces setkey(block) in the original */
	compkeys(&block[0], 0);

	/* use the salt to permute the E table; same as original */
	for (i = 0; i < 2; ++i) {
		c = *salt++;
		iobuf[i] = c;
		if (c > 'Z')
			c -= 6;
		if (c > '9')
			c -= 7;
		c -= '.';
		for (j = 0; j < 6; ++j)
			if ((c >> j) & 01) {
				/* missed some cse's here */
				temp = E[6*i + j];
				E[6*i + j] = E[6*i + j + 24];
				E[6*i + j + 24] = temp;
			}
	}

	/* permute the E table */
	mungE();

	/* do the actual encryption; replaces encrypt(block, 0) */
	block[0] = 0;
	block[1] = 0;
	des(&block[0], &block[0]);	/* apply salted DES 25 times */
	ipi(&block[0], &block[0]);	/* invert initial permutation */

	/* pull the actual encrypted string from the bits */
	/* new complexity due to requirement of unpacking from bit array */
	for (i = 0; i < 11; ++i) {
		c = (block[0] >> 26) & 077;
		block[0] <<= 6;
		block[0] |= (block[1] >> 26) & 077;
		block[1] <<= 6;
		c += '.';
		if (c > '9')
			c += 7;
		if (c > 'Z')
			c += 6;
		iobuf[i + 2] = c;
	}

	iobuf[i + 2] = '\0';
	if (iobuf[1] == 0)
		iobuf[1] = iobuf[0];
	return iobuf;
}

/* This routine does not appear in the original
   and does the permutation of E. */
mungE() /* 43f2 */
{
	register int i, j, k, l, m;
	register long n;
	long *ip, *ip2;

	/* initialize the words that will hold the result */
	for (i = 0; i < 8; ++i) {
		ip = &E_H[i][0];
		ip2 = &E_L[i][0];
		for (j = 0; j < 16; ++j)
			*ip2++ = *ip++ = 0;
	}

	/* E_H holds the high 16 bits and E_L the low 32 bits
	   (the E table expands a 32 bit vector into a 48 bit one) */
	/* E_H[x][y] means that the 4 bits which make up the integer y
	   (0 <= y <= 15) are in position 4 * x in the 32-bit word
	   that is being expanded */
	for (j = 0; j < 32; ++j) {
		n = 1 << (31 - j);
		k = 31 - E[j];
		l = 1 << (k & 03);
		m = k >> 2;
		ip = &E_L[m][0];
		for (i = 1; i < 16; ++i)
			if (i & l)
				ip[i] |= n;
	}

	for (j = 32; j < 48; ++j) {
		n = 1 << (63 - j);
		k = 31 - E[j];
		l = 1 << (k & 03);
		m = k >> 2;
		ip = &E_H[m][0];
		for (i = 1; i < 16; ++i)
			if (i & l)
				ip[i] |= n;
	}
}

/* next is compkeys() 44d4 */
