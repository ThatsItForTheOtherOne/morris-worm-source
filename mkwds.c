#include <stdio.h>

main()
{
	char buf[512];
	int i;

	printf("char *wds[] = {\n");

	while(gets(buf)){
		printf("\t\"");
		for(i = 0; buf[i]; i++)
			printf("\\%03o", buf[i] | 0x80);
		printf("\",\n");
	}
	printf("\t0\n};\n");
	exit(0);
}
