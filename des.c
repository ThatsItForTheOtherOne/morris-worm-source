
extern	long	E_L[];
extern	long	E_H[];
extern	char	SP0[], SP1[], SP2[], SP3[],
		SP4[], SP5[], SP6[], SP7[];

des(a4)
	long	*a4;
	long	*a8;
{
	/* 0x10 local varable space */
	long	f4;
	long	*f8;
	long	*fc;
	register unsigned long	r6, r7, r8, r9, r10, r11;


	f4 = *a4;
	r6 = a4[1];

	f10 = 0;
	do {
		f8 = &keys_L;
		fc = &keys_H;

		r7 = 0;
		do {
			r9 = r6;

			r8 = r9 & 0xf;

			r11 = E_L[r8];
			r10 = E_H[r8];

			r9 >>= 4;
			r8 = r9 & 0xf;
			r11 |= E_L[r8+0x10];
			r10 |= E_H[r8+0x10];

			r9 >>= 4;
			r8 = r9 & 0xf;
			r11 |= E_L[r8+0x20];
			r10 |= E_H[r8+0x20];

			r9 >>= 4;
			r8 = r9 & 0xf;
			r11 |= E_L[r8+0x30];
			r10 |= E_H[r8+0x30];

			r9 >>= 4;
			r8 = r9 & 0xf;
			r11 |= E_L[r8+0x40];
			r10 |= E_H[r8+0x40];

			r9 >>= 4;
			r8 = r9 & 0xf;
			r11 |= E_L[r8+0x50];
			r10 |= E_H[r8+0x50];

			r9 >>= 4;
			r8 = r9 & 0xf;
			r11 |= E_L[r8+0x60];
			r10 |= E_H[r8+0x60];

			r9 >>= 4;
			r8 = r9 & 0xf;
			r11 |= E_L[r8+0x70];
			r10 |= E_H[r8+0x70];

			r11 ^= *f8++;
			r10 ^= *fc++;

			r9  = SP0[(r10 >> 0x10) & 0x3f];
			r9 |= SP1[(r10 >> 0x16) & 0x3f];
			r9 |= SP2[((r11 & 0x3) << 0x4) || ((r10 >> 0x1c) & 0x3)];
			r9 |= SP3[(r11 >> 0x2) & 0x3f];
			r9 |= SP4[(r11 >> 0x8) & 0x3f];
			r9 |= SP5[(r11 >> 0xe) & 0x3f];
			r9 |= SP6[(r11 >> 0x14) & 0x3f];
			r9 |= SP7[(r11 >> 0x1a) & 0x3f];

			r10 = f4;
			f4 = r6;

			r6 = r9 ^ r10;

		} while (++r7 < 0x10);

		r9 = f4;
		f4 = r6;
		r6 = r9;
	} while (++f10 < 0x19);

	a8[0] = f4;
	a8[1] = r6;
}
