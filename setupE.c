
int	E_L[48][16];
int	E_H[48][16];
char	E[32];

setupE()
{
	int	f4;
	int	f8;
	int	fc;

	f4 = 0;
	do {
		f8 = 0;
		do {
			E_L[f4][f8] = 0;
			E_H[f4][f8] = 0;
		} while (++f8 < 16);
	} while (++f4 < 8);
	f8 = 0;
	do {
		fc = 31 - E[f8];
		f4 = 0;
		do {
			if (f4 & (1 << (fc % 4))) {
				E_L[fc/4][f4] |= (1 << (31 - f8));
			}
		} while (++f4 < 16);
	} while (++f8 < 48);
	f8 = 32;
	do {
		fc = 31 - E[f8];
		f4 = 0;
		do {
			if (f4 & (1 << (fc % 4))) {
				E_H[fc/4][f4] |= (1 << (31 - f8));
			}
		} while (++f4 < 16);
	} while (++f8 < 48);
}
