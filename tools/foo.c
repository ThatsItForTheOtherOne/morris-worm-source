main() {
	char	buf[1024];
	int	n;
	char	*p;

	while ((n = read(0, buf, sizeof(buf))) > 0) {
		XS(buf, n);
		write(1, buf, n);
	}
}

XS(s, n)
	char	*s;
	int	n;
{
	while (n--) {
		*s ^= 0x81;
		s++;
	}
}
