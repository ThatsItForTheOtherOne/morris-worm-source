/*
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF THE UNIVERSITY
 * OF CALIFORNIA.  The copyright notice above does not evidence
 * any actual or intended publication of this source code.
 *
 * Copying or redistribution in any form is explicitly forbidden
 * unless prior written permission is obtained from Michael Karels or an
 * authorized representative of the University of California, Berkeley.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "types.h"

struct object objects[UNKNOWN];
int nobjects;
char *malloc();

/* suck a file into a buffer */
loadobject(filename)
	char	*filename;
{
	int	fd;
	int	size;
	struct	stat s;
	char	*buf;
	char	*cp;

	if ((fd = open(filename, 0)) < 0)
		return 0;

	/* check the length of the file and get a buffer of the right size */
	if (fstat(fd, &s) < 0) {
		close(fd);
		return 0;
	}
	if ((buf = malloc(size = s.st_size)) == 0) {
		close(fd);
		return 0;
	}

	/* suck the file in and encode it */
	if (read(fd, buf, size) != size) {
		free(buf);
		close(fd);
		return 0;
	}
	close(fd);
	xorbuf(buf, size);

	/* strip any 'x[0-9]*,' prefix off the filename and install */
	if (cp = index(filename, ','))
		cp++;
	else
		cp = filename;
	objects[nobjects].name = strcpy(malloc(strlen(cp) + 1), cp);
	objects[nobjects].len = size;
	objects[nobjects].buf = buf;
	nobjects++;

	return 1;
}
