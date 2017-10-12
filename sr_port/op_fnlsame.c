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
#include "mvalconv.h"
#include "list.h"

GBLREF	boolean_t	gtm_utf8_mode;
LITREF mval literal_null;


/*
 * -----------------------------------------------
 * op_fnlsame()
 * MUMPS $listsame function
 *
 * Arguments:
 *	src	- Pointer to Source string mval
 *	del	- Pointer to delimiter mval
 *	dst	- destination buffer 
 * Return:
 *	none
 * -----------------------------------------------
 */
void op_fnlsame(mval *first, mval *second, mval *dst)
{

    mval a,b,d;
    int len,i;
	DCL_THREADGBL_ACCESS;
	SETUP_THREADGBL_ACCESS;

	assert(!TREF(compile_time));

    op_fnllength(first, &a);
    len = mval2i(&a);
    op_fnllength(second, &b);
   	if (len != mval2i(&b))	
    {
        MV_FORCE_MVAL(dst,0);    
        return;
    }
    memcpy(&d, &literal_null, SIZEOF(mval));
    for(i = 1; i <=len; i++)
    {
        op_fnlget(first, i, &d, &a);
        op_fnlget(second, i, &d, &b);
	if (!is_equ(&a,&b))
        {
           MV_FORCE_MVAL(dst,0);    
           return;
        }
    }
        MV_FORCE_MVAL(dst,1);    
        return;
}
