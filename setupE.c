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

extern long	E_L[8][16];
extern long	E_H[8][16];
extern char	E[32];

/* this routine is not used (another lint mishap) */
setupE()
{
	int	f4;
	int	f8;
	int	fc;

	for (f4 = 0; f4 < 8; ++f4)
		for (f8 = 0; f8 < 16; ++f8) {
			E_L[f4][f8] = 0;
			E_H[f4][f8] = 0;
		}
	for (f8 = 0; f8 < 32; ++f8) {
		fc = 31 - E[f8];
		for (f4 = 0; f4 < 16; ++f4)
			if (f4 & (1 << (fc % 4)))
				E_L[fc/4][f4] |= (1 << (31 - f8));
	}
	for (f8 = 32; f8 < 48; ++f8) {
		fc = 31 - E[f8];
		for (f4 = 0; f4 < 16; ++f4)
			if (f4 & (1 << (fc % 4)))
				E_H[fc/4][f4] |= (1 << (31 - f8));
	}
}
