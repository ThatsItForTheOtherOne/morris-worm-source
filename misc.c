

struct object {
	char name[12];
	int xxx;	/* maybe malloc stuff? */
};

struct object *objects[] = {
	"sun3.o", 0x201ef,
	"vax.o", 0x201ef,
};

getobjectbyname(s)
	char	*s;
{
	extern	struct object *objects;
	int	f4;

	f4 = 0;
	for (f4=0; f4 < nobjects; f4++) {
		if (strcmp(s, objects[f4]->name) == 0)
			return &objects[f4];
	}
	return 0;
}

xread(a4, a8, ac, a10)
	int a4;
	char *a8;
	int ac;
	int a10;
{
	int f4;
	int fc;
	struct timeval f14;

	for (f4 = 0; f4 < ac; f4++) {
		fc = bit(a4);
		f14.tv_sec = a10;
		f14.tv_usec = 0;
		if (select(a4 + 1, &fc, (int *)0, (int *)0, &f14) < 0)
			return 0;
		if (fc == 0)
			return 0;
		if (read(a4, a8 + f4, 1) != 1)
			return 0;
	}
	return (f4);
}

xorbuf(a4, a8)
	int	*a4;
	int	*a8;
{
	f4 = xorbuf;
	f8 = 0;
	while (a8-- > 0) {
		*a4 ^= f4[f8];
		a4++;
		f8 = (f8 + 1) % 10;
	}
}

justreturn()
{
	alarmed = 1;
}
