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

#include "compiler.h"
#include "op.h"
#include "toktyp.h"
#include "mmemory.h"
#include "advancewindow.h"

error_def(ERR_COMMA);



int f_listsame(oprtype *a, opctype op)
{
	mval		tmp_mval;
	triple		*r;
    oprtype    *newop;
    
	DCL_THREADGBL_ACCESS;
	SETUP_THREADGBL_ACCESS;

	r = maketriple(op);
	if (EXPR_FAIL == expr(&(r->operand[0]), MUMPS_STR))
		return FALSE;

	if (TK_COMMA != TREF(window_token))
	{
		stx_error(ERR_COMMA);
		return FALSE;
	}
   	advancewindow();
   	if (EXPR_FAIL == expr(&(r->operand[1]), MUMPS_STR))
		     return FALSE;
        
	ins_triple(r);
   *a = put_tref(r);
	return TRUE;
}
