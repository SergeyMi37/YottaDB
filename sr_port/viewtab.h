/****************************************************************
 *								*
 * Copyright (c) 2001-2018 Fidelity National Information	*
 * Services, Inc. and/or its subsidiaries. All rights reserved.	*
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

/* a few of the following VIEWTAB entries (be it VIEW command related or $VIEW function related) are not documented
 * in the programmer's guide. the reason behind the non-documentation is indicated across each such entry with a "nodoc :" prefix.
 */
/*      KEYWORD			PARAMETER-TYPE			KEYCODE		RESULT-TYPE */
VIEWTAB("BADCHAR",		VTP_NULL,			VTK_BADCHAR,		MV_NM),
VIEWTAB("BREAKMSG",		VTP_NULL | VTP_VALUE,		VTK_BREAKMSG,		MV_NM),
VIEWTAB("DBFLUSH",		VTP_DBREGION | VTP_NULL,	VTK_DBFLUSH,		MV_STR),
VIEWTAB("DBSYNC",		VTP_DBREGION | VTP_NULL,	VTK_DBSYNC,		MV_STR),
VIEWTAB("DEBUG1",		VTP_VALUE | VTP_NULL,		VTK_DEBUG1,		MV_STR),
VIEWTAB("DEBUG2",		VTP_VALUE | VTP_NULL,		VTK_DEBUG2,		MV_STR),
VIEWTAB("DEBUG3",		VTP_VALUE | VTP_NULL,		VTK_DEBUG3,		MV_STR),
VIEWTAB("DEBUG4",		VTP_VALUE | VTP_NULL,		VTK_DEBUG4,		MV_STR),
VIEWTAB("DMTERM",		VTP_NULL,			VTK_DMTERM,		MV_NM),
VIEWTAB("ENVIRONMENT",		VTP_NULL,			VTK_ENVIRONMENT,	MV_STR),
VIEWTAB("EPOCH",		VTP_DBREGION | VTP_NULL,	VTK_EPOCH,		MV_STR),
VIEWTAB("FILL_FACTOR",		VTP_VALUE | VTP_NULL,		VTK_FILLFACTOR,		MV_NM),
VIEWTAB("FLUSH",		VTP_DBREGION | VTP_NULL,	VTK_FLUSH,		MV_STR),
VIEWTAB("FREEBLOCKS",		VTP_DBREGION,			VTK_BLFREE,		MV_NM),
VIEWTAB("FREEZE",		VTP_DBREGION,			VTK_FREEZE,		MV_NM),
VIEWTAB("FULL_BOOLEAN",		VTP_NULL,			VTK_FULLBOOL,		MV_STR),
VIEWTAB("FULL_BOOLWARN",	VTP_NULL,			VTK_FULLBOOLWARN,	MV_STR),
VIEWTAB("GDSCERT",		VTP_NULL | VTP_VALUE,		VTK_GDSCERT,		MV_STR),
#ifdef TESTPOLLCRIT
VIEWTAB("GRABCRIT",		VTP_DBREGION,			VTK_GRABCRIT,		MV_STR),
VIEWTAB("GRABJNLPH2",		VTP_DBREGION,			VTK_GRABJNLPH2,		MV_STR),
VIEWTAB("GRABJNLPOOLPH2",	VTP_DBREGION,			VTK_GRABJNLPOOLPH2,	MV_STR),
VIEWTAB("GRABJNLQIO",		VTP_DBREGION,			VTK_GRABJNLQIO,		MV_STR),
VIEWTAB("GRABLOCK",		VTP_DBREGION,			VTK_GRABLOCK,		MV_STR),
#endif
VIEWTAB("GVACCESS_METHOD",	VTP_DBREGION,			VTK_GVACC_METH,		MV_STR),
VIEWTAB("GVDUPSETNOOP",		VTP_NULL | VTP_VALUE,		VTK_GVDUPSETNOOP,	MV_STR),
VIEWTAB("GVFILE",		VTP_DBREGION,			VTK_GVFILE,		MV_STR),
VIEWTAB("GVFIRST",		VTP_NULL,			VTK_GVFIRST,		MV_STR), /* nodoc : archaic and deprecated.
												  * use GVNEXT instead */
VIEWTAB("GVNEXT",		VTP_DBREGION,			VTK_GVNEXT,		MV_STR),
VIEWTAB("GVSRESET",		VTP_DBREGION | VTP_NULL,	VTK_GVSRESET,		MV_STR),
VIEWTAB("GVSTATS",		VTP_DBREGION,			VTK_GVSTATS,		MV_STR),
VIEWTAB("ICHITS",		VTP_NULL,			VTK_ICHITS,		MV_NM),
VIEWTAB("ICMISS",		VTP_NULL,			VTK_ICMISS,		MV_NM),
VIEWTAB("ICSIZE",		VTP_NULL,			VTK_ICSIZE,		MV_NM),
VIEWTAB("IMAGENAME",		VTP_NULL,			VTK_IMAGENAME,		MV_STR), /* nodoc : test system use returns
												  * running executable */
VIEWTAB("JNLACTIVE",		VTP_DBREGION,			VTK_JNLACTIVE,		MV_NM),
VIEWTAB("JNLERROR",		VTP_VALUE | VTP_NULL,		VTK_JNLERROR,		MV_NM), /* nodoc: see op_view */
VIEWTAB("JNLFILE",		VTP_DBREGION,			VTK_JNLFILE,		MV_STR),
VIEWTAB("JNLFLUSH",		VTP_DBREGION | VTP_NULL,	VTK_JNLFLUSH,		MV_STR),
VIEWTAB("JNLPOOL",		VTP_NULL,			VTK_JNLPOOL,		MV_STR),
VIEWTAB("JNLTRANSACTION",	VTP_NULL,			VTK_JNLTRANSACTION,	MV_NM),
VIEWTAB("JNLWAIT",		VTP_NULL,			VTK_JNLWAIT,		MV_STR),
VIEWTAB("JOBPID",		VTP_VALUE | VTP_NULL,		VTK_JOBPID,		MV_STR),
VIEWTAB("LABELS",		VTP_VALUE | VTP_NULL,		VTK_LABELS,		MV_NM),
VIEWTAB("LINK",			VTP_VALUE | VTP_NULL,		VTK_LINK,		MV_STR),
VIEWTAB("LOGNONTP",		VTP_VALUE | VTP_NULL,		VTK_LOGNONTP,		MV_NM),
VIEWTAB("LOGTPRESTART",		VTP_VALUE | VTP_NULL,		VTK_LOGTPRESTART,	MV_NM),
#ifdef DEBUG_ALIAS
VIEWTAB("LVAMONOUT",		VTP_NULL,			VTK_LVAMONOUT,		MV_NM), /* nodoc : code debugging feature */
VIEWTAB("LVAMONSTART",		VTP_NULL,			VTK_LVAMONSTART,	MV_NM), /* nodoc : code debugging feature */
VIEWTAB("LVAMONSTOP",		VTP_NULL,			VTK_LVAMONSTOP,		MV_NM), /* nodoc : code debugging feature */
#endif
#ifdef DEBUG
VIEWTAB("LVDMP",		VTP_LVN,			VTK_LVDMP,		MV_NM),
#endif
VIEWTAB("LVMON",		VTP_NULL | VTP_VALUE,		VTK_LVMON,		MV_STR),/* nodoc : code debugging feature */
VIEWTAB("LVNULLSUBS",		VTP_NULL,			VTK_LVNULLSUBS,		MV_NM),
VIEWTAB("LV_CREF",		VTP_LVN,			VTK_LVCREF,		MV_NM),
VIEWTAB("LV_GCOL",		VTP_NULL,			VTK_LVGCOL,		MV_NM),
VIEWTAB("LV_REF",		VTP_LVN,			VTK_LVREF,		MV_NM),
VIEWTAB("LV_REHASH",		VTP_NULL,			VTK_LVREHASH,		MV_NM),
VIEWTAB("MAX_SOCKETS",		VTP_NULL,			VTK_MAXSOCKETS,		MV_NM),
VIEWTAB("NEVERLVNULLSUBS",	VTP_NULL,			VTK_NEVERLVNULLSUBS,	MV_NM),
VIEWTAB("NOBADCHAR",		VTP_NULL,			VTK_NOBADCHAR,		MV_NM),
VIEWTAB("NODMTERM",		VTP_NULL,			VTK_NODMTERM,		MV_NM),
VIEWTAB("NOFULL_BOOLEAN",	VTP_NULL,			VTK_NOFULLBOOL,		MV_STR),
VIEWTAB("NOISOLATION",		VTP_NULL | VTP_DBKEYLIST,	VTK_NOISOLATION,	MV_NM),
VIEWTAB("NOLOGNONTP",		VTP_NULL,			VTK_NOLOGNONTP,		MV_NM),
VIEWTAB("NOLOGTPRESTART",	VTP_NULL,			VTK_NOLOGTPRESTART,	MV_NM),
VIEWTAB("NOLVNULLSUBS",		VTP_NULL,			VTK_NOLVNULLSUBS,	MV_NM),
VIEWTAB("NOSTATSHARE",		VTP_NULL | VTP_DBREGION,	VTK_NOSTATSHARE,	MV_NM),
VIEWTAB("NOUNDEF",		VTP_NULL,			VTK_NOUNDEF,		MV_NM),
VIEWTAB("PATCODE",		VTP_VALUE | VTP_NULL,		VTK_PATCODE,		MV_STR),
VIEWTAB("PATLOAD",		VTP_VALUE,			VTK_PATLOAD,		MV_NM),
VIEWTAB("POOLLIMIT",		VTP_DBREGION | VTP_NULL,	VTK_POOLLIMIT,		MV_NM),
VIEWTAB("PROBECRIT",		VTP_DBREGION,			VTK_PROBECRIT,		MV_STR),
VIEWTAB("RCHITS",		VTP_NULL,			VTK_RCHITS,		MV_NM),
VIEWTAB("RCMISSES",		VTP_NULL,			VTK_RCMISSES,		MV_NM),
VIEWTAB("RCSIZE",		VTP_NULL,			VTK_RCSIZE,		MV_NM),
VIEWTAB("REGION",		VTP_DBKEY,			VTK_REGION,		MV_STR),
#ifdef TESTPOLLCRIT
VIEWTAB("RELCRIT",		VTP_DBREGION,			VTK_RELCRIT,		MV_STR),
VIEWTAB("RELJNLPH2",		VTP_DBREGION,			VTK_RELJNLPH2,		MV_STR),
VIEWTAB("RELJNLPOOLPH2",	VTP_DBREGION,			VTK_RELJNLPOOLPH2,	MV_STR),
VIEWTAB("RELJNLQIO",		VTP_DBREGION,			VTK_RELJNLQIO,		MV_STR),
VIEWTAB("RELLOCK",		VTP_DBREGION,			VTK_RELLOCK,		MV_STR),
#endif
VIEWTAB("RESETGVSTATS",		VTP_NULL,			VTK_RESETGVSTATS,	MV_STR),
VIEWTAB("RTNCHECKSUM",		VTP_RTNAME,			VTK_RTNCHECKSUM,	MV_STR),
VIEWTAB("RTNNEXT",		VTP_RTNAME,			VTK_RTNEXT,		MV_STR),
VIEWTAB("SPSIZE",		VTP_NULL,			VTK_SPSIZE,		MV_STR),
VIEWTAB("STATSHARE",		VTP_NULL | VTP_DBREGION,	VTK_STATSHARE,		MV_NM),
VIEWTAB("STKSIZ",		VTP_NULL,			VTK_STKSIZ,		MV_NM),
VIEWTAB("STORDUMP",		VTP_NULL,			VTK_STORDUMP,		MV_NM), /* nodoc : code debugging feature */
VIEWTAB("STP_GCOL",		VTP_NULL,			VTK_STPGCOL,		MV_NM),
VIEWTAB("TESTPOINT",		VTP_VALUE,			VTK_TESTPOINT,		MV_NM),
VIEWTAB("TOTALBLOCKS",		VTP_DBREGION,			VTK_BLTOTAL,		MV_NM),
VIEWTAB("TRACE",		VTP_VALUE,			VTK_TRACE,		MV_NM),
VIEWTAB("TRANSACTIONID",	VTP_VALUE | VTP_NULL,		VTK_TID,		MV_STR),
VIEWTAB("UNDEF",		VTP_NULL,			VTK_UNDEF,		MV_NM),
VIEWTAB("YCHKCOLL",		VTP_NULL | VTP_VALUE,		VTK_YCHKCOLL,		MV_NM), /* nodoc : GDE related
												 * undocumented feature */
VIEWTAB("YCOLLATE",		VTP_VALUE,			VTK_YCOLLATE,		MV_NM), /* nodoc : collation related
												 * undocumented feature */
VIEWTAB("YDIRTREE",		VTP_VALUE,			VTK_YDIRTREE,		MV_STR), /* nodoc : collation related
												  * undocumented feature */
VIEWTAB("YDIRTVAL",		VTP_VALUE,			VTK_YDIRTVAL,		MV_STR), /* nodoc : collation related
												  * undocumented feature */
VIEWTAB("YGDS2GVN",		VTP_VALUE,			VTK_YGDS2GVN,		MV_STR), /* nodoc : GDE related
												  * undocumented feature */
VIEWTAB("YGLDCOLL",		VTP_DBKEY,			VTK_YGLDCOLL,		MV_STR), /* nodoc : collation related
												  * undocumented feature */
VIEWTAB("YGVN2GDS",		VTP_VALUE,			VTK_YGVN2GDS,		MV_STR), /* nodoc : GDE related
												  * undocumented feature */
VIEWTAB("YLCT",			VTP_NULL | VTP_VALUE,		VTK_YLCT,		MV_NM), /* nodoc : collation related
												 * undocumented feature */
VIEWTAB("ZDEFBUFFER",		VTP_DBREGION,			VTK_ZDEFBUFF,		MV_NM), /* nodoc : seems to be an archaic
												 * feature of GT.CM GNP */
VIEWTAB("ZDEFCOUNT",		VTP_DBREGION,			VTK_ZDEFCNT,		MV_NM), /* nodoc : seems to be an archaic
												 * feature of GT.CM GNP */
VIEWTAB("ZDEFER",		VTP_NULL | VTP_VALUE,		VTK_ZDEFER,		MV_NM), /* nodoc : seems to be an archaic
												 * feature of GT.CM GNP */
VIEWTAB("ZDEFSIZE",		VTP_DBREGION,			VTK_ZDEFSIZE,		MV_NM), /* nodoc : seems to be an archaic
												 * feature of GT.CM GNP */
VIEWTAB("ZDIR_FORM",		VTP_NULL | VTP_VALUE,		VTK_ZDIR_FORM,		MV_NM),
VIEWTAB("ZFLUSH",		VTP_NULL,			VTK_ZFLUSH,		MV_NM)
