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
#include "compiler.h"
#include "op.h"
#include "toktyp.h"
#include "opcode.h"
#include "advancewindow.h"

int f_listts(oprtype *a, opctype op)
{
	triple		*r, *arg;
    
	DCL_THREADGBL_ACCESS;
	SETUP_THREADGBL_ACCESS;

	r = maketriple(op);
	if (EXPR_FAIL == expr(&(r->operand[0]), MUMPS_STR))
		return FALSE;
	arg = newtriple(OC_PARAMETER);
	if (TK_COMMA != TREF(window_token))
	{
	    arg->operand[0] = put_str(",",1);
        arg->operand[1] = put_ilit(0);
	}
    else
    {
    	advancewindow();
    	if (EXPR_FAIL == expr(&(arg->operand[0]), MUMPS_STR))
		     return FALSE;
	    if (TK_COMMA != TREF(window_token))
	    {
           arg->operand[1] = put_ilit(0);
	    }
        else
        {
        	advancewindow();
        	if (EXPR_FAIL == expr(&(arg->operand[1]), MUMPS_INT))
		        return FALSE;
        }
        
    }

	r->operand[1] = put_tref(arg);
		    
	ins_triple(r);
	*a = put_tref(r);
	return TRUE;
}
