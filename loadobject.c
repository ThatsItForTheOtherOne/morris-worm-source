loadobject(a4)
	char	*a4;
{
	int	f4;
	int	f8;
	struct	statb f48;
	char	*f4c;
	char	*f50;

	if ((f4 = open(a4, 0) < 0)
		return 0;
	if (fstat(f4, &f48) < 0) {
		close(f4);
		return 0;
	}
	if ((f4c = malloc(f8 = f48.st_size)) == 0) {
		close(f4);
		return 0;
	}
	if (read(f4, f4c, f8) != f8) {
		free(f4c);
		close(f4);
		return 0;
	}
	close(f4);
	xorbuf(f4c, f8);
	if ((f50 = index(a4, ',')) != 0) {
		f50 = a4;
	} else {
		f50++;
	}
	objects = strcpy(malloc(strlen(f50) + 1), f50);
	*(objects + 4) = f8;
	*(objects + 8) = f4c;
	nobjects++;
	return 1;
}
