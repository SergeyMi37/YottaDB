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
#include "mvalconv.h"
#include "list.h"

void op_fnllength(mval *src, mval *dst)
{
	int count;
	mstr_len_t len;

	char  *dstend;
	char *ptr;

	error_def(ERR_LISTERR);
	MV_FORCE_STR(src);

	count = 0;
	ptr = src->str.addr;
	dstend = ptr + src->str.len;
	while (ptr < dstend) {
	    ptr = next_list(ptr,dstend);
	    if(ptr == 0) rts_error(VARLSTCNT(1) ERR_LISTERR);
	    count++;
	}
	MV_FORCE_MVAL(dst, count);

	return;		

	
	
}
