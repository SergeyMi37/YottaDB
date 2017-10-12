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
#include "mmemory.h"


int f_listget(oprtype *a, opctype op)
{
	triple *r, *arg;
	oprtype         result, *result_ptr;

	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;

	
	result_ptr = (oprtype *)mcalloc(sizeof(oprtype));
	result = put_indr(result_ptr);
	
	r = maketriple(op);

	if (EXPR_FAIL == expr(&(r->operand[0]), MUMPS_STR))
		return FALSE;
	arg = newtriple(OC_PARAMETER);
	
	if (TREF(window_token) != TK_COMMA)
	{
	    arg->operand[0] = put_ilit(1);
	    arg->operand[1] = put_str(0,0);
        } else {
	    advancewindow();
	    if (EXPR_FAIL == expr(&(arg->operand[0]), MUMPS_INT))
		return FALSE;
	    if (TREF(window_token) == TK_COMMA)
	    {
		advancewindow();
		if (EXPR_FAIL == expr(&(arg->operand[1]), MUMPS_STR))
			return FALSE;
	    } else
		arg->operand[1] = put_str(0,0);
	}
	
	r->operand[1] = put_tref(arg);
	
	ins_triple(r);
	*a = put_tref(r);
	return TRUE;
}
