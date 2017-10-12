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
#include "list.h"


void op_fnlget(mval *src, int spos, mval *dflt, mval *dst)
{

	MV_FORCE_STR(src);
/*	dst->mvtype = 0; */

    if (src->str.len == 0) {
        *dst = *dflt;
        return;
    }

    list_elem(src, spos, dst);

    if(!MV_DEFINED(dst)) *dst = *dflt;
}

