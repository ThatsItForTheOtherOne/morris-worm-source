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

/* Some comments are adapted from an article by Matt Bishop */

extern long	keys_L[25];
extern long	keys_H[25];

/*
 * The original calls these 'permuted choice' arrays.
 */

long	PC1[128] = {
0x10000000,	  0x0,		    0x100000,	      0x0,
0x1000,		  0x0,		    0x10,	      0x0,
0x0,		  0x10000,	    0x0,	      0x1000000,
0x1,		  0x0,		    0x0,	      0x0,
0x20000000,	  0x0,		    0x200000,	      0x0,
0x2000,		  0x0,		    0x20,	      0x0,
0x0,		  0x20000,	    0x0,	      0x2000000,
0x2,		  0x0,		    0x0,	      0x0,
0x40000000,	  0x0,		    0x400000,	      0x0,
0x4000,		  0x0,		    0x40,	      0x0,
0x0,		  0x40000,	    0x0,	      0x4000000,
0x4,		  0x0,		    0x0,	      0x0,
0x80000000,	  0x0,		    0x800000,	      0x0,
0x8000,		  0x0,		    0x80,	      0x0,
0x0,		  0x80000,	    0x0,	      0x8000000,
0x8,		  0x0,		    0x0,	      0x0,
0x1000000,	  0x0,		    0x10000,	      0x0,
0x100,		  0x0,		    0x0,	      0x100,
0x0,		  0x1000,	    0x0,	      0x100000,
0x0,		  0x10000000,	    0x0,	      0x0,
0x2000000,	  0x0,		    0x20000,	      0x0,
0x200,		  0x0,		    0x0,	      0x200,
0x0,		  0x2000,	    0x0,	      0x200000,
0x0,		  0x20000000,	    0x0,	      0x0,
0x4000000,	  0x0,		    0x40000,	      0x0,
0x400,		  0x0,		    0x0,	      0x400,
0x0,		  0x4000,	    0x0,	      0x400000,
0x0,		  0x40000000,	    0x0,	      0x0,
0x8000000,	  0x0,		    0x80000,	      0x0,
0x800,		  0x0,		    0x0,	      0x800,
0x0,		  0x8000,	    0x0,	      0x800000,
0x0,		  0x80000000,	    0x0,	      0x0,
};

long	PC2[128] = {
0x0,		  0x20000000,	    0x0,	      0x800000,
0x0,		  0x0,		    0x0,	      0x40000,
0x10,		  0x0,		    0x0,	      0x0,
0x0,		  0x2000000,	    0x1,	      0x0,
0x80,		  0x0,		    0x0,	      0x100000,
0x0,		  0x0,		    0x0,	      0x8000000,
0x0,		  0x40000000,	    0x0,	      0x200000,
0x8,		  0x0,		    0x0,	      0x10000000,
0x0,		  0x4000000,	    0x0,	      0x80000,
0x0,		  0x80000000,	    0x40,	      0x0,
0x0,		  0x400000,	    0x0,	      0x0,
0x4,		  0x0,		    0x0,	      0x1000000,
0x0,		  0x0,		    0x0,	      0x0,
0x0,		  0x0,		    0x0,	      0x0,
0x0,		  0x0,		    0x0,	      0x0,
0x0,		  0x0,		    0x0,	      0x0,
0x8000000,	  0x0,		    0x100,	      0x0,
0x2000000,	  0x0,		    0x10000,	      0x0,
0x4000000,	  0x0,		    0x400000,	      0x0,
0x1000,		  0x0,		    0x4000,	      0x0,
0x0,		  0x0,		    0x100000,	      0x0,
0x20000000,	  0x0,		    0x20000,	      0x0,
0x200,		  0x0,		    0x80000000,	      0x0,
0x800000,	  0x0,		    0x2000,	      0x0,
0x40000000,	  0x0,		    0x0,	      0x0,
0x40000,	  0x0,		    0x400,	      0x0,
0x200000,	  0x0,		    0x0,	      0x0,
0x80000,	  0x0,		    0x10000000,	      0x0,
0x0,		  0x0,		    0x8000,	      0x0,
0x800,		  0x0,		    0x1000000,	      0x0,
0x0,		  0x20000,	    0x2,	      0x0,
0x20,		  0x0,		    0x0,	      0x10000,
};

/* same as original: sequence of shifts used for the key schedule */
long	shift[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

/* This routine generates the 16 round keys and is very straightforward.
   The keys are stored 16 bits in keys_H[i] and 32 bits in keys_L[i],
   where i (0 <= i <= 15) is the number of the round. */
compkeys(block, direction) /* 44d4 */
	long	*block;
	int	direction;
{
	register long l;
	register long h;
	register long kl;
	register long kh;
	register int n;
	register long m;
	int	i;
	int	b16;
	int	b256;
	int	b1;

	l = 0;
	h = 0;

	for (m = block[1], n = 0; n < 64; m <<= 1, n += 2)
		if (m < 0) {
			l |= PC1[n];
			h |= PC1[n+1];
		}

	for (m = block[0]; n < 128; m <<= 1, n += 2)
		if (m < 0) {
			l |= PC1[n];
			h |= PC1[n+1];
		}

	/* The 56 bit result of the PC1 permutation is split into
	   two 28 bit vectors, each shifted left as indicated in the
	   shift schedule shift[], and then rejoined and run through
	   the permutation PC2; this code performs this shift in place,
	   hence thelength of the innermost loop. */
	for (i = 0; i < 16; i++) {
		for (m = 0; m < shift[i]; m++) {
			b16 = 0;
			b256 = 0;
			b1 = 0;
			if (l < 0)
				b16 = 16;
			if (l & 8)
				b256 = 256;
			if (h < 0)
				b1 = 1;
			l <<= 1;
			l &= ~16;
			l |= b16;
			l |= b1;
			h <<= 1;
			h |= b256;
		}

		kl = 0;
		kh = 0;

		for (n = 0, m = h; n < 64; m <<= 1, n += 2)
			if (m < 0) {
				kl |= PC2[n];
				kh |= PC2[n+1];
			}

		for (m = l; n < 128; m <<= 1, n += 2)
			if (m < 0) {
				kl |= PC2[n];
				kh |= PC2[n+1];
			}

		/* this code reverses the key schedule order if decrypting */
		/* but the worm never uses this feature */
		if (direction) {
			keys_L[15 - i] = kl;
			keys_H[15 - i] = kh;
		} else {
			keys_L[i] = kl;
			keys_H[i] = kh;
		}
	}
}
