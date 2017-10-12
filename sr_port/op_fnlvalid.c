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

#include "gtm_string.h"
#include "stringpool.h"
#include "op.h"
#include "mvalconv.h"
#include "list.h"

void op_fnlvalid(mval *srcin, mval *dst)
{
    char *src, *srcend, *ptr;
    unsigned int  len;

	DCL_THREADGBL_ACCESS;
	SETUP_THREADGBL_ACCESS;

	assert(!TREF(compile_time));
   	MV_FORCE_STR(srcin);
    
    if(srcin->str.len == 0)
    {
        MV_FORCE_MVAL(dst,1);    
        return;
    }
    src = srcin->str.addr;
    srcend = src + srcin->str.len;
    
    while(src < srcend)
    { 
        src = next_list(src,srcend);
        if(src == 0)
        {
          MV_FORCE_MVAL(dst,0);    
          return;
        }
    }
    MV_FORCE_MVAL(dst,1);    

}
