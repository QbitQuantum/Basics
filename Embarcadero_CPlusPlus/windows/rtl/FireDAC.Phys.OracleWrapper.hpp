// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.OracleWrapper.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_OraclewrapperHPP
#define Firedac_Phys_OraclewrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Win.Registry.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Data.SqlTimSt.hpp>
#include <Data.FmtBcd.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Consts.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.SQLTimeInt.hpp>
#include <FireDAC.Phys.OracleCli.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Oraclewrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TOCILib;
class DELPHICLASS TOCIHandle;
class DELPHICLASS TOCIEnv;
class DELPHICLASS EOCINativeException;
class DELPHICLASS TOCIError;
class DELPHICLASS TOCIService;
class DELPHICLASS TOCISession;
class DELPHICLASS TOCIServer;
class DELPHICLASS TOCIXid;
class DELPHICLASS TOCITransaction;
class DELPHICLASS TOCIStatement;
class DELPHICLASS TOCIVariable;
class DELPHICLASS TOCIDescriptor;
class DELPHICLASS TOCISelectItem;
class DELPHICLASS TOCILobLocator;
class DELPHICLASS TOCIIntLocator;
class DELPHICLASS TOCITempLocator;
class DELPHICLASS TOCIExtLocator;
class DELPHICLASS TOCILobLocatorStream;
class DELPHICLASS TOCIDescribe;
class DELPHICLASS TOCIDirectPath;
class DELPHICLASS TOCIDirectPathColArray;
class DELPHICLASS TOCIDirectPathStream;
class DELPHICLASS TOCIDirectPathColumnParam;
class DELPHICLASS TOCIPLSQLDescriber;
class DELPHICLASS TOCIOpaqueValue;
class DELPHICLASS TOCITimestamp;
class DELPHICLASS TOCITimeInterval;
class DELPHICLASS TOCICollection;
template<typename T> class DELPHICLASS TOCIDescCollection__1;
class DELPHICLASS TOCIAdmin;
class DELPHICLASS TOCISubscription;
class DELPHICLASS TOCIChangeRowDesc;
class DELPHICLASS TOCIChangeTableDesc;
class DELPHICLASS TOCIChangeQueryDesc;
class DELPHICLASS TOCIChangeDesc;
class DELPHICLASS TOCIQueryNotification;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
typedef System::TMetaClass* TOCILobLocatorClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TOCILobLocatorClass);
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TOCICollectionClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TOCICollectionClass);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TOCILib : public Firedac::Stan::Util::TFDLibrary
{
	typedef Firedac::Stan::Util::TFDLibrary inherited;
	
private:
	TOCIEnv* FEnv;
	Firedac::Stan::Util::TFDLog* FMessages;
	System::UnicodeString __fastcall GetOCIPaths(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib);
	void __fastcall GetTNSPaths();
	void __fastcall GetNLSLang();
	
protected:
	virtual void __fastcall GetLibraryInfo();
	virtual void __fastcall LoadEntries();
	
public:
	System::UnicodeString FKey;
	System::UnicodeString FOracleHome;
	System::UnicodeString FTNSNames;
	System::UnicodeString FNLSLang;
	bool FInstantClient;
	bool FThreaded;
	Firedac::Phys::Oraclecli::TOCIClientVersion OCIClientVersion;
	Firedac::Phys::Oraclecli::TOCIPasswordChange OCIPasswordChange;
	Firedac::Phys::Oraclecli::TOCIInitialize OCIInitialize;
	Firedac::Phys::Oraclecli::TOCIEnvInit OCIEnvInit;
	Firedac::Phys::Oraclecli::TOCIEnvCreate OCIEnvCreate;
	Firedac::Phys::Oraclecli::TOCIEnvNlsCreate OCIEnvNlsCreate;
	Firedac::Phys::Oraclecli::TOCIHandleAlloc OCIHandleAlloc;
	Firedac::Phys::Oraclecli::TOCIServerAttach OCIServerAttach;
	Firedac::Phys::Oraclecli::TOCIAttrSet OCIAttrSet;
	Firedac::Phys::Oraclecli::TOCISessionBegin OCISessionBegin;
	Firedac::Phys::Oraclecli::TOCISessionEnd OCISessionEnd;
	Firedac::Phys::Oraclecli::TOCIServerDetach OCIServerDetach;
	Firedac::Phys::Oraclecli::TOCIHandleFree OCIHandleFree;
	Firedac::Phys::Oraclecli::TOCIErrorGet OCIErrorGet;
	Firedac::Phys::Oraclecli::TOCIStmtPrepare OCIStmtPrepare;
	Firedac::Phys::Oraclecli::TOCIStmtExecute OCIStmtExecute;
	Firedac::Phys::Oraclecli::TOCIStmtGetNextResult OCIStmtGetNextResult;
	Firedac::Phys::Oraclecli::TOCIParamGet OCIParamGet;
	Firedac::Phys::Oraclecli::TOCIAttrGet OCIAttrGet;
	Firedac::Phys::Oraclecli::TOCIStmtFetch OCIStmtFetch;
	Firedac::Phys::Oraclecli::TOCIDefineByPos OCIDefineByPos;
	Firedac::Phys::Oraclecli::TOCIDefineArrayOfStruct OCIDefineArrayOfStruct;
	Firedac::Phys::Oraclecli::TOCIRowidToChar OCIRowidToChar;
	Firedac::Phys::Oraclecli::TOCIBindByPos OCIBindByPos;
	Firedac::Phys::Oraclecli::TOCIBindByName OCIBindByName;
	Firedac::Phys::Oraclecli::TOCITransStart OCITransStart;
	Firedac::Phys::Oraclecli::TOCITransCommit OCITransCommit;
	Firedac::Phys::Oraclecli::TOCITransRollback OCITransRollback;
	Firedac::Phys::Oraclecli::TOCITransDetach OCITransDetach;
	Firedac::Phys::Oraclecli::TOCITransPrepare OCITransPrepare;
	Firedac::Phys::Oraclecli::TOCITransForget OCITransForget;
	Firedac::Phys::Oraclecli::TOCIDescribeAny OCIDescribeAny;
	Firedac::Phys::Oraclecli::TOCIBreak OCIBreak;
	Firedac::Phys::Oraclecli::TOCIReset OCIReset;
	Firedac::Phys::Oraclecli::TOCIDescriptorAlloc OCIDescriptorAlloc;
	Firedac::Phys::Oraclecli::TOCIDescriptorFree OCIDescriptorFree;
	Firedac::Phys::Oraclecli::TOCIStmtGetPieceInfo OCIStmtGetPieceInfo;
	Firedac::Phys::Oraclecli::TOCIStmtSetPieceInfo OCIStmtSetPieceInfo;
	Firedac::Phys::Oraclecli::TOCIServerVersion OCIServerVersion;
	Firedac::Phys::Oraclecli::TOCIBindDynamic OCIBindDynamic;
	Firedac::Phys::Oraclecli::TOCILobAppend OCILobAppend;
	Firedac::Phys::Oraclecli::TOCILobAssign OCILobAssign;
	Firedac::Phys::Oraclecli::TOCILobCharSetForm OCILobCharSetForm;
	Firedac::Phys::Oraclecli::TOCILobClose OCILobClose;
	Firedac::Phys::Oraclecli::TOCILobCopy OCILobCopy;
	Firedac::Phys::Oraclecli::TOCILobEnableBuffering OCILobEnableBuffering;
	Firedac::Phys::Oraclecli::TOCILobDisableBuffering OCILobDisableBuffering;
	Firedac::Phys::Oraclecli::TOCILobErase OCILobErase;
	Firedac::Phys::Oraclecli::TOCILobFileExists OCILobFileExists;
	Firedac::Phys::Oraclecli::TOCILobFileGetName OCILobFileGetName;
	Firedac::Phys::Oraclecli::TOCILobFileSetName OCILobFileSetName;
	Firedac::Phys::Oraclecli::TOCILobFlushBuffer OCILobFlushBuffer;
	Firedac::Phys::Oraclecli::TOCILobGetLength OCILobGetLength;
	Firedac::Phys::Oraclecli::TOCILobIsOpen OCILobIsOpen;
	Firedac::Phys::Oraclecli::TOCILobLoadFromFile OCILobLoadFromFile;
	Firedac::Phys::Oraclecli::TOCILobLocatorIsInit OCILobLocatorIsInit;
	Firedac::Phys::Oraclecli::TOCILobOpen OCILobOpen;
	Firedac::Phys::Oraclecli::TOCILobRead OCILobRead;
	Firedac::Phys::Oraclecli::TOCILobTrim OCILobTrim;
	Firedac::Phys::Oraclecli::TOCILobWrite OCILobWrite;
	Firedac::Phys::Oraclecli::TOCILobCreateTemporary OCILobCreateTemporary;
	Firedac::Phys::Oraclecli::TOCILobFreeTemporary OCILobFreeTemporary;
	Firedac::Phys::Oraclecli::TOCILobIsTemporary OCILobIsTemporary;
	Firedac::Phys::Oraclecli::TOCIResultSetToStmt OCIResultSetToStmt;
	Firedac::Phys::Oraclecli::TOCIDirPathAbort OCIDirPathAbort;
	Firedac::Phys::Oraclecli::TOCIDirPathDataSave OCIDirPathDataSave;
	Firedac::Phys::Oraclecli::TOCIDirPathFinish OCIDirPathFinish;
	Firedac::Phys::Oraclecli::TOCIDirPathFlushRow OCIDirPathFlushRow;
	Firedac::Phys::Oraclecli::TOCIDirPathPrepare OCIDirPathPrepare;
	Firedac::Phys::Oraclecli::TOCIDirPathLoadStream OCIDirPathLoadStream;
	Firedac::Phys::Oraclecli::TOCIDirPathColArrayEntryGet OCIDirPathColArrayEntryGet;
	Firedac::Phys::Oraclecli::TOCIDirPathColArrayEntrySet OCIDirPathColArrayEntrySet;
	Firedac::Phys::Oraclecli::TOCIDirPathColArrayRowGet OCIDirPathColArrayRowGet;
	Firedac::Phys::Oraclecli::TOCIDirPathColArrayReset OCIDirPathColArrayReset;
	Firedac::Phys::Oraclecli::TOCIDirPathColArrayToStream OCIDirPathColArrayToStream;
	Firedac::Phys::Oraclecli::TOCIDirPathStreamReset OCIDirPathStreamReset;
	Firedac::Phys::Oraclecli::TOCIDirPathStreamToStream OCIDirPathStreamToStream;
	Firedac::Phys::Oraclecli::TOCIDateTimeGetDate OCIDateTimeGetDate;
	Firedac::Phys::Oraclecli::TOCIDateTimeGetTime OCIDateTimeGetTime;
	Firedac::Phys::Oraclecli::TOCIDateTimeConstruct OCIDateTimeConstruct;
	Firedac::Phys::Oraclecli::TOCIDateTimeGetTimeZoneOffset OCIDateTimeGetTimeZoneOffset;
	Firedac::Phys::Oraclecli::TOCIDateTimeAssign OCIDateTimeAssign;
	Firedac::Phys::Oraclecli::TOCIPing OCIPing;
	Firedac::Phys::Oraclecli::TOCINlsCharSetNameToId OCINlsCharSetNameToId;
	Firedac::Phys::Oraclecli::TOCINlsCharSetIdToName OCINlsCharSetIdToName;
	Firedac::Phys::Oraclecli::TOCINlsEnvironmentVariableGet OCINlsEnvironmentVariableGet;
	Firedac::Phys::Oraclecli::TOCIIntervalAssign OCIIntervalAssign;
	Firedac::Phys::Oraclecli::TOCIIntervalCheck OCIIntervalCheck;
	Firedac::Phys::Oraclecli::TOCIIntervalSetYearMonth OCIIntervalSetYearMonth;
	Firedac::Phys::Oraclecli::TOCIIntervalGetYearMonth OCIIntervalGetYearMonth;
	Firedac::Phys::Oraclecli::TOCIIntervalSetDaySecond OCIIntervalSetDaySecond;
	Firedac::Phys::Oraclecli::TOCIIntervalGetDaySecond OCIIntervalGetDaySecond;
	Firedac::Phys::Oraclecli::TOCIDBStartup OCIDBStartup;
	Firedac::Phys::Oraclecli::TOCIDBShutdown OCIDBShutdown;
	Firedac::Phys::Oraclecli::TOCICollSize OCICollSize;
	Firedac::Phys::Oraclecli::TOCICollMax OCICollMax;
	Firedac::Phys::Oraclecli::TOCICollGetElem OCICollGetElem;
	Firedac::Phys::Oraclecli::TOCICollAssignElem OCICollAssignElem;
	Firedac::Phys::Oraclecli::TOCICollAssign OCICollAssign;
	Firedac::Phys::Oraclecli::TOCICollAppend OCICollAppend;
	Firedac::Phys::Oraclecli::TOCICollTrim OCICollTrim;
	Firedac::Phys::Oraclecli::TOCICollIsLocator OCICollIsLocator;
	Firedac::Phys::Oraclecli::TOCIIterCreate OCIIterCreate;
	Firedac::Phys::Oraclecli::TOCIIterDelete OCIIterDelete;
	Firedac::Phys::Oraclecli::TOCIIterInit OCIIterInit;
	Firedac::Phys::Oraclecli::TOCIIterGetCurrent OCIIterGetCurrent;
	Firedac::Phys::Oraclecli::TOCIIterNext OCIIterNext;
	Firedac::Phys::Oraclecli::TOCIIterPrev OCIIterPrev;
	Firedac::Phys::Oraclecli::TOCISubscriptionRegister OCISubscriptionRegister;
	Firedac::Phys::Oraclecli::TOCISubscriptionPost OCISubscriptionPost;
	Firedac::Phys::Oraclecli::TOCISubscriptionUnRegister OCISubscriptionUnRegister;
	Firedac::Phys::Oraclecli::TOCISubscriptionDisable OCISubscriptionDisable;
	Firedac::Phys::Oraclecli::TOCISubscriptionEnable OCISubscriptionEnable;
	__fastcall TOCILib(Firedac::Stan::Util::TFDLog* AMessages, System::TObject* AOwningObj);
	HIDESBASE void __fastcall Load(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib, const System::UnicodeString ANLSLang, const System::UnicodeString ATNSAdmin, bool AThreaded);
	virtual void __fastcall Unload();
	static void __fastcall GetOracleHomeList(System::Classes::TStrings* AList);
	void __fastcall GetTNSServicesList(System::Classes::TStrings* AList);
	System::Word __fastcall CharSetNameToId(const System::UnicodeString AName);
public:
	/* TFDLibrary.Destroy */ inline __fastcall virtual ~TOCILib() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIHandle : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	void *FHandle;
	unsigned FType;
	bool FOwnHandle;
	TOCIHandle* FOwner;
	System::TObject* FOwningObj;
	TOCIEnv* FEnv;
	void __fastcall Init(unsigned AType);
	void __fastcall Check(int ACode);
	
protected:
	void __fastcall Trace(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	void __fastcall Trace(Firedac::Stan::Intf::TFDMoniEventKind AKind, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	void __fastcall Trace(const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	TOCICollection* __fastcall InitCollection(TOCICollectionClass ACollClass, TOCICollection* &AColl, void * AhColl);
	
public:
	__fastcall TOCIHandle(TOCIEnv* AEnv);
	__fastcall virtual ~TOCIHandle();
	void __fastcall SetStringAttr(int AAtrType, const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetStringAttr(int AAtrType);
#ifndef _WIN64
	void __fastcall SetBytesAttr(int AAtrType, const System::DynamicArray<System::Byte> AValue);
	System::DynamicArray<System::Byte> __fastcall GetBytesAttr(int AAtrType);
#else /* _WIN64 */
	void __fastcall SetBytesAttr(int AAtrType, const System::TArray__1<System::Byte> AValue);
	System::TArray__1<System::Byte> __fastcall GetBytesAttr(int AAtrType);
#endif /* _WIN64 */
	void __fastcall SetHandleAttr(int AAtrType, void * AValue);
	void * __fastcall GetHandleAttr(int AAtrType);
	void __fastcall SetUB1Attr(int AAtrType, System::Byte AValue);
	System::Byte __fastcall GetUB1Attr(int AAtrType);
	void __fastcall SetUB2Attr(int AAtrType, System::Word AValue);
	System::Word __fastcall GetUB2Attr(int AAtrType);
	void __fastcall SetUB4Attr(int AAtrType, unsigned AValue);
	unsigned __fastcall GetUB4Attr(int AAtrType);
	void __fastcall SetSB1Attr(int AAtrType, System::Int8 AValue);
	System::Int8 __fastcall GetSB1Attr(int AAtrType);
	void __fastcall SetSB4Attr(int AAtrType, int AValue);
	int __fastcall GetSB4Attr(int AAtrType);
	void __fastcall SetUB8Attr(int AAtrType, unsigned __int64 AValue);
	unsigned __int64 __fastcall GetUB8Attr(int AAtrType);
	__property void * Value = {read=FHandle};
	__property void * Handle = {read=FHandle, write=FHandle};
	__property unsigned HType = {read=FType, nodefault};
	__property TOCIEnv* Env = {read=FEnv};
	__property TOCIHandle* Owner = {read=FOwner};
	__property System::TObject* OwningObj = {read=FOwningObj};
	__property bool OwnHandle = {read=FOwnHandle, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIEnv : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
private:
	TOCIError* FError;
	TOCILib* FLib;
	System::Word FNLS_CHARSET_ID;
	System::Word FNLS_NCHARSET_ID;
	System::UnicodeString FCharsetName;
	System::Word FExplicitCharsetID;
	bool FByteSemantic;
	Firedac::Stan::Util::TFDBuffer* FBuffer;
	Firedac::Stan::Util::TFDEncoder* FDataEncoder;
	Firedac::Stan::Util::TFDEncoder* FMetaEncoder;
	Firedac::Stan::Intf::_di_IFDMoniClient FMonitor;
	bool FTracing;
	bool __fastcall GetTracing();
	void __fastcall InitEnvBase(System::Word ACharsetID);
	void __fastcall UpdateNLSCharsets();
	void __fastcall UpdateEncoder();
	
public:
	__fastcall TOCIEnv(TOCILib* ALib, System::TObject* AOwningObj, const Firedac::Stan::Intf::_di_IFDMoniClient AMonitor);
	__fastcall TOCIEnv(TOCILib* ALib, System::TObject* AOwningObj, void * AHandle, void * AErrHandle, const System::UnicodeString ACharsetName, System::Word AExplicitCharsetID, bool AByteSemantic, const Firedac::Stan::Intf::_di_IFDMoniClient AMonitor);
	__fastcall virtual ~TOCIEnv();
	void __fastcall InitEnv(const System::UnicodeString ACharsetName);
	System::UnicodeString __fastcall CharSetIdToName(System::Word AId);
	System::Word __fastcall CharSetNameToId(const System::UnicodeString AName);
	__property Firedac::Stan::Intf::_di_IFDMoniClient Monitor = {read=FMonitor, write=FMonitor};
	__property bool Tracing = {read=GetTracing, write=FTracing, nodefault};
	__property TOCIError* Error = {read=FError};
	__property TOCILib* Lib = {read=FLib};
	__property Firedac::Stan::Util::TFDBuffer* Buffer = {read=FBuffer};
	__property Firedac::Stan::Util::TFDEncoder* DataEncoder = {read=FDataEncoder};
	__property Firedac::Stan::Util::TFDEncoder* MetaEncoder = {read=FMetaEncoder};
	__property int CACHE_ARRAYFLUSH = {read=GetSB4Attr, write=SetSB4Attr, index=64, nodefault};
	__property unsigned CACHE_MAX_SIZE = {read=GetUB4Attr, write=SetUB4Attr, index=35, nodefault};
	__property unsigned CACHE_OPT_SIZE = {read=GetUB4Attr, write=SetUB4Attr, index=34, nodefault};
	__property unsigned PINOPTION = {read=GetUB4Attr, write=SetUB4Attr, index=36, nodefault};
	__property System::Word ALLOC_DURATION = {read=GetUB2Attr, write=SetUB2Attr, index=37, nodefault};
	__property System::Word PIN_DURATION = {read=GetUB2Attr, write=SetUB2Attr, index=38, nodefault};
	__property unsigned HEAPALLOC = {read=GetUB4Attr, index=30, nodefault};
	__property unsigned SHARED_HEAPALLOC = {read=GetUB4Attr, index=84, nodefault};
	__property int OBJECT_ = {read=GetSB4Attr, index=2, nodefault};
	__property int OBJECT_NEWNOTNULL = {read=GetSB4Attr, write=SetSB4Attr, index=16, nodefault};
	__property int OBJECT_DETECTCHANGE = {read=GetSB4Attr, write=SetSB4Attr, index=32, nodefault};
	__property System::Word ENV_CHARSET_ID = {read=GetUB2Attr, index=31, nodefault};
	__property System::Word ENV_NCHARSET_ID = {read=GetUB2Attr, index=262, nodefault};
	__property System::Byte ENV_UTF16 = {read=GetUB1Attr, index=209, nodefault};
	__property System::Word NLS_CHARSET_ID = {read=FNLS_CHARSET_ID, nodefault};
	__property System::Word NLS_NCHARSET_ID = {read=FNLS_NCHARSET_ID, nodefault};
	__property System::UnicodeString CharsetName = {read=FCharsetName};
	__property System::Word ExplicitCharsetID = {read=FExplicitCharsetID, nodefault};
	__property bool ByteSemantic = {read=FByteSemantic, nodefault};
	__property System::UnicodeString BIND_DN = {read=GetStringAttr, write=SetStringAttr, index=155};
	__property System::Word LDAP_AUTH = {read=GetUB2Attr, write=SetUB2Attr, index=158, nodefault};
	__property System::UnicodeString LDAP_CRED = {read=GetStringAttr, write=SetStringAttr, index=156};
	__property System::UnicodeString LDAP_CTX = {read=GetStringAttr, write=SetStringAttr, index=159};
	__property System::UnicodeString LDAP_HOST = {read=GetStringAttr, write=SetStringAttr, index=153};
	__property System::Word LDAP_PORT = {read=GetUB2Attr, write=SetUB2Attr, index=154, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EOCINativeException : public Firedac::Stan::Error::EFDDBEngineException
{
	typedef Firedac::Stan::Error::EFDDBEngineException inherited;
	
public:
	__fastcall EOCINativeException(TOCIError* AError)/* overload */;
	__fastcall EOCINativeException(TOCIHandle* AObj, int AErrorCode, const System::UnicodeString AMessage)/* overload */;
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual EOCINativeException()/* overload */ : Firedac::Stan::Error::EFDDBEngineException() { }
	/* EFDDBEngineException.Create */ inline __fastcall EOCINativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~EOCINativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EOCINativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EOCINativeException(NativeUInt Ident)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EOCINativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EOCINativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EOCINativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EOCINativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EOCINativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EOCINativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EOCINativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EOCINativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EOCINativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High, AHelpContext) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIError : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
private:
	Firedac::Stan::Error::EFDDBEngineException* FInfo;
	bool FIgnoreErrors;
	
public:
	__fastcall TOCIError(TOCIEnv* AEnv);
	__fastcall TOCIError(TOCIEnv* AEnv, void * AErrHandle);
	__fastcall virtual ~TOCIError();
	HIDESBASE void __fastcall Check(int ACode, System::TObject* AInitiator = (System::TObject*)(0x0));
	void __fastcall ClearInfo();
	void __fastcall CheckAllocateInfo();
	__property Firedac::Stan::Error::EFDDBEngineException* Info = {read=FInfo};
	__property unsigned DML_ROW_OFFSET = {read=GetUB4Attr, index=74, nodefault};
	__property bool IgnoreErrors = {read=FIgnoreErrors, write=FIgnoreErrors, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TOCIService : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
private:
	System::Classes::TNotifyEvent FOnYield;
	bool FNonBlockinMode;
	System::Byte FBytesPerChar;
	unsigned __int64 FServerVersion;
	void __fastcall DoYield();
	void __fastcall SetNonblockingMode(const bool Value);
	
public:
	__fastcall TOCIService(TOCIEnv* AEnv, System::TObject* AOwningObj);
	__fastcall TOCIService(TOCIEnv* AEnv, void * AHandle, System::TObject* AOwningObj);
	void __fastcall Break(bool ADoException);
	void __fastcall Reset(bool ADoException);
	void __fastcall TurnNONBLOCKING_MODE();
	void __fastcall UpdateNonBlockingMode();
	void __fastcall Ping();
	__property System::Classes::TNotifyEvent OnYield = {read=FOnYield, write=FOnYield};
	__property void * ENV_ = {read=GetHandleAttr, index=5};
	__property void * SERVER = {read=GetHandleAttr, write=SetHandleAttr, index=6};
	__property void * SESSION = {read=GetHandleAttr, write=SetHandleAttr, index=7};
	__property void * TRANS = {read=GetHandleAttr, write=SetHandleAttr, index=8};
	__property System::Byte IN_V8_MODE = {read=GetUB1Attr, index=44, nodefault};
	__property bool NONBLOCKING_MODE = {read=FNonBlockinMode, write=SetNonblockingMode, nodefault};
	__property unsigned STMTCACHESIZE = {read=GetUB4Attr, write=SetUB4Attr, index=176, nodefault};
	__property System::Byte VARTYPE_MAXLEN_COMPAT = {read=GetUB1Attr, index=489, nodefault};
	__property System::Byte BytesPerChar = {read=FBytesPerChar, write=FBytesPerChar, nodefault};
	__property unsigned __int64 ServerVersion = {read=FServerVersion, write=FServerVersion};
public:
	/* TOCIHandle.Destroy */ inline __fastcall virtual ~TOCIService() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCISession : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
private:
	bool FStarted;
	
public:
	__fastcall TOCISession(TOCIService* AService);
	__fastcall TOCISession(TOCIService* AService, void * AHandle);
	__fastcall virtual ~TOCISession();
	void __fastcall Start(const System::UnicodeString AUser, const System::UnicodeString APassword, unsigned AAuthentMode);
	void __fastcall ChangePassword(const System::UnicodeString AUser, const System::UnicodeString AOldPassword, const System::UnicodeString ANewPassword);
	void __fastcall Stop();
	void __fastcall Select();
	__property bool Started = {read=FStarted, nodefault};
	__property System::UnicodeString USERNAME = {read=GetStringAttr, write=SetStringAttr, index=22};
	__property System::UnicodeString PASSWORD = {read=GetStringAttr, write=SetStringAttr, index=23};
	__property System::Byte MIGSESSION = {read=GetUB1Attr, write=SetUB1Attr, index=86, nodefault};
	__property void * INITIAL_CLIENT_ROLES = {write=SetHandleAttr, index=100};
	__property unsigned APPCTX_SIZE = {write=SetUB4Attr, index=273, nodefault};
	__property void * APPCTX_LIST = {read=GetHandleAttr, index=274};
	__property System::UnicodeString APPCTX_NAME = {write=SetStringAttr, index=275};
	__property System::UnicodeString APPCTX_ATTR = {write=SetStringAttr, index=276};
	__property System::UnicodeString APPCTX_VALUE = {write=SetStringAttr, index=277};
	__property System::Byte COLLECT_CALL_TIME = {read=GetUB1Attr, write=SetUB1Attr, index=369, nodefault};
	__property unsigned __int64 CALL_TIME = {read=GetUB8Attr, index=370};
	__property System::UnicodeString ACTION = {write=SetStringAttr, index=367};
	__property System::UnicodeString CLIENT_INFO = {write=SetStringAttr, index=368};
	__property System::UnicodeString MODULE = {write=SetStringAttr, index=366};
	__property void * CERTIFICATE = {write=SetHandleAttr, index=169};
	__property System::UnicodeString CLIENT_IDENTIFIER = {write=SetStringAttr, index=278};
	__property System::UnicodeString DISTINGUISHED_NAME = {write=SetStringAttr, index=300};
	__property void * PROXY_CREDENTIALS = {write=SetHandleAttr, index=99};
	__property System::UnicodeString CURRENT_SCHEMA = {read=GetStringAttr, write=SetStringAttr, index=224};
	__property unsigned MAX_OPEN_CURSORS = {read=GetUB4Attr, index=471, nodefault};
	__property unsigned TRANSACTION_IN_PROGRESS = {read=GetUB4Attr, index=484, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TOCIServer : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
private:
	bool FAttached;
	System::UnicodeString FServerVersionStr;
	unsigned __int64 FServerVersion;
	System::UnicodeString __fastcall GetServerVersionStr();
	unsigned __int64 __fastcall GetServerVersion();
	
public:
	__fastcall TOCIServer(TOCIService* AService);
	__fastcall TOCIServer(TOCIService* AService, void * AHandle);
	__fastcall virtual ~TOCIServer();
	void __fastcall Attach(const System::UnicodeString AServerName);
	void __fastcall Detach();
	void __fastcall Select();
	__property System::UnicodeString ServerVersionStr = {read=GetServerVersionStr};
	__property unsigned __int64 ServerVersion = {read=GetServerVersion};
	__property bool Attached = {read=FAttached, nodefault};
	__property void * ENV_ = {read=GetHandleAttr, index=5};
	__property System::UnicodeString EXTERNAL_NAME = {read=GetStringAttr, write=SetStringAttr, index=26};
	__property System::UnicodeString INTERNAL_NAME = {read=GetStringAttr, write=SetStringAttr, index=25};
	__property System::Byte IN_V8_MODE = {read=GetUB1Attr, index=44, nodefault};
	__property void * FOCBK = {read=GetHandleAttr, write=SetHandleAttr, index=43};
	__property System::UnicodeString SERVER_GROUP = {read=GetStringAttr, write=SetStringAttr, index=85};
	__property unsigned SERVER_STATUS = {read=GetUB4Attr, index=143, nodefault};
	__property unsigned SEND_TIMEOUT = {read=GetUB4Attr, write=SetUB4Attr, index=435, nodefault};
	__property unsigned RECEIVE_TIMEOUT = {read=GetUB4Attr, write=SetUB4Attr, index=436, nodefault};
};


class PASCALIMPLEMENTATION TOCIXid : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TOCIEnv* FEnv;
	System::Classes::TNotifyEvent FOnChanging;
	System::Classes::TNotifyEvent FOnChanged;
	System::UnicodeString FName;
	void __fastcall SetBQUAL(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetBQUAL();
	void __fastcall SetGTRID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetGTRID();
	bool __fastcall GetIsNull();
	void __fastcall SetName(const System::UnicodeString AValue);
	
public:
	Firedac::Phys::Oraclecli::TXID FXID;
	__fastcall TOCIXid(TOCIEnv* AEnv);
	virtual void __fastcall Assign(System::Classes::TPersistent* AValue);
	void __fastcall Clear();
	void __fastcall SetParts(const System::UnicodeString AGTRID, const System::UnicodeString ABQUAL);
	void __fastcall MarkTransaction(TOCITransaction* ATrans);
	__property bool IsNull = {read=GetIsNull, nodefault};
	__property System::Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
	__property System::Classes::TNotifyEvent OnChanged = {read=FOnChanged, write=FOnChanged};
	
__published:
	__property System::UnicodeString GTRID = {read=GetGTRID, write=SetGTRID};
	__property System::UnicodeString BQUAL = {read=GetBQUAL, write=SetBQUAL};
	__property System::UnicodeString Name = {read=FName, write=SetName};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TOCIXid() { }
	
};


enum DECLSPEC_DENUM TOCITransactionMode : unsigned int { tmDefault, tmReadWrite, tmSerializable, tmReadOnly };

enum DECLSPEC_DENUM TOCICoupleMode : unsigned int { omDefault, omTightly, omLoosely };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCITransaction : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
public:
	__fastcall TOCITransaction(TOCIService* AService);
	__fastcall TOCITransaction(TOCIService* AService, void * AHandle);
	void __fastcall Detach();
	void __fastcall StartLocal(TOCITransactionMode AMode);
	void __fastcall StartGlobal(TOCITransactionMode AMode, unsigned ATimeOut, bool ANew, TOCICoupleMode ACoupleMode);
	void __fastcall Commit();
	void __fastcall RollBack();
	void __fastcall Select();
	void __fastcall Prepare2PC();
	void __fastcall Commit2PC();
	void __fastcall Forget();
	void __fastcall GetXID(Firedac::Phys::Oraclecli::TXID &AValue);
	void __fastcall SetXID(Firedac::Phys::Oraclecli::TXID &AValue);
	__property System::UnicodeString TRANS_NAME = {read=GetStringAttr, write=SetStringAttr, index=29};
public:
	/* TOCIHandle.Destroy */ inline __fastcall virtual ~TOCITransaction() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TOCIVarDataType : unsigned int { otUnknown, otInt32, otUInt32, otInt64, otUInt64, otSingle, otDouble, otNumber, otString, otChar, otNString, otNChar, otRaw, otDateTime, otLong, otNLong, otLongRaw, otROWID, otBoolean, otCursor, otNestedDataSet, otCLOB, otNCLOB, otBLOB, otCFile, otBFile, otTimeStamp, otIntervalYM, otIntervalDS };

typedef System::Set<TOCIVarDataType, TOCIVarDataType::otUnknown, TOCIVarDataType::otIntervalDS> TOCIVarDataTypes;

enum DECLSPEC_DENUM TOCIVarType : unsigned int { odUnknown, odIn, odOut, odInOut, odRet, odDefine };

typedef System::Set<TOCIVarType, TOCIVarType::odUnknown, TOCIVarType::odDefine> TOCIVarTypes;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIStatement : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
	
private:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TPieceLoopData
	{
	public:
		void *FVarHndl;
		TOCIVariable* FVar;
		unsigned FPieceSize;
		short FInd;
		unsigned FIter;
		System::Byte FPiece;
		System::Word FRCode;
		System::Byte FInOut;
		System::Byte *FBuff;
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	
private:
	bool FEof;
	unsigned FLastRowCount;
	unsigned FPieceBuffLen;
	System::Byte *FPieceBuff;
	System::Classes::TList* FPieceOutVars;
	System::Classes::TList* FVars;
	TOCIService* FService;
	TOCITransaction* FTrans;
	bool FRef;
	bool FCanceled;
	System::WideChar FDecimalSep;
	System::LongBool FStrsTrim;
	System::LongBool FStrsEmpty2Null;
	bool FStrsTrim2Len;
	bool FMapWC2NChar;
	System::Word FSTMT_TYPE;
	void __fastcall SetPieceBuffLen(unsigned AValue);
	void __fastcall AllocPieceBuff();
	void __fastcall FreePieceBuff();
	TOCIVariable* __fastcall Hndl2PieceVar(void * varHndl);
	bool __fastcall GetPiecedExchange();
	void __fastcall InitPiecedExchange(/* out */ TPieceLoopData &pld);
	void __fastcall DoPiecedExchange(TPieceLoopData &AData, int ARes);
	void __fastcall DumpColumns(unsigned ARows, bool AEof);
	void __fastcall DumpParameters(int ARows, int AOffset, TOCIVarTypes ATypes);
	TOCIVariable* __fastcall AddVarBase(const System::UnicodeString AName, unsigned APosition, TOCIVarType AVarType, TOCIVarDataType ADataType, unsigned ASize);
	System::UnicodeString __fastcall GetRowId();
	
protected:
	void __fastcall AddPieceVar(TOCIVariable* AVar);
	void __fastcall RemovePieceVar(TOCIVariable* AVar);
	void __fastcall AddVar(TOCIVariable* AVar)/* overload */;
	void __fastcall RemoveVar(TOCIVariable* AVar);
	
public:
	__fastcall TOCIStatement(TOCIEnv* AEnv, TOCIService* AService, TOCITransaction* ATrans, System::TObject* AOwningObj);
	__fastcall TOCIStatement(TOCIEnv* AEnv, TOCIService* AService, TOCITransaction* ATrans, void * AHandle, System::TObject* AOwningObj);
	__fastcall virtual ~TOCIStatement();
	void __fastcall AttachToHandle(void * AHandle);
	void __fastcall Prepare(const System::UnicodeString AStatement);
	void __fastcall Describe();
	void __fastcall Execute(int ARows, int AOffset, bool AExact, bool ACommit);
	void * __fastcall NextResultSet();
	void __fastcall CancelCursor();
	void __fastcall Fetch(unsigned ANRows);
	TOCIVariable* __fastcall AddVar(const System::UnicodeString AName, TOCIVarType AVarType, TOCIVarDataType ADataType, unsigned ASize = (unsigned)(0x0))/* overload */;
	TOCIVariable* __fastcall AddVar(unsigned APosition, TOCIVarType AVarType, TOCIVarDataType ADataType, unsigned ASize = (unsigned)(0x0))/* overload */;
	bool __fastcall FetchImplRowids();
	__property TOCIService* Service = {read=FService};
	__property bool Ref = {read=FRef, write=FRef, nodefault};
	__property bool Eof = {read=FEof, nodefault};
	__property bool Canceled = {read=FCanceled, nodefault};
	__property unsigned LastRowCount = {read=FLastRowCount, nodefault};
	__property bool PiecedExchange = {read=GetPiecedExchange, nodefault};
	__property System::UnicodeString RowId = {read=GetRowId};
	__property unsigned PieceBuffLen = {read=FPieceBuffLen, write=SetPieceBuffLen, nodefault};
	__property System::WideChar DecimalSep = {read=FDecimalSep, write=FDecimalSep, nodefault};
	__property System::LongBool StrsTrim = {read=FStrsTrim, write=FStrsTrim, nodefault};
	__property System::LongBool StrsEmpty2Null = {read=FStrsEmpty2Null, write=FStrsEmpty2Null, nodefault};
	__property bool StrsTrim2Len = {read=FStrsTrim2Len, write=FStrsTrim2Len, nodefault};
	__property bool MapWC2NChar = {read=FMapWC2NChar, write=FMapWC2NChar, nodefault};
	__property void * ENV_ = {read=GetHandleAttr, index=5};
	__property System::Word PARSE_ERROR_OFFSET = {read=GetUB2Attr, index=129, nodefault};
	__property System::Word STMT_TYPE = {read=FSTMT_TYPE, nodefault};
	__property System::Word SQLFNCODE = {read=GetUB2Attr, index=10, nodefault};
	__property unsigned PARAM_COUNT = {read=GetUB4Attr, index=18, nodefault};
	__property System::Byte IS_RETURNING = {read=GetUB1Attr, index=218, nodefault};
	__property unsigned PREFETCH_ROWS = {read=GetUB4Attr, write=SetUB4Attr, index=11, nodefault};
	__property unsigned PREFETCH_MEMORY = {read=GetUB4Attr, write=SetUB4Attr, index=13, nodefault};
	__property unsigned FETCH_ROWID = {read=GetUB4Attr, write=SetUB4Attr, index=448, nodefault};
	__property unsigned ROW_COUNT = {read=GetUB4Attr, index=9, nodefault};
	__property unsigned __int64 UB8_ROW_COUNT = {read=GetUB8Attr, index=457};
	__property void * DML_ROW_COUNT_ARRAY = {read=GetHandleAttr, index=469};
	__property unsigned NUM_DML_ERRORS = {read=GetUB4Attr, index=73, nodefault};
	__property unsigned ROWS_FETCHED = {read=GetUB4Attr, index=197, nodefault};
	__property unsigned IMPLICIT_RESULT_COUNT = {read=GetUB4Attr, index=463, nodefault};
	__property unsigned __int64 CQ_QUERYID = {read=GetUB8Attr, index=304};
	__property void * CHNF_REGHANDLE = {write=SetHandleAttr, index=414};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIVariable : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
	
private:
	#pragma pack(push,1)
	struct DECLSPEC_DRECORD TBindData
	{
	public:
		Firedac::Phys::Oraclecli::TSB2Array *FInd;
		Firedac::Phys::Oraclecli::TUB2Array *FALen;
		Firedac::Phys::Oraclecli::TUB2Array *FRCode;
		System::Byte *FBuffer;
	};
	#pragma pack(pop)
	
	
	typedef TBindData *PBindData;
	
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TLongData
	{
	public:
		unsigned FSize;
		System::Byte *FData;
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	typedef TLongData *PLongData;
	
	
private:
	System::UnicodeString FPlaceHolder;
	unsigned FPosition;
	TBindData *FBindData;
	unsigned FValue_byte_sz;
	unsigned FValue_char_sz;
	System::Word FValue_ty;
	unsigned FMaxArr_len;
	unsigned FCurEle;
	TOCIVarDataType FDataType;
	TOCIVarType FVarType;
	System::LongBool FLongData;
	System::UnicodeString FDumpLabel;
	System::Byte *FLastBindedBuffer;
	bool FBufferInited;
	bool FIsPLSQLTable;
	bool FIsCaseSensitive;
	bool FFlagsUpdated;
	bool FByteSemantic;
	void __fastcall SetArrayLen(const unsigned AValue);
	void __fastcall SetDataSize(const unsigned AValue);
	void __fastcall SetDataType(const TOCIVarDataType AValue);
	void __fastcall SetVarType(const TOCIVarType AValue);
	Firedac::Phys::Oraclecli::pUb1 __fastcall GetBuffer(unsigned AIndex);
	void __fastcall FreeBuffer();
	void __fastcall CheckBufferAccess();
	void __fastcall FreeLong(PLongData ApLong);
	void __fastcall InitLong(PLongData ApLong);
	void __fastcall GetLong(PLongData ApLong, Firedac::Phys::Oraclecli::pUb1 &AData, unsigned &ASize);
	void __fastcall SetLong(PLongData ApLong, Firedac::Phys::Oraclecli::pUb1 AData, unsigned ASize);
	void __fastcall AppendLong(PLongData ApLong, Firedac::Phys::Oraclecli::pUb1 AData, unsigned ASize);
	System::UnicodeString __fastcall GetDumpLabel();
	bool __fastcall UpdateHValueNullInd(unsigned AIndex);
	unsigned __fastcall GetBindDataSize();
	void __fastcall MapBuffer();
	void __fastcall UpdateFlags();
	System::UnicodeString __fastcall GetAsString();
	int __fastcall GetAsInteger();
	TOCIStatement* __fastcall GetStatement();
	unsigned __fastcall GetMaxStrSize();
	
protected:
	__property Firedac::Phys::Oraclecli::pUb1 Buffer[unsigned AIndex] = {read=GetBuffer};
	
public:
	__fastcall TOCIVariable(TOCIStatement* AStmt);
	__fastcall virtual ~TOCIVariable();
	void __fastcall Bind();
	void __fastcall BindTo(TOCIStatement* AStmt);
	void __fastcall BindOff();
	void __fastcall ClearBuffer(int ATimes, int AOffset);
	void __fastcall InitBuffer(int ATimes, int AOffset);
	void __fastcall ResetBuffer(int ATimes, int AOffset);
	bool __fastcall GetRawData(unsigned AIndex, /* out */ Firedac::Phys::Oraclecli::pUb1 &ABuff, /* out */ unsigned &ASize);
	bool __fastcall GetData(unsigned AIndex, Firedac::Phys::Oraclecli::pUb1 &ABuff, /* out */ unsigned &ASize, bool AByRef)/* overload */;
	bool __fastcall GetData(unsigned AIndex, Firedac::Phys::Oraclecli::pUb1 ABuff, /* out */ unsigned &ASize)/* overload */;
	void __fastcall SetData(unsigned AIndex, Firedac::Phys::Oraclecli::pUb1 ABuff, unsigned ASize);
	void __fastcall AppendData(unsigned AIndex, Firedac::Phys::Oraclecli::pUb1 ABuff, unsigned ASize);
	void __fastcall SetIsNull(unsigned AIndex, bool AIsNull);
	System::UnicodeString __fastcall DumpValue(unsigned AIndex);
	__property System::UnicodeString Name = {read=FPlaceHolder, write=FPlaceHolder};
	__property unsigned Position = {read=FPosition, write=FPosition, nodefault};
	__property System::UnicodeString DumpLabel = {read=GetDumpLabel, write=FDumpLabel};
	__property bool IsPLSQLTable = {read=FIsPLSQLTable, write=FIsPLSQLTable, nodefault};
	__property bool IsCaseSensitive = {read=FIsCaseSensitive, write=FIsCaseSensitive, nodefault};
	__property TOCIVarDataType DataType = {read=FDataType, write=SetDataType, nodefault};
	__property unsigned DataSize = {read=FValue_byte_sz, write=SetDataSize, nodefault};
	__property unsigned CharSize = {read=FValue_char_sz, write=FValue_char_sz, nodefault};
	__property TOCIVarType VarType = {read=FVarType, write=SetVarType, nodefault};
	__property unsigned ArrayLen = {read=FMaxArr_len, write=SetArrayLen, nodefault};
	__property unsigned ArrayCount = {read=FCurEle, nodefault};
	__property TOCIStatement* Statement = {read=GetStatement};
	__property unsigned BindDataSize = {read=GetBindDataSize, nodefault};
	__property System::LongBool LongData = {read=FLongData, nodefault};
	__property bool ByteSemantic = {read=FByteSemantic, nodefault};
	__property System::UnicodeString AsString = {read=GetAsString};
	__property int AsInteger = {read=GetAsInteger, nodefault};
	__property unsigned CHAR_COUNT = {read=GetUB4Attr, write=SetUB4Attr, index=15, nodefault};
	__property System::Word CHARSET_ID = {read=GetUB2Attr, write=SetUB2Attr, index=31, nodefault};
	__property System::Byte CHARSET_FORM = {read=GetUB1Attr, write=SetUB1Attr, index=32, nodefault};
	__property System::Word PDPRC = {read=GetUB2Attr, write=SetUB2Attr, index=17, nodefault};
	__property System::Word PDSCL = {read=GetUB2Attr, write=SetUB2Attr, index=16, nodefault};
	__property unsigned ROWS_RETURNED = {read=GetUB4Attr, index=42, nodefault};
	__property int MAXDATA_SIZE = {read=GetSB4Attr, write=SetSB4Attr, index=33, nodefault};
	__property int MAXCHAR_SIZE = {read=GetSB4Attr, write=SetSB4Attr, index=163, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIDescriptor : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
protected:
	HIDESBASE void __fastcall Init(unsigned AType);
	
public:
	__fastcall virtual ~TOCIDescriptor();
	__fastcall virtual TOCIDescriptor(TOCIEnv* AEnv, void * AHandle)/* overload */;
public:
	/* TOCIHandle.Create */ inline __fastcall TOCIDescriptor(TOCIEnv* AEnv) : TOCIHandle(AEnv) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCISelectItem : public TOCIDescriptor
{
	typedef TOCIDescriptor inherited;
	
private:
	TOCIService* FService;
	int FPosition;
	unsigned FDATA_TYPE;
	unsigned FDATA_SIZE;
	unsigned FPRECISION;
	unsigned FSCALE_;
	System::Byte FCHARSET_FORM;
	System::Word FCHAR_SIZE;
	TOCIVarDataType FDataType;
	void __fastcall InitFields();
	TOCIVarDataType __fastcall GetDataType();
	TOCIVarType __fastcall GetVarType();
	bool __fastcall GetIsNull();
	int __fastcall GetDataPrecision();
	int __fastcall GetDataScale();
	System::Byte __fastcall GetBytesPerChar();
	System::Word __fastcall GetCharSize();
	unsigned __fastcall GetDataSize();
	unsigned __fastcall GetColumnSize();
	bool __fastcall GetIsUnicode();
	System::Byte __fastcall GetCHARSET_FORM();
	unsigned __fastcall GetDATA_SIZE();
	unsigned __fastcall GetDATA_TYPE();
	unsigned __fastcall GetPRECISION();
	unsigned __fastcall GetSCALE();
	System::Word __fastcall GetCHAR_SIZE();
	unsigned __int64 __fastcall GetColProperties();
	
public:
	__fastcall TOCISelectItem(TOCIHandle* AOwner, TOCIService* AService)/* overload */;
	__fastcall TOCISelectItem(TOCIHandle* AOwner, TOCIService* AService, int APosition)/* overload */;
	void __fastcall Bind();
	__property int Position = {read=FPosition, write=FPosition, nodefault};
	__property TOCIVarDataType DataType = {read=GetDataType, nodefault};
	__property unsigned DataSize = {read=GetDataSize, nodefault};
	__property System::Word CharSize = {read=GetCharSize, nodefault};
	__property unsigned ColumnSize = {read=GetColumnSize, nodefault};
	__property int DataPrecision = {read=GetDataPrecision, nodefault};
	__property int DataScale = {read=GetDataScale, nodefault};
	__property TOCIVarType VarType = {read=GetVarType, nodefault};
	__property bool IsNull = {read=GetIsNull, nodefault};
	__property System::Byte BytesPerChar = {read=GetBytesPerChar, nodefault};
	__property bool IsUnicode = {read=GetIsUnicode, nodefault};
	__property unsigned __int64 ColProperties = {read=GetColProperties};
	__property unsigned DATA_SIZE = {read=GetDATA_SIZE, nodefault};
	__property unsigned DATA_TYPE = {read=GetDATA_TYPE, nodefault};
	__property unsigned DISP_SIZE = {read=GetUB4Attr, index=3, nodefault};
	__property System::UnicodeString NAME = {read=GetStringAttr, index=4};
	__property unsigned PRECISION = {read=GetPRECISION, nodefault};
	__property unsigned SCALE = {read=GetSCALE, nodefault};
	__property unsigned IS_NULL = {read=GetUB4Attr, index=7, nodefault};
	__property System::UnicodeString TYPE_NAME = {read=GetStringAttr, index=8};
	__property System::UnicodeString SUB_NAME = {read=GetStringAttr, index=10};
	__property System::UnicodeString SCHEMA_NAME = {read=GetStringAttr, index=9};
	__property unsigned IOMODE = {read=GetUB4Attr, index=213, nodefault};
	__property System::Word CHARSET_ID = {read=GetUB2Attr, index=31, nodefault};
	__property System::Byte CHARSET_FORM = {read=GetCHARSET_FORM, nodefault};
	__property System::Word CHAR_SIZE = {read=GetCHAR_SIZE, nodefault};
	__property unsigned CHAR_USED = {read=GetUB4Attr, index=285, nodefault};
	__property unsigned __int64 COL_PROPERTIES = {read=GetUB8Attr, index=104};
public:
	/* TOCIDescriptor.Destroy */ inline __fastcall virtual ~TOCISelectItem() { }
	/* TOCIDescriptor.CreateUsingHandle */ inline __fastcall virtual TOCISelectItem(TOCIEnv* AEnv, void * AHandle)/* overload */ : TOCIDescriptor(AEnv, AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCILobLocator : public TOCIDescriptor
{
	typedef TOCIDescriptor inherited;
	
private:
	bool FNational;
	System::Byte FCharsetForm;
	bool FOpened;
	int __fastcall GetLength();
	System::LongBool __fastcall GetIsOpen();
	System::LongBool __fastcall GetIsInit();
	void __fastcall CheckCharsetForm();
	
public:
	__fastcall TOCILobLocator(TOCIService* AService, unsigned AType);
	__fastcall virtual TOCILobLocator(TOCIService* AService, void * AHandle)/* overload */;
	__fastcall virtual ~TOCILobLocator();
	void __fastcall Assign(TOCILobLocator* AFrom);
	void __fastcall Close();
	void __fastcall Open(bool AReadOnly);
	unsigned __fastcall Read(Firedac::Phys::Oraclecli::pUb1 ABuff, unsigned amount, unsigned offset);
	__property int Length = {read=GetLength, nodefault};
	__property System::LongBool IsOpen = {read=GetIsOpen, nodefault};
	__property System::LongBool IsInit = {read=GetIsInit, nodefault};
	__property bool National = {read=FNational, write=FNational, nodefault};
public:
	/* TOCIDescriptor.CreateUsingHandle */ inline __fastcall virtual TOCILobLocator(TOCIEnv* AEnv, void * AHandle)/* overload */ : TOCIDescriptor(AEnv, AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIIntLocator : public TOCILobLocator
{
	typedef TOCILobLocator inherited;
	
private:
	bool FBuffering;
	void __fastcall SetBuffering(const bool Value);
	System::LongBool __fastcall GetIsTemporary();
	
public:
	__fastcall virtual TOCIIntLocator(TOCIService* AService, void * AHandle)/* overload */;
	void __fastcall Append(TOCIIntLocator* AFrom);
	void __fastcall Copy(TOCIIntLocator* AFrom, unsigned amount, unsigned dst_offset, unsigned src_offset);
	void __fastcall Erase(unsigned &amount, unsigned offset);
	void __fastcall FlushBuffer();
	void __fastcall Trim(unsigned ANewLen);
	unsigned __fastcall Write(Firedac::Phys::Oraclecli::pUb1 ABuff, unsigned amount, unsigned offset);
	void __fastcall LoadFromFile(TOCIExtLocator* AFrom, unsigned amount, unsigned dst_offset, unsigned src_offset);
	__property System::LongBool IsTemporary = {read=GetIsTemporary, nodefault};
	__property bool Buffering = {read=FBuffering, write=SetBuffering, nodefault};
public:
	/* TOCILobLocator.Create */ inline __fastcall TOCIIntLocator(TOCIService* AService, unsigned AType) : TOCILobLocator(AService, AType) { }
	/* TOCILobLocator.Destroy */ inline __fastcall virtual ~TOCIIntLocator() { }
	
public:
	/* TOCIDescriptor.CreateUsingHandle */ inline __fastcall virtual TOCIIntLocator(TOCIEnv* AEnv, void * AHandle)/* overload */ : TOCILobLocator(AEnv, AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCITempLocator : public TOCIIntLocator
{
	typedef TOCIIntLocator inherited;
	
public:
	__fastcall TOCITempLocator(TOCIService* AService, System::Byte ALobType, bool ACache);
	__fastcall virtual ~TOCITempLocator();
public:
	/* TOCIIntLocator.CreateUsingHandle */ inline __fastcall virtual TOCITempLocator(TOCIService* AService, void * AHandle)/* overload */ : TOCIIntLocator(AService, AHandle) { }
	
public:
	/* TOCILobLocator.Create */ inline __fastcall TOCITempLocator(TOCIService* AService, unsigned AType) : TOCIIntLocator(AService, AType) { }
	
public:
	/* TOCIDescriptor.CreateUsingHandle */ inline __fastcall virtual TOCITempLocator(TOCIEnv* AEnv, void * AHandle)/* overload */ : TOCIIntLocator(AEnv, AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIExtLocator : public TOCILobLocator
{
	typedef TOCILobLocator inherited;
	
private:
	System::LongBool __fastcall GetFileExists();
	System::UnicodeString __fastcall GetDirectory();
	System::UnicodeString __fastcall GetFileName();
	void __fastcall SetDirectory(const System::UnicodeString Value);
	void __fastcall SetFileName(const System::UnicodeString Value);
	void __fastcall GetFileDir(System::UnicodeString &ADir, System::UnicodeString &AFileName);
	void __fastcall SetFileDir(const System::UnicodeString ADir, const System::UnicodeString AFileName);
	
public:
	__fastcall virtual TOCIExtLocator(TOCIService* AService, void * AHandle)/* overload */;
	__property System::LongBool FileExists = {read=GetFileExists, nodefault};
	__property System::UnicodeString FileName = {read=GetFileName, write=SetFileName};
	__property System::UnicodeString Directory = {read=GetDirectory, write=SetDirectory};
public:
	/* TOCILobLocator.Create */ inline __fastcall TOCIExtLocator(TOCIService* AService, unsigned AType) : TOCILobLocator(AService, AType) { }
	/* TOCILobLocator.Destroy */ inline __fastcall virtual ~TOCIExtLocator() { }
	
public:
	/* TOCIDescriptor.CreateUsingHandle */ inline __fastcall virtual TOCIExtLocator(TOCIEnv* AEnv, void * AHandle)/* overload */ : TOCILobLocator(AEnv, AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCILobLocatorStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	TOCILobLocator* FLocator;
	unsigned FOffset;
	System::TObject* FOwningObj;
	unsigned __fastcall Bytes2Chars(unsigned ABytes);
	unsigned __fastcall Chars2Bytes(unsigned AChars);
	
protected:
	virtual __int64 __fastcall GetSize();
	virtual void __fastcall SetSize(const __int64 NewSize)/* overload */;
	
public:
	__fastcall TOCILobLocatorStream(TOCILobLocator* ALocator, System::TObject* AOwningObj);
	__fastcall virtual ~TOCILobLocatorStream();
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	__property TOCILobLocator* Locator = {read=FLocator};
	__property System::TObject* OwningObj = {read=FOwningObj};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  SetSize _DEPRECATED_ATTRIBUTE0 (int NewSize){ System::Classes::TStream::SetSize(NewSize); }
	
public:
#ifndef _WIN64
	inline int __fastcall  Read(System::DynamicArray<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::DynamicArray<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* _WIN64 */
	inline int __fastcall  Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* _WIN64 */
	inline int __fastcall  Seek(int Offset, System::Word Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIDescribe : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
private:
	TOCIHandle* FCurr;
	System::Classes::TList* FStack;
	void * __fastcall GetPtr(int AIndex);
	System::Int8 __fastcall GetSB1(int AIndex);
	System::UnicodeString __fastcall GetText(int AIndex);
	System::Byte __fastcall GetUB1(int AIndex);
	System::Word __fastcall GetUB2(int AIndex);
	unsigned __fastcall GetUB4(int AIndex);
	TOCISelectItem* __fastcall GetSelectItem(int AIndex);
	bool __fastcall GetIsListOpened();
	
public:
	__fastcall TOCIDescribe(TOCIService* ASvc);
	__fastcall virtual ~TOCIDescribe();
	void __fastcall DescribeName(const System::UnicodeString AName);
	unsigned __fastcall OpenList(int AAtrType);
	void __fastcall CloseList();
	void __fastcall GoToItem(int AIndex);
	__property System::Int8 SB1[int AIndex] = {read=GetSB1};
	__property System::Byte UB1[int AIndex] = {read=GetUB1};
	__property System::Word UB2[int AIndex] = {read=GetUB2};
	__property unsigned UB4[int AIndex] = {read=GetUB4};
	__property System::UnicodeString TEXT[int AIndex] = {read=GetText};
	__property void * PTR[int AIndex] = {read=GetPtr};
	__property TOCISelectItem* SelectItem[int AIndex] = {read=GetSelectItem};
	__property bool IsListOpened = {read=GetIsListOpened, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIDirectPath : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
private:
	TOCIDirectPathColumnParam* __fastcall GetColumns(int AIndex);
	
public:
	__fastcall TOCIDirectPath(TOCIService* ASvc);
	void __fastcall AbortJob();
	void __fastcall Finish();
	void __fastcall Prepare();
	void __fastcall LoadStream(TOCIDirectPathStream* AStream);
	__property unsigned BUF_SIZE = {read=GetUB4Attr, write=SetUB4Attr, index=77, nodefault};
	__property System::Word CHARSET_ID = {read=GetUB2Attr, write=SetUB2Attr, index=31, nodefault};
	__property System::UnicodeString DATEFORMAT = {read=GetStringAttr, write=SetStringAttr, index=75};
	__property System::Byte DIRPATH_MODE = {read=GetUB1Attr, write=SetUB1Attr, index=78, nodefault};
	__property System::Byte DIRPATH_NOLOG = {read=GetUB1Attr, write=SetUB1Attr, index=79, nodefault};
	__property System::Byte DIRPATH_PARALLEL = {read=GetUB1Attr, write=SetUB1Attr, index=80, nodefault};
	__property System::Word NUM_COLS = {read=GetUB2Attr, write=SetUB2Attr, index=102, nodefault};
	__property void * LIST_COLUMNS = {read=GetHandleAttr, index=103};
	__property System::UnicodeString SCHEMA_NAME = {read=GetStringAttr, write=SetStringAttr, index=9};
	__property System::UnicodeString NAME = {read=GetStringAttr, write=SetStringAttr, index=4};
	__property System::UnicodeString SUB_NAME = {read=GetStringAttr, write=SetStringAttr, index=10};
	__property TOCIDirectPathColumnParam* Columns[int AIndex] = {read=GetColumns};
public:
	/* TOCIHandle.Destroy */ inline __fastcall virtual ~TOCIDirectPath() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TOCIDirecPathDataType : unsigned int { dpUnknown, dpString, dpDateTime, dpInteger, dpUInteger, dpFloat, dpRaw };

typedef System::Set<TOCIDirecPathDataType, TOCIDirecPathDataType::dpUnknown, TOCIDirecPathDataType::dpRaw> TOCIDirecPathDataTypes;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIDirectPathColArray : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
public:
	__fastcall TOCIDirectPathColArray(TOCIDirectPath* ADP);
	void __fastcall EntryGet(unsigned ARowNum, System::Word AColIndex, Firedac::Phys::Oraclecli::pUb1 &AData, unsigned &ALen, System::Byte &AFlag);
	void __fastcall EntrySet(unsigned ARowNum, System::Word AColIndex, Firedac::Phys::Oraclecli::pUb1 AData, unsigned ALen, System::Byte AFlag);
	void __fastcall RowGet(unsigned ARowNum, Firedac::Phys::Oraclecli::ppUb1 &ADataArr, Firedac::Phys::Oraclecli::pUb4 &ALenArr, Firedac::Phys::Oraclecli::pUb1 &AFlagArr);
	void __fastcall Reset();
	int __fastcall ToStream(TOCIDirectPathStream* AStream, unsigned ARowCount, unsigned ARowIndex);
	__property System::Word NUM_COLS = {read=GetUB2Attr, write=SetUB2Attr, index=102, nodefault};
	__property System::Word NUM_ROWS = {read=GetUB2Attr, write=SetUB2Attr, index=81, nodefault};
	__property System::Word COL_COUNT = {read=GetUB2Attr, write=SetUB2Attr, index=82, nodefault};
	__property System::Word ROW_COUNT = {read=GetUB2Attr, write=SetUB2Attr, index=9, nodefault};
public:
	/* TOCIHandle.Destroy */ inline __fastcall virtual ~TOCIDirectPathColArray() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIDirectPathStream : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
public:
	__fastcall TOCIDirectPathStream(TOCIDirectPath* ADP);
	void __fastcall Reset();
	__property void * BUF_ADDR = {read=GetHandleAttr, write=SetHandleAttr, index=76};
	__property unsigned BUF_SIZE = {read=GetUB4Attr, write=SetUB4Attr, index=77, nodefault};
	__property unsigned ROW_COUNT = {read=GetUB4Attr, write=SetUB4Attr, index=9, nodefault};
	__property unsigned STREAM_OFFSET = {read=GetUB4Attr, write=SetUB4Attr, index=83, nodefault};
public:
	/* TOCIHandle.Destroy */ inline __fastcall virtual ~TOCIDirectPathStream() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIDirectPathColumnParam : public TOCIDescriptor
{
	typedef TOCIDescriptor inherited;
	
private:
	TOCIDirecPathDataType __fastcall GetDataType();
	void __fastcall SetDataType(TOCIDirecPathDataType AValue);
	
public:
	__fastcall TOCIDirectPathColumnParam(TOCIDirectPath* ADP);
	__property System::Word CHARSET_ID = {read=GetUB2Attr, write=SetUB2Attr, index=31, nodefault};
	__property unsigned DATA_SIZE = {read=GetUB4Attr, write=SetUB4Attr, index=1, nodefault};
	__property System::Word DATA_TYPE = {read=GetUB2Attr, write=SetUB2Attr, index=2, nodefault};
	__property System::UnicodeString DATEFORMAT = {read=GetStringAttr, write=SetStringAttr, index=75};
	__property System::UnicodeString NAME = {read=GetStringAttr, write=SetStringAttr, index=4};
	__property System::Byte PRECISION = {read=GetUB1Attr, write=SetUB1Attr, index=5, nodefault};
	__property System::Int8 SCALE = {read=GetSB1Attr, write=SetSB1Attr, index=6, nodefault};
	__property TOCIDirecPathDataType DataType = {read=GetDataType, write=SetDataType, nodefault};
public:
	/* TOCIDescriptor.Destroy */ inline __fastcall virtual ~TOCIDirectPathColumnParam() { }
	/* TOCIDescriptor.CreateUsingHandle */ inline __fastcall virtual TOCIDirectPathColumnParam(TOCIEnv* AEnv, void * AHandle)/* overload */ : TOCIDescriptor(AEnv, AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TOCIOnDefineParam)(const System::UnicodeString ANm, const System::UnicodeString ATpNm, TOCIVarType AVt, TOCIVarDataType FDt, int ASz, int APrec, int ASCale, bool AIsTable, bool AIsResult);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIPLSQLDescriber : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TOCIService* FSrvc;
	System::TObject* FOwningObj;
	System::UnicodeString FOPackageName;
	System::UnicodeString FOProcedureName;
	int FOverload;
	System::UnicodeString FBoolTrue;
	System::UnicodeString FBoolFalse;
	TOCIVarDataType FBoolType;
	int FBoolSize;
	bool FBindByName;
	TOCIDescribe* FDescr;
	System::UnicodeString FSPName;
	System::Byte FObjType;
	unsigned FNumProcs;
	unsigned FProcIndex;
	bool FForProc;
	
public:
	__fastcall TOCIPLSQLDescriber(TOCIService* ASrvc, const System::UnicodeString AOPackageName, const System::UnicodeString AOProcedureName, int AOverload, System::TObject* AOwningObj);
	__fastcall TOCIPLSQLDescriber(TOCIService* ASrvc, const System::UnicodeString AOPackageName, System::TObject* AOwningObj);
	__fastcall virtual ~TOCIPLSQLDescriber();
	void __fastcall Describe();
	bool __fastcall LocateProc(bool AExactOverload);
	void __fastcall First(System::UnicodeString &AProcName, int &AOverload);
	void __fastcall Next(System::UnicodeString &AProcName, int &AOverload);
	bool __fastcall Eol();
	System::UnicodeString __fastcall BuildSQL(TOCIOnDefineParam AOnDefPar);
	void __fastcall CleanUp();
	__property TOCIDescribe* Descr = {read=FDescr};
	__property System::Byte ObjType = {read=FObjType, nodefault};
	__property System::TObject* OwningObj = {read=FOwningObj};
	__property System::UnicodeString BoolFalse = {read=FBoolFalse, write=FBoolFalse};
	__property System::UnicodeString BoolTrue = {read=FBoolTrue, write=FBoolTrue};
	__property TOCIVarDataType BoolType = {read=FBoolType, write=FBoolType, nodefault};
	__property int BoolSize = {read=FBoolSize, write=FBoolSize, nodefault};
	__property bool BindByName = {read=FBindByName, write=FBindByName, nodefault};
public:
	/* TObject.Create */ inline __fastcall TOCIPLSQLDescriber() : System::TObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIOpaqueValue : public TOCIDescriptor
{
	typedef TOCIDescriptor inherited;
	
private:
	void __fastcall CheckSupported();
	
protected:
	bool FIsNull;
	bool FParsed;
	virtual void __fastcall InternalAssign(TOCIOpaqueValue* ASource) = 0 ;
	virtual void __fastcall InternalErase() = 0 ;
	virtual void __fastcall InternalParse() = 0 ;
	virtual System::UnicodeString __fastcall GetAsString() = 0 ;
	virtual void __fastcall SetAsString(const System::UnicodeString AValue) = 0 ;
	__classmethod virtual unsigned __int64 __fastcall GetMinClientVersion();
	
public:
	__fastcall TOCIOpaqueValue(TOCIEnv* AEnv, unsigned AType);
	__fastcall virtual TOCIOpaqueValue(TOCIEnv* AEnv, void * AHandle)/* overload */;
	void __fastcall Assign(TOCIOpaqueValue* ASource);
	void __fastcall Clear();
	void __fastcall Parse();
	__property bool IsNull = {read=FIsNull, nodefault};
	__property System::UnicodeString AsString = {read=GetAsString, write=SetAsString};
public:
	/* TOCIDescriptor.Destroy */ inline __fastcall virtual ~TOCIOpaqueValue() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCITimestamp : public TOCIOpaqueValue
{
	typedef TOCIOpaqueValue inherited;
	
private:
	short FYear;
	System::Byte FMonth;
	System::Byte FDay;
	System::Byte FHour;
	System::Byte FMinute;
	System::Byte FSecond;
	unsigned FNanoSeconds;
	System::Int8 FTZHour;
	System::Int8 FTZMinute;
	System::TDateTime __fastcall GetAsDateTime();
	void __fastcall SetAsDateTime(const System::TDateTime AValue);
	Data::Sqltimst::TSQLTimeStamp __fastcall GetAsSQLTimeStampFun();
	
protected:
	virtual void __fastcall InternalAssign(TOCIOpaqueValue* ASource);
	virtual void __fastcall InternalErase();
	virtual void __fastcall InternalParse();
	virtual System::UnicodeString __fastcall GetAsString();
	virtual void __fastcall SetAsString(const System::UnicodeString AValue);
	__classmethod virtual unsigned __int64 __fastcall GetMinClientVersion();
	
public:
	void __fastcall SetValues(short AYear, System::Byte AMonth, System::Byte ADay, System::Byte AHour, System::Byte AMinute, System::Byte ASecond, unsigned ANanoSeconds, short ATZHour = (short)(0x0), short ATZMinute = (short)(0x0));
	void __fastcall SetAsSQLTimeStamp(const Data::Sqltimst::TSQLTimeStamp &AValue);
	void __fastcall GetAsSQLTimeStamp(/* out */ Data::Sqltimst::TSQLTimeStamp &AValue);
	__property System::TDateTime AsDateTime = {read=GetAsDateTime, write=SetAsDateTime};
	__property Data::Sqltimst::TSQLTimeStamp AsSQLTimeStamp = {read=GetAsSQLTimeStampFun, write=SetAsSQLTimeStamp};
	__property short Year = {read=FYear, nodefault};
	__property System::Byte Month = {read=FMonth, nodefault};
	__property System::Byte Day = {read=FDay, nodefault};
	__property System::Byte Hour = {read=FHour, nodefault};
	__property System::Byte Minute = {read=FMinute, nodefault};
	__property System::Byte Second = {read=FSecond, nodefault};
	__property unsigned NanoSeconds = {read=FNanoSeconds, nodefault};
	__property System::Int8 TZHour = {read=FTZHour, nodefault};
	__property System::Int8 TZMinute = {read=FTZMinute, nodefault};
public:
	/* TOCIOpaqueValue.Create */ inline __fastcall TOCITimestamp(TOCIEnv* AEnv, unsigned AType) : TOCIOpaqueValue(AEnv, AType) { }
	/* TOCIOpaqueValue.CreateUsingHandle */ inline __fastcall virtual TOCITimestamp(TOCIEnv* AEnv, void * AHandle)/* overload */ : TOCIOpaqueValue(AEnv, AHandle) { }
	
public:
	/* TOCIDescriptor.Destroy */ inline __fastcall virtual ~TOCITimestamp() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TOCITimeIntervalKind : unsigned int { ikUnknown, ikYear2Month, ikDay2Second };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCITimeInterval : public TOCIOpaqueValue
{
	typedef TOCIOpaqueValue inherited;
	
private:
	int FYears;
	int FMonths;
	int FDays;
	int FHours;
	int FMinutes;
	int FSeconds;
	int FNanoSeconds;
	TOCITimeIntervalKind FKind;
	Firedac::Stan::Sqltimeint::TFDSQLTimeInterval __fastcall GetAsSQLTimeIntervalFun();
	
protected:
	virtual void __fastcall InternalAssign(TOCIOpaqueValue* ASource);
	virtual void __fastcall InternalErase();
	virtual void __fastcall InternalParse();
	virtual System::UnicodeString __fastcall GetAsString();
	virtual void __fastcall SetAsString(const System::UnicodeString AValue);
	__classmethod virtual unsigned __int64 __fastcall GetMinClientVersion();
	
public:
	__fastcall TOCITimeInterval(TOCIEnv* AEnv, unsigned AType);
	__fastcall TOCITimeInterval(TOCIEnv* AEnv, void * AHandle, TOCIVarDataType ADataType)/* overload */;
	void __fastcall SetYear2Month(int AYears, int AMonths);
	void __fastcall SetDay2Second(int ADays, int AHours, int AMinutes, int ASeconds, int ANanoSeconds);
	void __fastcall SetAsSQLTimeInterval(const Firedac::Stan::Sqltimeint::TFDSQLTimeInterval &AValue);
	void __fastcall GetAsSQLTimeInterval(/* out */ Firedac::Stan::Sqltimeint::TFDSQLTimeInterval &AValue);
	__property Firedac::Stan::Sqltimeint::TFDSQLTimeInterval AsSQLTimeInterval = {read=GetAsSQLTimeIntervalFun, write=SetAsSQLTimeInterval};
	__property int Years = {read=FYears, nodefault};
	__property int Months = {read=FMonths, nodefault};
	__property int Days = {read=FDays, nodefault};
	__property int Hours = {read=FHours, nodefault};
	__property int Minutes = {read=FMinutes, nodefault};
	__property int Seconds = {read=FSeconds, nodefault};
	__property int NanoSeconds = {read=FNanoSeconds, nodefault};
	__property TOCITimeIntervalKind Kind = {read=FKind, nodefault};
public:
	/* TOCIOpaqueValue.CreateUsingHandle */ inline __fastcall virtual TOCITimeInterval(TOCIEnv* AEnv, void * AHandle)/* overload */ : TOCIOpaqueValue(AEnv, AHandle) { }
	
public:
	/* TOCIDescriptor.Destroy */ inline __fastcall virtual ~TOCITimeInterval() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCICollection : public TOCIDescriptor
{
	typedef TOCIDescriptor inherited;
	
private:
	int __fastcall GetCount();
	
public:
	void __fastcall Assign(TOCICollection* AColl);
	bool __fastcall GetData(int AIndex, void * &AData);
	void __fastcall SetData(int AIndex, void * AData);
	void __fastcall Trim(int ANumber);
	__property int Count = {read=GetCount, nodefault};
public:
	/* TOCIDescriptor.Destroy */ inline __fastcall virtual ~TOCICollection() { }
	/* TOCIDescriptor.CreateUsingHandle */ inline __fastcall virtual TOCICollection(TOCIEnv* AEnv, void * AHandle)/* overload */ : TOCIDescriptor(AEnv, AHandle) { }
	
public:
	/* TOCIHandle.Create */ inline __fastcall TOCICollection(TOCIEnv* AEnv) : TOCIDescriptor(AEnv) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TOCIDescCollection__1 : public TOCICollection
{
	typedef TOCICollection inherited;
	
public:
	T operator[](int AIndex) { return this->Items[AIndex]; }
	
private:
	T FDesc;
	T __fastcall GetItems(int AIndex);
	
public:
	__fastcall virtual ~TOCIDescCollection__1();
	__property T Items[int AIndex] = {read=GetItems/*, default*/};
public:
	/* TOCIDescriptor.CreateUsingHandle */ inline __fastcall virtual TOCIDescCollection__1(TOCIEnv* AEnv, void * AHandle)/* overload */ : TOCICollection(AEnv, AHandle) { }
	
public:
	/* TOCIHandle.Create */ inline __fastcall TOCIDescCollection__1(TOCIEnv* AEnv) : TOCICollection(AEnv) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TOCIStartupFlag : unsigned int { sfRestrict, sfForce };

typedef System::Set<TOCIStartupFlag, TOCIStartupFlag::sfRestrict, TOCIStartupFlag::sfForce> TOCIStartupFlags;

enum DECLSPEC_DENUM TOCIShutdownMode : unsigned int { smTransactional, smTransactionalLocal, smImmediate, smAbort, smFinal };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIAdmin : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
public:
	__fastcall TOCIAdmin(TOCIService* AService);
	void __fastcall Startup(TOCIStartupFlags AFlags = TOCIStartupFlags() );
	void __fastcall Shutdown(TOCIShutdownMode AMode = (TOCIShutdownMode)(0x0));
	__property System::UnicodeString PFILE = {read=GetStringAttr, write=SetStringAttr, index=389};
public:
	/* TOCIHandle.Destroy */ inline __fastcall virtual ~TOCIAdmin() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCISubscription : public TOCIHandle
{
	typedef TOCIHandle inherited;
	
	
private:
	enum DECLSPEC_DENUM TState : unsigned int { ssInactive, ssActive, ssDisabled };
	
	
private:
	TState FState;
	static void __cdecl SubEventCallback(void * ctx, void * subscrhp, void * payload, unsigned paylen, void * desc, unsigned mode);
	
protected:
	virtual void __fastcall DoSubEvent(void * payload, unsigned paylen, void * desc, unsigned mode);
	
public:
	__fastcall TOCISubscription(TOCIService* AService);
	void __fastcall Register();
	void __fastcall Unregister();
	void __fastcall Enable();
	void __fastcall Disable();
	void __fastcall Post();
	__property unsigned NAMESPACE = {read=GetUB4Attr, write=SetUB4Attr, index=98, nodefault};
	__property void * _CALLBACK = {read=GetHandleAttr, write=SetHandleAttr, index=95};
	__property void * CTX = {read=GetHandleAttr, write=SetHandleAttr, index=96};
	__property unsigned QOSFLAGS = {read=GetUB4Attr, write=SetUB4Attr, index=225, nodefault};
	__property unsigned TIMEOUT = {read=GetUB4Attr, write=SetUB4Attr, index=227, nodefault};
	__property unsigned RECPTPROTO = {read=GetUB4Attr, write=SetUB4Attr, index=149, nodefault};
	__property System::UnicodeString RECPT = {read=GetStringAttr, write=SetStringAttr, index=148};
	__property unsigned RECPTPRES = {read=GetUB4Attr, write=SetUB4Attr, index=195, nodefault};
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> PAYLOAD = {read=GetBytesAttr, write=SetBytesAttr, index=97};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> PAYLOAD = {read=GetBytesAttr, write=SetBytesAttr, index=97};
#endif /* _WIN64 */
	__property System::UnicodeString IPADDR = {read=GetStringAttr, write=SetStringAttr, index=452};
	__property unsigned PORTNO = {read=GetUB4Attr, write=SetUB4Attr, index=390, nodefault};
public:
	/* TOCIHandle.Destroy */ inline __fastcall virtual ~TOCISubscription() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIChangeRowDesc : public TOCIDescriptor
{
	typedef TOCIDescriptor inherited;
	
public:
	__fastcall virtual TOCIChangeRowDesc(TOCIEnv* AEnv, void * AHandle)/* overload */;
	__property System::UnicodeString ROWID = {read=GetStringAttr, index=412};
	__property unsigned OPFLAGS = {read=GetUB4Attr, index=413, nodefault};
public:
	/* TOCIDescriptor.Destroy */ inline __fastcall virtual ~TOCIChangeRowDesc() { }
	
public:
	/* TOCIHandle.Create */ inline __fastcall TOCIChangeRowDesc(TOCIEnv* AEnv) : TOCIDescriptor(AEnv) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIChangeTableDesc : public TOCIDescriptor
{
	typedef TOCIDescriptor inherited;
	
	
public:
	typedef TOCIDescCollection__1<TOCIChangeRowDesc*>* TRows;
	
	
private:
	TOCICollection* FRows;
	TOCIDescCollection__1<TOCIChangeRowDesc*>* __fastcall GetRows();
	
public:
	__fastcall virtual TOCIChangeTableDesc(TOCIEnv* AEnv, void * AHandle)/* overload */;
	__fastcall virtual ~TOCIChangeTableDesc();
	__property System::UnicodeString NAME = {read=GetStringAttr, index=409};
	__property unsigned OPFLAGS = {read=GetUB4Attr, index=410, nodefault};
	__property void * ROW_CHANGES = {read=GetHandleAttr, index=411};
	__property TOCIDescCollection__1<TOCIChangeRowDesc*>* Rows = {read=GetRows};
public:
	/* TOCIHandle.Create */ inline __fastcall TOCIChangeTableDesc(TOCIEnv* AEnv) : TOCIDescriptor(AEnv) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIChangeQueryDesc : public TOCIDescriptor
{
	typedef TOCIDescriptor inherited;
	
	
public:
	typedef TOCIDescCollection__1<TOCIChangeTableDesc*>* TTables;
	
	
private:
	TOCIDescCollection__1<TOCIChangeTableDesc*>* FTables;
	TOCIDescCollection__1<TOCIChangeTableDesc*>* __fastcall GetTables();
	
public:
	__fastcall virtual TOCIChangeQueryDesc(TOCIEnv* AEnv, void * AHandle)/* overload */;
	__fastcall virtual ~TOCIChangeQueryDesc();
	__property unsigned OPERATION = {read=GetUB4Attr, index=422, nodefault};
	__property unsigned __int64 QUERYID = {read=GetUB8Attr, index=424};
	__property void * TABLE_CHANGES = {read=GetHandleAttr, index=423};
	__property TOCIDescCollection__1<TOCIChangeTableDesc*>* Tables = {read=GetTables};
public:
	/* TOCIHandle.Create */ inline __fastcall TOCIChangeQueryDesc(TOCIEnv* AEnv) : TOCIDescriptor(AEnv) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOCIChangeDesc : public TOCIDescriptor
{
	typedef TOCIDescriptor inherited;
	
	
public:
	typedef TOCIDescCollection__1<TOCIChangeQueryDesc*>* TQueries;
	
	
private:
	TOCIDescCollection__1<TOCIChangeTableDesc*>* FTables;
	TOCIDescCollection__1<TOCIChangeQueryDesc*>* FQueries;
	TOCIDescCollection__1<TOCIChangeTableDesc*>* __fastcall GetTables();
	TOCIDescCollection__1<TOCIChangeQueryDesc*>* __fastcall GetQueries();
	
public:
	__fastcall virtual TOCIChangeDesc(TOCIEnv* AEnv, void * AHandle)/* overload */;
	__fastcall virtual ~TOCIChangeDesc();
	__property System::UnicodeString DBNAME = {read=GetStringAttr, index=405};
	__property unsigned __int64 XID = {read=GetUB8Attr, index=407};
	__property unsigned NFYTYPE = {read=GetUB4Attr, index=406, nodefault};
	__property void * TABLE_CHANGES = {read=GetHandleAttr, index=408};
	__property void * QUERIES_ = {read=GetHandleAttr, index=425};
	__property TOCIDescCollection__1<TOCIChangeTableDesc*>* Tables = {read=GetTables};
	__property TOCIDescCollection__1<TOCIChangeQueryDesc*>* Queries = {read=GetQueries};
public:
	/* TOCIHandle.Create */ inline __fastcall TOCIChangeDesc(TOCIEnv* AEnv) : TOCIDescriptor(AEnv) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TOCIQueryChangeEvent)(TOCIQueryNotification* ASender, TOCIChangeDesc* AChange);

class PASCALIMPLEMENTATION TOCIQueryNotification : public TOCISubscription
{
	typedef TOCISubscription inherited;
	
private:
	TOCIChangeDesc* FChange;
	TOCICollection* FTables;
	TOCIQueryChangeEvent FOnChange;
	TOCICollection* __fastcall GetTables();
	
protected:
	virtual void __fastcall DoSubEvent(void * payload, unsigned paylen, void * desc, unsigned mode);
	virtual void __fastcall DoChangeEvent(TOCIChangeDesc* AChange);
	
public:
	__fastcall TOCIQueryNotification(TOCIService* AService);
	__fastcall virtual ~TOCIQueryNotification();
	__property unsigned CQ_QOSFLAGS = {read=GetUB4Attr, write=SetUB4Attr, index=229, nodefault};
	__property unsigned ROWIDS = {read=GetUB4Attr, write=SetUB4Attr, index=402, nodefault};
	__property unsigned OPERATIONS = {read=GetUB4Attr, write=SetUB4Attr, index=403, nodefault};
	__property unsigned CHANGELAG = {read=GetUB4Attr, write=SetUB4Attr, index=404, nodefault};
	__property void * TABLENAMES = {read=GetHandleAttr, index=401};
	__property TOCICollection* Tables = {read=GetTables};
	__property TOCIQueryChangeEvent OnChange = {read=FOnChange, write=FOnChange};
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 C_NumStrLen = System::Int8(0x2a);
static const System::Int8 C_RowIdLen = System::Int8(0x17);
extern DELPHI_PACKAGE System::UnicodeString C_Oracle_Home;
extern DELPHI_PACKAGE System::UnicodeString C_NLS_LANG;
extern DELPHI_PACKAGE System::UnicodeString C_Tns_Names;
extern DELPHI_PACKAGE System::UnicodeString C_Tns_Admin;
extern DELPHI_PACKAGE System::UnicodeString C_Network;
extern DELPHI_PACKAGE System::UnicodeString C_Net80;
extern DELPHI_PACKAGE System::UnicodeString C_Admin;
extern DELPHI_PACKAGE System::UnicodeString C_TnsNamesOra;
extern DELPHI_PACKAGE TOCIVarDataTypes otCrsTypes;
extern DELPHI_PACKAGE TOCIVarDataTypes otHTypes;
extern DELPHI_PACKAGE TOCIVarDataTypes otHBlobs;
extern DELPHI_PACKAGE TOCIVarDataTypes otVBlobs;
extern DELPHI_PACKAGE TOCIVarDataTypes otAllBlobs;
extern DELPHI_PACKAGE void __fastcall OraDate2DateTime(Firedac::Phys::Oraclecli::pUb1 pIn, Data::Db::TDateTimeRec &D);
extern DELPHI_PACKAGE void __fastcall DateTime2OraDate(Firedac::Phys::Oraclecli::pUb1 pOut, const Data::Db::TDateTimeRec &D);
extern DELPHI_PACKAGE void __fastcall Bcd2OraNumber(Firedac::Phys::Oraclecli::pOCINumber pOut, const Data::Fmtbcd::TBcd &B, /* out */ System::Word &ALen);
extern DELPHI_PACKAGE void __fastcall OraNumber2Bcd(Firedac::Phys::Oraclecli::pOCINumber pIn, Data::Fmtbcd::TBcd &B);
}	/* namespace Oraclewrapper */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ORACLEWRAPPER)
using namespace Firedac::Phys::Oraclewrapper;
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
#endif	// Firedac_Phys_OraclewrapperHPP
