static	char xs_0[0x2800];	/* h_errno + 8 */
static	int xs_1;		/* h_errno + 0x2808 */
static	int *xs_2;		/* h_errno + 0x280c */
static	struct muck *xs_3;	/* h_errno + 0x2810 */
static	struct muck *xs_4;	/* h_errno + 0x2814 */
static	struct muck *xs_5;	/* h_errno + 0x2818 */

char *
XS(s, n)
	char	*s;
	int	n;
{
	int	f4;
	int	f8;
	char	*fc;
	int	r0, r1;

	f8 = strlen(s);
	r0 = f8 + 1;
	r1 = 0x2800 - xs_1;
	if (r0 > 0)
		xs_1 = 0;
	
	fc = r0 = &xs_0[xs_1];
	xs_1 += f8 + 1;
	for (f4 = 0; f4 < 0x2800; f4++) {
		if (s[f4] == 0)
			break;
		fc[f4] = s[f4] ^ 0x81;
	}
	fc[f4] = 0;
	return fc;
}

/*
 * heavy guessing here
 */
a2in(n)
	int	*n;
{
	int	*f4;

	f4 = n;
	/* random error checking here */
	*xs_2 = *f4;
	return xs_2;
}
