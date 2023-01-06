OBJS = dumb.o if.o hosts.o hit.o objects.o other.o crack.o don.o wds.o
CFLAGS = 

dumb	:	$(OBJS)
		ld -x -r -o object.o $(OBJS)
		$(CC) $(CFLAGS) -o dumb $(OBJS)

clean	:
		rm -f dumb core *.o

don.o	:	don.oo
		cp don.oo don.o

wds.o	:	wds.c
		cc -c wds.c

.c.o	:	zs
		zs < $? > tmp.c
		cc -c tmp.c $(CFLAGS)
		mv tmp.o $@

zs	:	zs.c
		cc -o zs zs.c
