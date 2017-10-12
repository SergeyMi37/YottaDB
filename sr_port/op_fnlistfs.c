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
#include "op.h"
#include "gtm_string.h"
#include "matchc.h"
#include "fnpc.h"
#include "stringpool.h"
#include "list.h"

GBLREF spdesc stringpool;
GBLREF	boolean_t	gtm_utf8_mode;
/*
GBLREF gd_region	*gv_cur_region;
*/

/*
 * -----------------------------------------------
 * op_fnlistfs()
 * MUMPS $listfromstring function
 *
 * Arguments:
 *	src	- Pointer to Source string mval
 *	del	- Pointer to delimiter mval
 *	dst	- destination buffer 
 *
 * Return:
 *	none
 * -----------------------------------------------
 */
void op_fnlistfs(mval *src, mval *del, mval *dst)
{
    char *src_top, *del_top;
	char *del_str, *src_str,*psrc;
	char *delp, *srcp;
    int maxlen = 0,len,delta;
    mval tmp_val;

	DCL_THREADGBL_ACCESS;
	SETUP_THREADGBL_ACCESS;

	assert(!TREF(compile_time) || valid_utf_string(&src->str));

	MV_FORCE_STR(src);
   	MV_FORCE_STR(del);
   	if (src->str.len < del->str.len)	
		     return;
     srcp = src->str.addr;       
     delp = del->str.addr;       
	 src_str = src->str.addr;
     src_top = src_str + src->str.len;
   	 del_str = del->str.addr;
    del_top = del_str + del->str.len;
    while((psrc = liststr(src_str,src_top,del_str,del_top)))
    {
        len = psrc - src_str;
        tmp_val.mvtype = MV_STR;
        tmp_val.str.len = len;
        tmp_val.str.addr = src_str;
        maxlen = list_add(maxlen,&tmp_val);
        if(srcp != src->str.addr)
        {
            delta = src->str.addr - srcp;
            src_str += delta;
            psrc += delta;
            src_top += delta;
            srcp = src->str.addr;       
        }
        if(delp != del->str.addr)
        {
            delta = del->str.addr - delp;
            del_str += delta;
            del_top += delta;
            delp = del->str.addr;       
        }
        src_str = psrc + del->str.len;
    }

	dst->mvtype = MV_STR;
	dst->str.addr = (char *)stringpool.free;
	dst->str.len = maxlen;
	
	stringpool.free += dst->str.len;
}

