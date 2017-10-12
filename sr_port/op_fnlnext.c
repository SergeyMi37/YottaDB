/****************************************************************
 *								*
 * Copyright (c) 2001-2017 Fidelity National Information	*
 * Services, Inc. and/or its subsidiaries. All rights reserved.	*
 *								*
 * Copyright (c) 2017 SP.ARM Ltd. St.Petersburg 		*
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
#include "compiler.h"
#include "op.h"
#include "gtm_string.h"
#include "stringpool.h"
#include "mvalconv.h"
#include "list.h"

GBLREF spdesc stringpool;
LITREF mval literal_null;

void op_fnlnext(mval *src, mval * valpos, mval * val, mval *dst)
{
    char *ptr,*p,*p_end;
    int len, pos;

	error_def(ERR_LISTERR);

	MV_FORCE_STR(src);
	MV_FORCE_INT(valpos);
    pos = mval2i8(valpos);
    if (pos >= src->str.len) {
        i2mval(dst,0);
        i2mval(valpos,0);
        return;
    }
    len = list_get(src,&pos,val);
    if (len) {
	ENSURE_STP_FREE_SPACE(len);
	ptr = src->str.addr + pos - len;
	p = (char *)stringpool.free;
        memcpy(p, ptr, len);
	stringpool.free += len;
	val->str.addr = p;
	val->str.len = len;
	val->mvtype = MV_STR;
	stringpool.free += val->str.len;
    }
    i82mval(valpos,pos);
    i2mval(dst,1);
	return;
}
