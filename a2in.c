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
#include <sys/socket.h>
#include <netinet/in.h>

/*
 * Convert a u_long address to a struct in_addr.
 */
struct in_addr
a2in(addr)
	u_long addr;
{
	struct in_addr ret;

	ret.s_addr = addr;
	return ret;
}
