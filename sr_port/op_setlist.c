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

#include "gtm_string.h"
#include "stringpool.h"
#include "min_max.h"
#include "op.h"
#include "list.h"

GBLREF spdesc		stringpool;
LITREF	mval		literal_null;

error_def(ERR_MAXSTRLEN);


void op_setlist(mval *src, mval *expr, int spos, int epos, mval *dst)
{

	unsigned int	prev_len, after_len, after_start, expr_len, maxlen;
	char	*prev_p, *tmp, *srcend, *base;

	int num_prev, num_empty;

	error_def(ERR_LISTERR);
	error_def(ERR_LISTRANGE);
	if (MV_DEFINED(src)) {
	    MV_FORCE_STR(src);
	} else {
	    *src = literal_null;
	}
        prev_p = src->str.addr;
        srcend = prev_p + src->str.len;

	if (spos < -1) rts_error(VARLSTCNT(1) ERR_LISTRANGE);

	if (spos == 0) rts_error(VARLSTCNT(1) ERR_LISTERR);
	tmp = prev_p;
	expr_len = 0;		/* Len of inserted element */
	num_prev = 0;		/* Num of elements to copy before inserted element */
	prev_len = after_len = after_start = 0;
	if (srcend > prev_p) {
		if (spos == -1) {	/* Replace last element */
		    while (prev_p < srcend) {
			tmp = prev_p;
			prev_p = next_list(prev_p, srcend);
			num_prev++;				/* Num real elements before insert */
		    }
		    num_empty = 0;	/* No empty elements to insert */
		    prev_len = tmp - src->str.addr;
		} else {
		    while (prev_p < srcend)
    		    {
			    tmp = prev_p;
            		    prev_p = next_list(prev_p, srcend);
            		    num_prev++;
			    if (num_prev == spos) break;
		    }
		    num_empty = spos - num_prev;
		    if (num_empty == 0 ) {
			    prev_len = tmp - src->str.addr;
    			    after_start = prev_len + (prev_p - tmp);
			    after_len = src->str.len - after_start;
		    } else {
			    prev_len = src->str.len;
		    }
            if (num_empty) num_empty--;
		}
	} else {
	    if (spos > 0) num_empty = spos - 1;
	}
	expr_len = list_add(0,expr);
	maxlen = expr_len + prev_len + after_len + num_empty;
	if (maxlen > MAX_STRLEN)
		rts_error(VARLSTCNT(1) ERR_MAXSTRLEN);
	base = (char *)stringpool.free;
	ENSURE_STP_FREE_SPACE(maxlen);
	if (base != (char *)stringpool.free)
	{
	    memcpy(stringpool.free,base,expr_len);
	    base = (char *)stringpool.free;
	}

	if ( (prev_len + num_empty) > 0 )
	{
	    memmove(base + prev_len + num_empty, base, expr_len);
	    memcpy(base,src->str.addr,prev_len);
	    base += prev_len;
	    while(num_empty--) *base++ = 1;
	}
        base += expr_len;

	if (after_len > 0) memcpy(base,src->str.addr + after_start, after_len);
	dst->mvtype = MV_STR;
	dst->str.len = maxlen;
	dst->str.addr = (char *)stringpool.free;
	stringpool.free += maxlen;
}

