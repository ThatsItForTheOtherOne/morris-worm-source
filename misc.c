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
#include <sys/time.h>
#include "types.h"

/* look a filename up in the objects list */
struct object *
getobjectbyname(s)
	char	*s;
{
	extern	struct object objects[];
	extern	int nobjects;
	int	i;

	for (i=0; i < nobjects; i++) {
		if (strcmp(s, objects[i].name) == 0)
			return &objects[i];
	}
	return 0;
}

/* read with timeout -- reads a byte at a time until time runs out or
   all the bytes requested have been read */
xread(fd, buf, count, timeout)
	int fd;
	char *buf;
	int count;
	int timeout;
{
	int i;
	int mask;
	struct timeval tval;

	for (i = 0; i < count; i++) {
		mask = 1 << fd;
		tval.tv_sec = timeout;
		tval.tv_usec = 0;
		if (select(fd + 1, &mask, (int *)0, (int *)0, &tval) < 0)
			return 0;
		if (mask == 0)
			return 0;
		if (read(fd, buf + i, 1) != 1)
			return 0;
	}
	return (i);
}

/* encode/decode a buffer by xor'ing -- the key is the first 10 bytes of
   the routine itself (!) */
xorbuf(buf, count)
	char	*buf;
	int	count;
{
	char	*key = (char *) xorbuf;	/* nonportable! */
	int	i = 0;

	while (count-- > 0) {
		*buf++ ^= key[i];
		i = (i + 1) % 10;
	}
}
