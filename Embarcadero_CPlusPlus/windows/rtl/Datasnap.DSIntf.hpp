// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSIntf.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsintfHPP
#define Datasnap_DsintfHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Variants.hpp>
#include <Data.DB.hpp>
#include <Data.DBCommon.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsintf
{
//-- forward type declarations -----------------------------------------------
struct AGGVALUE;
struct DSBOOKMRK;
struct DSProps;
struct DSFLDDesc;
struct DSIDXDesc;
struct TDSDataPacketFldDesc;
__interface DELPHIINTERFACE IDSBase;
typedef System::DelphiInterface<IDSBase> _di_IDSBase;
__interface DELPHIINTERFACE IDSCursor;
typedef System::DelphiInterface<IDSCursor> _di_IDSCursor;
__interface DELPHIINTERFACE IDSWriter;
typedef System::DelphiInterface<IDSWriter> _di_IDSWriter;
//-- type declarations -------------------------------------------------------
typedef System::LongBool *PLongBool;

typedef System::Word DBResult;

enum DECLSPEC_DENUM DBSearchCond : unsigned int { keySEARCHEQ, keySEARCHGT, keySEARCHGEQ };

typedef System::StaticArray<char, 32> MIDASNAME;

typedef System::StaticArray<char, 261> MIDASPATH;

typedef System::PVarArray TDataPacket;

typedef System::Byte DSAttr;

typedef DSAttr *pDSAttr;

typedef void *hDSFilter;

typedef hDSFilter *phDSFilter;

enum DECLSPEC_DENUM GROUPSTATE : unsigned int { grSTATEMIDDLE, grSTATEFIRST, grSTATELAST, grSTATEFIRSTLAST };

typedef int hDSAggregate;

typedef hDSAggregate *phDSAggregate;

enum DECLSPEC_DENUM AGGSTATE : unsigned int { aggSTATEUNDEF, aggSTATEOK, aggSTATEBLANK, aggSTATEERROR };

#ifndef _WIN64
#pragma pack(push,1)
#endif /* not _WIN64 */
struct DECLSPEC_DRECORD AGGVALUE
{
	
private:
	struct DECLSPEC_DRECORD _AGGVALUE__1
	{
	};
	
	
	
public:
	int iCnt;
	AGGSTATE eAggState;
	_AGGVALUE__1 Value;
};
#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */


typedef DSBOOKMRK *pDSBOOKMRK;

struct DECLSPEC_DRECORD DSBOOKMRK
{
public:
	int iPos;
	int iState;
	int iRecNo;
	int iSeqNo;
	int iOrderID;
};


typedef int SAVEPOINT;

typedef SAVEPOINT *pSAVEPOINT;

typedef System::StaticArray<int, 16> DSKEY;

typedef System::StaticArray<System::LongBool, 16> DSKEYBOOL;

enum DECLSPEC_DENUM DSProp : unsigned int { dspropLOGCHANGES, dspropREADONLY, dspropNOOFCHANGES, dspropCONSTRAINTS_DISABLED, dspropDSISPARTIAL, dspropRECORDSINDS, dspropAUTOINC_DISABLED, dspropISDELTA, dspropDONTINCLMETADATA, dspropINCLBLOBSINDELTA, dspropGETSAVEPOINT, dspropCOMPRESSARRAYS, dspropMD_SEMANTICS, dspropFIELD_FULLNAME, dspropFIELDID_FORNAME, dspropFIELDID_FORPARENT, dspropCHANGEINDEX_VIEW, dspropGETUNIQUEINDEX, dspropREMOTE_UPDATEMODE, dspropXML_STREAMMODE, dspropDISABLEDELETES, dspropDISABLEINSERTS, dspropDISABLEEDITS, dspropDISABLESTRINGTRIM, dspropDATAHASCHANGED, dspropUTF8METADATA, dspropUTF8ERRORMSG, dspropANSICODEPAGE, dspropUPDATESPENDING };

enum DECLSPEC_DENUM CURProp : unsigned int { curpropCONSTRAINT_ERROR_MESSAGE, curpropDSBASE, curpropSETCRACK, curpropGETORG_RECBUF };

typedef DSProps *pDSProps;

#ifndef _WIN64
#pragma pack(push,1)
#endif /* not _WIN64 */
struct DECLSPEC_DRECORD DSProps
{
public:
	MIDASPATH szName;
	int iFields;
	int iRecBufSize;
	int iBookMarkSize;
	System::LongBool bReadOnly;
	int iIndexes;
	int iOptParams;
	System::LongBool bDelta;
	int iLCID;
	System::StaticArray<int, 8> iUnused;
};
#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */


typedef DSFLDDesc *pDSFLDDesc;

struct DECLSPEC_DRECORD DSFLDDesc
{
public:
	MIDASNAME szName;
	int iFldType;
	int iFldSubType;
	int iUnits1;
	int iUnits2;
	int iFldLen;
	int iFldOffsInRec;
	int iNullOffsInRec;
	System::Word iFieldID;
	System::Word iFieldIDParent;
	System::LongBool bCalculated;
	int iFldAttr;
	int iOptParameters;
};


typedef DSIDXDesc *pDSIDXDesc;

struct DECLSPEC_DRECORD DSIDXDesc
{
public:
	MIDASNAME szName;
	int iFields;
	DSKEY iKeyFields;
	int iKeyLen;
	System::LongBool bUnique;
	DSKEYBOOL bDescending;
	DSKEYBOOL bCaseInsensitive;
};


typedef void __stdcall (*pfCHANGECallBack)(NativeUInt iClientData);

typedef System::LongBool __stdcall (*pfDSFilter)(NativeUInt iClientData, void * pRecBuf);

typedef System::Word __stdcall (*pfDSCalcField)(NativeUInt iClientData, void * pRecBuf);

typedef int dsCBRType;

typedef int *pdsCBRType;

typedef int __stdcall (*pfDSReconcile)(NativeUInt iClientData, int iRslt, DSAttr iAction, int iResponse, int iErrCode, char * pErrMessage, char * pErrContext, void * pRecUpd, void * pRecOrg, void * pRecConflict);

typedef int __fastcall (*pfDSReconcile_MD)(NativeUInt iClientData, int iRslt, DSAttr iAction, int iErrResponse, int iErrCode, char * pErrMessage, char * pErrContext, System::PByte pRecUpd, System::PByte pRecOrg, System::PByte pRecConflict, int iLevels, System::PInteger piFieldIDs);

typedef int __fastcall (*pfFLDComp)(NativeUInt iClientData, void * pVal1, void * pVal2);

enum DECLSPEC_DENUM TPcktAttrArea : unsigned int { fldAttrArea, pcktAttrArea };

enum DECLSPEC_DENUM TPcktFldStatus : unsigned int { fldIsChanged, fldIsNull, fldIsUnChanged };

typedef TDSDataPacketFldDesc *PDSDataPacketFldDesc;

#ifndef _WIN64
#pragma pack(push,1)
#endif /* not _WIN64 */
struct DECLSPEC_DRECORD TDSDataPacketFldDesc
{
public:
	MIDASNAME szFieldName;
	int iFieldType;
	System::Word iAttributes;
};
#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */


__interface  INTERFACE_UUID("{9E8D2FA2-591C-11D0-BF52-0020AF32BD64}") IDSBase  : public System::IInterface 
{
	virtual System::Word __stdcall Create(unsigned iFields, pDSFLDDesc pFldDes, char * pszName) = 0 ;
	virtual System::Word __stdcall AddField(pDSFLDDesc pFldDes) = 0 ;
	virtual System::Word __stdcall AppendData(System::PVarArray Packet, System::LongBool bEof) = 0 ;
	virtual System::Word __stdcall GetOptParameter(unsigned iNo, unsigned iFldNo, void * &ppName, unsigned &piType, unsigned &piLen, void * &ppValue) = 0 ;
	virtual System::Word __stdcall AddOptParameter(unsigned iFldNo, char * pszAttr, unsigned iType, unsigned iLen, void * pValue) = 0 ;
	virtual System::Word __stdcall GetProps(DSProps &Prop) = 0 ;
	virtual System::Word __stdcall GetFieldDescs(pDSFLDDesc Fields) = 0 ;
	virtual System::Word __stdcall GetIndexDescs(pDSIDXDesc p1) = 0 ;
	virtual System::Word __stdcall GetDelta(/* out */ _di_IDSBase &DsDelta) = 0 ;
	virtual System::Word __stdcall StreamDS(/* out */ System::PVarArray &Packet) = 0 ;
	virtual System::Word __stdcall AcceptChanges() = 0 ;
	virtual System::Word __stdcall PutBlank(void * pRecBuf, unsigned iRecNo, unsigned iFldNo, unsigned iBlankValue) = 0 ;
	virtual System::Word __stdcall CreateIndex(const DSIDXDesc &IdxDesc) = 0 ;
	virtual System::Word __stdcall RemoveIndex(char * pszName) = 0 ;
	virtual System::Word __stdcall GetErrorString(System::Word iErrCode, char * pString) = 0 ;
	virtual int __stdcall FldCmp(unsigned iFldType, void * pFld1, void * pFld2, unsigned iUnits1, unsigned iUnits2) = 0 ;
	virtual System::Word __stdcall GetProp(DSProp eProp, void * piPropValue) = 0 ;
	virtual System::Word __stdcall SetProp(DSProp eProp, NativeUInt iPropValue) = 0 ;
	virtual System::Word __stdcall SetFieldCalculation(NativeUInt iClientData, pfDSCalcField pfCalc) = 0 ;
	virtual System::Word __stdcall Reconcile(System::PVarArray DeltaPacket, System::PVarArray ErrorPacket, NativeUInt iClientData, pfDSReconcile pfReconcile) = 0 ;
	virtual System::Word __stdcall Reserved1(void * Input) = 0 ;
	virtual System::Word __stdcall Reserved2(void * Input) = 0 ;
	virtual System::Word __stdcall Reserved3(void * Input) = 0 ;
	virtual System::Word __stdcall Refresh(System::PVarArray NewPacket, NativeUInt iClientData, pfDSReconcile pfReconcile) = 0 ;
	virtual System::Word __stdcall Reset() = 0 ;
	virtual System::Word __stdcall RollBack(SAVEPOINT iSavePoint) = 0 ;
	virtual System::Word __stdcall GetEmbeddedDS(unsigned iFieldID, /* out */ _di_IDSBase &DsDet) = 0 ;
	virtual System::Word __stdcall MakeEmbedded(_di_IDSBase DsDet, unsigned iFieldsLink, System::PCardinal piFieldsM, System::PCardinal piFieldsD, char * pMasterFieldName, char * pDetailFieldName) = 0 ;
	virtual System::Word __stdcall RefreshRecords(System::PVarArray NewDataPacket, unsigned iRecNo, NativeUInt iClientData, pfDSReconcile pfReconcile) = 0 ;
	virtual System::Word __stdcall ReleaseBlobs(unsigned iBlobId) = 0 ;
	virtual System::Word __stdcall Clone(unsigned iPType, System::LongBool bRecurse, System::LongBool bCloneOptParams, _di_IDSBase &DataSet) = 0 ;
	virtual System::Word __stdcall Reconcile_MD(_di_IDSBase pDsRec, System::PVarArray pDeltaPacket, System::PVarArray pErrorPacket, NativeUInt iClientData, pfDSReconcile_MD pfReconcile_MD) = 0 ;
	virtual System::Word __stdcall DropOptParameter(unsigned iFldNo, char * pName) = 0 ;
};

__interface  INTERFACE_UUID("{9E8D2FA4-591C-11D0-BF52-0020AF32BD64}") IDSCursor  : public System::IInterface 
{
	virtual System::Word __stdcall InitCursor(_di_IDSBase DataSet) = 0 ;
	virtual System::Word __stdcall CloneCursor(_di_IDSCursor Cursor) = 0 ;
	virtual System::Word __stdcall GetCursorProps(DSProps &p1) = 0 ;
	virtual System::Word __stdcall GetIndexDescs(System::LongBool bCurrentOnly, DSIDXDesc &IdxDesc) = 0 ;
	virtual System::Word __stdcall GetFieldDescs(pDSFLDDesc p1) = 0 ;
	virtual System::Word __stdcall GetCurrentRecord(void * pRecBuf) = 0 ;
	virtual System::Word __stdcall GetRecordBlock(System::PCardinal piRecs, void * pRecBuf) = 0 ;
	virtual System::Word __stdcall GetCurrentBookMark(void * pBookMark) = 0 ;
	virtual System::Word __stdcall GetSequenceNumber(unsigned &iSeq) = 0 ;
	virtual System::Word __stdcall GetRecordAttribute(DSAttr &Attr) = 0 ;
	virtual System::Word __stdcall GetRecordCount(int &iRecs) = 0 ;
	virtual System::Word __stdcall MoveToBOF() = 0 ;
	virtual System::Word __stdcall MoveToEOF() = 0 ;
	virtual System::Word __stdcall MoveRelative(int i) = 0 ;
	virtual System::Word __stdcall MoveToSeqNo(unsigned i) = 0 ;
	virtual System::Word __stdcall MoveToBookMark(void * pBookMark) = 0 ;
	virtual System::Word __stdcall MoveToKey(DBSearchCond SearchCond, unsigned iFields, unsigned iPartLen, void * pRecBuf) = 0 ;
	virtual System::Word __stdcall CompareBookMarks(void * pBookMark1, void * pBookMark2, int &iCmp) = 0 ;
	virtual System::Word __stdcall ExtractKey(void * pRecBuf, void * pKeyBuf) = 0 ;
	virtual System::Word __stdcall GetRecordForKey(unsigned iFields, unsigned iPartLen, void * pKey, void * pRecBuf) = 0 ;
	virtual System::Word __stdcall GetField(void * pRecBuf, unsigned iFieldNo, void * pFldBuf, System::LongBool &bBlank) = 0 ;
	virtual System::Word __stdcall PutField(void * pRecBuf, unsigned iFieldNo, void * pFldBuf) = 0 ;
	virtual System::Word __stdcall GetBlobLen(void * pRecBuf, unsigned iFieldNo, unsigned &iLength) = 0 ;
	virtual System::Word __stdcall GetBlob(void * pRecBuf, unsigned iFieldNo, unsigned iOffSet, void * pBuf, unsigned &iLength) = 0 ;
	virtual System::Word __stdcall PutBlob(void * pRecBuf, unsigned iFieldNo, unsigned iOffSet, void * pBuf, unsigned iLength) = 0 ;
	virtual System::Word __stdcall InitRecord(void * pRecBuf) = 0 ;
	virtual System::Word __stdcall DeleteRecord() = 0 ;
	virtual System::Word __stdcall ModifyRecord(void * pRecBuf) = 0 ;
	virtual System::Word __stdcall InsertRecord(void * pRecBuf) = 0 ;
	virtual System::Word __stdcall UndoLastChange(System::LongBool bFollowChange) = 0 ;
	virtual System::Word __stdcall AddFilter(void * pcanExpr, unsigned iLen, hDSFilter &hFilter) = 0 ;
	virtual System::Word __stdcall DropFilter(hDSFilter hFilter) = 0 ;
	virtual System::Word __stdcall SetRange(unsigned iFields, void * pKey1, System::LongBool bKey1Incl, void * pKey2, System::LongBool bKey2Incl) = 0 ;
	virtual System::Word __stdcall DropRange() = 0 ;
	virtual System::Word __stdcall SortOnFields(unsigned iFields, System::PPointer piFields, PLongBool pDescending, PLongBool pCaseInsensitive) = 0 ;
	virtual System::Word __stdcall UseIndexOrder(char * pszName) = 0 ;
	virtual System::Word __stdcall SetNotifyCallBack(NativeUInt iClientData, pfCHANGECallBack pfCallBack) = 0 ;
	virtual System::Word __stdcall AddFilterCallBack(NativeUInt iClientData, pfDSFilter pfFilter, hDSFilter &hFilter) = 0 ;
	virtual System::Word __stdcall VerifyField(unsigned iFieldNo, void * pFldBuf) = 0 ;
	virtual System::Word __stdcall GetProp(CURProp eProp, void * piPropValue) = 0 ;
	virtual System::Word __stdcall RevertRecord() = 0 ;
	virtual System::Word __stdcall LocateWithFilter(void * pCanExpr, unsigned iLen) = 0 ;
	virtual System::Word __stdcall AddAggregate(unsigned iFlds, unsigned iCanLen, void * pCanExpr, hDSAggregate &hAgg) = 0 ;
	virtual System::Word __stdcall DropAggregate(hDSAggregate hAgg) = 0 ;
	virtual System::Word __stdcall GetAggregateValue(hDSAggregate hAgg, void * pValue, System::LongBool &bBlank) = 0 ;
	virtual System::Word __stdcall GetAggregateDesc(hDSAggregate hAgg, DSFLDDesc &Desc) = 0 ;
	virtual System::Word __stdcall MoveToNextSubGroup(unsigned iFields) = 0 ;
	virtual System::Word __stdcall GetSubGroupState(unsigned iFields, GROUPSTATE &iSubGroupState) = 0 ;
	virtual System::Word __stdcall LinkCursors(unsigned iFieldsM, System::PCardinal piFieldsM, System::PCardinal piFieldsD, _di_IDSCursor hCurDet) = 0 ;
	virtual System::Word __stdcall ResyncWithMaster() = 0 ;
	virtual System::Word __stdcall SetProp(CURProp eProp, NativeUInt iPropValue) = 0 ;
	virtual System::Word __stdcall GetRecordNumber(unsigned &iRecNo) = 0 ;
	virtual System::Word __stdcall GetRowRequestPacket(System::LongBool bKeysOnly, System::LongBool bFetchAllBlobs, System::LongBool bFetchAllDetails, System::LongBool bInclMetaData, /* out */ System::PVarArray &Packet) = 0 ;
	virtual System::Word __stdcall RefreshRecord(System::PVarArray Packet) = 0 ;
};

__interface  INTERFACE_UUID("{9E8D2FA6-591C-11D0-BF52-0020AF32BD64}") IDSWriter  : public System::IInterface 
{
	virtual System::Word __stdcall Init_Sequential(unsigned Version, System::Word Columns) = 0 ;
	virtual System::Word __stdcall Init(unsigned Version, System::Word Columns, PDSDataPacketFldDesc FieldDesc) = 0 ;
	virtual System::Word __stdcall AddAttribute(TPcktAttrArea AttrArea, char * Attr, unsigned AttrType, unsigned Len, void * Value) = 0 ;
	virtual System::Word __stdcall GetDataPacket(System::PVarArray &SA) = 0 ;
	virtual System::Word __stdcall GetSize(unsigned &DataPacketSize) = 0 ;
	virtual System::Word __stdcall PutField(TPcktFldStatus FldStatus, unsigned Len, void * Src) = 0 ;
	virtual System::Word __stdcall AddColumnDesc(const TDSDataPacketFldDesc &FldDes) = 0 ;
	virtual System::Word __stdcall Reset() = 0 ;
	virtual System::Word __stdcall GetColumnCount(unsigned &Count) = 0 ;
	virtual System::Word __stdcall GetColumnDescs(PDSDataPacketFldDesc FieldDes) = 0 ;
	virtual System::Word __stdcall GetErrorString(System::Word iErrCode, char * pString) = 0 ;
	virtual System::Word __stdcall EndOfNestedRows() = 0 ;
	virtual System::Word __stdcall SetXMLMode(int iMode) = 0 ;
	virtual unsigned __stdcall GetXMLMode() = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 dsRecUnmodified = System::Int8(0x0);
static const System::Int8 dsRecOrg = System::Int8(0x1);
static const System::Int8 dsRecDeleted = System::Int8(0x2);
static const System::Int8 dsRecNew = System::Int8(0x4);
static const System::Int8 dsRecModified = System::Int8(0x8);
static const System::Int8 dsUnused = System::Int8(0x20);
static const System::Int8 dsDetUpd = System::Int8(0x40);
static const System::Int8 dsIsNotVisible = System::Int8(0x23);
static const System::Int8 dsIsVisible = System::Int8(-36);
static const System::Int8 fldAttrHIDDEN = System::Int8(0x1);
static const System::Int8 fldAttrREADONLY = System::Int8(0x2);
static const System::Int8 fldAttrREQUIRED = System::Int8(0x4);
static const System::Int8 fldAttrLINK = System::Int8(0x8);
static const System::Int8 BLANK_NULL = System::Int8(0x1);
static const System::Int8 BLANK_NOTCHANGED = System::Int8(0x2);
static const System::Int8 MAXKEYFIELDS = System::Int8(0x10);
static const System::Int8 mdCASCADEDEL = System::Int8(0x4);
static const System::Int8 mdCASCADEMOD = System::Int8(0x8);
static const System::Int8 mdALLOWLINKCHANGE = System::Int8(0x10);
static const System::Int8 dscbrSKIP = System::Int8(0x1);
static const System::Int8 dscbrABORT = System::Int8(0x2);
static const System::Int8 dscbrMERGE = System::Int8(0x3);
static const System::Int8 dscbrAPPLY = System::Int8(0x4);
static const System::Int8 dscbrIGNORE = System::Int8(0x5);
static const System::Int8 dscbrCORRECT = System::Int8(0x4);
static const System::Int8 dscbrCANCEL = System::Int8(0x5);
static const System::Int8 dscbrREFRESH = System::Int8(0x6);
static const System::Int8 xmlUNTYPED = System::Int8(0x1);
static const System::Int8 xmlXMLDATATYPED = System::Int8(0x2);
static const System::Int8 xmlXMLSCHEMA = System::Int8(0x4);
static const System::Int8 xmlXMLUTF8 = System::Int8(0x8);
static const System::Int8 xmlON = System::Int8(0x5);
static const System::Int8 xmlUTF8 = System::Int8(0xd);
static const System::Int8 xmlOFF = System::Int8(0x0);
#define szUNIQUE_KEY L"UNIQUE_KEY"
#define szPRIMARY_KEY L"PRIMARY_KEY"
#define szDEFAULT_ORDER L"DEFAULT_ORDER"
#define szCHANGEINDEX L"CHANGEINDEX"
#define szCHANGE_LOG L"CHANGE_LOG"
#define szSERVER_COL L"SERVER_COL"
#define szCONSTRAINTS L"CONSTRAINTS"
#define szDATASET_CONTEXT L"DATASET_CONTEXT"
#define szDATASET_DELTA L"DATASET_DELTA"
#define szREADONLY L"READONLY"
#define szSUBTYPE L"SUBTYPE"
#define szDECIMALS L"DECIMALS"
#define szWIDTH L"WIDTH"
#define szFIELDNAME L"FIELDNAME"
#define szLCID L"LCID"
#define szBDEDOMX L"BDEDOMAIN_X"
#define szBDERECX L"BDERECORD_X"
#define szBDEDEFX L"BDEDEFAULT_X"
#define szAUTOINCVALUE L"AUTOINCVALUE"
#define szELEMENTS L"ELEMENTS"
#define szTABLE_NAME L"TABLE_NAME"
#define szMD_FIELDLINKS L"MD_FIELDLINKS"
#define szTYPENAME L"TYPENAME"
#define szUPDATEMODE L"UPDATEMODE"
#define szFIELDPROPS L"FIELDPROPS"
#define szPROVFLAGS L"PROVFLAGS"
#define szORIGIN L"ORIGIN"
#define szMD_SEMANTICS L"MD_SEMANTICS"
#define szSERVERCALC L"SERVER_CALC"
#define szBDEDOMCL L"BDEDOMAIN_CL"
#define szBDERECCL L"BDERECORD_CL"
#define szBDEDEFCL L"BDEDEFAULT_CL"
#define szDISABLE_INSERTS L"DISABLE_INSERTS"
#define szDISABLE_DELETES L"DISABLE_DELETES"
#define szDISABLE_EDITS L"DISABLE_EDITS"
#define szNO_RESET_CALL L"NO_RESET_CALL"
#define szMINVALUE L"MINVALUE"
#define szMAXVALUE L"MAXVALUE"
#define szstMEMO L"Text"
#define szstWideMEMO L"WideText"
#define szstBINARY L"Binary"
#define szstFMTMEMO L"Formatted"
#define szstOLEOBJ L"Ole"
#define szstGRAPHIC L"Graphics"
#define szstDBSOLEOBJ L"dBASEOle"
#define szstTYPEDBINARY L"TypedBinary"
#define szstMONEY L"Money"
#define szstAUTOINC L"Autoinc"
#define szstADTNESTEDTABLE L"ADTNestedTable"
#define szstFIXEDCHAR L"FixedChar"
#define szstREFNESTEDTABLE L"Reference"
#define szstGUID L"Guid"
#define szstACCOLEOBJ L"AccessOle"
#define szstHMEMO L"HMemo"
#define szstHBINARY L"HBinary"
static const System::Int8 fldstReference = System::Int8(0x46);
static const System::Int8 dsfldUNKNOWN = System::Int8(0x0);
static const System::Int8 dsfldINT = System::Int8(0x1);
static const System::Int8 dsfldUINT = System::Int8(0x2);
static const System::Int8 dsfldBOOL = System::Int8(0x3);
static const System::Int8 dsfldFLOATIEEE = System::Int8(0x4);
static const System::Int8 dsfldBCD = System::Int8(0x5);
static const System::Int8 dsfldDATE = System::Int8(0x6);
static const System::Int8 dsfldTIME = System::Int8(0x7);
static const System::Int8 dsfldTIMESTAMP = System::Int8(0x8);
static const System::Int8 dsfldZSTRING = System::Int8(0x9);
static const System::Int8 dsfldUNICODE = System::Int8(0xa);
static const System::Int8 dsfldBYTES = System::Int8(0xb);
static const System::Int8 dsfldADT = System::Int8(0xc);
static const System::Int8 dsfldARRAY = System::Int8(0xd);
static const System::Int8 dsfldEMBEDDEDTBL = System::Int8(0xe);
static const System::Int8 dsfldREF = System::Int8(0xf);
static const System::Int8 dsfldDATETIME = System::Int8(0x11);
static const System::Int8 dsfldFMTBCD = System::Int8(0x12);
static const System::Int8 dsfldSINGLE = System::Int8(0x1b);
static const System::Int8 dsfldDATETIMEOFFSET = System::Int8(0x24);
static const System::Int8 dsSizeBitsLen = System::Int8(0x10);
static const System::Word dsSizeBitsMask = System::Word(0xffff);
static const int dsTypeBitsMask = int(0x3f0000);
static const int dsVaryingFldType = int(0x400000);
static const int dsArrayFldType = int(0x800000);
static const int dsPseudoFldType = int(0x1000000);
static const int dsCompArrayFldType = int(0x2000000);
static const int dsEmbeddedFldType = int(0x4000000);
static const unsigned dsIncInDelta = unsigned(0x80000000);
static const System::Word dskeyCASEINSENSITIVE = System::Word(0x4000);
static const System::Word dskeyDESCENDING = System::Word(0x8000);
static const unsigned dsDELAYEDBIT = unsigned(0x80000000);
static const System::Int8 PACKETVERSION_1 = System::Int8(0x1);
static const System::Int8 PACKETVERSION_2 = System::Int8(0x2);
static const System::Int8 PACKETVERSION_3 = System::Int8(0x3);
static const System::Int8 dsCASCADEDELETES = System::Int8(0x1);
static const System::Int8 dsCASCADEUPDATES = System::Int8(0x2);
static const System::Int8 fldUNKNOWN = System::Int8(0x0);
static const System::Int8 fldZSTRING = System::Int8(0x1);
static const System::Int8 fldDATE = System::Int8(0x2);
static const System::Int8 fldBLOB = System::Int8(0x3);
static const System::Int8 fldBOOL = System::Int8(0x4);
static const System::Int8 fldINT16 = System::Int8(0x5);
static const System::Int8 fldINT32 = System::Int8(0x6);
static const System::Int8 fldFLOAT = System::Int8(0x7);
static const System::Int8 fldBCD = System::Int8(0x8);
static const System::Int8 fldBYTES = System::Int8(0x9);
static const System::Int8 fldTIME = System::Int8(0xa);
static const System::Int8 fldTIMESTAMP = System::Int8(0xb);
static const System::Int8 fldUINT16 = System::Int8(0xc);
static const System::Int8 fldUINT32 = System::Int8(0xd);
static const System::Int8 fldFLOATIEEE = System::Int8(0xe);
static const System::Int8 fldVARBYTES = System::Int8(0xf);
static const System::Int8 fldLOCKINFO = System::Int8(0x10);
static const System::Int8 fldCURSOR = System::Int8(0x11);
static const System::Int8 fldINT64 = System::Int8(0x12);
static const System::Int8 fldUINT64 = System::Int8(0x13);
static const System::Int8 fldADT = System::Int8(0x14);
static const System::Int8 fldARRAY = System::Int8(0x15);
static const System::Int8 fldREF = System::Int8(0x16);
static const System::Int8 fldTABLE = System::Int8(0x17);
static const System::Int8 fldDATETIME = System::Int8(0x18);
static const System::Int8 fldFMTBCD = System::Int8(0x19);
static const System::Int8 fldWIDESTRING = System::Int8(0x1a);
static const System::Int8 MAXLOGFLDTYPES = System::Int8(0x1b);
static const System::Word fldUNICODE = System::Word(0x1007);
static const System::Int8 fldINT8 = System::Int8(0x1c);
static const System::Int8 fldUINT8 = System::Int8(0x1d);
static const System::Int8 fldSINGLE = System::Int8(0x1b);
static const System::Int8 fldDATETIMEOFFSET = System::Int8(0x24);
static const System::Int8 fldstMONEY = System::Int8(0x15);
static const System::Int8 fldstMEMO = System::Int8(0x16);
static const System::Int8 fldstBINARY = System::Int8(0x17);
static const System::Int8 fldstFMTMEMO = System::Int8(0x18);
static const System::Int8 fldstOLEOBJ = System::Int8(0x19);
static const System::Int8 fldstGRAPHIC = System::Int8(0x1a);
static const System::Int8 fldstDBSOLEOBJ = System::Int8(0x1b);
static const System::Int8 fldstTYPEDBINARY = System::Int8(0x1c);
static const System::Int8 fldstACCOLEOBJ = System::Int8(0x1e);
static const System::Int8 fldstWIDEMEMO = System::Int8(0x20);
static const System::Int8 fldstHMEMO = System::Int8(0x21);
static const System::Int8 fldstHBINARY = System::Int8(0x22);
static const System::Int8 fldstBFILE = System::Int8(0x24);
static const System::Int8 fldstPASSWORD = System::Int8(0x1);
static const System::Int8 fldstFIXED = System::Int8(0x1f);
static const System::Int8 fldstGUID = System::Int8(0x26);
static const System::Int8 fldstORAINTERVAL = System::Int8(0x28);
static const System::Int8 fldstORATIMESTAMP = System::Int8(0x27);
static const System::Int8 fldstAUTOINC = System::Int8(0x1d);
extern DELPHI_PACKAGE Data::Dbcommon::TFieldMap FieldTypeMap;
extern DELPHI_PACKAGE System::StaticArray<System::Word, 52> FldSubTypeMap;
extern DELPHI_PACKAGE System::StaticArray<Data::Db::TFieldType, 27> DataTypeMap;
extern DELPHI_PACKAGE System::StaticArray<Data::Db::TFieldType, 15> BlobTypeMap;
static const System::Int8 DBERR_NONE = System::Int8(0x0);
static const System::Word DBERR_BOF = System::Word(0x2201);
static const System::Word DBERR_EOF = System::Word(0x2202);
static const System::Word DBERR_NOSUCHINDEX = System::Word(0x270d);
static const System::Int8 ERRCAT_ALC = System::Int8(0x40);
static const System::Word ERRBASE_ALC = System::Word(0x4000);
static const System::Int8 ERRCODE_DELTAISEMPTY = System::Int8(0x1);
static const System::Int8 ERRCODE_NOTHINGTOUNDO = System::Int8(0x2);
static const System::Int8 ERRCODE_NOMETADATA = System::Int8(0x3);
static const System::Int8 ERRCODE_CANNOTAPPEND = System::Int8(0x4);
static const System::Int8 ERRCODE_DATAPACKETMISMATCH = System::Int8(0x5);
static const System::Int8 ERRCODE_ABORTED = System::Int8(0x6);
static const System::Int8 ERRCODE_CANCELLED = System::Int8(0x7);
static const System::Int8 ERRCODE_NEWERVERSIONREQ = System::Int8(0x8);
static const System::Int8 ERRCODE_BLOBNOTFETCHED = System::Int8(0x9);
static const System::Int8 ERRCODE_DETAILSNOTFETCHED = System::Int8(0xa);
static const System::Int8 ERRCODE_NOMASTERRECORD = System::Int8(0xb);
static const System::Int8 ERRCODE_LINKFIELDSNOTUNIQUE = System::Int8(0xc);
static const System::Int8 ERRCODE_FLYAWAY_WRONGORDER = System::Int8(0xd);
static const System::Int8 ERRCODE_NOCASCADEDUPDATES = System::Int8(0xe);
static const System::Word DBERR_DELTAISEMPTY = System::Word(0x4001);
static const System::Word DBERR_NOTHINGTOUNDO = System::Word(0x4002);
static const System::Word DBERR_NOMETADATA = System::Word(0x4003);
static const System::Word DBERR_CANNOTAPPEND = System::Word(0x4004);
static const System::Word DBERR_DATAPACKETMISMATCH = System::Word(0x4005);
static const System::Word DBERR_ABORTED = System::Word(0x4006);
static const System::Word DBERR_CANCELLED = System::Word(0x4007);
static const System::Word DBERR_NEWERVERSIONREQ = System::Word(0x4008);
static const System::Word DBERR_BLOBNOTFETCHED = System::Word(0x4009);
static const System::Word DBERR_DETAILSNOTFETCHED = System::Word(0x400a);
static const System::Word DBERR_NOMASTERRECORD = System::Word(0x400b);
static const System::Word DBERR_LINKFIELDSNOTUNIQUE = System::Word(0x400c);
static const System::Word DBERR_FLYAWAY_WRONGORDER = System::Word(0x400d);
static const System::Word DBERR_NOCASCADEDUPDATES = System::Word(0x400e);
static const System::Word ERRBASE_INVALIDREQ = System::Word(0x2700);
static const System::Int8 ERRCODE_OUTOFRANGE = System::Int8(0x1);
static const System::Word DBERR_OUTOFRANGE = System::Word(0x2701);
static const System::Int8 ERRCODE_OUTOFMEMORY = System::Int8(0x1);
static const System::Int8 ERRCODE_INVALIDARG = System::Int8(0x2);
static const System::Int8 ERRCODE_UNABLETOLOADICU = System::Int8(0x5);
extern DELPHI_PACKAGE GUID CLSID_DSBase;
extern DELPHI_PACKAGE GUID CLSID_DSCursor;
extern DELPHI_PACKAGE GUID CLSID_DSWriter;
extern DELPHI_PACKAGE void __fastcall RaiseErr(int Status);
extern DELPHI_PACKAGE void __fastcall CreateDbClientObject(const GUID &CLSID, const GUID &IID, /* out */ void *Obj);
extern DELPHI_PACKAGE void __fastcall FreeDataPacket(System::PVarArray &DataPacket);
extern DELPHI_PACKAGE System::PVarArray __fastcall VarToDataPacket(const System::OleVariant &V);
extern DELPHI_PACKAGE int __fastcall DataPacketSize(const System::PVarArray DataPacket);
extern DELPHI_PACKAGE void __fastcall DataPacketToVariant(const System::PVarArray DataPacket, System::OleVariant &V);
#ifndef _WIN64
extern DELPHI_PACKAGE System::DynamicArray<System::Byte> __fastcall VariantArrayToBytes(const System::OleVariant &V);
extern DELPHI_PACKAGE System::OleVariant __fastcall BytesToVariantArray(const System::DynamicArray<System::Byte> S);
#else /* _WIN64 */
extern DELPHI_PACKAGE System::TArray__1<System::Byte> __fastcall VariantArrayToBytes(const System::OleVariant &V);
extern DELPHI_PACKAGE System::OleVariant __fastcall BytesToVariantArray(const System::TArray__1<System::Byte> S);
#endif /* _WIN64 */
extern DELPHI_PACKAGE void __fastcall RegisterMidasLib(void * GetClassProc);
}	/* namespace Dsintf */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSINTF)
using namespace Datasnap::Dsintf;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsintfHPP
