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
#include "stringpool.h"
#include "list.h"

#include "arit.h"
#include "mvalconv.h"
#include "gtm_stdio.h"
#include "gtm_string.h"

#include "math.h"

GBLREF spdesc stringpool;

char * liststr(char * src,char *src_top,char *del,char *del_top)
{
    char *psrc = src;


    char *pdel = del;
    while(psrc < src_top)
    {
          while(*psrc != *pdel && psrc < src_top)
          {
              psrc++;
          }
          if(*psrc == *pdel)
          {
              char *ret = psrc;
              while(pdel < del_top && psrc < src_top && *psrc == *pdel)
              {
                  pdel++;
                  psrc++;
              }
              if(pdel == del_top)
                  return ret;
              pdel = del;
          }
    }
    if(src < psrc)
        return psrc;
    return 0;
}

int len_list_element (char **ptr, char *srcend)
{
    int len = 0;
    char *p, *tmp;

    p = *ptr;

    len += (unsigned char)*p++;
    if (len > 0)
    {
        *ptr = p;
        return --len; /* Single byte len    srcend = src->str.addr + src->str.len;
		      , pointer to type */
    } else {
        len += (unsigned char) *p++;
        len += ((unsigned char)*p++ * 256);
        if ( len == 0 )
        {
            p += 4;
            tmp = p;
            len += (unsigned char)*(--tmp);
            len <<= 8;
            len += (unsigned char)*(--tmp);
            len <<= 8;
            len += (unsigned char)*(--tmp);
            len <<= 8;
            len += (unsigned char)*(--tmp);
            if (len < 65536) return -1;   /* 4 byte len > 65534*/
        } else {
            if (len<255) return -1;       /* 2 byte len > 254 */
        }
    }
    *ptr = p;
    return len;
}

char* next_list(char *src, char *srcend)
{
    char *ptr;
    int  len;

    len = len_list_element(&src,srcend);
    if (len < 0) return 0;
    if(len) {
    switch (*src) {
    case 8:
	if (len != 10)  return 0; /* DOUBEL PRECISION have fixed length */
	    break;
	case 1:		/* STRING */
	case 2:		/* Unicode String */
	case 4:		/* INTEGER */
	case 5:		/* NEGATIV INTEGER */
	case 6:		/* FLOAT */
	case 7:		/* NEGATIV FLOAT */
	        break;
	default:
	        return 0;
	}
    }
    src += len;
    if (src > srcend) return 0;
    return src; /* Pointer to next element or end list */
}

int list_add(int space, mval *in) { /* Add one element in list */

    char 	*dst, *src;
    gtm_int64_t	rez,tmp;
    int 	l, need;
    signed char exp;
    unsigned char ch,typ,len;

    error_def(ERR_MAXSTRLEN);

        if (!MV_DEFINED(in))		/* Not defined element of list */
        {
            need = space +1;
            if (!IS_STP_SPACE_AVAILABLE(need))
            {
                src = (char *)stringpool.free;
                INVOKE_STP_GCOL(need);
                assert(IS_STP_SPACE_AVAILABLE(need));
                if (space > 0) memcpy(stringpool.free, src, space);
            }
            dst = (char *)stringpool.free + space;
            *dst = 1;
            space++;
        } else {
            if ((MV_IS_NUMERIC(in)) && MV_IS_CANONICAL(in)) {	/* Numeric value, may be integer */
                rez =(gtm_int64_t)in->m[1];
                if (MV_IS_INT(in)) {    /* Value from -999999 to 999999 */
                    exp = -3;
                } else	{
                    if (in->m[0]) {	/* Num of digits more then 9 */
                        rez = rez * MANT_HI + in->m[0];
                        exp = in->e - EXP_IDX_BIAQ;
                    } else {	/* Num of digits less then 10 */
                        exp = in->e - EXP_IDX_BIAL;
                    }
                }
                if (rez) {	/* Value not NULL, processing needed */
                    if (in->sgn) rez = -rez;
                    while (!(rez%10)) {
                        rez /= 10;
                        exp++;
                        if (exp == 0) break;
                    }
                    ch = 8;
                    tmp = 0xFF00000000000000;
                    if (rez > 0) {
                        typ = 4;		/* Positive integer */
                        while (!(tmp & rez)) {
                            tmp >>= 8;
                            ch--;
                        }
                    } else {
                        typ = 5;		/* Negative integer */
                        tmp = ~tmp;
                        while (((tmp | rez) == -1) && (ch > 0))
                        {
                            tmp >>= 8;
                            ch--;
                        }
                    }
                    len = 2 + ch;
                    if (exp != 0) {		/* Floating */
                        len++;		/* One byte exp */
                        typ += 2;
                    }
                } else {
                /* NULL value, finish */
                    typ = 4;
                    len = 2;
                    exp = 0;
                }
		need = space + len;
		if (!IS_STP_SPACE_AVAILABLE(need))
		{
		    src = (char *) stringpool.free;
		    INVOKE_STP_GCOL(need);
		    assert(IS_STP_SPACE_AVAILABLE(need));
		    if (space > 0) memcpy(stringpool.free, src, space);
		}
		dst = (char *)stringpool.free + space;
                *dst++ = len;
                *dst++ = typ;
                if (exp != 0) *dst++ = exp;
                while (ch--) {
                    *dst++ = (rez % 256);
                    rez >>= 8;
                }
            } else {	/* Element is string type */
                l = in->str.len;
                ch = (l < 254 ? 2 : l < 65535 ? 4 : 8);
                l = in->str.len + ch;
		need = space + l;
		if (!IS_STP_SPACE_AVAILABLE(need))
		{
		    src = (char *)stringpool.free;
		    INVOKE_STP_GCOL(need);
		    assert(IS_STP_SPACE_AVAILABLE(need));
		    if (space > 0) memcpy(stringpool.free, src, space);
		}
		dst = (char *)stringpool.free + space;
                if (ch == 2)			/* Single byte len */
                    *dst++ = (l % 256);
                else {
                    *dst++ = 0;
                    if (ch == 4) {
                        l -= 3;
                        *dst++ = (l % 256);
                        l >>= 8;
                        *dst++ = (l % 256);
                    } else {
                        *dst++ = 0;
                        *dst++ = 0;
                        l -= 7;
                        *dst++ = (l % 256);
                        l >>= 8;
                        *dst++ = (l % 256);
                        l >>= 8;
                        *dst++ = (l % 256);
                        l >>= 8;
                        *dst++ = (l % 256);
                    }
                }
                *dst++ = 1;
                memcpy(dst, in->str.addr, in->str.len);
            }
        }
    return need;
}

int list_get(mval *src, mstr_len_t *pos, mval *dst)
{
    char *p, *next, *inp, *srcend;
    int 	len;
    char	exp = 0;
    int		num = 0;
    double tmp;

    error_def(ERR_LISTERR);
    if(*pos > (src->str.len)) {
        dst->mvtype = 0;
        return 0;
    }
    srcend = src->str.addr + src->str.len;
    inp = src->str.addr + *pos;
    len = len_list_element(&inp, srcend);
    if (len < 0) {
        rts_error(VARLSTCNT(1) ERR_LISTERR);
	}
    if (inp > srcend) {
        rts_error(VARLSTCNT(1) ERR_LISTERR);
	}
    if (len == 0) {
        dst->mvtype = 0;	/* Element not defined */
        *pos += 1;
	return 0;
    } else {
        if (*inp % 2)
            num = ~num;	/* For 5 and 7 negative types */
        switch (*inp++) {
        case 8:
            if (len != 10) {
                rts_error(VARLSTCNT(1) ERR_LISTERR); /* DOUBEL PRECISION must have the fixed length */
	    }
            break;
        case 1:		/* STRING */
        case 2:		/* Unicode String */
            len--;  /* Skip type byte */
	    if (len==0) {
		dst->str.len=0;
		dst->mvtype = MV_STR;
	    } else
            *pos = inp - (src->str.addr) + len;
            return len;
            break;
        case 6:		/* FLOAT */
        case 7:		/* NEGATIV FLOAT */
            exp = *inp++;
            len--;              /* Skip exponent byte */
        case 5:		/* NEGATIV INTEGER */
        case 4:		/* INTEGER */
            if (len > 9) {
                rts_error(VARLSTCNT(1) ERR_LISTERR);
		}
            inp += (len - 2);
            *pos = inp - src->str.addr + 1;
            while (--len) {     /* Skip type byte */
                num <<= 8;
                num += (unsigned char) *inp--;
            }
            if (exp) {
                tmp = (double)num * pow(10,exp);
                double2mval(dst, tmp);
            } else {
                i82mval(dst, num);
            }
	        break;
        default:
	        rts_error(VARLSTCNT(1) ERR_LISTERR);
        }
    }
    return 0;
}

void list_elem(mval *src, int pos, mval *dst)
{
    char 	*p, *tmp, *srcend;
    int len;
    int st;

	error_def(ERR_LISTRANGE);
	error_def(ERR_LISTERR);
    if (pos < -1) rts_error(VARLSTCNT(1) ERR_LISTRANGE);
    p = src->str.addr;
    srcend = p + src->str.len;

    	if (pos == -1)  /* Last element */
        {
        while (p != srcend)
            {
                tmp = p;
                p = next_list(p, srcend);
		if (p == 0) {
        	    rts_error(VARLSTCNT(1) ERR_LISTERR);
		}
            }
            p = tmp;
        } else {
            if (pos == 0) return;
            while (--pos)
            {
                p = next_list(p, srcend);
		if (p == 0) {
        	    rts_error(VARLSTCNT(1) ERR_LISTERR);
		}
                if (p == srcend) break;
            }
        }

    if (p == srcend) return;
    st = p - src->str.addr;
    len = list_get(src,&st,dst);
    if (len == 0) return;                   /* It is not string, dst defined */
    ENSURE_STP_FREE_SPACE(len);
    p = src->str.addr + st - len;
    memcpy((char *)stringpool.free,p,len);
    dst->str.addr = (char *)stringpool.free;
    stringpool.free += len;
    dst->str.len = len;
    dst->mvtype = MV_STR;
}
