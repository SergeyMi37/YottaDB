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
#include "opcode.h"
#include "toktyp.h"
#include "advancewindow.h"


int f_listupdt(oprtype *a, opctype op)
{

	int	argc;
	oprtype	*argp, argv[CHARMAXARGS],tmp;
	triple	*curr,*ref, *last, *root;
    boolean_t was_colon = FALSE;
    DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
    
    error_def(ERR_COMMA);
    error_def(ERR_FCHARMAXARGS);

	argp = &argv[0];
	argc = 0;
	if (EXPR_FAIL == expr(argp, MUMPS_EXPR))
		return FALSE;
	assert(TRIP_REF == argp->oprclass);
	argc++;
	argp++;
    if (TK_COMMA != TREF(window_token))
    {
       stx_error(ERR_COMMA);
       return FALSE;     
    }
	advancewindow();
	if (EXPR_FAIL == expr(argp, MUMPS_EXPR))
		return FALSE;
	assert(TRIP_REF == argp->oprclass);
	argc++;
	argp++;
    if (TK_COMMA != TREF(window_token))
    {
       stx_error(ERR_COMMA);
       return FALSE;     
    }
	while (TK_COMMA == TREF(window_token))
	{
		advancewindow();
        if(TK_COMMA == TREF(window_token) || TK_RPAREN == TREF(window_token))
        {
           *argp = put_str("0",1);
           argc++;
	    	argp++;
		    if (argc >= CHARMAXARGS)
		    {
		       stx_error(ERR_FCHARMAXARGS);
		       return FALSE;
		    }
           *argp = put_str("0",1);
           argc++;
	    	argp++;
		    if (argc >= CHARMAXARGS)
		    {
		       stx_error(ERR_FCHARMAXARGS);
		       return FALSE;
		    }
           continue;
        }
        if(TK_COLON == TREF(director_token))
        {
		     if (EXPR_FAIL == expr(argp, MUMPS_EXPR))
				     return FALSE;
		     assert(TRIP_REF == argp->oprclass);
            advancewindow();
        }
        else
        {
             *argp = put_str("1",1);
        }
        argc++;
		 argp++;
		 if (argc >= CHARMAXARGS)
		 {
		    stx_error(ERR_FCHARMAXARGS);
		    return FALSE;
		 }
        if (EXPR_FAIL == expr(argp, MUMPS_EXPR))
				     return FALSE;
	    assert(TRIP_REF == argp->oprclass);
        argc++;
	    argp++;
		if (argc >= CHARMAXARGS)
		{
			      stx_error(ERR_FCHARMAXARGS);
			      return FALSE;
		}
	}
	root = last = maketriple(op);
	root->operand[0] = put_ilit(argc + 1);
	argp = &argv[0];
	for (; argc > 0 ;argc--, argp++)
	{
		curr = newtriple(OC_PARAMETER);
		curr->operand[0] = *argp;
		last->operand[1] = put_tref(curr);
		last = curr;
	}
	ins_triple(root);
	*a = put_tref(root);
	return TRUE;
	
}
