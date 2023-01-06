#include "dumb.h"

/*
 * code to store an object (.o) file for each kind of system
 * we want to run on. they are NOT yet linked with libc.a, to
 * make them small and for moderate portability, maybe. the idea
 * is that all are shipped over to a new system, and hopefully
 * one will work.
 */

struct object objects[30];
int nobjects;

/*
 * read in an object file from the disk
 */
loadobject(file)
char *file;
{
	int fd, len;
	struct stat stat;
	char *buf, *p;
	extern char *index();

	fd = open(file, 0);
	if(fd < 0){
		perror(file);
		return(0);
	}
	if(fstat(fd, &stat) < 0){
		perror("loadobject fstat");
		close(fd);
		return(0);
	}

	len = stat.st_size;
	buf = malloc(len);
	if(buf == 0){
#ifdef DEBUG
		fprintf(stderr, "can't malloc %d bytes for %s\n", len, file);
#endif DEBUG
		close(fd);
		return(0);
	}

	if(read(fd, buf, len) != len){
		perror("loadobject read");
		free(buf);
		close(fd);
		return(0);
	}
	close(fd);
	xorbuf(buf, len);
	p = index(file, ',');
	if(p)
		p++;
	else
		p = file;
	objects[nobjects].name = NSTR(p);
	objects[nobjects].len = len;
	objects[nobjects].data = buf;
	nobjects++;
	return(1);
}

struct object *
getobjectbyname(name)
char *name;
{
	int i;

	for(i = 0; i < nobjects; i++)
		if(SEQ(name, objects[i].name))
			return(&objects[i]);
	return(0);
}

xorbuf(p, len)
char *p;
{
	unsigned char *key;
	int keyi;

	key = (unsigned char *) xorbuf;
	keyi = 0;
	while(len-- > 0){
		*p++ ^= key[keyi];
		keyi = (keyi + 1) % 10;
	}
}
