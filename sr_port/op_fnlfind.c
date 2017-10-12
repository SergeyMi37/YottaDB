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
#include "gtm_string.h"
#include "mvalconv.h"
#include "list.h"

LITREF mval literal_null;

void op_fnlfind(mval *src, mval *val, int pos, mval *dst)
{
    int len;
    int ret = 0;
    mval tmp,*t;
	DCL_THREADGBL_ACCESS;
	SETUP_THREADGBL_ACCESS;
    
    if(pos > -1)
    {
       pos++;
       op_fnllength(src, &tmp);
       len = mval2i(&tmp);
       MV_FORCE_STR(val);
       for(;pos <= len; pos++)
       {
           list_elem(src,pos,&tmp);
           t = &tmp;
           if (MV_DEFINED(t))
	    {
		if( is_equ(&tmp, val) )
        	{
            	    ret = pos;
            	    break;
        	}
	    }
       }
    }
    MV_FORCE_MVAL(dst,ret);
    return;
	
}
