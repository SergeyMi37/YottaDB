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
#include "op.h"
#include "error.h"
#include "matchc.h"
#include "fnpc.h"
#include "stringpool.h"
#include "errorsp.h"
#include "gtm_maxstr.h"
#include "list.h"

GBLREF spdesc stringpool;
GBLREF	boolean_t	gtm_utf8_mode;
LITREF mval literal_null;


/*
 * -----------------------------------------------
 * op_fnlistts()
 * MUMPS $listtostring function
 *
 * Arguments:
 *	src	- Pointer to Source list
 *	del	- Pointer to delimiter mval
 * flag- how to handle an omitted list element
 *	dst	- destination buffer
 *
 * Return:
 *	none
 * -----------------------------------------------
 */

void op_fnlistts(mval *src, mval *del, int flag, mval *dst)
{
    MAXSTR_BUFF_DECL(buff);
    char * base, *ptr;
    mstr_len_t len,pos = 0,maxlen = 0,srclen;
    int i;

    error_def(ERR_LISTNULL);

    DCL_THREADGBL_ACCESS;
	SETUP_THREADGBL_ACCESS;

	assert(!TREF(compile_time));

    MAXSTR_BUFF_INIT;
    base = &buff[0];
    MV_FORCE_STR(src);
    if(src->str.len == 0)
    {
        memcpy(dst,&literal_null,sizeof(mval));
        return;
    }
   	 MV_FORCE_STR(del);
   	 srclen = src->str.len;

    while (pos < srclen)
    {
         dst->mvtype = 0;
         len = list_get(src,&pos,dst);
         if (!flag && !MV_DEFINED(dst) && !len)
         {
           	MAXSTR_BUFF_FINI;
              rts_error(VARLSTCNT(1) ERR_LISTNULL);
         }
         if (len){
            ptr = src->str.addr + pos - len;
            memcpy(base,ptr,len);
            base += len;
            maxlen += len;
         } else {
            if (MV_DEFINED(dst))
            {
                MV_FORCE_STR(dst);
                memcpy(base,dst->str.addr,dst->str.len);
                base += dst->str.len;
                maxlen += dst->str.len;
            }
         }
         if (pos < srclen)
        {
            memcpy(base,del->str.addr,del->str.len);
            base += del->str.len;
            maxlen += del->str.len;
        }
        else
            break;

    }

  	if (!IS_STP_SPACE_AVAILABLE(maxlen))
		    INVOKE_STP_GCOL(maxlen);
    assert(IS_STP_SPACE_AVAILABLE(maxlen));
    memcpy(stringpool.free,buff,maxlen);

   	MAXSTR_BUFF_FINI;

	dst->mvtype = MV_STR;
	dst->str.addr = (char *)stringpool.free;
	dst->str.len = maxlen;
    stringpool.free += maxlen;
}

