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
#include "mvalconv.h"

void op_fnldata(mval *src, int pos, mval *dst)
{
	char 	*p, *srcend;

	error_def(ERR_LISTERR);

	MV_FORCE_STR(src);

	if ((src->str.len == 0) || (pos == 0))
    {
        MV_FORCE_MVAL(dst,0);
        return;
    }

	p = src->str.addr;
	srcend = src->str.addr + src->str.len;
	while(--pos) {
	    p = next_list(p, srcend);
	    if (p == 0) rts_error(VARLSTCNT(1) ERR_LISTERR);
	    if (p == srcend) break;
	}
	if ((p == srcend) || (*p == 1))
    {
        MV_FORCE_MVAL(dst,0);
        return;
    }
	if(next_list(p, srcend) == 0) rts_error(VARLSTCNT(1) ERR_LISTERR); /* Generate error if this element is broken */
	MV_FORCE_MVAL(dst,1);
	return;
}
