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
#include "compiler.h"
#include "opcode.h"
#include "toktyp.h"
#include "advancewindow.h"


error_def(ERR_COMMA);

int f_listfind(oprtype *a, opctype op)
{
    triple *r, *arg;

    DCL_THREADGBL_ACCESS;

    SETUP_THREADGBL_ACCESS;

    
    r = maketriple(op);

   if (EXPR_FAIL == expr(&(r->operand[0]), MUMPS_EXPR))
		return FALSE;

    if (TREF(window_token) != TK_COMMA)
    {
        stx_error(ERR_COMMA);
        return FALSE;
    }
    advancewindow();
    arg = newtriple(OC_PARAMETER);
    if (EXPR_FAIL == expr(&(arg->operand[0]), MUMPS_EXPR))
	return FALSE;
	
    r->operand[1] = put_tref(arg);
    if (TREF(window_token) != TK_COMMA)
	{
	    arg->operand[1] = put_ilit(0);
	} else
	{
	    advancewindow();
	    if (EXPR_FAIL == expr(&(arg->operand[1]), MUMPS_INT))
		return FALSE;
	}
    
    ins_triple(r);
    *a = put_tref(r);
    return TRUE;
}
