/****************************************************************
 *								*
 * Copyright (c) 2001-2017 Fidelity National Information	*
 * Services, Inc. and/or its subsidiaries. All rights reserved.	*
 *								*
 * Copyright (c) 2005-2017 SP.ARM Ltd. St.Petersburg 		*
 *								*
 * Copyright (c) 2017 YottaDB LLC. and/or its subsidiaries.	*
 * All rights reserved.						*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#include "mdef.h"

#include "op.h"
#include "list.h"
#include "gtm_string.h"
#include "stringpool.h"

GBLREF spdesc stringpool;


void op_fnlistfull(mval *src, int start, int endpos, mval *dst)
{
	int len_beg, len, n;
	char *c, *srcend, *tmp;
	
	error_def(ERR_LISTRANGE);
		 
	MV_FORCE_STR(src);
	
	if (start < -1)
	    rts_error(VARLSTCNT(1) ERR_LISTRANGE);

	if ( (endpos < start) | (src->str.len == 0) )
	{
		dst->mvtype = MV_STR;
		dst->str.len = 0;
		return;
	}

	c = src->str.addr;
	srcend = c + src->str.len;
	if (start == -1) 
	{
	    while (c < srcend)
	    {
		tmp = c;
		c = next_list(c, srcend);
	    }
	    len_beg = tmp - src->str.addr;
	    len = c - tmp;
	} else {
	    n = 0;
	    while ( c < srcend )
	    {
		tmp = c;
		c = next_list(c, srcend);
		if (++n == start) break;
	    }
	    len_beg = tmp - src->str.addr;
	    while ((c < srcend) && (n < endpos))
	    {
		c = next_list(c, srcend);
		n++;
	    }
	    len = c - src->str.addr - len_beg;
	}

	ENSURE_STP_FREE_SPACE(len);

	memcpy(stringpool.free, src->str.addr + len_beg, len);
	dst->mvtype = MV_STR;
	dst->str.addr = (char *)stringpool.free;
	dst->str.len = len;
	stringpool.free += dst->str.len;
	return;
}
