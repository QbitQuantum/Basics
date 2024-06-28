// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.OracleCli.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_OraclecliHPP
#define Firedac_Phys_OraclecliHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Oraclecli
{
//-- forward type declarations -----------------------------------------------
struct TOraDate;
struct TXID;
//-- type declarations -------------------------------------------------------
typedef int sword;

typedef int eword;

typedef unsigned uword;

typedef __int64 sb8;

typedef unsigned __int64 ub8;

typedef int sb4;

typedef unsigned ub4;

typedef short sb2;

typedef System::Word ub2;

typedef System::Int8 sb1;

typedef System::Byte ub1;

typedef void * dvoid;

typedef System::PByte pOCIText;

typedef System::Byte *pUb1;

typedef System::Int8 *pSb1;

typedef System::Word *pUb2;

typedef short *pSb2;

typedef unsigned *pUb4;

typedef int *pSb4;

typedef pUb1 *ppUb1;

typedef pUb4 *ppUb4;

typedef System::StaticArray<System::Byte, 65536> TUB1Array;

typedef TUB1Array *PUB1Array;

typedef System::StaticArray<short, 65536> TSB2Array;

typedef TSB2Array *PSB2Array;

typedef System::StaticArray<System::Word, 65536> TUB2Array;

typedef TUB2Array *PUB2Array;

typedef System::StaticArray<unsigned, 65536> TUB4Array;

typedef TUB4Array *PUB4Array;

typedef System::StaticArray<bool, 65536> TBoolArray;

typedef TBoolArray *PBoolArray;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TOraDate
{
public:
	System::Byte century;
	System::Byte year;
	System::Byte month;
	System::Byte day;
	System::Byte hour;
	System::Byte minute;
	System::Byte second;
};
#pragma pack(pop)


typedef TOraDate *POraDate;

typedef void * pOCIHandle;

typedef void * *ppOCIHandle;

typedef void * pOCIEnv;

typedef void * pOCIServer;

typedef void * pOCIError;

typedef void * pOCISvcCtx;

typedef void * pOCIStmt;

typedef void * pOCIDefine;

typedef void * pOCISession;

typedef void * pOCITrans;

typedef void * pOCIBind;

typedef void * pOCIDescribe;

typedef void * pOCIDirPathCtx;

typedef void * pOCIDirPathColArray;

typedef void * pOCIDirPathStream;

typedef void * pOCIAdmin;

typedef void * pOCISubscription;

typedef void * pOCIDescriptor;

typedef void * pOCISnapshot;

typedef void * pOCILobLocator;

typedef void * pOCIParam;

typedef void * pOCIRowid;

typedef void * pOCIComplexObjectComp;

typedef void * pOCIAQEnqOptions;

typedef void * pOCIAQDeqOptions;

typedef void * pOCIAQMsgProperties;

typedef void * pOCIAQAgent;

typedef void * pOCIDirPathDesc;

typedef void * pOCIDateTime;

typedef void * pOCIInterval;

typedef short OCIInd;

typedef short *pOCIInd;

typedef System::Word OCIDuration;

typedef System::StaticArray<System::Byte, 22> OCINumber;

typedef OCINumber *pOCINumber;

typedef void * pOCIColl;

typedef void * pOCIArray;

typedef void * pOCITable;

typedef void * pOCIIter;

typedef TXID *PXID;

struct DECLSPEC_DRECORD TXID
{
public:
	int formatID;
	int gtrid_length;
	int bqual_length;
	System::StaticArray<System::Byte, 128> data;
};


typedef int __cdecl (*TOCIInitialize)(unsigned mode, void * ctxp, void * malocfp, void * ralocfp, void * mfreefp);

typedef int __cdecl (*TOCIEnvInit)(void * &envhpp, unsigned mode, NativeUInt xtramemsz, System::PPointer usrmempp);

typedef int __cdecl (*TOCIEnvCreate)(void * &envhpp, unsigned mode, void * ctxp, void * malocfp, void * ralocfp, void * mfreefp, NativeUInt xtramemsz, System::PPointer usrmempp);

typedef int __cdecl (*TOCIEnvNlsCreate)(void * &envhpp, unsigned mode, void * ctxp, void * malocfp, void * ralocfp, void * mfreefp, NativeUInt xtramemsz, System::PPointer usrmempp, System::Word charset, System::Word ncharset);

typedef int __cdecl (*TOCIHandleAlloc)(void * parenth, void * &hndlpp, unsigned atype, NativeUInt xtramem_sz, System::PPointer usrmempp);

typedef int __cdecl (*TOCIServerAttach)(void * srvhp, void * errhp, System::PByte dblink, int dblink_len, unsigned mode);

typedef int __cdecl (*TOCIAttrSet)(void * trgthndlp, unsigned trghndltyp, void * attributep, unsigned size, unsigned attrtype, void * errhp);

typedef int __cdecl (*TOCISessionBegin)(void * svchp, void * errhp, void * usrhp, unsigned credt, unsigned mode);

typedef int __cdecl (*TOCISessionEnd)(void * svchp, void * errhp, void * usrhp, unsigned mode);

typedef int __cdecl (*TOCIServerDetach)(void * srvhp, void * errhp, unsigned mode);

typedef int __cdecl (*TOCIHandleFree)(void * hndlp, unsigned atype);

typedef int __cdecl (*TOCIErrorGet)(void * hndlp, unsigned recordno, System::PByte sqlstate, int &errcodep, System::PByte bufp, unsigned bufsiz, unsigned atype);

typedef int __cdecl (*TOCIStmtPrepare)(void * stmtp, void * errhp, System::PByte stmt, unsigned stmt_len, unsigned language, unsigned mode);

typedef int __cdecl (*TOCIStmtPrepare2)(void * svchp, void * &stmtp, void * errhp, System::PByte stmt, unsigned stmt_len, System::PByte key, unsigned key_len, unsigned language, unsigned mode);

typedef int __cdecl (*TOCIStmtExecute)(void * svchp, void * stmtp, void * errhp, unsigned iters, unsigned rowoff, void * snap_in, void * snap_out, unsigned mode);

typedef int __cdecl (*TOCIStmtGetNextResult)(void * stmtp, void * errhp, void * &result, unsigned &rtype, unsigned mode);

typedef int __cdecl (*TOCIParamGet)(void * hndlp, unsigned htype, void * errhp, void * &parmdpp, unsigned pos);

typedef int __cdecl (*TOCIAttrGet)(void * trgthndlp, unsigned trghndltyp, void * attributep, void * sizep, unsigned attrtype, void * errhp);

typedef int __cdecl (*TOCIStmtFetch)(void * stmtp, void * errhp, unsigned nrows, System::Word orientation, unsigned mode);

typedef int __cdecl (*TOCIStmtFetch2)(void * stmtp, void * errhp, unsigned nrows, System::Word orientation, unsigned scrollOffset, unsigned mode);

typedef int __cdecl (*TOCIDefineByPos)(void * stmtp, void * &defnpp, void * errhp, unsigned position, void * valuep, int value_sz, System::Word dty, void * indp, pUb2 rlenp, pUb2 rcodep, unsigned mode);

typedef int __cdecl (*TOCIDefineByPos2)(void * stmtp, void * &defnpp, void * errhp, unsigned position, void * valuep, __int64 value_sz, System::Word dty, void * indp, pUb4 rlenp, pUb2 rcodep, unsigned mode);

typedef int __cdecl (*TOCIDefineArrayOfStruct)(void * defnpp, void * errhp, unsigned pvskip, unsigned indskip, unsigned rlskip, unsigned rcskip);

typedef int __cdecl (*TOCIRowidToChar)(void * rowidDesc, System::PByte outbfp, System::Word &outbflp, void * errhp);

typedef int __cdecl (*TOCIBindByPos)(void * stmtp, void * &bindpp, void * errhp, unsigned position, void * valuep, int value_sz, System::Word dty, void * indp, pUb2 alenp, pUb2 rcodep, unsigned maxarr_len, pUb4 curelep, unsigned mode);

typedef int __cdecl (*TOCIBindByPos2)(void * stmtp, void * &bindpp, void * errhp, unsigned position, void * valuep, __int64 value_sz, System::Word dty, void * indp, pUb4 alenp, pUb2 rcodep, unsigned maxarr_len, pUb4 curelep, unsigned mode);

typedef int __cdecl (*TOCIBindByName)(void * stmtp, void * &bindpp, void * errhp, System::PByte placeholder, int placeh_len, void * valuep, int value_sz, System::Word dty, void * indp, pUb2 alenp, pUb2 rcodep, unsigned maxarr_len, pUb4 curelep, unsigned mode);

typedef int __cdecl (*TOCIBindByName2)(void * stmtp, void * &bindpp, void * errhp, System::PByte placeholder, int placeh_len, void * valuep, __int64 value_sz, System::Word dty, void * indp, pUb4 alenp, pUb2 rcodep, unsigned maxarr_len, pUb4 curelep, unsigned mode);

typedef int __cdecl (*TOCIInCBFunc)(void * ictxp, void * bindp, unsigned iter, unsigned index, void * &bufpp, unsigned &alenp, System::Byte &piecep, pSb2 &indp);

typedef int __cdecl (*TOCIOutCBFunc)(void * octxp, void * bindp, unsigned iter, unsigned index, void * &bufpp, pUb4 &alenpp, System::Byte &piecep, pSb2 &indpp, pUb2 &rcodepp);

typedef int __cdecl (*TOCIBindDynamic)(void * bindp, void * errhp, void * ictxp, TOCIInCBFunc icbfp, void * octxp, TOCIOutCBFunc ocbfp);

typedef int __cdecl (*TOCITransStart)(void * svchp, void * errhp, unsigned timeout, unsigned flags);

typedef int __cdecl (*TOCITransRollback)(void * svchp, void * errhp, unsigned flags);

typedef int __cdecl (*TOCITransCommit)(void * svchp, void * errhp, unsigned flags);

typedef int __cdecl (*TOCITransDetach)(void * svchp, void * errhp, unsigned flags);

typedef int __cdecl (*TOCITransPrepare)(void * svchp, void * errhp, unsigned flags);

typedef int __cdecl (*TOCITransForget)(void * svchp, void * errhp, unsigned flags);

typedef int __cdecl (*TOCIDescribeAny)(void * svchp, void * errhp, System::PByte objptr, unsigned objnm_len, System::Byte objptr_typ, System::Byte info_level, System::Byte objtyp, void * dschp);

typedef int __cdecl (*TOCIBreak)(void * svchp, void * errhp);

typedef int __cdecl (*TOCIReset)(void * svchp, void * errhp);

typedef int __cdecl (*TOCIDescriptorAlloc)(void * parenth, void * &descpp, unsigned htype, int xtramem_sz, void * usrmempp);

typedef int __cdecl (*TOCIDescriptorFree)(void * descp, unsigned htype);

typedef int __cdecl (*TOCILobAppend)(void * svchp, void * errhp, void * dst_locp, void * src_locp);

typedef int __cdecl (*TOCILobAssign)(void * envhp, void * errhp, void * src_locp, void * &dst_locpp);

typedef int __cdecl (*TOCILobCharSetForm)(void * envhp, void * errhp, void * locp, System::Byte &csfrm);

typedef int __cdecl (*TOCILobClose)(void * svchp, void * errhp, void * locp);

typedef int __cdecl (*TOCILobCopy)(void * svchp, void * errhp, void * dst_locp, void * src_locp, unsigned amount, unsigned dst_offset, unsigned src_offset);

typedef int __cdecl (*TOCILobEnableBuffering)(void * svchp, void * errhp, void * locp);

typedef int __cdecl (*TOCILobDisableBuffering)(void * svchp, void * errhp, void * locp);

typedef int __cdecl (*TOCILobErase)(void * svchp, void * errhp, void * locp, unsigned &amount, unsigned offset);

typedef int __cdecl (*TOCILobFileExists)(void * svchp, void * errhp, void * filep, System::LongBool &flag);

typedef int __cdecl (*TOCILobFileGetName)(void * envhp, void * errhp, void * filep, System::PByte dir_alias, System::Word &d_length, System::PByte filename, System::Word &f_length);

typedef int __cdecl (*TOCILobFileSetName)(void * envhp, void * errhp, void * &filep, System::PByte dir_alias, System::Word d_length, System::PByte filename, System::Word f_length);

typedef int __cdecl (*TOCILobFlushBuffer)(void * svchp, void * errhp, void * locp, unsigned flag);

typedef int __cdecl (*TOCILobGetLength)(void * svchp, void * errhp, void * locp, unsigned &lenp);

typedef int __cdecl (*TOCILobIsOpen)(void * svchp, void * errhp, void * locp, System::LongBool &flag);

typedef int __cdecl (*TOCILobLoadFromFile)(void * svchp, void * errhp, void * dst_locp, void * src_locp, unsigned amount, unsigned dst_offset, unsigned src_offset);

typedef int __cdecl (*TOCILobLocatorIsInit)(void * envhp, void * errhp, void * locp, System::LongBool &is_initialized);

typedef int __cdecl (*TOCILobOpen)(void * svchp, void * errhp, void * locp, System::Byte mode);

typedef int __cdecl (*TOCILobRead)(void * svchp, void * errhp, void * locp, unsigned &amtp, unsigned offset, void * bufp, unsigned bufl, void * ctxp, void * cbfp, System::Word csid, System::Byte csfrm);

typedef int __cdecl (*TOCILobTrim)(void * svchp, void * errhp, void * locp, unsigned newlen);

typedef int __cdecl (*TOCILobWrite)(void * svchp, void * errhp, void * locp, unsigned &amtp, unsigned offset, void * bufp, unsigned bufl, System::Byte piece, void * ctxp, void * cbfp, System::Word csid, System::Byte csfrm);

typedef int __cdecl (*TOCILobCreateTemporary)(void * svchp, void * errhp, void * locp, System::Word csid, System::Byte csfrm, System::Byte lobtype, System::LongBool cache, System::Word duration);

typedef int __cdecl (*TOCILobFreeTemporary)(void * svchp, void * errhp, void * locp);

typedef int __cdecl (*TOCILobIsTemporary)(void * envhp, void * errhp, void * locp, System::LongBool &is_temporary);

typedef int __cdecl (*TOCIStmtGetPieceInfo)(void * stmtp, void * errhp, void * &hndlpp, unsigned &typep, System::Byte &in_outp, unsigned &iterp, unsigned &idxp, System::Byte &piecep);

typedef int __cdecl (*TOCIStmtSetPieceInfo)(void * handle, unsigned typep, void * errhp, void * buf, unsigned &alenp, System::Byte piece, void * indp, System::Word &rcodep);

typedef int __cdecl (*TOCIPasswordChange)(void * svchp, void * errhp, System::PByte user_name, unsigned usernm_len, System::PByte opasswd, unsigned opasswd_len, System::PByte npasswd, int npasswd_len, unsigned mode);

typedef int __cdecl (*TOCIServerVersion)(void * hndlp, void * errhp, System::PByte bufp, unsigned bufsz, System::Byte hndltype);

typedef int __cdecl (*TOCIResultSetToStmt)(void * rsetdp, void * errhp);

typedef int __cdecl (*TOCIDirPathAbort)(void * dpctx, void * errhp);

typedef int __cdecl (*TOCIDirPathDataSave)(void * dpctx, void * errhp, unsigned action);

typedef int __cdecl (*TOCIDirPathFinish)(void * dpctx, void * errhp);

typedef int __cdecl (*TOCIDirPathFlushRow)(void * dpctx, void * errhp);

typedef int __cdecl (*TOCIDirPathPrepare)(void * dpctx, void * svchp, void * errhp);

typedef int __cdecl (*TOCIDirPathLoadStream)(void * dpctx, void * dpstr, void * errhp);

typedef int __cdecl (*TOCIDirPathColArrayEntryGet)(void * dpca, void * errhp, unsigned rownum, System::Word colIdx, pUb1 &cvalpp, unsigned &clenp, System::Byte &cflgp);

typedef int __cdecl (*TOCIDirPathColArrayEntrySet)(void * dpca, void * errhp, unsigned rownum, System::Word colIdx, pUb1 cvalp, unsigned clen, System::Byte cflg);

typedef int __cdecl (*TOCIDirPathColArrayRowGet)(void * dpca, void * errhp, unsigned rownum, ppUb1 &cvalppp, pUb4 &clenpp, pUb1 &cflgpp);

typedef int __cdecl (*TOCIDirPathColArrayReset)(void * dpca, void * errhp);

typedef int __cdecl (*TOCIDirPathColArrayToStream)(void * dpca, void * dpctx, void * dpstr, void * errhp, unsigned rowcnt, unsigned rowoff);

typedef int __cdecl (*TOCIDirPathStreamReset)(void * dpstr, void * errhp);

typedef int __cdecl (*TOCIDirPathStreamToStream)(void * istr, void * ostr, void * dpctx, void * errhp, unsigned isoff, unsigned osoff);

typedef int __cdecl (*TOCILogon)(void * envhp, void * errhp, void * &svchp, System::PByte username, unsigned uname_len, System::PByte password, unsigned passwd_len, System::PByte dbname, unsigned dbname_len);

typedef int __cdecl (*TOCILogon2)(void * envhp, void * errhp, void * &svchp, System::PByte username, unsigned uname_len, System::PByte password, unsigned passwd_len, System::PByte dbname, unsigned dbname_len, unsigned mode);

typedef int __cdecl (*TOCILogoff)(void * svchp, void * errhp);

typedef int __cdecl (*TOCIDateTimeGetDate)(void * envhp, void * errhp, void * datetime, short &year, System::Byte &month, System::Byte &day);

typedef int __cdecl (*TOCIDateTimeGetTime)(void * envhp, void * errhp, void * datetime, System::Byte &hour, System::Byte &min, System::Byte &sec, unsigned &fsec);

typedef int __cdecl (*TOCIDateTimeConstruct)(void * envhp, void * errhp, void * datetime, short year, System::Byte month, System::Byte day, System::Byte hour, System::Byte min, System::Byte sec, unsigned fsec, System::PByte timezone, unsigned timezone_length);

typedef int __cdecl (*TOCIDateTimeGetTimeZoneOffset)(void * envhp, void * errhp, void * datetime, System::Int8 &hour, System::Int8 &minute);

typedef int __cdecl (*TOCIDateTimeAssign)(void * envhp, void * err, void * from, void * to_);

typedef int __cdecl (*TOCIPing)(void * svchp, void * errhp, unsigned mode);

typedef System::Word __cdecl (*TOCINlsCharSetNameToId)(void * envhp, System::PByte name);

typedef int __cdecl (*TOCINlsCharSetIdToName)(void * envhp, System::PByte buf, NativeUInt buflen, System::Word id);

typedef int __cdecl (*TOCINlsEnvironmentVariableGet)(void * valp, NativeUInt size, System::Word item, System::Word charset, NativeUInt &rsize);

typedef int __cdecl (*TOCIClientVersion)(int &major_version, int &minor_version, int &update_num, int &patch_num, int &port_update_num);

typedef int __cdecl (*TOCIIntervalAssign)(void * envhp, void * err, void * from, void * to_);

typedef int __cdecl (*TOCIIntervalCheck)(void * envhp, void * err, void * interval, unsigned &valid);

typedef int __cdecl (*TOCIIntervalSetYearMonth)(void * envhp, void * err, int yr, int mnth, void * result);

typedef int __cdecl (*TOCIIntervalGetYearMonth)(void * envhp, void * err, /* out */ int &yr, /* out */ int &mnth, void * result);

typedef int __cdecl (*TOCIIntervalSetDaySecond)(void * envhp, void * err, int dy, int hr, int mm, int ss, int fsec, void * result);

typedef int __cdecl (*TOCIIntervalGetDaySecond)(void * envhp, void * err, /* out */ int &dy, /* out */ int &hr, /* out */ int &mm, /* out */ int &ss, /* out */ int &fsec, void * result);

typedef int __cdecl (*TOCIDBStartup)(void * svchp, void * errhp, void * admhp, unsigned mode, unsigned flags);

typedef int __cdecl (*TOCIDBShutdown)(void * svchp, void * errhp, void * admhp, unsigned mode);

typedef int __cdecl (*TOCISubscriptionRegister)(void * svchp, ppOCIHandle subscrhpp, System::Word count, void * errhp, unsigned mode);

typedef int __cdecl (*TOCISubscriptionPost)(void * svchp, ppOCIHandle subscrhpp, System::Word count, void * errhp, unsigned mode);

typedef int __cdecl (*TOCISubscriptionUnRegister)(void * svchp, void * subscrhp, void * errhp, unsigned mode);

typedef int __cdecl (*TOCISubscriptionDisable)(void * subscrhp, void * errhp, unsigned mode);

typedef int __cdecl (*TOCISubscriptionEnable)(void * subscrhp, void * errhp, unsigned mode);

typedef int __cdecl (*TOCINumberToText)(void * errhp, pOCINumber number, System::PByte fmt, unsigned fmt_length, System::PByte nls_params, unsigned nls_p_length, unsigned &buf_size, System::PByte buf);

typedef int __cdecl (*TOCICollSize)(void * envhp, void * err, void * coll, int &size);

typedef int __cdecl (*TOCICollMax)(void * env, void * coll);

typedef int __cdecl (*TOCICollGetElem)(void * envhp, void * err, void * coll, int index, System::LongBool &exists, void * &elem, void * &elemind);

typedef int __cdecl (*TOCICollAssignElem)(void * envhp, void * err, int index, void * elem, void * elemind, void * coll);

typedef int __cdecl (*TOCICollAssign)(void * envhp, void * err, void * rhs, void * lhs);

typedef int __cdecl (*TOCICollAppend)(void * envhp, void * err, void * elem, void * elemind, void * coll);

typedef int __cdecl (*TOCICollTrim)(void * envhp, void * err, int trim_num, void * coll);

typedef int __cdecl (*TOCICollIsLocator)(void * envhp, void * err, void * coll, System::LongBool &result);

typedef int __cdecl (*TOCIIterCreate)(void * envhp, void * err, void * coll, void * &itr);

typedef int __cdecl (*TOCIIterDelete)(void * envhp, void * err, void * &itr);

typedef int __cdecl (*TOCIIterInit)(void * envhp, void * err, void * coll, void * itr);

typedef int __cdecl (*TOCIIterGetCurrent)(void * envhp, void * err, void * itr, void * &elem, void * &elemind);

typedef int __cdecl (*TOCIIterNext)(void * envhp, void * err, void * itr, void * &elem, void * &elemind, System::LongBool &eoc);

typedef int __cdecl (*TOCIIterPrev)(void * envhp, void * err, void * itr, void * &elem, void * &elemind, System::LongBool &boc);

//-- var, const, procedure ---------------------------------------------------
static const unsigned MAXUB4 = unsigned(0xffffffff);
static const int MAXSB4 = int(2147483647);
static const unsigned MINUB4MAXVAL = unsigned(0xffffffff);
static const unsigned UB4MAXVAL = unsigned(0xffffffff);
static const System::Int8 OCI_HTYPE_FIRST = System::Int8(0x1);
static const System::Int8 OCI_HTYPE_ENV = System::Int8(0x1);
static const System::Int8 OCI_HTYPE_ERROR = System::Int8(0x2);
static const System::Int8 OCI_HTYPE_SVCCTX = System::Int8(0x3);
static const System::Int8 OCI_HTYPE_STMT = System::Int8(0x4);
static const System::Int8 OCI_HTYPE_BIND = System::Int8(0x5);
static const System::Int8 OCI_HTYPE_DEFINE = System::Int8(0x6);
static const System::Int8 OCI_HTYPE_DESCRIBE = System::Int8(0x7);
static const System::Int8 OCI_HTYPE_SERVER = System::Int8(0x8);
static const System::Int8 OCI_HTYPE_SESSION = System::Int8(0x9);
static const System::Int8 OCI_HTYPE_TRANS = System::Int8(0xa);
static const System::Int8 OCI_HTYPE_COMPLEXOBJECT = System::Int8(0xb);
static const System::Int8 OCI_HTYPE_SECURITY = System::Int8(0xc);
static const System::Int8 OCI_HTYPE_SUBSCRIPTION = System::Int8(0xd);
static const System::Int8 OCI_HTYPE_DIRPATH_CTX = System::Int8(0xe);
static const System::Int8 OCI_HTYPE_DIRPATH_COLUMN_ARRAY = System::Int8(0xf);
static const System::Int8 OCI_HTYPE_DIRPATH_STREAM = System::Int8(0x10);
static const System::Int8 OCI_HTYPE_PROC = System::Int8(0x11);
static const System::Int8 OCI_HTYPE_DIRPATH_FN_CTX = System::Int8(0x12);
static const System::Int8 OCI_HTYPE_DIRPATH_FN_COL_ARRAY = System::Int8(0x13);
static const System::Int8 OCI_HTYPE_XADSESSION = System::Int8(0x14);
static const System::Int8 OCI_HTYPE_XADTABLE = System::Int8(0x15);
static const System::Int8 OCI_HTYPE_XADFIELD = System::Int8(0x16);
static const System::Int8 OCI_HTYPE_XADGRANULE = System::Int8(0x17);
static const System::Int8 OCI_HTYPE_XADRECORD = System::Int8(0x18);
static const System::Int8 OCI_HTYPE_XADIO = System::Int8(0x19);
static const System::Int8 OCI_HTYPE_CPOOL = System::Int8(0x1a);
static const System::Int8 OCI_HTYPE_SPOOL = System::Int8(0x1b);
static const System::Int8 OCI_HTYPE_ADMIN = System::Int8(0x1c);
static const System::Int8 OCI_HTYPE_EVENT = System::Int8(0x1d);
static const System::Int8 OCI_HTYPE_LAST = System::Int8(0x1d);
static const System::Int8 OCI_DTYPE_FIRST = System::Int8(0x32);
static const System::Int8 OCI_DTYPE_LOB = System::Int8(0x32);
static const System::Int8 OCI_DTYPE_SNAP = System::Int8(0x33);
static const System::Int8 OCI_DTYPE_RSET = System::Int8(0x34);
static const System::Int8 OCI_DTYPE_PARAM = System::Int8(0x35);
static const System::Int8 OCI_DTYPE_ROWID = System::Int8(0x36);
static const System::Int8 OCI_DTYPE_COMPLEXOBJECTCOMP = System::Int8(0x37);
static const System::Int8 OCI_DTYPE_FILE = System::Int8(0x38);
static const System::Int8 OCI_DTYPE_AQENQ_OPTIONS = System::Int8(0x39);
static const System::Int8 OCI_DTYPE_AQDEQ_OPTIONS = System::Int8(0x3a);
static const System::Int8 OCI_DTYPE_AQMSG_PROPERTIES = System::Int8(0x3b);
static const System::Int8 OCI_DTYPE_AQAGENT = System::Int8(0x3c);
static const System::Int8 OCI_DTYPE_LOCATOR = System::Int8(0x3d);
static const System::Int8 OCI_DTYPE_INTERVAL_YM = System::Int8(0x3e);
static const System::Int8 OCI_DTYPE_INTERVAL_DS = System::Int8(0x3f);
static const System::Int8 OCI_DTYPE_AQNFY_DESCRIPTOR = System::Int8(0x40);
static const System::Int8 OCI_DTYPE_DATE = System::Int8(0x41);
static const System::Int8 OCI_DTYPE_TIME = System::Int8(0x42);
static const System::Int8 OCI_DTYPE_TIME_TZ = System::Int8(0x43);
static const System::Int8 OCI_DTYPE_TIMESTAMP = System::Int8(0x44);
static const System::Int8 OCI_DTYPE_TIMESTAMP_TZ = System::Int8(0x45);
static const System::Int8 OCI_DTYPE_TIMESTAMP_LTZ = System::Int8(0x46);
static const System::Int8 OCI_DTYPE_UCB = System::Int8(0x47);
static const System::Int8 OCI_DTYPE_SRVDN = System::Int8(0x48);
static const System::Int8 OCI_DTYPE_SIGNATURE = System::Int8(0x49);
static const System::Int8 OCI_DTYPE_RESERVED_1 = System::Int8(0x4a);
static const System::Int8 OCI_DTYPE_AQLIS_OPTIONS = System::Int8(0x4b);
static const System::Int8 OCI_DTYPE_AQLIS_MSG_PROPERTIES = System::Int8(0x4c);
static const System::Int8 OCI_DTYPE_CHDES = System::Int8(0x4d);
static const System::Int8 OCI_DTYPE_TABLE_CHDES = System::Int8(0x4e);
static const System::Int8 OCI_DTYPE_ROW_CHDES = System::Int8(0x4f);
static const System::Int8 OCI_DTYPE_CQDES = System::Int8(0x50);
static const System::Int8 OCI_DTYPE_LOB_REGION = System::Int8(0x51);
static const System::Int8 OCI_DTYPE_RESERVED_82 = System::Int8(0x52);
static const System::Int8 OCI_DTYPE_LAST = System::Int8(0x52);
static const System::Int8 OCI_TEMP_BLOB = System::Int8(0x1);
static const System::Int8 OCI_TEMP_CLOB = System::Int8(0x2);
static const System::Int8 OCI_TEMP_NCLOB = System::Int8(0x3);
static const System::Int8 OCI_OTYPE_NAME = System::Int8(0x1);
static const System::Int8 OCI_OTYPE_REF = System::Int8(0x2);
static const System::Int8 OCI_OTYPE_PTR = System::Int8(0x3);
static const System::Int8 OCI_ATTR_FNCODE = System::Int8(0x1);
static const System::Int8 OCI_ATTR_OBJECT = System::Int8(0x2);
static const System::Int8 OCI_ATTR_NONBLOCKING_MODE = System::Int8(0x3);
static const System::Int8 OCI_ATTR_SQLCODE = System::Int8(0x4);
static const System::Int8 OCI_ATTR_ENV = System::Int8(0x5);
static const System::Int8 OCI_ATTR_SERVER = System::Int8(0x6);
static const System::Int8 OCI_ATTR_SESSION = System::Int8(0x7);
static const System::Int8 OCI_ATTR_TRANS = System::Int8(0x8);
static const System::Int8 OCI_ATTR_ROW_COUNT = System::Int8(0x9);
static const System::Int8 OCI_ATTR_SQLFNCODE = System::Int8(0xa);
static const System::Int8 OCI_ATTR_PREFETCH_ROWS = System::Int8(0xb);
static const System::Int8 OCI_ATTR_NESTED_PREFETCH_ROWS = System::Int8(0xc);
static const System::Int8 OCI_ATTR_PREFETCH_MEMORY = System::Int8(0xd);
static const System::Int8 OCI_ATTR_NESTED_PREFETCH_MEMORY = System::Int8(0xe);
static const System::Int8 OCI_ATTR_CHAR_COUNT = System::Int8(0xf);
static const System::Int8 OCI_ATTR_PDSCL = System::Int8(0x10);
static const System::Int8 OCI_ATTR_FSPRECISION = System::Int8(0x10);
static const System::Int8 OCI_ATTR_PDPRC = System::Int8(0x11);
static const System::Int8 OCI_ATTR_LFPRECISION = System::Int8(0x11);
static const System::Int8 OCI_ATTR_PARAM_COUNT = System::Int8(0x12);
static const System::Int8 OCI_ATTR_ROWID = System::Int8(0x13);
static const System::Int8 OCI_ATTR_CHARSET = System::Int8(0x14);
static const System::Int8 OCI_ATTR_NCHAR = System::Int8(0x15);
static const System::Int8 OCI_ATTR_USERNAME = System::Int8(0x16);
static const System::Int8 OCI_ATTR_PASSWORD = System::Int8(0x17);
static const System::Int8 OCI_ATTR_STMT_TYPE = System::Int8(0x18);
static const System::Int8 OCI_ATTR_INTERNAL_NAME = System::Int8(0x19);
static const System::Int8 OCI_ATTR_EXTERNAL_NAME = System::Int8(0x1a);
static const System::Int8 OCI_ATTR_XID = System::Int8(0x1b);
static const System::Int8 OCI_ATTR_TRANS_LOCK = System::Int8(0x1c);
static const System::Int8 OCI_ATTR_TRANS_NAME = System::Int8(0x1d);
static const System::Int8 OCI_ATTR_HEAPALLOC = System::Int8(0x1e);
static const System::Int8 OCI_ATTR_CHARSET_ID = System::Int8(0x1f);
static const System::Int8 OCI_ATTR_CHARSET_FORM = System::Int8(0x20);
static const System::Int8 OCI_ATTR_MAXDATA_SIZE = System::Int8(0x21);
static const System::Int8 OCI_ATTR_CACHE_OPT_SIZE = System::Int8(0x22);
static const System::Int8 OCI_ATTR_CACHE_MAX_SIZE = System::Int8(0x23);
static const System::Int8 OCI_ATTR_PINOPTION = System::Int8(0x24);
static const System::Int8 OCI_ATTR_ALLOC_DURATION = System::Int8(0x25);
static const System::Int8 OCI_ATTR_PIN_DURATION = System::Int8(0x26);
static const System::Int8 OCI_ATTR_FDO = System::Int8(0x27);
static const System::Int8 OCI_ATTR_POSTPROCESSING_CALLBACK = System::Int8(0x28);
static const System::Int8 OCI_ATTR_POSTPROCESSING_CONTEXT = System::Int8(0x29);
static const System::Int8 OCI_ATTR_ROWS_RETURNED = System::Int8(0x2a);
static const System::Int8 OCI_ATTR_FOCBK = System::Int8(0x2b);
static const System::Int8 OCI_ATTR_IN_V8_MODE = System::Int8(0x2c);
static const System::Int8 OCI_ATTR_LOBEMPTY = System::Int8(0x2d);
static const System::Int8 OCI_ATTR_SESSLANG = System::Int8(0x2e);
static const System::Int8 OCI_ATTR_VISIBILITY = System::Int8(0x2f);
static const System::Int8 OCI_ATTR_RELATIVE_MSGID = System::Int8(0x30);
static const System::Int8 OCI_ATTR_SEQUENCE_DEVIATION = System::Int8(0x31);
static const System::Int8 OCI_ATTR_CONSUMER_NAME = System::Int8(0x32);
static const System::Int8 OCI_ATTR_DEQ_MODE = System::Int8(0x33);
static const System::Int8 OCI_ATTR_NAVIGATION = System::Int8(0x34);
static const System::Int8 OCI_ATTR_WAIT = System::Int8(0x35);
static const System::Int8 OCI_ATTR_DEQ_MSGID = System::Int8(0x36);
static const System::Int8 OCI_ATTR_PRIORITY = System::Int8(0x37);
static const System::Int8 OCI_ATTR_DELAY = System::Int8(0x38);
static const System::Int8 OCI_ATTR_EXPIRATION = System::Int8(0x39);
static const System::Int8 OCI_ATTR_CORRELATION = System::Int8(0x3a);
static const System::Int8 OCI_ATTR_ATTEMPTS = System::Int8(0x3b);
static const System::Int8 OCI_ATTR_RECIPIENT_LIST = System::Int8(0x3c);
static const System::Int8 OCI_ATTR_EXCEPTION_QUEUE = System::Int8(0x3d);
static const System::Int8 OCI_ATTR_ENQ_TIME = System::Int8(0x3e);
static const System::Int8 OCI_ATTR_MSG_STATE = System::Int8(0x3f);
static const System::Int8 OCI_ATTR_AGENT_NAME = System::Int8(0x40);
static const System::Int8 OCI_ATTR_AGENT_ADDRESS = System::Int8(0x41);
static const System::Int8 OCI_ATTR_AGENT_PROTOCOL = System::Int8(0x42);
static const System::Int8 OCI_ATTR_SENDER_ID = System::Int8(0x44);
static const System::Int8 OCI_ATTR_ORIGINAL_MSGID = System::Int8(0x45);
static const System::Int8 OCI_ATTR_QUEUE_NAME = System::Int8(0x46);
static const System::Int8 OCI_ATTR_NFY_MSGID = System::Int8(0x47);
static const System::Int8 OCI_ATTR_MSG_PROP = System::Int8(0x48);
static const System::Int8 OCI_ATTR_NUM_DML_ERRORS = System::Int8(0x49);
static const System::Int8 OCI_ATTR_DML_ROW_OFFSET = System::Int8(0x4a);
static const System::Int8 OCI_ATTR_DATEFORMAT = System::Int8(0x4b);
static const System::Int8 OCI_ATTR_BUF_ADDR = System::Int8(0x4c);
static const System::Int8 OCI_ATTR_BUF_SIZE = System::Int8(0x4d);
static const System::Int8 OCI_ATTR_NUM_ROWS = System::Int8(0x51);
static const System::Int8 OCI_ATTR_COL_COUNT = System::Int8(0x52);
static const System::Int8 OCI_ATTR_STREAM_OFFSET = System::Int8(0x53);
static const System::Int8 OCI_ATTR_SHARED_HEAPALLOC = System::Int8(0x54);
static const System::Int8 OCI_ATTR_SERVER_GROUP = System::Int8(0x55);
static const System::Int8 OCI_ATTR_MIGSESSION = System::Int8(0x56);
static const System::Int8 OCI_ATTR_NOCACHE = System::Int8(0x57);
static const System::Int8 OCI_ATTR_MEMPOOL_SIZE = System::Int8(0x58);
static const System::Int8 OCI_ATTR_MEMPOOL_INSTNAME = System::Int8(0x59);
static const System::Int8 OCI_ATTR_MEMPOOL_APPNAME = System::Int8(0x5a);
static const System::Int8 OCI_ATTR_MEMPOOL_HOMENAME = System::Int8(0x5b);
static const System::Int8 OCI_ATTR_MEMPOOL_MODEL = System::Int8(0x5c);
static const System::Int8 OCI_ATTR_MODES = System::Int8(0x5d);
static const System::Int8 OCI_ATTR_SUBSCR_NAME = System::Int8(0x5e);
static const System::Int8 OCI_ATTR_SUBSCR_CALLBACK = System::Int8(0x5f);
static const System::Int8 OCI_ATTR_SUBSCR_CTX = System::Int8(0x60);
static const System::Int8 OCI_ATTR_SUBSCR_PAYLOAD = System::Int8(0x61);
static const System::Int8 OCI_ATTR_SUBSCR_NAMESPACE = System::Int8(0x62);
static const System::Int8 OCI_ATTR_PROXY_CREDENTIALS = System::Int8(0x63);
static const System::Int8 OCI_ATTR_INITIAL_CLIENT_ROLES = System::Int8(0x64);
static const System::Int8 OCI_ATTR_UNK = System::Int8(0x65);
static const System::Int8 OCI_ATTR_NUM_COLS = System::Int8(0x66);
static const System::Int8 OCI_ATTR_LIST_COLUMNS = System::Int8(0x67);
static const System::Int8 OCI_ATTR_RDBA = System::Int8(0x68);
static const System::Int8 OCI_ATTR_CLUSTERED = System::Int8(0x69);
static const System::Int8 OCI_ATTR_PARTITIONED = System::Int8(0x6a);
static const System::Int8 OCI_ATTR_INDEX_ONLY = System::Int8(0x6b);
static const System::Int8 OCI_ATTR_LIST_ARGUMENTS = System::Int8(0x6c);
static const System::Int8 OCI_ATTR_LIST_SUBPROGRAMS = System::Int8(0x6d);
static const System::Int8 OCI_ATTR_REF_TDO = System::Int8(0x6e);
static const System::Int8 OCI_ATTR_LINK = System::Int8(0x6f);
static const System::Int8 OCI_ATTR_MIN = System::Int8(0x70);
static const System::Int8 OCI_ATTR_MAX = System::Int8(0x71);
static const System::Int8 OCI_ATTR_INCR = System::Int8(0x72);
static const System::Int8 OCI_ATTR_CACHE = System::Int8(0x73);
static const System::Int8 OCI_ATTR_ORDER = System::Int8(0x74);
static const System::Int8 OCI_ATTR_HW_MARK = System::Int8(0x75);
static const System::Int8 OCI_ATTR_TYPE_SCHEMA = System::Int8(0x76);
static const System::Int8 OCI_ATTR_TIMESTAMP = System::Int8(0x77);
static const System::Int8 OCI_ATTR_NUM_ATTRS = System::Int8(0x78);
static const System::Int8 OCI_ATTR_NUM_PARAMS = System::Int8(0x79);
static const System::Int8 OCI_ATTR_OBJID = System::Int8(0x7a);
static const System::Int8 OCI_ATTR_PTYPE = System::Int8(0x7b);
static const System::Int8 OCI_ATTR_PARAM = System::Int8(0x7c);
static const System::Int8 OCI_ATTR_OVERLOAD_ID = System::Int8(0x7d);
static const System::Int8 OCI_ATTR_TABLESPACE = System::Int8(0x7e);
static const System::Int8 OCI_ATTR_TDO = System::Int8(0x7f);
static const System::Byte OCI_ATTR_LTYPE = System::Byte(0x80);
static const System::Byte OCI_ATTR_PARSE_ERROR_OFFSET = System::Byte(0x81);
static const System::Byte OCI_ATTR_IS_TEMPORARY = System::Byte(0x82);
static const System::Byte OCI_ATTR_IS_TYPED = System::Byte(0x83);
static const System::Byte OCI_ATTR_DURATION = System::Byte(0x84);
static const System::Byte OCI_ATTR_IS_INVOKER_RIGHTS = System::Byte(0x85);
static const System::Byte OCI_ATTR_OBJ_NAME = System::Byte(0x86);
static const System::Byte OCI_ATTR_OBJ_SCHEMA = System::Byte(0x87);
static const System::Byte OCI_ATTR_OBJ_ID = System::Byte(0x88);
static const System::Byte OCI_ATTR_TRANS_TIMEOUT = System::Byte(0x8e);
static const System::Byte OCI_ATTR_SERVER_STATUS = System::Byte(0x8f);
static const System::Byte OCI_ATTR_STATEMENT = System::Byte(0x90);
static const System::Byte OCI_ATTR_NO_CACHE = System::Byte(0x91);
static const System::Byte OCI_ATTR_DEQCOND = System::Byte(0x92);
static const System::Byte OCI_ATTR_RESERVED_2 = System::Byte(0x93);
static const System::Byte OCI_ATTR_SUBSCR_RECPT = System::Byte(0x94);
static const System::Byte OCI_ATTR_SUBSCR_RECPTPROTO = System::Byte(0x95);
static const System::Byte OCI_ATTR_LDAP_HOST = System::Byte(0x99);
static const System::Byte OCI_ATTR_LDAP_PORT = System::Byte(0x9a);
static const System::Byte OCI_ATTR_BIND_DN = System::Byte(0x9b);
static const System::Byte OCI_ATTR_LDAP_CRED = System::Byte(0x9c);
static const System::Byte OCI_ATTR_WALL_LOC = System::Byte(0x9d);
static const System::Byte OCI_ATTR_LDAP_AUTH = System::Byte(0x9e);
static const System::Byte OCI_ATTR_LDAP_CTX = System::Byte(0x9f);
static const System::Byte OCI_ATTR_SERVER_DNS = System::Byte(0xa0);
static const System::Byte OCI_ATTR_DN_COUNT = System::Byte(0xa1);
static const System::Byte OCI_ATTR_SERVER_DN = System::Byte(0xa2);
static const System::Byte OCI_ATTR_MAXCHAR_SIZE = System::Byte(0xa3);
static const System::Byte OCI_ATTR_CURRENT_POSITION = System::Byte(0xa4);
static const System::Byte OCI_ATTR_RESERVED_3 = System::Byte(0xa5);
static const System::Byte OCI_ATTR_RESERVED_4 = System::Byte(0xa6);
static const System::Byte OCI_ATTR_DIGEST_ALGO = System::Byte(0xa8);
static const System::Byte OCI_ATTR_CERTIFICATE = System::Byte(0xa9);
static const System::Byte OCI_ATTR_SIGNATURE_ALGO = System::Byte(0xaa);
static const System::Byte OCI_ATTR_CANONICAL_ALGO = System::Byte(0xab);
static const System::Byte OCI_ATTR_PRIVATE_KEY = System::Byte(0xac);
static const System::Byte OCI_ATTR_DIGEST_VALUE = System::Byte(0xad);
static const System::Byte OCI_ATTR_SIGNATURE_VAL = System::Byte(0xae);
static const System::Byte OCI_ATTR_SIGNATURE = System::Byte(0xaf);
static const System::Byte OCI_ATTR_STMTCACHESIZE = System::Byte(0xb0);
static const System::Byte OCI_ATTR_CONN_NOWAIT = System::Byte(0xb2);
static const System::Byte OCI_ATTR_CONN_BUSY_COUNT = System::Byte(0xb3);
static const System::Byte OCI_ATTR_CONN_OPEN_COUNT = System::Byte(0xb4);
static const System::Byte OCI_ATTR_CONN_TIMEOUT = System::Byte(0xb5);
static const System::Byte OCI_ATTR_STMT_STATE = System::Byte(0xb6);
static const System::Byte OCI_ATTR_CONN_MIN = System::Byte(0xb7);
static const System::Byte OCI_ATTR_CONN_MAX = System::Byte(0xb8);
static const System::Byte OCI_ATTR_CONN_INCR = System::Byte(0xb9);
static const System::Byte OCI_ATTR_NUM_OPEN_STMTS = System::Byte(0xbc);
static const System::Byte OCI_ATTR_DESCRIBE_NATIVE = System::Byte(0xbd);
static const System::Byte OCI_ATTR_BIND_COUNT = System::Byte(0xbe);
static const System::Byte OCI_ATTR_HANDLE_POSITION = System::Byte(0xbf);
static const System::Byte OCI_ATTR_RESERVED_5 = System::Byte(0xc0);
static const System::Byte OCI_ATTR_SERVER_BUSY = System::Byte(0xc1);
static const System::Byte OCI_ATTR_SUBSCR_RECPTPRES = System::Byte(0xc3);
static const System::Byte OCI_ATTR_TRANSFORMATION = System::Byte(0xc4);
static const System::Byte OCI_ATTR_ROWS_FETCHED = System::Byte(0xc5);
static const System::Byte OCI_ATTR_SCN_BASE = System::Byte(0xc6);
static const System::Byte OCI_ATTR_SCN_WRAP = System::Byte(0xc7);
static const System::Byte OCI_ATTR_RESERVED_6 = System::Byte(0xc8);
static const System::Byte OCI_ATTR_READONLY_TXN = System::Byte(0xc9);
static const System::Byte OCI_ATTR_RESERVED_7 = System::Byte(0xca);
static const System::Byte OCI_ATTR_ERRONEOUS_COLUMN = System::Byte(0xcb);
static const System::Byte OCI_ATTR_RESERVED_8 = System::Byte(0xcc);
static const System::Byte OCI_ATTR_ASM_VOL_SPRT = System::Byte(0xcd);
static const System::Byte OCI_ATTR_INST_TYPE = System::Byte(0xcf);
static const System::Byte OCI_ATTR_ENV_UTF16 = System::Byte(0xd1);
static const System::Int8 OCI_ATTR_ENV_CHARSET_ID = System::Int8(0x1f);
static const System::Word OCI_ATTR_ENV_NCHARSET_ID = System::Word(0x106);
static const System::Byte OCI_ATTR_RESERVED_9 = System::Byte(0xd2);
static const System::Byte OCI_ATTR_RESERVED_10 = System::Byte(0xd3);
static const System::Byte OCI_ATTR_RESERVED_12 = System::Byte(0xd6);
static const System::Byte OCI_ATTR_RESERVED_13 = System::Byte(0xd7);
static const System::Byte OCI_ATTR_IS_EXTERNAL = System::Byte(0xd8);
static const System::Byte OCI_ATTR_RESERVED_15 = System::Byte(0xd9);
static const System::Byte OCI_ATTR_STMT_IS_RETURNING = System::Byte(0xda);
static const System::Byte OCI_ATTR_RESERVED_16 = System::Byte(0xdb);
static const System::Byte OCI_ATTR_RESERVED_17 = System::Byte(0xdc);
static const System::Byte OCI_ATTR_RESERVED_18 = System::Byte(0xdd);
static const System::Byte OCI_ATTR_RESERVED_19 = System::Byte(0xde);
static const System::Byte OCI_ATTR_RESERVED_20 = System::Byte(0xdf);
static const System::Byte OCI_ATTR_CURRENT_SCHEMA = System::Byte(0xe0);
static const System::Word OCI_ATTR_RESERVED_21 = System::Word(0x19f);
static const System::Word OCI_ATTR_LAST_LOGON_TIME_UTC = System::Word(0x1cf);
static const System::Byte OCI_ATTR_SUBSCR_QOSFLAGS = System::Byte(0xe1);
static const System::Byte OCI_ATTR_SUBSCR_PAYLOADCBK = System::Byte(0xe2);
static const System::Byte OCI_ATTR_SUBSCR_TIMEOUT = System::Byte(0xe3);
static const System::Byte OCI_ATTR_SUBSCR_NAMESPACE_CTX = System::Byte(0xe4);
static const System::Byte OCI_ATTR_SUBSCR_CQ_QOSFLAGS = System::Byte(0xe5);
static const System::Byte OCI_ATTR_SUBSCR_CQ_REGID = System::Byte(0xe6);
static const System::Byte OCI_ATTR_SUBSCR_NTFN_GROUPING_CLASS = System::Byte(0xe7);
static const System::Byte OCI_ATTR_SUBSCR_NTFN_GROUPING_VALUE = System::Byte(0xe8);
static const System::Byte OCI_ATTR_SUBSCR_NTFN_GROUPING_TYPE = System::Byte(0xe9);
static const System::Byte OCI_ATTR_SUBSCR_NTFN_GROUPING_START_TIME = System::Byte(0xea);
static const System::Byte OCI_ATTR_SUBSCR_NTFN_GROUPING_REPEAT_COUNT = System::Byte(0xeb);
static const System::Byte OCI_ATTR_AQ_NTFN_GROUPING_MSGID_ARRAY = System::Byte(0xec);
static const System::Byte OCI_ATTR_AQ_NTFN_GROUPING_COUNT = System::Byte(0xed);
static const System::Word OCI_ATTR_BIND_ROWCBK = System::Word(0x12d);
static const System::Word OCI_ATTR_BIND_ROWCTX = System::Word(0x12e);
static const System::Word OCI_ATTR_SKIP_BUFFER = System::Word(0x12f);
static const System::Word OCI_ATTR_XSTREAM_ACK_INTERVAL = System::Word(0x15e);
static const System::Word OCI_ATTR_XSTREAM_IDLE_TIMEOUT = System::Word(0x15f);
static const System::Word OCI_ATTR_CQ_QUERYID = System::Word(0x130);
static const System::Word OCI_ATTR_CHNF_TABLENAMES = System::Word(0x191);
static const System::Word OCI_ATTR_CHNF_ROWIDS = System::Word(0x192);
static const System::Word OCI_ATTR_CHNF_OPERATIONS = System::Word(0x193);
static const System::Word OCI_ATTR_CHNF_CHANGELAG = System::Word(0x194);
static const System::Word OCI_ATTR_CHDES_DBNAME = System::Word(0x195);
static const System::Word OCI_ATTR_CHDES_NFYTYPE = System::Word(0x196);
static const System::Word OCI_ATTR_CHDES_XID = System::Word(0x197);
static const System::Word OCI_ATTR_CHDES_TABLE_CHANGES = System::Word(0x198);
static const System::Word OCI_ATTR_CHDES_TABLE_NAME = System::Word(0x199);
static const System::Word OCI_ATTR_CHDES_TABLE_OPFLAGS = System::Word(0x19a);
static const System::Word OCI_ATTR_CHDES_TABLE_ROW_CHANGES = System::Word(0x19b);
static const System::Word OCI_ATTR_CHDES_ROW_ROWID = System::Word(0x19c);
static const System::Word OCI_ATTR_CHDES_ROW_OPFLAGS = System::Word(0x19d);
static const System::Word OCI_ATTR_CHNF_REGHANDLE = System::Word(0x19e);
static const System::Word OCI_ATTR_NETWORK_FILE_DESC = System::Word(0x19f);
static const System::Word OCI_ATTR_PROXY_CLIENT = System::Word(0x1a0);
static const System::Word OCI_ATTR_TABLE_ENC = System::Word(0x1a1);
static const System::Word OCI_ATTR_TABLE_ENC_ALG = System::Word(0x1a2);
static const System::Word OCI_ATTR_TABLE_ENC_ALG_ID = System::Word(0x1a3);
static const System::Word OCI_ATTR_STMTCACHE_CBKCTX = System::Word(0x1a4);
static const System::Word OCI_ATTR_STMTCACHE_CBK = System::Word(0x1a5);
static const System::Word OCI_ATTR_CQDES_OPERATION = System::Word(0x1a6);
static const System::Word OCI_ATTR_CQDES_TABLE_CHANGES = System::Word(0x1a7);
static const System::Word OCI_ATTR_CQDES_QUERYID = System::Word(0x1a8);
static const System::Word OCI_ATTR_CHDES_QUERIES = System::Word(0x1a9);
static const System::Word OCI_ATTR_CONNECTION_CLASS = System::Word(0x1a9);
static const System::Word OCI_ATTR_PURITY = System::Word(0x1aa);
static const System::Int8 OCI_ATTR_PURITY_DEFAULT = System::Int8(0x0);
static const System::Int8 OCI_ATTR_PURITY_NEW = System::Int8(0x1);
static const System::Int8 OCI_ATTR_PURITY_SELF = System::Int8(0x2);
static const System::Word OCI_ATTR_SEND_TIMEOUT = System::Word(0x1b3);
static const System::Word OCI_ATTR_RECEIVE_TIMEOUT = System::Word(0x1b4);
static const System::Word OCI_ATTR_DEFAULT_LOBPREFETCH_SIZE = System::Word(0x1b6);
static const System::Word OCI_ATTR_LOBPREFETCH_SIZE = System::Word(0x1b7);
static const System::Word OCI_ATTR_LOBPREFETCH_LENGTH = System::Word(0x1b8);
static const System::Word OCI_ATTR_LOB_REGION_PRIMARY = System::Word(0x1ba);
static const System::Word OCI_ATTR_LOB_REGION_PRIMOFF = System::Word(0x1bb);
static const System::Word OCI_ATTR_LOB_REGION_OFFSET = System::Word(0x1bd);
static const System::Word OCI_ATTR_LOB_REGION_LENGTH = System::Word(0x1be);
static const System::Word OCI_ATTR_LOB_REGION_MIME = System::Word(0x1bf);
static const System::Word OCI_ATTR_FETCH_ROWID = System::Word(0x1c0);
static const System::Word OCI_ATTR_RESERVED_37 = System::Word(0x1c1);
static const System::Word OCI_ATTR_NO_COLUMN_AUTH_WARNING = System::Word(0x1c2);
static const System::Word OCI_ATTR_XDS_POLICY_STATUS = System::Word(0x1c3);
static const System::Int8 OCI_XDS_POLICY_NONE = System::Int8(0x0);
static const System::Int8 OCI_XDS_POLICY_ENABLED = System::Int8(0x1);
static const System::Int8 OCI_XDS_POLICY_UNKNOWN = System::Int8(0x2);
static const System::Word OCI_ATTR_SUBSCR_IPADDR = System::Word(0x1c4);
static const System::Word OCI_ATTR_RESERVED_40 = System::Word(0x1c5);
static const System::Word OCI_ATTR_RESERVED_42 = System::Word(0x1c7);
static const System::Word OCI_ATTR_RESERVED_43 = System::Word(0x1c8);
static const System::Word OCI_ATTR_UB8_ROW_COUNT = System::Word(0x1c9);
static const System::Word OCI_ATTR_RESERVED_458 = System::Word(0x1ca);
static const System::Word OCI_ATTR_RESERVED_459 = System::Word(0x1cb);
static const System::Word OCI_ATTR_SHOW_INVISIBLE_COLUMNS = System::Word(0x1cc);
static const System::Word OCI_ATTR_INVISIBLE_COL = System::Word(0x1cd);
static const System::Word OCI_ATTR_LTXID = System::Word(0x1ce);
static const System::Word OCI_ATTR_IMPLICIT_RESULT_COUNT = System::Word(0x1cf);
static const System::Word OCI_ATTR_RESERVED_464 = System::Word(0x1d0);
static const System::Word OCI_ATTR_RESERVED_465 = System::Word(0x1d1);
static const System::Word OCI_ATTR_RESERVED_466 = System::Word(0x1d2);
static const System::Word OCI_ATTR_RESERVED_467 = System::Word(0x1d3);
static const System::Word OCI_ATTR_SQL_TRANSLATION_PROFILE = System::Word(0x1d4);
static const System::Word OCI_ATTR_DML_ROW_COUNT_ARRAY = System::Word(0x1d5);
static const System::Word OCI_ATTR_RESERVED_470 = System::Word(0x1d6);
static const System::Word OCI_ATTR_MAX_OPEN_CURSORS = System::Word(0x1d7);
static const System::Word OCI_ATTR_ERROR_IS_RECOVERABLE = System::Word(0x1d8);
static const System::Word OCI_ATTR_RESERVED_473 = System::Word(0x1d9);
static const System::Word OCI_ATTR_ILM_TRACK_WRITE = System::Word(0x1da);
static const System::Word OCI_ATTR_SUBSCR_FAILURE_CBK = System::Word(0x1dd);
static const System::Word OCI_ATTR_SUBSCR_FAILURE_CTX = System::Word(0x1de);
static const System::Word OCI_ATTR_RESERVED_479 = System::Word(0x1df);
static const System::Word OCI_ATTR_RESERVED_480 = System::Word(0x1e0);
static const System::Word OCI_ATTR_RESERVED_481 = System::Word(0x1e1);
static const System::Word OCI_ATTR_RESERVED_482 = System::Word(0x1e2);
static const System::Word OCI_ATTR_TRANS_PROFILE_FOREIGN = System::Word(0x1e3);
static const System::Word OCI_ATTR_TRANSACTION_IN_PROGRESS = System::Word(0x1e4);
static const System::Word OCI_ATTR_DBOP = System::Word(0x1e5);
static const System::Word OCI_ATTR_RESERVED_486 = System::Word(0x1e6);
static const System::Word OCI_ATTR_RESERVED_487 = System::Word(0x1e7);
static const System::Word OCI_ATTR_RESERVED_488 = System::Word(0x1e8);
static const System::Word OCI_ATTR_VARTYPE_MAXLEN_COMPAT = System::Word(0x1e9);
static const System::Word OCI_ATTR_SPOOL_MAX_LIFETIME_SESSION = System::Word(0x1ea);
static const System::Word OCI_ATTR_RESERVED_491 = System::Word(0x1eb);
static const System::Word OCI_ATTR_RESERVED_492 = System::Word(0x1ec);
static const System::Word OCI_ATTR_RESERVED_493 = System::Word(0x1ed);
static const System::Word OCI_ATTR_ITERS_PROCESSED = System::Word(0x1ee);
static const System::Word OCI_ATTR_BREAK_ON_NET_TIMEOUT = System::Word(0x1ef);
static const System::Int8 OCI_EVENT_NONE = System::Int8(0x0);
static const System::Int8 OCI_EVENT_STARTUP = System::Int8(0x1);
static const System::Int8 OCI_EVENT_SHUTDOWN = System::Int8(0x2);
static const System::Int8 OCI_EVENT_SHUTDOWN_ANY = System::Int8(0x3);
static const System::Int8 OCI_EVENT_DROP_DB = System::Int8(0x4);
static const System::Int8 OCI_EVENT_DEREG = System::Int8(0x5);
static const System::Int8 OCI_EVENT_OBJCHANGE = System::Int8(0x6);
static const System::Int8 OCI_EVENT_QUERYCHANGE = System::Int8(0x7);
static const System::Int8 OCI_OPCODE_ALLROWS = System::Int8(0x1);
static const System::Int8 OCI_OPCODE_ALLOPS = System::Int8(0x0);
static const System::Int8 OCI_OPCODE_INSERT = System::Int8(0x2);
static const System::Int8 OCI_OPCODE_UPDATE = System::Int8(0x4);
static const System::Int8 OCI_OPCODE_DELETE = System::Int8(0x8);
static const System::Int8 OCI_OPCODE_ALTER = System::Int8(0x10);
static const System::Int8 OCI_OPCODE_DROP = System::Int8(0x20);
static const System::Int8 OCI_OPCODE_UNKNOWN = System::Int8(0x40);
static const System::Word OCI_ATTR_EVTCBK = System::Word(0x130);
static const System::Word OCI_ATTR_EVTCTX = System::Word(0x131);
static const System::Word OCI_ATTR_USER_MEMORY = System::Word(0x132);
static const System::Word OCI_ATTR_ACCESS_BANNER = System::Word(0x133);
static const System::Word OCI_ATTR_AUDIT_BANNER = System::Word(0x134);
static const System::Word OCI_ATTR_SUBSCR_PORTNO = System::Word(0x186);
static const System::Int8 OCI_SUBSCR_PROTO_OCI = System::Int8(0x0);
static const System::Int8 OCI_SUBSCR_PROTO_MAIL = System::Int8(0x1);
static const System::Int8 OCI_SUBSCR_PROTO_SERVER = System::Int8(0x2);
static const System::Int8 OCI_SUBSCR_PROTO_HTTP = System::Int8(0x3);
static const System::Int8 OCI_SUBSCR_PROTO_MAX = System::Int8(0x4);
static const System::Int8 OCI_SUBSCR_PRES_DEFAULT = System::Int8(0x0);
static const System::Int8 OCI_SUBSCR_PRES_XML = System::Int8(0x1);
static const System::Int8 OCI_SUBSCR_PRES_MAX = System::Int8(0x2);
static const System::Int8 OCI_SUBSCR_QOS_RELIABLE = System::Int8(0x1);
static const System::Int8 OCI_SUBSCR_QOS_PAYLOAD = System::Int8(0x2);
static const System::Int8 OCI_SUBSCR_QOS_REPLICATE = System::Int8(0x4);
static const System::Int8 OCI_SUBSCR_QOS_SECURE = System::Int8(0x8);
static const System::Int8 OCI_SUBSCR_QOS_PURGE_ON_NTFN = System::Int8(0x10);
static const System::Int8 OCI_SUBSCR_QOS_MULTICBK = System::Int8(0x20);
static const System::Byte OCI_SUBSCR_QOS_HAREG = System::Byte(0x80);
static const System::Word OCI_SUBSCR_QOS_NONDURABLE = System::Word(0x100);
static const System::Word OCI_SUBSCR_QOS_ASYNC_DEQ = System::Word(0x200);
static const System::Word OCI_SUBSCR_QOS_AUTO_ACK = System::Word(0x400);
static const System::Word OCI_SUBSCR_QOS_TX_ACK = System::Word(0x800);
static const System::Int8 OCI_SUBSCR_CQ_QOS_QUERY = System::Int8(0x1);
static const System::Int8 OCI_SUBSCR_CQ_QOS_BEST_EFFORT = System::Int8(0x2);
static const System::Int8 OCI_SUBSCR_CQ_QOS_CLQRYCACHE = System::Int8(0x4);
static const System::Int8 OCI_SUBSCR_NTFN_GROUPING_CLASS_TIME = System::Int8(0x1);
static const System::Int8 OCI_SUBSCR_NTFN_GROUPING_TYPE_SUMMARY = System::Int8(0x1);
static const System::Int8 OCI_SUBSCR_NTFN_GROUPING_TYPE_LAST = System::Int8(0x2);
static const System::Int8 OCI_US7ASCIIID = System::Int8(0x1);
static const System::Word OCI_UTF8ID = System::Word(0x367);
static const System::Word OCI_UCS2ID = System::Word(0x3e8);
static const System::Word OCI_UTF16ID = System::Word(0x3e8);
static const System::Int8 OCI_RESULT_TYPE_SELECT = System::Int8(0x1);
static const System::Int8 OCI_SERVER_NOT_CONNECTED = System::Int8(0x0);
static const System::Int8 OCI_SERVER_NORMAL = System::Int8(0x1);
static const System::Int8 OCI_SUBSCR_NAMESPACE_ANONYMOUS = System::Int8(0x0);
static const System::Int8 OCI_SUBSCR_NAMESPACE_AQ = System::Int8(0x1);
static const System::Int8 OCI_SUBSCR_NAMESPACE_DBCHANGE = System::Int8(0x2);
static const System::Int8 OCI_SUBSCR_NAMESPACE_RESERVED1 = System::Int8(0x3);
static const System::Int8 OCI_SUBSCR_NAMESPACE_MAX = System::Int8(0x4);
static const System::Int8 OCI_CRED_RDBMS = System::Int8(0x1);
static const System::Int8 OCI_CRED_EXT = System::Int8(0x2);
static const System::Int8 OCI_CRED_PROXY = System::Int8(0x3);
static const System::Int8 OCI_CRED_RESERVED_1 = System::Int8(0x4);
static const System::Int8 OCI_CRED_RESERVED_2 = System::Int8(0x5);
static const System::Int8 OCI_CRED_RESERVED_3 = System::Int8(0x6);
static const System::Int8 OCI_SUCCESS = System::Int8(0x0);
static const System::Int8 OCI_SUCCESS_WITH_INFO = System::Int8(0x1);
static const System::Byte OCI_RESERVED_FOR_INT_USE = System::Byte(0xc8);
static const System::Int8 OCI_NO_DATA = System::Int8(0x64);
static const System::Int8 OCI_ERROR = System::Int8(-1);
static const System::Int8 OCI_INVALID_HANDLE = System::Int8(-2);
static const System::Int8 OCI_NEED_DATA = System::Int8(0x63);
static const short OCI_STILL_EXECUTING = short(-3123);
static const short OCI_CONTINUE = short(-24200);
static const short OCI_ROWCBK_DONE = short(-24201);
static const System::Int8 OCI_DT_INVALID_DAY = System::Int8(0x1);
static const System::Int8 OCI_DT_DAY_BELOW_VALID = System::Int8(0x2);
static const System::Int8 OCI_DT_INVALID_MONTH = System::Int8(0x4);
static const System::Int8 OCI_DT_MONTH_BELOW_VALID = System::Int8(0x8);
static const System::Int8 OCI_DT_INVALID_YEAR = System::Int8(0x10);
static const System::Int8 OCI_DT_YEAR_BELOW_VALID = System::Int8(0x20);
static const System::Int8 OCI_DT_INVALID_HOUR = System::Int8(0x40);
static const System::Byte OCI_DT_HOUR_BELOW_VALID = System::Byte(0x80);
static const System::Word OCI_DT_INVALID_MINUTE = System::Word(0x100);
static const System::Word OCI_DT_MINUTE_BELOW_VALID = System::Word(0x200);
static const System::Word OCI_DT_INVALID_SECOND = System::Word(0x400);
static const System::Word OCI_DT_SECOND_BELOW_VALID = System::Word(0x800);
static const System::Word OCI_DT_DAY_MISSING_FROM_1582 = System::Word(0x1000);
static const System::Word OCI_DT_YEAR_ZERO = System::Word(0x2000);
static const System::Word OCI_DT_INVALID_TIMEZONE = System::Word(0x4000);
static const System::Word OCI_DT_INVALID_FORMAT = System::Word(0x8000);
static const System::Int8 OCI_INTER_INVALID_DAY = System::Int8(0x1);
static const System::Int8 OCI_INTER_DAY_BELOW_VALID = System::Int8(0x2);
static const System::Int8 OCI_INTER_INVALID_MONTH = System::Int8(0x4);
static const System::Int8 OCI_INTER_MONTH_BELOW_VALID = System::Int8(0x8);
static const System::Int8 OCI_INTER_INVALID_YEAR = System::Int8(0x10);
static const System::Int8 OCI_INTER_YEAR_BELOW_VALID = System::Int8(0x20);
static const System::Int8 OCI_INTER_INVALID_HOUR = System::Int8(0x40);
static const System::Byte OCI_INTER_HOUR_BELOW_VALID = System::Byte(0x80);
static const System::Word OCI_INTER_INVALID_MINUTE = System::Word(0x100);
static const System::Word OCI_INTER_MINUTE_BELOW_VALID = System::Word(0x200);
static const System::Word OCI_INTER_INVALID_SECOND = System::Word(0x400);
static const System::Word OCI_INTER_SECOND_BELOW_VALID = System::Word(0x800);
static const System::Word OCI_INTER_INVALID_FRACSEC = System::Word(0x1000);
static const System::Word OCI_INTER_FRACSEC_BELOW_VALID = System::Word(0x2000);
static const System::Int8 OCI_V7_SYNTAX = System::Int8(0x2);
static const System::Int8 OCI_V8_SYNTAX = System::Int8(0x3);
static const System::Int8 OCI_NTV_SYNTAX = System::Int8(0x1);
static const unsigned OCI_FOREIGN_SYNTAX = unsigned(0xffffffff);
static const System::Int8 OCI_FETCH_CURRENT = System::Int8(0x1);
static const System::Int8 OCI_FETCH_NEXT = System::Int8(0x2);
static const System::Int8 OCI_FETCH_FIRST = System::Int8(0x4);
static const System::Int8 OCI_FETCH_LAST = System::Int8(0x8);
static const System::Int8 OCI_FETCH_PRIOR = System::Int8(0x10);
static const System::Int8 OCI_FETCH_ABSOLUTE = System::Int8(0x20);
static const System::Int8 OCI_FETCH_RELATIVE = System::Int8(0x40);
static const System::Byte OCI_FETCH_RESERVED_1 = System::Byte(0x80);
static const System::Word OCI_FETCH_RESERVED_2 = System::Word(0x100);
static const System::Word OCI_FETCH_RESERVED_3 = System::Word(0x200);
static const System::Word OCI_FETCH_RESERVED_4 = System::Word(0x400);
static const System::Word OCI_FETCH_RESERVED_5 = System::Word(0x800);
static const System::Word OCI_FETCH_RESERVED_6 = System::Word(0x1000);
static const System::Int8 OCI_SB2_IND_PTR = System::Int8(0x1);
static const System::Int8 OCI_DATA_AT_EXEC = System::Int8(0x2);
static const System::Int8 OCI_DYNAMIC_FETCH = System::Int8(0x2);
static const System::Int8 OCI_PIECEWISE = System::Int8(0x4);
static const System::Int8 OCI_DEFINE_RESERVED_1 = System::Int8(0x8);
static const System::Int8 OCI_BIND_RESERVED_2 = System::Int8(0x10);
static const System::Int8 OCI_DEFINE_RESERVED_2 = System::Int8(0x20);
static const System::Int8 OCI_BIND_SOFT = System::Int8(0x40);
static const System::Byte OCI_DEFINE_SOFT = System::Byte(0x80);
static const System::Word OCI_BIND_RESERVED_3 = System::Word(0x100);
static const System::Word OCI_IOV = System::Word(0x200);
static const System::Int8 OCI_DEFAULT = System::Int8(0x0);
static const System::Int8 OCI_THREADED = System::Int8(0x1);
static const System::Int8 OCI_OBJECT = System::Int8(0x2);
static const System::Int8 OCI_EVENTS = System::Int8(0x4);
static const System::Int8 OCI_RESERVED1 = System::Int8(0x8);
static const System::Int8 OCI_SHARED = System::Int8(0x10);
static const System::Int8 OCI_RESERVED2 = System::Int8(0x20);
static const System::Int8 OCI_NO_UCB = System::Int8(0x40);
static const System::Byte OCI_NO_MUTEX = System::Byte(0x80);
static const System::Word OCI_SHARED_EXT = System::Word(0x100);
static const System::Word OCI_ALWAYS_BLOCKING = System::Word(0x400);
static const System::Word OCI_USE_LDAP = System::Word(0x1000);
static const System::Word OCI_REG_LDAPONLY = System::Word(0x2000);
static const System::Word OCI_UTF16 = System::Word(0x4000);
static const System::Word OCI_AFC_PAD_ON = System::Word(0x8000);
static const int OCI_ENVCR_RESERVED3 = int(0x10000);
static const int OCI_NEW_LENGTH_SEMANTICS = int(0x20000);
static const int OCI_NO_MUTEX_STMT = int(0x40000);
static const int OCI_MUTEX_ENV_ONLY = int(0x80000);
static const int OCI_SUPPRESS_NLS_VALIDATION = int(0x100000);
static const int OCI_MUTEX_TRY = int(0x200000);
static const int OCI_NCHAR_LITERAL_REPLACE_ON = int(0x400000);
static const int OCI_NCHAR_LITERAL_REPLACE_OFF = int(0x800000);
static const int OCI_ENABLE_NLS_VALIDATION = int(0x1000000);
static const int OCI_ENVCR_RESERVED4 = int(0x2000000);
static const int OCI_ENVCR_RESERVED5 = int(0x4000000);
static const int OCI_ENVCR_RESERVED6 = int(0x8000000);
static const int OCI_ENVCR_RESERVED7 = int(0x10000000);
static const int OCI_SECURE_NOTIFICATION = int(0x20000000);
static const int OCI_DISABLE_DIAG = int(0x40000000);
static const System::Int8 OCI_BATCH_MODE = System::Int8(0x1);
static const System::Int8 OCI_EXACT_FETCH = System::Int8(0x2);
static const System::Int8 OCI_STMT_SCROLLABLE_READONLY = System::Int8(0x8);
static const System::Int8 OCI_DESCRIBE_ONLY = System::Int8(0x10);
static const System::Int8 OCI_COMMIT_ON_SUCCESS = System::Int8(0x20);
static const System::Int8 OCI_NON_BLOCKING = System::Int8(0x40);
static const System::Byte OCI_BATCH_ERRORS = System::Byte(0x80);
static const System::Word OCI_PARSE_ONLY = System::Word(0x100);
static const System::Word OCI_EXACT_FETCH_RESERVED_1 = System::Word(0x200);
static const System::Word OCI_SHOW_DML_WARNINGS = System::Word(0x400);
static const System::Word OCI_EXEC_RESERVED_2 = System::Word(0x800);
static const System::Word OCI_DESC_RESERVED_1 = System::Word(0x1000);
static const System::Word OCI_EXEC_RESERVED_3 = System::Word(0x2000);
static const System::Word OCI_EXEC_RESERVED_4 = System::Word(0x4000);
static const System::Word OCI_EXEC_RESERVED_5 = System::Word(0x8000);
static const int OCI_EXEC_RESERVED_6 = int(0x10000);
static const int OCI_RESULT_CACHE = int(0x20000);
static const int OCI_NO_RESULT_CACHE = int(0x40000);
static const int OCI_EXEC_RESERVED_7 = int(0x80000);
static const int OCI_RETURN_ROW_COUNT_ARRAY = int(0x100000);
static const System::Int8 OCI_MIGRATE = System::Int8(0x1);
static const System::Int8 OCI_SYSDBA = System::Int8(0x2);
static const System::Int8 OCI_SYSOPER = System::Int8(0x4);
static const System::Int8 OCI_PRELIM_AUTH = System::Int8(0x8);
static const System::Int8 OCIP_ICACHE = System::Int8(0x10);
static const System::Int8 OCI_AUTH_RESERVED_1 = System::Int8(0x20);
static const System::Int8 OCI_STMT_CACHE = System::Int8(0x40);
static const System::Byte OCI_STATELESS_CALL = System::Byte(0x80);
static const System::Word OCI_STATELESS_TXN = System::Word(0x100);
static const System::Word OCI_STATELESS_APP = System::Word(0x200);
static const System::Word OCI_AUTH_RESERVED_2 = System::Word(0x400);
static const System::Word OCI_AUTH_RESERVED_3 = System::Word(0x800);
static const System::Word OCI_AUTH_RESERVED_4 = System::Word(0x1000);
static const System::Word OCI_AUTH_RESERVED_5 = System::Word(0x2000);
static const System::Word OCI_SYSASM = System::Word(0x8000);
static const int OCI_AUTH_RESERVED_6 = int(0x10000);
static const int OCI_SYSBKP = int(0x20000);
static const int OCI_SYSDGD = int(0x40000);
static const int OCI_SYSKMT = int(0x80000);
static const System::Int8 OCI_PREP2_CACHE_SEARCHONLY = System::Int8(0x10);
static const System::Int8 OCI_PREP2_GET_PLSQL_WARNINGS = System::Int8(0x20);
static const System::Int8 OCI_PREP2_RESERVED_1 = System::Int8(0x40);
static const System::Byte OCI_PREP2_RESERVED_2 = System::Byte(0x80);
static const System::Word OCI_PREP2_RESERVED_3 = System::Word(0x100);
static const System::Word OCI_PREP2_RESERVED_4 = System::Word(0x200);
static const System::Word OCI_PREP2_IMPL_RESULTS_CLIENT = System::Word(0x400);
static const System::Word OCI_PREP2_RESERVED_5 = System::Word(0x800);
static const System::Int8 OCI_STRLS_CACHE_DELETE = System::Int8(0x10);
static const System::Int8 OCI_PARAM_IN = System::Int8(0x1);
static const System::Int8 OCI_PARAM_OUT = System::Int8(0x2);
static const System::Int8 OCI_TRANS_NEW = System::Int8(0x1);
static const System::Int8 OCI_TRANS_JOIN = System::Int8(0x2);
static const System::Int8 OCI_TRANS_RESUME = System::Int8(0x4);
static const System::Int8 OCI_TRANS_PROMOTE = System::Int8(0x8);
static const System::Byte OCI_TRANS_STARTMASK = System::Byte(0xff);
static const System::Word OCI_TRANS_READONLY = System::Word(0x100);
static const System::Word OCI_TRANS_READWRITE = System::Word(0x200);
static const System::Word OCI_TRANS_SERIALIZABLE = System::Word(0x400);
static const System::Word OCI_TRANS_ISOLMASK = System::Word(0xff00);
static const int OCI_TRANS_LOOSE = int(0x10000);
static const int OCI_TRANS_TIGHT = int(0x20000);
static const int OCI_TRANS_TYPEMASK = int(0xf0000);
static const int OCI_TRANS_NOMIGRATE = int(0x100000);
static const int OCI_TRANS_SEPARABLE = int(0x200000);
static const int OCI_TRANS_OTSRESUME = int(0x400000);
static const unsigned OCI_TRANS_OTHRMASK = unsigned(0xfff00000);
static const int OCI_TRANS_TWOPHASE = int(0x1000000);
static const System::Int8 OCI_TRANS_WRITEBATCH = System::Int8(0x1);
static const System::Int8 OCI_TRANS_WRITEIMMED = System::Int8(0x2);
static const System::Int8 OCI_TRANS_WRITEWAIT = System::Int8(0x4);
static const System::Int8 OCI_TRANS_WRITENOWAIT = System::Int8(0x8);
static const System::Int8 OCI_ENQ_IMMEDIATE = System::Int8(0x1);
static const System::Int8 OCI_ENQ_ON_COMMIT = System::Int8(0x2);
static const System::Int8 OCI_DEQ_BROWSE = System::Int8(0x1);
static const System::Int8 OCI_DEQ_LOCKED = System::Int8(0x2);
static const System::Int8 OCI_DEQ_REMOVE = System::Int8(0x3);
static const System::Int8 OCI_DEQ_REMOVE_NODATA = System::Int8(0x4);
static const System::Int8 OCI_DEQ_GETSIG = System::Int8(0x5);
static const System::Int8 OCI_DEQ_FIRST_MSG = System::Int8(0x1);
static const System::Int8 OCI_DEQ_NEXT_MSG = System::Int8(0x3);
static const System::Int8 OCI_DEQ_NEXT_TRANSACTION = System::Int8(0x2);
static const System::Int8 OCI_DEQ_FIRST_MSG_MULTI_GROUP = System::Int8(0x4);
static const System::Int8 OCI_DEQ_MULT_TRANSACTION = System::Int8(0x5);
static const System::Int8 OCI_DEQ_NEXT_MSG_MULTI_GROUP = System::Int8(0x5);
static const System::Int8 OCI_DEQ_RESERVED_1 = System::Int8(0x1);
static const System::Int8 OCI_MSG_WAITING = System::Int8(0x1);
static const System::Int8 OCI_MSG_READY = System::Int8(0x0);
static const System::Int8 OCI_MSG_PROCESSED = System::Int8(0x2);
static const System::Int8 OCI_MSG_EXPIRED = System::Int8(0x3);
static const System::Int8 OCI_ENQ_BEFORE = System::Int8(0x2);
static const System::Int8 OCI_ENQ_TOP = System::Int8(0x3);
static const System::Int8 OCI_DEQ_IMMEDIATE = System::Int8(0x1);
static const System::Int8 OCI_DEQ_ON_COMMIT = System::Int8(0x2);
static const System::Int8 OCI_DEQ_WAIT_FOREVER = System::Int8(-1);
static const System::Int8 OCI_NTFN_GROUPING_FOREVER = System::Int8(-1);
static const System::Int8 OCI_DEQ_NO_WAIT = System::Int8(0x0);
static const System::Int8 OCI_FLOW_CONTROL_NO_TIMEOUT = System::Int8(-1);
static const System::Int8 OCI_MSG_NO_DELAY = System::Int8(0x0);
static const System::Int8 OCI_MSG_NO_EXPIRATION = System::Int8(-1);
static const System::Int8 OCI_MSG_PERSISTENT_OR_BUFFERED = System::Int8(0x3);
static const System::Int8 OCI_MSG_BUFFERED = System::Int8(0x2);
static const System::Int8 OCI_MSG_PERSISTENT = System::Int8(0x1);
static const System::Int8 OCI_AQ_RESERVED_1 = System::Int8(0x2);
static const System::Int8 OCI_AQ_RESERVED_2 = System::Int8(0x4);
static const System::Int8 OCI_AQ_RESERVED_3 = System::Int8(0x8);
static const System::Int8 OCI_AQ_RESERVED_4 = System::Int8(0x10);
static const int OCI_AQ_STREAMING_FLAG = int(0x2000000);
static const System::Int8 OCI_AQJMS_RAW_MSG = System::Int8(0x1);
static const System::Int8 OCI_AQJMS_TEXT_MSG = System::Int8(0x2);
static const System::Int8 OCI_AQJMS_MAP_MSG = System::Int8(0x4);
static const System::Int8 OCI_AQJMS_BYTE_MSG = System::Int8(0x8);
static const System::Int8 OCI_AQJMS_STREAM_MSG = System::Int8(0x10);
static const System::Int8 OCI_AQJMS_ADT_MSG = System::Int8(0x20);
static const System::Int8 OCI_AQMSG_FIRST_CHUNK = System::Int8(0x1);
static const System::Int8 OCI_AQMSG_NEXT_CHUNK = System::Int8(0x2);
static const System::Int8 OCI_AQMSG_LAST_CHUNK = System::Int8(0x4);
static const System::Int8 OCI_AQ_LAST_ENQUEUED = System::Int8(0x0);
static const System::Int8 OCI_AQ_LAST_ACKNOWLEDGED = System::Int8(0x1);
static const System::Int8 OCI_ATTR_DATA_SIZE = System::Int8(0x1);
static const System::Int8 OCI_ATTR_DATA_TYPE = System::Int8(0x2);
static const System::Int8 OCI_ATTR_DISP_SIZE = System::Int8(0x3);
static const System::Int8 OCI_ATTR_NAME = System::Int8(0x4);
static const System::Int8 OCI_ATTR_PRECISION = System::Int8(0x5);
static const System::Int8 OCI_ATTR_SCALE = System::Int8(0x6);
static const System::Int8 OCI_ATTR_IS_NULL = System::Int8(0x7);
static const System::Int8 OCI_ATTR_TYPE_NAME = System::Int8(0x8);
static const System::Int8 OCI_ATTR_SCHEMA_NAME = System::Int8(0x9);
static const System::Int8 OCI_ATTR_SUB_NAME = System::Int8(0xa);
static const System::Int8 OCI_ATTR_POSITION = System::Int8(0xb);
static const System::Int8 OCI_ATTR_COMPLEXOBJECTCOMP_TYPE = System::Int8(0x32);
static const System::Int8 OCI_ATTR_COMPLEXOBJECTCOMP_TYPE_LEVEL = System::Int8(0x33);
static const System::Int8 OCI_ATTR_COMPLEXOBJECT_LEVEL = System::Int8(0x34);
static const System::Int8 OCI_ATTR_COMPLEXOBJECT_COLL_OUTOFLINE = System::Int8(0x35);
static const System::Int8 OCI_ATTR_DISP_NAME = System::Int8(0x64);
static const System::Int8 OCI_ATTR_ENCC_SIZE = System::Int8(0x65);
static const System::Int8 OCI_ATTR_COL_ENC = System::Int8(0x66);
static const System::Int8 OCI_ATTR_COL_ENC_SALT = System::Int8(0x67);
static const System::Int8 OCI_ATTR_COL_PROPERTIES = System::Int8(0x68);
static const System::Int8 OCI_ATTR_COL_PROPERTY_IS_IDENTITY = System::Int8(0x1);
static const System::Int8 OCI_ATTR_COL_PROPERTY_IS_GEN_ALWAYS = System::Int8(0x2);
static const System::Int8 OCI_ATTR_COL_PROPERTY_IS_GEN_BY_DEF_ON_NULL = System::Int8(0x4);
static const System::Byte OCI_ATTR_OVERLOAD = System::Byte(0xd2);
static const System::Byte OCI_ATTR_LEVEL = System::Byte(0xd3);
static const System::Byte OCI_ATTR_HAS_DEFAULT = System::Byte(0xd4);
static const System::Byte OCI_ATTR_IOMODE = System::Byte(0xd5);
static const System::Byte OCI_ATTR_RADIX = System::Byte(0xd6);
static const System::Byte OCI_ATTR_NUM_ARGS = System::Byte(0xd7);
static const System::Byte OCI_ATTR_TYPECODE = System::Byte(0xd8);
static const System::Byte OCI_ATTR_COLLECTION_TYPECODE = System::Byte(0xd9);
static const System::Byte OCI_ATTR_VERSION = System::Byte(0xda);
static const System::Byte OCI_ATTR_IS_INCOMPLETE_TYPE = System::Byte(0xdb);
static const System::Byte OCI_ATTR_IS_SYSTEM_TYPE = System::Byte(0xdc);
static const System::Byte OCI_ATTR_IS_PREDEFINED_TYPE = System::Byte(0xdd);
static const System::Byte OCI_ATTR_IS_TRANSIENT_TYPE = System::Byte(0xde);
static const System::Byte OCI_ATTR_IS_SYSTEM_GENERATED_TYPE = System::Byte(0xdf);
static const System::Byte OCI_ATTR_HAS_NESTED_TABLE = System::Byte(0xe0);
static const System::Byte OCI_ATTR_HAS_LOB = System::Byte(0xe1);
static const System::Byte OCI_ATTR_HAS_FILE = System::Byte(0xe2);
static const System::Byte OCI_ATTR_COLLECTION_ELEMENT = System::Byte(0xe3);
static const System::Byte OCI_ATTR_NUM_TYPE_ATTRS = System::Byte(0xe4);
static const System::Byte OCI_ATTR_LIST_TYPE_ATTRS = System::Byte(0xe5);
static const System::Byte OCI_ATTR_NUM_TYPE_METHODS = System::Byte(0xe6);
static const System::Byte OCI_ATTR_LIST_TYPE_METHODS = System::Byte(0xe7);
static const System::Byte OCI_ATTR_MAP_METHOD = System::Byte(0xe8);
static const System::Byte OCI_ATTR_ORDER_METHOD = System::Byte(0xe9);
static const System::Byte OCI_ATTR_NUM_ELEMS = System::Byte(0xea);
static const System::Byte OCI_ATTR_ENCAPSULATION = System::Byte(0xeb);
static const System::Byte OCI_ATTR_IS_SELFISH = System::Byte(0xec);
static const System::Byte OCI_ATTR_IS_VIRTUAL = System::Byte(0xed);
static const System::Byte OCI_ATTR_IS_INLINE = System::Byte(0xee);
static const System::Byte OCI_ATTR_IS_CONSTANT = System::Byte(0xef);
static const System::Byte OCI_ATTR_HAS_RESULT = System::Byte(0xf0);
static const System::Byte OCI_ATTR_IS_CONSTRUCTOR = System::Byte(0xf1);
static const System::Byte OCI_ATTR_IS_DESTRUCTOR = System::Byte(0xf2);
static const System::Byte OCI_ATTR_IS_OPERATOR = System::Byte(0xf3);
static const System::Byte OCI_ATTR_IS_MAP = System::Byte(0xf4);
static const System::Byte OCI_ATTR_IS_ORDER = System::Byte(0xf5);
static const System::Byte OCI_ATTR_IS_RNDS = System::Byte(0xf6);
static const System::Byte OCI_ATTR_IS_RNPS = System::Byte(0xf7);
static const System::Byte OCI_ATTR_IS_WNDS = System::Byte(0xf8);
static const System::Byte OCI_ATTR_IS_WNPS = System::Byte(0xf9);
static const System::Byte OCI_ATTR_DESC_PUBLIC = System::Byte(0xfa);
static const System::Byte OCI_ATTR_CACHE_CLIENT_CONTEXT = System::Byte(0xfb);
static const System::Byte OCI_ATTR_UCI_CONSTRUCT = System::Byte(0xfc);
static const System::Byte OCI_ATTR_UCI_DESTRUCT = System::Byte(0xfd);
static const System::Byte OCI_ATTR_UCI_COPY = System::Byte(0xfe);
static const System::Byte OCI_ATTR_UCI_PICKLE = System::Byte(0xff);
static const System::Word OCI_ATTR_UCI_UNPICKLE = System::Word(0x100);
static const System::Word OCI_ATTR_UCI_REFRESH = System::Word(0x101);
static const System::Word OCI_ATTR_IS_SUBTYPE = System::Word(0x102);
static const System::Word OCI_ATTR_SUPERTYPE_SCHEMA_NAME = System::Word(0x103);
static const System::Word OCI_ATTR_SUPERTYPE_NAME = System::Word(0x104);
static const System::Word OCI_ATTR_LIST_OBJECTS = System::Word(0x105);
static const System::Word OCI_ATTR_NCHARSET_ID = System::Word(0x106);
static const System::Word OCI_ATTR_LIST_SCHEMAS = System::Word(0x107);
static const System::Word OCI_ATTR_MAX_PROC_LEN = System::Word(0x108);
static const System::Word OCI_ATTR_MAX_COLUMN_LEN = System::Word(0x109);
static const System::Word OCI_ATTR_CURSOR_COMMIT_BEHAVIOR = System::Word(0x10a);
static const System::Word OCI_ATTR_MAX_CATALOG_NAMELEN = System::Word(0x10b);
static const System::Word OCI_ATTR_CATALOG_LOCATION = System::Word(0x10c);
static const System::Word OCI_ATTR_SAVEPOINT_SUPPORT = System::Word(0x10d);
static const System::Word OCI_ATTR_NOWAIT_SUPPORT = System::Word(0x10e);
static const System::Word OCI_ATTR_AUTOCOMMIT_DDL = System::Word(0x10f);
static const System::Word OCI_ATTR_LOCKING_MODE = System::Word(0x110);
static const System::Word OCI_ATTR_APPCTX_SIZE = System::Word(0x111);
static const System::Word OCI_ATTR_APPCTX_LIST = System::Word(0x112);
static const System::Word OCI_ATTR_APPCTX_NAME = System::Word(0x113);
static const System::Word OCI_ATTR_APPCTX_ATTR = System::Word(0x114);
static const System::Word OCI_ATTR_APPCTX_VALUE = System::Word(0x115);
static const System::Word OCI_ATTR_CLIENT_IDENTIFIER = System::Word(0x116);
static const System::Word OCI_ATTR_IS_FINAL_TYPE = System::Word(0x117);
static const System::Word OCI_ATTR_IS_INSTANTIABLE_TYPE = System::Word(0x118);
static const System::Word OCI_ATTR_IS_FINAL_METHOD = System::Word(0x119);
static const System::Word OCI_ATTR_IS_INSTANTIABLE_METHOD = System::Word(0x11a);
static const System::Word OCI_ATTR_IS_OVERRIDING_METHOD = System::Word(0x11b);
static const System::Word OCI_ATTR_CHAR_USED = System::Word(0x11d);
static const System::Word OCI_ATTR_CHAR_SIZE = System::Word(0x11e);
static const System::Word OCI_ATTR_IS_JAVA_TYPE = System::Word(0x11f);
static const System::Word OCI_ATTR_DISTINGUISHED_NAME = System::Word(0x12c);
static const System::Word OCI_ATTR_KERBEROS_TICKET = System::Word(0x12d);
static const System::Word OCI_ATTR_ORA_DEBUG_JDWP = System::Word(0x12e);
static const System::Word OCI_ATTR_RESERVED_14 = System::Word(0x12f);
static const System::Word OCI_ATTR_SPOOL_TIMEOUT = System::Word(0x134);
static const System::Word OCI_ATTR_SPOOL_GETMODE = System::Word(0x135);
static const System::Word OCI_ATTR_SPOOL_BUSY_COUNT = System::Word(0x136);
static const System::Word OCI_ATTR_SPOOL_OPEN_COUNT = System::Word(0x137);
static const System::Word OCI_ATTR_SPOOL_MIN = System::Word(0x138);
static const System::Word OCI_ATTR_SPOOL_MAX = System::Word(0x139);
static const System::Word OCI_ATTR_SPOOL_INCR = System::Word(0x13a);
static const System::Byte OCI_ATTR_SPOOL_STMTCACHESIZE = System::Byte(0xd0);
static const System::Word OCI_ATTR_SPOOL_AUTH = System::Word(0x1cc);
static const System::Word OCI_ATTR_IS_XMLTYPE = System::Word(0x13b);
static const System::Word OCI_ATTR_XMLSCHEMA_NAME = System::Word(0x13c);
static const System::Word OCI_ATTR_XMLELEMENT_NAME = System::Word(0x13d);
static const System::Word OCI_ATTR_XMLSQLTYPSCH_NAME = System::Word(0x13e);
static const System::Word OCI_ATTR_XMLSQLTYPE_NAME = System::Word(0x13f);
static const System::Word OCI_ATTR_XMLTYPE_STORED_OBJ = System::Word(0x140);
static const System::Word OCI_ATTR_XMLTYPE_BINARY_XML = System::Word(0x1a6);
static const System::Word OCI_ATTR_HAS_SUBTYPES = System::Word(0x141);
static const System::Word OCI_ATTR_NUM_SUBTYPES = System::Word(0x142);
static const System::Word OCI_ATTR_LIST_SUBTYPES = System::Word(0x143);
static const System::Word OCI_ATTR_XML_HRCHY_ENABLED = System::Word(0x144);
static const System::Word OCI_ATTR_IS_OVERRIDDEN_METHOD = System::Word(0x145);
static const System::Word OCI_ATTR_OBJ_SUBS = System::Word(0x150);
static const System::Word OCI_ATTR_XADFIELD_RESERVED_1 = System::Word(0x153);
static const System::Word OCI_ATTR_XADFIELD_RESERVED_2 = System::Word(0x154);
static const System::Word OCI_ATTR_KERBEROS_CID = System::Word(0x155);
static const System::Word OCI_ATTR_CONDITION = System::Word(0x156);
static const System::Word OCI_ATTR_COMMENT = System::Word(0x157);
static const System::Word OCI_ATTR_VALUE = System::Word(0x158);
static const System::Word OCI_ATTR_EVAL_CONTEXT_OWNER = System::Word(0x159);
static const System::Word OCI_ATTR_EVAL_CONTEXT_NAME = System::Word(0x15a);
static const System::Word OCI_ATTR_EVALUATION_FUNCTION = System::Word(0x15b);
static const System::Word OCI_ATTR_VAR_TYPE = System::Word(0x15c);
static const System::Word OCI_ATTR_VAR_VALUE_FUNCTION = System::Word(0x15d);
static const System::Word OCI_ATTR_VAR_METHOD_FUNCTION = System::Word(0x15e);
static const System::Word OCI_ATTR_ACTION_CONTEXT = System::Word(0x15f);
static const System::Word OCI_ATTR_LIST_TABLE_ALIASES = System::Word(0x160);
static const System::Word OCI_ATTR_LIST_VARIABLE_TYPES = System::Word(0x161);
static const System::Word OCI_ATTR_TABLE_NAME = System::Word(0x164);
static const System::Word OCI_ATTR_MESSAGE_CSCN = System::Word(0x168);
static const System::Word OCI_ATTR_MESSAGE_DSCN = System::Word(0x169);
static const System::Word OCI_ATTR_AUDIT_SESSION_ID = System::Word(0x16a);
static const System::Word OCI_ATTR_KERBEROS_KEY = System::Word(0x16b);
static const System::Word OCI_ATTR_KERBEROS_CID_KEY = System::Word(0x16c);
static const System::Word OCI_ATTR_TRANSACTION_NO = System::Word(0x16d);
static const System::Word OCI_ATTR_MODULE = System::Word(0x16e);
static const System::Word OCI_ATTR_ACTION = System::Word(0x16f);
static const System::Word OCI_ATTR_CLIENT_INFO = System::Word(0x170);
static const System::Word OCI_ATTR_COLLECT_CALL_TIME = System::Word(0x171);
static const System::Word OCI_ATTR_CALL_TIME = System::Word(0x172);
static const System::Word OCI_ATTR_ECONTEXT_ID = System::Word(0x173);
static const System::Word OCI_ATTR_ECONTEXT_SEQ = System::Word(0x174);
static const System::Word OCI_ATTR_SESSION_STATE = System::Word(0x175);
static const System::Int8 OCI_SESSION_STATELESS = System::Int8(0x1);
static const System::Int8 OCI_SESSION_STATEFUL = System::Int8(0x2);
static const System::Word OCI_ATTR_SESSION_STATETYPE = System::Word(0x176);
static const System::Int8 OCI_SESSION_STATELESS_DEF = System::Int8(0x0);
static const System::Int8 OCI_SESSION_STATELESS_CAL = System::Int8(0x1);
static const System::Int8 OCI_SESSION_STATELESS_TXN = System::Int8(0x2);
static const System::Int8 OCI_SESSION_STATELESS_APP = System::Int8(0x3);
static const System::Word OCI_ATTR_SESSION_STATE_CLEARED = System::Word(0x178);
static const System::Word OCI_ATTR_SESSION_MIGRATED = System::Word(0x179);
static const System::Word OCI_ATTR_SESSION_PRESERVE_STATE = System::Word(0x184);
static const System::Word OCI_ATTR_DRIVER_NAME = System::Word(0x1a8);
static const System::Word OCI_ATTR_ADMIN_PFILE = System::Word(0x185);
static const System::Word OCI_ATTR_HOSTNAME = System::Word(0x186);
static const System::Word OCI_ATTR_DBNAME = System::Word(0x187);
static const System::Word OCI_ATTR_INSTNAME = System::Word(0x188);
static const System::Word OCI_ATTR_SERVICENAME = System::Word(0x189);
static const System::Word OCI_ATTR_INSTSTARTTIME = System::Word(0x18a);
static const System::Word OCI_ATTR_HA_TIMESTAMP = System::Word(0x18b);
static const System::Word OCI_ATTR_RESERVED_22 = System::Word(0x18c);
static const System::Word OCI_ATTR_RESERVED_23 = System::Word(0x18d);
static const System::Word OCI_ATTR_RESERVED_24 = System::Word(0x18e);
static const System::Word OCI_ATTR_DBDOMAIN = System::Word(0x18f);
static const System::Word OCI_ATTR_RESERVED_27 = System::Word(0x1a9);
static const System::Word OCI_ATTR_EVENTTYPE = System::Word(0x190);
static const System::Int8 OCI_EVENTTYPE_HA = System::Int8(0x0);
static const System::Word OCI_ATTR_HA_SOURCE = System::Word(0x191);
static const System::Int8 OCI_HA_SOURCE_INSTANCE = System::Int8(0x0);
static const System::Int8 OCI_HA_SOURCE_DATABASE = System::Int8(0x1);
static const System::Int8 OCI_HA_SOURCE_NODE = System::Int8(0x2);
static const System::Int8 OCI_HA_SOURCE_SERVICE = System::Int8(0x3);
static const System::Int8 OCI_HA_SOURCE_SERVICE_MEMBER = System::Int8(0x4);
static const System::Int8 OCI_HA_SOURCE_ASM_INSTANCE = System::Int8(0x5);
static const System::Int8 OCI_HA_SOURCE_SERVICE_PRECONNECT = System::Int8(0x6);
static const System::Word OCI_ATTR_HA_STATUS = System::Word(0x192);
static const System::Int8 OCI_HA_STATUS_DOWN = System::Int8(0x0);
static const System::Int8 OCI_HA_STATUS_UP = System::Int8(0x1);
static const System::Word OCI_ATTR_HA_SRVFIRST = System::Word(0x193);
static const System::Word OCI_ATTR_HA_SRVNEXT = System::Word(0x194);
static const System::Word OCI_ATTR_TAF_ENABLED = System::Word(0x195);
static const System::Word OCI_ATTR_NFY_FLAGS = System::Word(0x196);
static const System::Word OCI_ATTR_MSG_DELIVERY_MODE = System::Word(0x197);
static const System::Word OCI_ATTR_DB_CHARSET_ID = System::Word(0x1a0);
static const System::Word OCI_ATTR_DB_NCHARSET_ID = System::Word(0x1a1);
static const System::Word OCI_ATTR_RESERVED_25 = System::Word(0x1a2);
static const System::Word OCI_ATTR_FLOW_CONTROL_TIMEOUT = System::Word(0x1a7);
static const System::Word OCI_ATTR_ENV_NLS_LANGUAGE = System::Word(0x1a8);
static const System::Word OCI_ATTR_ENV_NLS_TERRITORY = System::Word(0x1a9);
static const System::Int8 OCI_DIRPATH_STREAM_VERSION_1 = System::Int8(0x64);
static const System::Byte OCI_DIRPATH_STREAM_VERSION_2 = System::Byte(0xc8);
static const System::Word OCI_DIRPATH_STREAM_VERSION_3 = System::Word(0x12c);
static const System::Int8 OCI_ATTR_DIRPATH_MODE = System::Int8(0x4e);
static const System::Int8 OCI_ATTR_DIRPATH_NOLOG = System::Int8(0x4f);
static const System::Int8 OCI_ATTR_DIRPATH_PARALLEL = System::Int8(0x50);
static const System::Byte OCI_ATTR_DIRPATH_SORTED_INDEX = System::Byte(0x89);
static const System::Byte OCI_ATTR_DIRPATH_INDEX_MAINT_METHOD = System::Byte(0x8a);
static const System::Byte OCI_ATTR_DIRPATH_FILE = System::Byte(0x8b);
static const System::Byte OCI_ATTR_DIRPATH_STORAGE_INITIAL = System::Byte(0x8c);
static const System::Byte OCI_ATTR_DIRPATH_STORAGE_NEXT = System::Byte(0x8d);
static const System::Byte OCI_ATTR_DIRPATH_EXPR_TYPE = System::Byte(0x96);
static const System::Byte OCI_ATTR_DIRPATH_INPUT = System::Byte(0x97);
static const System::Int8 OCI_DIRPATH_INPUT_TEXT = System::Int8(0x1);
static const System::Int8 OCI_DIRPATH_INPUT_STREAM = System::Int8(0x2);
static const System::Int8 OCI_DIRPATH_INPUT_UNKNOWN = System::Int8(0x4);
static const System::Byte OCI_ATTR_DIRPATH_FN_CTX = System::Byte(0xa7);
static const System::Byte OCI_ATTR_DIRPATH_OID = System::Byte(0xbb);
static const System::Byte OCI_ATTR_DIRPATH_SID = System::Byte(0xc2);
static const System::Byte OCI_ATTR_DIRPATH_OBJ_CONSTR = System::Byte(0xce);
static const System::Byte OCI_ATTR_DIRPATH_STREAM_VERSION = System::Byte(0xd4);
static const System::Byte OCIP_ATTR_DIRPATH_VARRAY_INDEX = System::Byte(0xd5);
static const System::Word OCI_ATTR_DIRPATH_DCACHE_NUM = System::Word(0x12f);
static const System::Word OCI_ATTR_DIRPATH_DCACHE_SIZE = System::Word(0x130);
static const System::Word OCI_ATTR_DIRPATH_DCACHE_MISSES = System::Word(0x131);
static const System::Word OCI_ATTR_DIRPATH_DCACHE_HITS = System::Word(0x132);
static const System::Word OCI_ATTR_DIRPATH_DCACHE_DISABLE = System::Word(0x133);
static const System::Word OCI_ATTR_DIRPATH_RESERVED_7 = System::Word(0x146);
static const System::Word OCI_ATTR_DIRPATH_RESERVED_8 = System::Word(0x147);
static const System::Word OCI_ATTR_DIRPATH_CONVERT = System::Word(0x148);
static const System::Word OCI_ATTR_DIRPATH_BADROW = System::Word(0x149);
static const System::Word OCI_ATTR_DIRPATH_BADROW_LENGTH = System::Word(0x14a);
static const System::Word OCI_ATTR_DIRPATH_WRITE_ORDER = System::Word(0x14b);
static const System::Word OCI_ATTR_DIRPATH_GRANULE_SIZE = System::Word(0x14c);
static const System::Word OCI_ATTR_DIRPATH_GRANULE_OFFSET = System::Word(0x14d);
static const System::Word OCI_ATTR_DIRPATH_RESERVED_1 = System::Word(0x14e);
static const System::Word OCI_ATTR_DIRPATH_RESERVED_2 = System::Word(0x14f);
static const System::Word OCI_ATTR_DIRPATH_RESERVED_3 = System::Word(0x151);
static const System::Word OCI_ATTR_DIRPATH_RESERVED_4 = System::Word(0x152);
static const System::Word OCI_ATTR_DIRPATH_RESERVED_5 = System::Word(0x165);
static const System::Word OCI_ATTR_DIRPATH_RESERVED_6 = System::Word(0x166);
static const System::Word OCI_ATTR_DIRPATH_LOCK_WAIT = System::Word(0x167);
static const System::Int8 OCI_DIRPATH_LOAD = System::Int8(0x1);
static const System::Int8 OCI_DIRPATH_UNLOAD = System::Int8(0x2);
static const System::Int8 OCI_DIRPATH_CONVERT = System::Int8(0x3);
static const System::Int8 OCI_DIRPATH_INDEX_MAINT_SINGLE_ROW = System::Int8(0x1);
static const System::Int8 OCI_DIRPATH_INDEX_MAINT_SKIP_UNUSABLE = System::Int8(0x2);
static const System::Int8 OCI_DIRPATH_INDEX_MAINT_SKIP_ALL = System::Int8(0x3);
static const System::Int8 OCI_DIRPATH_NORMAL = System::Int8(0x1);
static const System::Int8 OCI_DIRPATH_PARTIAL = System::Int8(0x2);
static const System::Int8 OCI_DIRPATH_NOT_PREPARED = System::Int8(0x3);
static const System::Int8 OCI_DIRPATH_COL_COMPLETE = System::Int8(0x0);
static const System::Int8 OCI_DIRPATH_COL_NULL = System::Int8(0x1);
static const System::Int8 OCI_DIRPATH_COL_PARTIAL = System::Int8(0x2);
static const System::Int8 OCI_DIRPATH_DATASAVE_SAVEONLY = System::Int8(0x0);
static const System::Int8 OCI_DIRPATH_DATASAVE_FINISH = System::Int8(0x1);
static const System::Int8 OCI_CURSOR_OPEN = System::Int8(0x0);
static const System::Int8 OCI_CURSOR_CLOSED = System::Int8(0x1);
static const System::Int8 OCI_CL_START = System::Int8(0x0);
static const System::Int8 OCI_CL_END = System::Int8(0x1);
static const System::Int8 OCI_SP_SUPPORTED = System::Int8(0x0);
static const System::Int8 OCI_SP_UNSUPPORTED = System::Int8(0x1);
static const System::Int8 OCI_NW_SUPPORTED = System::Int8(0x0);
static const System::Int8 OCI_NW_UNSUPPORTED = System::Int8(0x1);
static const System::Int8 OCI_AC_DDL = System::Int8(0x0);
static const System::Int8 OCI_NO_AC_DDL = System::Int8(0x1);
static const System::Int8 OCI_LOCK_IMMEDIATE = System::Int8(0x0);
static const System::Int8 OCI_LOCK_DELAYED = System::Int8(0x1);
static const System::Int8 OCI_INSTANCE_TYPE_UNKNOWN = System::Int8(0x0);
static const System::Int8 OCI_INSTANCE_TYPE_RDBMS = System::Int8(0x1);
static const System::Int8 OCI_INSTANCE_TYPE_OSM = System::Int8(0x2);
static const System::Int8 OCI_INSTANCE_TYPE_PROXY = System::Int8(0x3);
static const System::Int8 OCI_INSTANCE_TYPE_IOS = System::Int8(0x4);
static const System::Int8 OCI_ASM_VOLUME_UNSUPPORTED = System::Int8(0x0);
static const System::Int8 OCI_ASM_VOLUME_SUPPORTED = System::Int8(0x1);
static const System::Int8 OCI_AUTH = System::Int8(0x8);
static const System::Int8 OCI_MAX_FNS = System::Int8(0x64);
static const System::Int8 OCI_SQLSTATE_SIZE = System::Int8(0x5);
static const System::Word OCI_ERROR_MAXMSG_SIZE = System::Word(0x400);
static const System::Word OCI_ERROR_MAXMSG_SIZE2 = System::Word(0xc00);
static const unsigned OCI_LOBMAXSIZE = unsigned(0xffffffff);
static const System::Int8 OCI_ROWID_LEN = System::Int8(0x17);
static const System::Byte OCI_LOB_CONTENTTYPE_MAXSIZE = System::Byte(0x80);
static const System::Byte OCI_LOB_CONTENTTYPE_MAXBYTESIZE = System::Byte(0x80);
static const System::Word OCI_MAX_ATTR_LEN = System::Word(0x400);
static const System::Int8 OCI_NLS_MAXBUFSZ = System::Int8(0x64);
static const System::Int8 OCI_FO_END = System::Int8(0x1);
static const System::Int8 OCI_FO_ABORT = System::Int8(0x2);
static const System::Int8 OCI_FO_REAUTH = System::Int8(0x4);
static const System::Int8 OCI_FO_BEGIN = System::Int8(0x8);
static const System::Int8 OCI_FO_ERROR = System::Int8(0x10);
static const System::Word OCI_FO_RETRY = System::Word(0x6342);
static const System::Int8 OCI_FO_NONE = System::Int8(0x1);
static const System::Int8 OCI_FO_SESSION = System::Int8(0x2);
static const System::Int8 OCI_FO_SELECT = System::Int8(0x4);
static const System::Int8 OCI_FO_TXNAL = System::Int8(0x8);
static const System::Int8 OCI_ATTR_MAXLEN_COMPAT_STANDARD = System::Int8(0x1);
static const System::Int8 OCI_ATTR_MAXLEN_COMPAT_EXTENDED = System::Int8(0x2);
static const System::Int8 OCI_ONE_PIECE = System::Int8(0x0);
static const System::Int8 OCI_FIRST_PIECE = System::Int8(0x1);
static const System::Int8 OCI_NEXT_PIECE = System::Int8(0x2);
static const System::Int8 OCI_LAST_PIECE = System::Int8(0x3);
static const System::Int8 OCI_FILE_READONLY = System::Int8(0x1);
static const System::Int8 OCI_LOB_READONLY = System::Int8(0x1);
static const System::Int8 OCI_LOB_READWRITE = System::Int8(0x2);
static const System::Int8 OCI_LOB_WRITEONLY = System::Int8(0x3);
static const System::Int8 OCI_LOB_APPENDONLY = System::Int8(0x4);
static const System::Int8 OCI_LOB_FULLOVERWRITE = System::Int8(0x5);
static const System::Int8 OCI_LOB_FULLREAD = System::Int8(0x6);
static const System::Int8 OCI_LOB_BUFFER_FREE = System::Int8(0x1);
static const System::Int8 OCI_LOB_BUFFER_NOFREE = System::Int8(0x2);
static const System::Int8 OCI_LOB_OPT_COMPRESS = System::Int8(0x1);
static const System::Int8 OCI_LOB_OPT_ENCRYPT = System::Int8(0x2);
static const System::Int8 OCI_LOB_OPT_DEDUPLICATE = System::Int8(0x4);
static const System::Int8 OCI_LOB_OPT_ALLOCSIZE = System::Int8(0x8);
static const System::Int8 OCI_LOB_OPT_CONTENTTYPE = System::Int8(0x10);
static const System::Int8 OCI_LOB_OPT_MODTIME = System::Int8(0x20);
static const System::Int8 OCI_LOB_COMPRESS_OFF = System::Int8(0x0);
static const System::Int8 OCI_LOB_COMPRESS_ON = System::Int8(0x1);
static const System::Int8 OCI_LOB_ENCRYPT_OFF = System::Int8(0x0);
static const System::Int8 OCI_LOB_ENCRYPT_ON = System::Int8(0x2);
static const System::Int8 OCI_LOB_DEDUPLICATE_OFF = System::Int8(0x0);
static const System::Int8 OCI_LOB_DEDUPLICATE_ON = System::Int8(0x4);
static const System::Int8 OCI_STMT_SELECT = System::Int8(0x1);
static const System::Int8 OCI_STMT_UPDATE = System::Int8(0x2);
static const System::Int8 OCI_STMT_DELETE = System::Int8(0x3);
static const System::Int8 OCI_STMT_INSERT = System::Int8(0x4);
static const System::Int8 OCI_STMT_CREATE = System::Int8(0x5);
static const System::Int8 OCI_STMT_DROP = System::Int8(0x6);
static const System::Int8 OCI_STMT_ALTER = System::Int8(0x7);
static const System::Int8 OCI_STMT_BEGIN = System::Int8(0x8);
static const System::Int8 OCI_STMT_DECLARE = System::Int8(0x9);
static const System::Int8 OCI_STMT_CALL = System::Int8(0xa);
static const System::Int8 OCI_STMT_EXPLAIN1 = System::Int8(0xe);
static const System::Int8 OCI_STMT_EXPLAIN2 = System::Int8(0xf);
static const System::Int8 OCI_PTYPE_UNK = System::Int8(0x0);
static const System::Int8 OCI_PTYPE_TABLE = System::Int8(0x1);
static const System::Int8 OCI_PTYPE_VIEW = System::Int8(0x2);
static const System::Int8 OCI_PTYPE_PROC = System::Int8(0x3);
static const System::Int8 OCI_PTYPE_FUNC = System::Int8(0x4);
static const System::Int8 OCI_PTYPE_PKG = System::Int8(0x5);
static const System::Int8 OCI_PTYPE_TYPE = System::Int8(0x6);
static const System::Int8 OCI_PTYPE_SYN = System::Int8(0x7);
static const System::Int8 OCI_PTYPE_SEQ = System::Int8(0x8);
static const System::Int8 OCI_PTYPE_COL = System::Int8(0x9);
static const System::Int8 OCI_PTYPE_ARG = System::Int8(0xa);
static const System::Int8 OCI_PTYPE_LIST = System::Int8(0xb);
static const System::Int8 OCI_PTYPE_TYPE_ATTR = System::Int8(0xc);
static const System::Int8 OCI_PTYPE_TYPE_COLL = System::Int8(0xd);
static const System::Int8 OCI_PTYPE_TYPE_METHOD = System::Int8(0xe);
static const System::Int8 OCI_PTYPE_TYPE_ARG = System::Int8(0xf);
static const System::Int8 OCI_PTYPE_TYPE_RESULT = System::Int8(0x10);
static const System::Int8 OCI_PTYPE_SCHEMA = System::Int8(0x11);
static const System::Int8 OCI_PTYPE_DATABASE = System::Int8(0x12);
static const System::Int8 OCI_PTYPE_RULE = System::Int8(0x13);
static const System::Int8 OCI_PTYPE_RULE_SET = System::Int8(0x14);
static const System::Int8 OCI_PTYPE_EVALUATION_CONTEXT = System::Int8(0x15);
static const System::Int8 OCI_PTYPE_TABLE_ALIAS = System::Int8(0x16);
static const System::Int8 OCI_PTYPE_VARIABLE_TYPE = System::Int8(0x17);
static const System::Int8 OCI_PTYPE_NAME_VALUE = System::Int8(0x18);
static const System::Int8 OCI_NLS_CHARSET_ID = System::Int8(0x5d);
static const System::Int8 OCI_NLS_NCHARSET_ID = System::Int8(0x5e);
static const System::Int8 OCI_DBSTARTUPFLAG_FORCE = System::Int8(0x1);
static const System::Int8 OCI_DBSTARTUPFLAG_RESTRICT = System::Int8(0x2);
static const System::Int8 OCI_DBSHUTDOWN_TRANSACTIONAL = System::Int8(0x1);
static const System::Int8 OCI_DBSHUTDOWN_TRANSACTIONAL_LOCAL = System::Int8(0x2);
static const System::Int8 OCI_DBSHUTDOWN_IMMEDIATE = System::Int8(0x3);
static const System::Int8 OCI_DBSHUTDOWN_ABORT = System::Int8(0x4);
static const System::Int8 OCI_DBSHUTDOWN_FINAL = System::Int8(0x5);
static const System::Int8 OCI_IND_NOTNULL = System::Int8(0x0);
static const System::Int8 OCI_IND_NULL = System::Int8(-1);
static const System::Int8 OCI_IND_BADNULL = System::Int8(-2);
static const System::Int8 OCI_IND_NOTNULLABLE = System::Int8(-3);
static const System::Int8 OCI_ATTR_OBJECT_NEWNOTNULL = System::Int8(0x10);
static const System::Int8 OCI_ATTR_OBJECT_DETECTCHANGE = System::Int8(0x20);
static const System::Int8 OCI_ATTR_CACHE_ARRAYFLUSH = System::Int8(0x40);
static const System::Word OCI_DURATION_INVALID = System::Word(0xffff);
static const System::Int8 OCI_DURATION_BEGIN = System::Int8(0xa);
static const System::Int8 OCI_DURATION_NULL = System::Int8(0x9);
static const System::Int8 OCI_DURATION_DEFAULT = System::Int8(0x8);
static const System::Int8 OCI_DURATION_USER_CALLBACK = System::Int8(0x7);
static const System::Int8 OCI_DURATION_NEXT = System::Int8(0x6);
static const System::Int8 OCI_DURATION_SESSION = System::Int8(0xa);
static const System::Int8 OCI_DURATION_TRANS = System::Int8(0xb);
static const System::Int8 OCI_TYPEPARAM_IN = System::Int8(0x0);
static const System::Int8 OCI_TYPEPARAM_OUT = System::Int8(0x1);
static const System::Int8 OCI_TYPEPARAM_INOUT = System::Int8(0x2);
static const System::Int8 OCI_TYPEPARAM_BYREF = System::Int8(0x3);
static const System::Int8 OCI_TYPEPARAM_OUTNCPY = System::Int8(0x4);
static const System::Int8 OCI_TYPEPARAM_INOUTNCPY = System::Int8(0x5);
static const System::Int8 OCI_NUMBER_SIZE = System::Int8(0x16);
static const System::Int8 OCI_NUMBER_UNSIGNED = System::Int8(0x0);
static const System::Int8 OCI_NUMBER_SIGNED = System::Int8(0x2);
static const System::Int8 MAXTXNAMELEN = System::Int8(0x40);
static const System::Byte XIDDATASIZE = System::Byte(0x80);
static const System::Int8 MAXGTRIDSIZE = System::Int8(0x40);
static const System::Int8 MAXBQUALSIZE = System::Int8(0x40);
static const System::Int8 NULLXID_ID = System::Int8(-1);
static const System::Int8 SQLT_CHR = System::Int8(0x1);
static const System::Int8 SQLT_NUM = System::Int8(0x2);
static const System::Int8 SQLT_INT = System::Int8(0x3);
static const System::Int8 SQLT_FLT = System::Int8(0x4);
static const System::Int8 SQLT_STR = System::Int8(0x5);
static const System::Int8 SQLT_VNU = System::Int8(0x6);
static const System::Int8 SQLT_PDN = System::Int8(0x7);
static const System::Int8 SQLT_LNG = System::Int8(0x8);
static const System::Int8 SQLT_VCS = System::Int8(0x9);
static const System::Int8 SQLT_NON = System::Int8(0xa);
static const System::Int8 SQLT_RID = System::Int8(0xb);
static const System::Int8 SQLT_DAT = System::Int8(0xc);
static const System::Int8 SQLT_VBI = System::Int8(0xf);
static const System::Int8 SQLT_BIN = System::Int8(0x17);
static const System::Int8 SQLT_LBI = System::Int8(0x18);
static const System::Int8 _SQLT_PLI = System::Int8(0x1d);
static const System::Int8 SQLT_UIN = System::Int8(0x44);
static const System::Int8 SQLT_SLS = System::Int8(0x5b);
static const System::Int8 SQLT_LVC = System::Int8(0x5e);
static const System::Int8 SQLT_LVB = System::Int8(0x5f);
static const System::Int8 SQLT_AFC = System::Int8(0x60);
static const System::Int8 SQLT_AVC = System::Int8(0x61);
static const System::Int8 SQLT_CUR = System::Int8(0x66);
static const System::Int8 SQLT_RDD = System::Int8(0x68);
static const System::Int8 SQLT_LAB = System::Int8(0x69);
static const System::Int8 SQLT_OSL = System::Int8(0x6a);
static const System::Int8 SQLT_NTY = System::Int8(0x6c);
static const System::Int8 SQLT_REF = System::Int8(0x6e);
static const System::Int8 SQLT_CLOB = System::Int8(0x70);
static const System::Int8 SQLT_BLOB = System::Int8(0x71);
static const System::Int8 SQLT_BFILEE = System::Int8(0x72);
static const System::Int8 SQLT_CFILEE = System::Int8(0x73);
static const System::Int8 SQLT_RSET = System::Int8(0x74);
static const System::Int8 SQLT_NCO = System::Int8(0x7a);
static const System::Byte SQLT_VST = System::Byte(0x9b);
static const System::Byte SQLT_ODT = System::Byte(0x9c);
static const System::Byte SQLT_REC = System::Byte(0xfa);
static const System::Byte SQLT_TAB = System::Byte(0xfb);
static const System::Byte SQLT_BOL = System::Byte(0xfc);
static const System::Byte SQLT_DATE = System::Byte(0xb8);
static const System::Byte SQLT_TIME = System::Byte(0xb9);
static const System::Byte SQLT_TIME_TZ = System::Byte(0xba);
static const System::Byte SQLT_TIMESTAMP = System::Byte(0xbb);
static const System::Byte SQLT_TIMESTAMP_TZ = System::Byte(0xbc);
static const System::Byte SQLT_INTERVAL_YM = System::Byte(0xbd);
static const System::Byte SQLT_INTERVAL_DS = System::Byte(0xbe);
static const System::Byte SQLT_TIMESTAMP_LTZ = System::Byte(0xe8);
static const System::Byte SQLT_PNTY = System::Byte(0xf1);
static const System::Int8 SQLT_IBFLOAT = System::Int8(0x64);
static const System::Int8 SQLT_IBDOUBLE = System::Int8(0x65);
static const System::Int8 SQLCS_IMPLICIT = System::Int8(0x1);
static const System::Int8 SQLCS_NCHAR = System::Int8(0x2);
static const System::Int8 SQLCS_EXPLICIT = System::Int8(0x3);
static const System::Int8 SQLCS_FLEXIBLE = System::Int8(0x4);
static const System::Int8 SQLCS_LIT_NULL = System::Int8(0x5);
}	/* namespace Oraclecli */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ORACLECLI)
using namespace Firedac::Phys::Oraclecli;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS)
using namespace Firedac::Phys;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Phys_OraclecliHPP
