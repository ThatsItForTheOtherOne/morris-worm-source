#include <stdio.h>

main()
{
	int c, i, sharp;
	char buf[512];

	sharp = 0;
	while((c = getchar()) != EOF){
		if(c != '\"' || sharp){
			putchar(c);
			if(c == '#')
				sharp = 1;
			else if(c == '\n')
				sharp = 0;
			continue;
		}

		i = 0;
		while(1){
			c = getchar();
			if(c == EOF){
				fprintf(stderr, "EOF in string\n");
				exit(1);
			}
			if(c == '\\'){
				c = getchar();
				switch(c){
				case '"':
					buf[i++] = '"';
					break;
				case 'n':
					buf[i++] = '\n';
					break;
				default:
fprintf(stderr, "unknown \\ escape %c\n", c);
					exit(1);
				}
			} else if(c == '"'){
				break;
			} else
				buf[i++] = c;
		}
		buf[i] = '\0';
		printf("XS(\"");
		for(i = 0; buf[i]; i++)
			printf("\\%03o", buf[i] ^ 0x81);
		printf("\")");
	}
	exit(0);
}
