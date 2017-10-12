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
#include "arit.h"
#include "gtm_maxstr.h"
#include "gtm_string.h"

#include "stringpool.h"
#include "op.h"
#include "list.h"

#include <stdarg.h>
#include "mv_stent.h"
#include "mvalconv.h"

GBLREF spdesc stringpool;

void op_fnlbuild(UNIX_ONLY_COMMA(int cnt) mval *dst, ...)
{
    va_list 	var;
    mval 	*in;
    int 	maxlen;

    error_def(ERR_LISTERR);

    VMS_ONLY(int	cnt;)
    VAR_START(var, dst);
    VMS_ONLY(va_count(cnt);)
    cnt -= 1;

    maxlen=0;
    while (cnt-- > 0)
    {
	in = va_arg(var, mval *);
	maxlen = list_add(maxlen, in);
    }

    va_end(var);

    dst->mvtype = MV_STR;
    dst->str.addr = (char *)stringpool.free;
    dst->str.len = maxlen;		/* INTCAST((char *)base - dst->str.addr); */
    stringpool.free += maxlen; 		/* dst->str.len; */
}

