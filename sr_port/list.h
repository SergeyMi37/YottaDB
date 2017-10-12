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

#ifndef LIST_included
#define LIST_included

/*void stp_gcolEx(int space_asked, unsigned char **base);
void stp_gcolEx2(int delta_space_asked, unsigned char **base); */
void list_next(unsigned char *src, unsigned int srcL, unsigned char *srcmarker, int count, unsigned char **rslt, unsigned int *xcount);
void list_addx(mval *src, int ipos, mval *dst);

/*void xl2mval(mval *v, long long i); */
void mval2iEx(mval *v, unsigned long *i, unsigned short int *sign, short int *exp);
void mval2iExD(mval *v, unsigned long *i, unsigned short int *sign, short int *exp);
char list_getD(unsigned char *c, unsigned int lilen, double *dx);

char* next_list(char *src, char *srcend);
int len_list_element (char **ptr, char *srcend);
char * liststr(char * src,char *src_top,char *del,char *del_top);
int list_add(int space, mval *in);
int list_get(mval *src, mstr_len_t *pos, mval *dst);
void list_elem(mval *src, int pos, mval *dst);
#endif

