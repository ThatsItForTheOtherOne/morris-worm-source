int	keys_L[16];
int	keys_H[16];


compkeys(a4, direction)
	int	*a4;
	int	direction;
{
	register int r11;
	register int r10;
	register int r9;
	register int r8;
	register int r7;
	register int r6;
	int	f4;
	int	f8;
	int	fc;
	int	f10;

	r11 = 0;
	r10 = 0;
	r6 = a4[1];
	for (r7=0; r7 < 64; r7 += 2) {
		if (r6 < 0) {
			r11 |= PC1[r7] 
			r10 |= PC1[r7+1];
		}
		r6 += r6;
	}
	r6 = a4[0];
	for ( ; r7 < 128; r7 += 2) {
		if (r6 < 0) {
			r11 |= PC1[r7];
			r10 |= PC1[r7+1];
		}
		r6 += r6;
	}
	for (f4 = 0; f4 < 16; f4++) {
		for (r6 = 0; r6 < shift[f4]; r6++) {
			f8 = 0;
			fc = 0;
			f10 = 0;
			if (r11 < 0)
				f8 = 16;
			if (r11 & bit(3))
				fc = 256;
			if (r10 < 0)
				f10 = 1;
			r11 += r11;
			r11 &= ~16;
			r11 |= f8;
			r11 |= f10;
			r10 += r10;
			r10 |= fc;
		}
		r9 = 0;
		r8 = 0;
		for (r7=0, r6=r10; r7 < 64; r7 += 2) {
			if (r6 < 0) {
				r9 |= PC2[r7];
				r8 |= PC2[r7+1];
			}
			r6 += r6;
		}
		r6 = r11;
		for ( ; r7 < 128; r7 += 2) {
			if (r6 < 0) {
				r9 |= PC2[r7];
				r8 |= PC2[r7+1];
			}
			r6 += r6;
		}
		if (direction != 0) {
			keys_L[15 - f4] = r9;
			keys_H[15 - f4] = r8;
		} else {
			keys_L[f4] = r9;
			keys_H[f4] = r8;
		}
	}
}
