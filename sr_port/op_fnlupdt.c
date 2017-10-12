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
#include "op.h"
#include "list.h"

#include <stdarg.h> 
#include "mv_stent.h"
#include "mvalconv.h"
#include "math.h"
#include "gtm_maxstr.h"


GBLREF spdesc stringpool;

void op_fnlupdt(UNIX_ONLY_COMMA(int cnt) mval *dst, ...)
{
	va_list 	var;
	mval *in_list;
    int len_list, curr_list_index = 1, updt_index; 
    int updt;
    mval a;
    char * in_base, *in_base_end;
    char * p;
    int delta; 
    int len;

    MAXSTR_BUFF_DECL(buff);

	error_def(ERR_LISTERR);

	mval *in;
	int maxlen;
	
	char 	*base;

	VMS_ONLY(int	cnt;)
	VAR_START(var, dst);
	VMS_ONLY(va_count(cnt);)

	in_list = va_arg(var, mval *);
    op_fnllength(in_list, &a);
    len_list = mval2i(&a);
    in_base = in_list->str.addr;
    in_base_end = in_base + in_list->str.len;
    cnt--;

	in = va_arg(var, mval *);
    MV_FORCE_INT(in);
    updt_index = mval2i(in);
	cnt--;
    MAXSTR_BUFF_INIT;

    if(updt_index < 1)
    {
        if (!IS_STP_SPACE_AVAILABLE(in_list->str.len))
	      	   INVOKE_STP_GCOL(in_list->str.len);
	          assert(IS_STP_SPACE_AVAILABLE(in_list->str.len));
              memcpy(stringpool.free,in_list->str.addr,in_list->str.len); 
	          MAXSTR_BUFF_FINI;
	
              dst->mvtype = MV_STR;
	          dst->str.addr = (char *)stringpool.free;
	          dst->str.len = in_list->str.len;
	          stringpool.free += dst->str.len;
              return;
    }
    base = &buff[0];
    maxlen=0;	
    while(curr_list_index < updt_index && curr_list_index <= len_list)
    {
        p = next_list(in_base, in_base_end);
        delta = p - in_base;
        maxlen += delta;
        memcpy(base,in_base,delta);
        base += delta;
        in_base = p;
        curr_list_index++;
    }
    while(curr_list_index < updt_index)
    {
        maxlen++;
        *base++ = 1;
        curr_list_index++;
    }
	while (cnt > 1)
	{
		in = va_arg(var, mval *);
        cnt--;
       MV_FORCE_INT(in);
       updt = mval2i(in);
		in = va_arg(var, mval *);
       cnt--;
       if(updt)
       {
           len = list_add(0, in);   
           memcpy(base,stringpool.free,len);
           base += len;
           maxlen += len; 
           if(in_base < in_base_end)
                in_base = next_list(in_base, in_base_end);
       }
       else
       {
              if(in_base < in_base_end)
              {
                   p = next_list(in_base, in_base_end);
                   delta = p - in_base;
                   maxlen += delta;
                   memcpy(base,in_base,delta);
                   base += delta;
                   in_base = p;
              }
              else
              {
                 maxlen++;
                 *base++ = 1;
              }
       }
	}


	va_end(var);
   if (!IS_STP_SPACE_AVAILABLE(maxlen))
		INVOKE_STP_GCOL(maxlen);
	assert(IS_STP_SPACE_AVAILABLE(maxlen));
   memcpy(stringpool.free,buff,maxlen); 
	MAXSTR_BUFF_FINI;
	
    dst->mvtype = MV_STR;
	dst->str.addr = (char *)stringpool.free;
	dst->str.len = maxlen;
	
	stringpool.free += dst->str.len;
	

}
