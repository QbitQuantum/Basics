// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ADSWrapper.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_AdswrapperHPP
#define Firedac_Phys_AdswrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Consts.hpp>
#include <FireDAC.Phys.ADSCli.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Adswrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EADSNativeException;
class DELPHICLASS TADSLib;
class DELPHICLASS TADSHandle;
class DELPHICLASS TADSConnection;
class DELPHICLASS TADSColumnDef;
class DELPHICLASS TADSBLOBStream;
class DELPHICLASS TADSVariable;
class DELPHICLASS TADSVariables;
class DELPHICLASS TADSStatement;
class DELPHICLASS TADSCursor;
class DELPHICLASS TADSTable;
class DELPHICLASS TADSDictionary;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EADSNativeException : public Firedac::Stan::Error::EFDDBEngineException
{
	typedef Firedac::Stan::Error::EFDDBEngineException inherited;
	
public:
	__fastcall EADSNativeException(unsigned ACode, TADSLib* ALib, TADSHandle* AOwner)/* overload */;
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual EADSNativeException()/* overload */ : Firedac::Stan::Error::EFDDBEngineException() { }
	/* EFDDBEngineException.Create */ inline __fastcall EADSNativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~EADSNativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EADSNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EADSNativeException(NativeUInt Ident)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EADSNativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EADSNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EADSNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EADSNativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EADSNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EADSNativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EADSNativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EADSNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EADSNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High, AHelpContext) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TADSLib : public Firedac::Stan::Util::TFDLibrary
{
	typedef Firedac::Stan::Util::TFDLibrary inherited;
	
private:
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	System::UnicodeString FVersionStr;
	System::Classes::TStrings* FServers;
	void __fastcall UpdateVersion();
	void __fastcall Check(unsigned ACode);
	System::UnicodeString __fastcall GetDateFormat();
	void __fastcall SetDateFormat(const System::UnicodeString AValue);
	System::Word __fastcall GetDecimals();
	void __fastcall SetDecimals(const System::Word AValue);
	System::UnicodeString __fastcall GetDefaultPath();
	void __fastcall SetDefaultPath(const System::UnicodeString AValue);
	bool __fastcall GetShowDeleted();
	void __fastcall SetShowDeleted(const bool AValue);
	System::Word __fastcall GetEpoch();
	void __fastcall SetEpoch(const System::Word AValue);
	bool __fastcall GetExact();
	void __fastcall SetExact(const bool AValue);
	System::UnicodeString __fastcall GetSearchPath();
	void __fastcall SetSearchPath(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetAliasFileName();
	
protected:
	virtual void __fastcall LoadEntries();
	
public:
	Firedac::Phys::Adscli::TAdsNullTerminateStrings FAdsNullTerminateStrings;
	Firedac::Phys::Adscli::TAdsGetLastError FAdsGetLastError;
	Firedac::Phys::Adscli::TAdsConnect101 FAdsConnect101;
	Firedac::Phys::Adscli::TAdsConnect60 FAdsConnect60;
	Firedac::Phys::Adscli::TAdsDisconnect FAdsDisconnect;
	Firedac::Phys::Adscli::TAdsBeginTransaction FAdsBeginTransaction;
	Firedac::Phys::Adscli::TAdsCreateSavepoint FAdsCreateSavepoint;
	Firedac::Phys::Adscli::TAdsCommitTransaction FAdsCommitTransaction;
	Firedac::Phys::Adscli::TAdsRollbackTransaction80 FAdsRollbackTransaction80;
	Firedac::Phys::Adscli::TAdsGetTransactionCount FAdsGetTransactionCount;
	Firedac::Phys::Adscli::TAdsDisableAutoIncEnforcement FAdsDisableAutoIncEnforcement;
	Firedac::Phys::Adscli::TAdsEnableAutoIncEnforcement FAdsEnableAutoIncEnforcement;
	Firedac::Phys::Adscli::TAdsDisableRI FAdsDisableRI;
	Firedac::Phys::Adscli::TAdsEnableRI FAdsEnableRI;
	Firedac::Phys::Adscli::TAdsDisableUniqueEnforcement FAdsDisableUniqueEnforcement;
	Firedac::Phys::Adscli::TAdsEnableUniqueEnforcement FAdsEnableUniqueEnforcement;
	Firedac::Phys::Adscli::TAdsFindServers FAdsFindServers;
	Firedac::Phys::Adscli::TAdsGetCollation FAdsGetCollation;
	Firedac::Phys::Adscli::TAdsSetCollation FAdsSetCollation;
	Firedac::Phys::Adscli::TAdsGetConnectionPath FAdsGetConnectionPath;
	Firedac::Phys::Adscli::TAdsGetDateFormat FAdsGetDateFormat;
	Firedac::Phys::Adscli::TAdsSetDateFormat FAdsSetDateFormat;
	Firedac::Phys::Adscli::TAdsGetDateFormat60 FAdsGetDateFormat60;
	Firedac::Phys::Adscli::TAdsSetDateFormat60 FAdsSetDateFormat60;
	Firedac::Phys::Adscli::TAdsGetDecimals FAdsGetDecimals;
	Firedac::Phys::Adscli::TAdsSetDecimals FAdsSetDecimals;
	Firedac::Phys::Adscli::TAdsGetDefault FAdsGetDefault;
	Firedac::Phys::Adscli::TAdsSetDefault FAdsSetDefault;
	Firedac::Phys::Adscli::TAdsGetDeleted FAdsGetDeleted;
	Firedac::Phys::Adscli::TAdsShowDeleted FAdsShowDeleted;
	Firedac::Phys::Adscli::TAdsGetEpoch FAdsGetEpoch;
	Firedac::Phys::Adscli::TAdsSetEpoch FAdsSetEpoch;
	Firedac::Phys::Adscli::TAdsGetExact FAdsGetExact;
	Firedac::Phys::Adscli::TAdsSetExact FAdsSetExact;
	Firedac::Phys::Adscli::TAdsGetSearchPath FAdsGetSearchPath;
	Firedac::Phys::Adscli::TAdsSetSearchPath FAdsSetSearchPath;
	Firedac::Phys::Adscli::TAdsGetVersion FAdsGetVersion;
	Firedac::Phys::Adscli::TAdsIsConnectionAlive FAdsIsConnectionAlive;
#ifndef _WIN64
	Firedac::Phys::Adscli::TAdsRegisterCallbackFunction FAdsRegisterCallbackFunction;
#else /* _WIN64 */
	Firedac::Phys::Adscli::TAdsRegisterCallbackFunction101 FAdsRegisterCallbackFunction101;
#endif /* _WIN64 */
	Firedac::Phys::Adscli::TAdsClearCallbackFunction FAdsClearCallbackFunction;
	Firedac::Phys::Adscli::TAdsDDGetDatabaseProperty FAdsDDGetDatabaseProperty;
	Firedac::Phys::Adscli::TAdsDDSetDatabaseProperty FAdsDDSetDatabaseProperty;
	Firedac::Phys::Adscli::TAdsCreateSQLStatement FAdsCreateSQLStatement;
	Firedac::Phys::Adscli::TAdsPrepareSQLW FAdsPrepareSQLW;
	Firedac::Phys::Adscli::TAdsExecuteSQLDirectW FAdsExecuteSQLDirectW;
	Firedac::Phys::Adscli::TAdsPrepareSQL FAdsPrepareSQL;
	Firedac::Phys::Adscli::TAdsExecuteSQLDirect FAdsExecuteSQLDirect;
	Firedac::Phys::Adscli::TAdsCloseSQLStatement FAdsCloseSQLStatement;
	Firedac::Phys::Adscli::TAdsClearSQLParams FAdsClearSQLParams;
	Firedac::Phys::Adscli::TAdsExecuteSQL FAdsExecuteSQL;
	Firedac::Phys::Adscli::TAdsGetLastAutoinc FAdsGetLastAutoinc;
	Firedac::Phys::Adscli::TAdsSetSQLTimeout FAdsSetSQLTimeout;
	Firedac::Phys::Adscli::TAdsStmtSetTableReadOnly FAdsStmtSetTableReadOnly;
	Firedac::Phys::Adscli::TAdsStmtSetTableCharType FAdsStmtSetTableCharType;
	Firedac::Phys::Adscli::TAdsStmtSetTableCollation FAdsStmtSetTableCollation;
	Firedac::Phys::Adscli::TAdsStmtSetTableLockType FAdsStmtSetTableLockType;
	Firedac::Phys::Adscli::TAdsStmtSetTableType FAdsStmtSetTableType;
	Firedac::Phys::Adscli::TAdsStmtSetTablePassword FAdsStmtSetTablePassword;
	Firedac::Phys::Adscli::TAdsGetBinary FAdsGetBinary;
	Firedac::Phys::Adscli::TAdsSetBinary FAdsSetBinary;
	Firedac::Phys::Adscli::TAdsGetBinaryLength FAdsGetBinaryLength;
	Firedac::Phys::Adscli::TAdsGetMemoLength FAdsGetMemoLength;
	Firedac::Phys::Adscli::TAdsFileToBinary FAdsFileToBinary;
	Firedac::Phys::Adscli::TAdsBinaryToFile FAdsBinaryToFile;
	Firedac::Phys::Adscli::TAdsIsNull FAdsIsNull;
	Firedac::Phys::Adscli::TAdsSetNull FAdsSetNull;
	Firedac::Phys::Adscli::TAdsIsEmpty FAdsIsEmpty;
	Firedac::Phys::Adscli::TAdsSetEmpty FAdsSetEmpty;
	Firedac::Phys::Adscli::TAdsGetLogical FAdsGetLogical;
	Firedac::Phys::Adscli::TAdsGetString FAdsGetString;
	Firedac::Phys::Adscli::TAdsGetDouble FAdsGetDouble;
	Firedac::Phys::Adscli::TAdsGetLong FAdsGetLong;
	Firedac::Phys::Adscli::TAdsGetShort FAdsGetShort;
	Firedac::Phys::Adscli::TAdsGetLongLong FAdsGetLongLong;
	Firedac::Phys::Adscli::TAdsGetJulian FAdsGetJulian;
	Firedac::Phys::Adscli::TAdsGetMilliseconds FAdsGetMilliseconds;
	Firedac::Phys::Adscli::TAdsGetFieldLength FAdsGetFieldLength;
	Firedac::Phys::Adscli::TAdsGetFieldLength100 FAdsGetFieldLength100;
	Firedac::Phys::Adscli::TAdsGetStringW FAdsGetStringW;
	Firedac::Phys::Adscli::TAdsGetField FAdsGetField;
	Firedac::Phys::Adscli::TAdsSetLogical FAdsSetLogical;
	Firedac::Phys::Adscli::TAdsSetString FAdsSetString;
	Firedac::Phys::Adscli::TAdsSetDouble FAdsSetDouble;
	Firedac::Phys::Adscli::TAdsSetLong FAdsSetLong;
	Firedac::Phys::Adscli::TAdsSetShort FAdsSetShort;
	Firedac::Phys::Adscli::TAdsSetLongLong FAdsSetLongLong;
	Firedac::Phys::Adscli::TAdsSetJulian FAdsSetJulian;
	Firedac::Phys::Adscli::TAdsSetMilliseconds FAdsSetMilliseconds;
	Firedac::Phys::Adscli::TAdsSetStringW FAdsSetStringW;
	Firedac::Phys::Adscli::TAdsSetField FAdsSetField;
	Firedac::Phys::Adscli::TAdsSetTimeStampRaw FAdsSetTimeStampRaw;
	Firedac::Phys::Adscli::TAdsGetRecordCount FAdsGetRecordCount;
	Firedac::Phys::Adscli::TAdsGetNumFields FAdsGetNumFields;
	Firedac::Phys::Adscli::TAdsAtBOF FAdsAtBOF;
	Firedac::Phys::Adscli::TAdsAtEOF FAdsAtEOF;
	Firedac::Phys::Adscli::TAdsCacheRecords FAdsCacheRecords;
	Firedac::Phys::Adscli::TAdsCloseTable FAdsCloseTable;
	Firedac::Phys::Adscli::TAdsSkip FAdsSkip;
	Firedac::Phys::Adscli::TAdsGetRecordNum FAdsGetRecordNum;
	Firedac::Phys::Adscli::TAdsGotoRecord FAdsGotoRecord;
	Firedac::Phys::Adscli::TAdsGotoTop FAdsGotoTop;
	Firedac::Phys::Adscli::TAdsGotoBottom FAdsGotoBottom;
	Firedac::Phys::Adscli::TAdsGetFieldType FAdsGetFieldType;
	Firedac::Phys::Adscli::TAdsGetMemoDataType FAdsGetMemoDataType;
	Firedac::Phys::Adscli::TAdsGetFieldDecimals FAdsGetFieldDecimals;
	Firedac::Phys::Adscli::TAdsGetFieldName FAdsGetFieldName;
	Firedac::Phys::Adscli::TAdsGetKeyColumn FAdsGetKeyColumn;
	Firedac::Phys::Adscli::TAdsGetLastTableUpdate FAdsGetLastTableUpdate;
	Firedac::Phys::Adscli::TAdsConvertStringToJulian FAdsConvertStringToJulian;
	Firedac::Phys::Adscli::TAdsAppendRecord FAdsAppendRecord;
	Firedac::Phys::Adscli::TAdsDeleteRecord FAdsDeleteRecord;
	Firedac::Phys::Adscli::TAdsWriteRecord FAdsWriteRecord;
	Firedac::Phys::Adscli::TAdsRecallRecord FAdsRecallRecord;
	Firedac::Phys::Adscli::TAdsRecallAllRecords FAdsRecallAllRecords;
	Firedac::Phys::Adscli::TAdsIsRecordDeleted FAdsIsRecordDeleted;
	Firedac::Phys::Adscli::TAdsOpenTable101 FAdsOpenTable101;
	Firedac::Phys::Adscli::TAdsOpenTable FAdsOpenTable;
	Firedac::Phys::Adscli::TAdsCreateTable FAdsCreateTable;
	Firedac::Phys::Adscli::TAdsPackTable FAdsPackTable;
	Firedac::Phys::Adscli::TAdsZapTable FAdsZapTable;
	Firedac::Phys::Adscli::TAdsGetTableType FAdsGetTableType;
	Firedac::Phys::Adscli::TAdsGetTableRights FAdsGetTableRights;
	Firedac::Phys::Adscli::TAdsGetTableLockType FAdsGetTableLockType;
	Firedac::Phys::Adscli::TAdsGetTableCharType FAdsGetTableCharType;
	Firedac::Phys::Adscli::TAdsCreateIndex FAdsCreateIndex;
	Firedac::Phys::Adscli::TAdsCopyTable FAdsCopyTable;
	Firedac::Phys::Adscli::TAdsEnableEncryption FAdsEnableEncryption;
	Firedac::Phys::Adscli::TAdsEncryptTable FAdsEncryptTable;
	Firedac::Phys::Adscli::TAdsIsTableEncrypted FAdsIsTableEncrypted;
	Firedac::Phys::Adscli::TAdsDecryptTable FAdsDecryptTable;
	Firedac::Phys::Adscli::TAdsReindex FAdsReindex;
	Firedac::Phys::Adscli::TAdsLockRecord FAdsLockRecord;
	Firedac::Phys::Adscli::TAdsUnlockRecord FAdsUnLockRecord;
	Firedac::Phys::Adscli::TAdsMgGetInstallInfo FAdsMgGetInstallInfo;
	__fastcall TADSLib(System::TObject* AOwningObj);
	__fastcall virtual ~TADSLib();
	HIDESBASE void __fastcall Load(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib);
	void __fastcall ListServers(System::Classes::TStrings* AList);
	void __fastcall ListAliases(System::Classes::TStrings* AList);
	bool __fastcall ResolveAlias(const System::UnicodeString AName, System::UnicodeString &APath, System::UnicodeString AType);
	static System::UnicodeString __fastcall DumpField(Firedac::Phys::Adscli::PAceChar AField);
	__property System::UnicodeString AliasFileName = {read=GetAliasFileName};
	__property Firedac::Stan::Util::TFDEncoder* Encoder = {read=FEncoder};
	__property System::UnicodeString DateFormat = {read=GetDateFormat, write=SetDateFormat};
	__property System::Word Decimals = {read=GetDecimals, write=SetDecimals, nodefault};
	__property System::UnicodeString DefaultPath = {read=GetDefaultPath, write=SetDefaultPath};
	__property System::UnicodeString SearchPath = {read=GetSearchPath, write=SetSearchPath};
	__property bool ShowDeleted = {read=GetShowDeleted, write=SetShowDeleted, nodefault};
	__property System::Word Epoch = {read=GetEpoch, write=SetEpoch, nodefault};
	__property bool Exact = {read=GetExact, write=SetExact, nodefault};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TADSHandle : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TADSLib* FLib;
	NativeUInt FHandle;
	bool FOwnHandle;
	System::TObject* FOwningObj;
	TADSConnection* FConnection;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	bool __fastcall GetTracing();
	
protected:
	void __fastcall Trace(const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	void __fastcall Trace(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	__property bool Tracing = {read=GetTracing, nodefault};
	
public:
	__fastcall TADSHandle();
	__fastcall TADSHandle(NativeUInt AHandle);
	__fastcall virtual ~TADSHandle();
	void __fastcall Check(unsigned ACode);
#ifndef _WIN64
	__property NativeUInt Handle = {read=FHandle, nodefault};
#else /* _WIN64 */
	__property NativeUInt Handle = {read=FHandle};
#endif /* _WIN64 */
	__property TADSLib* Lib = {read=FLib};
	__property System::TObject* OwningObj = {read=FOwningObj, write=FOwningObj};
	__property TADSConnection* Connection = {read=FConnection};
	__property Firedac::Stan::Util::TFDEncoder* Encoder = {read=FEncoder};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TADSProgressCallback)(TADSConnection* ASender, System::Word APercent, bool &AAbort);

class PASCALIMPLEMENTATION TADSConnection : public TADSHandle
{
	typedef TADSHandle inherited;
	
private:
	unsigned __int64 FServerVersion;
	bool FAutoIncEnforcement;
	bool FRIEnforcement;
	bool FUniqueEnforcement;
	bool FAbortRequest;
	unsigned FLastAutoInc;
	System::UnicodeString FServerVersionStr;
	TADSProgressCallback FOnProgress;
	int FProgressCount;
	bool FTracing;
	Firedac::Stan::Intf::_di_IFDMoniClient FMonitor;
	void __fastcall BeforeConnecting();
	void __fastcall AfterConnecting();
	unsigned __fastcall GetTransactionCount();
	void __fastcall SetAutoIncEnforcement(const bool AValue);
	void __fastcall SetRIEnforcement(const bool AValue);
	void __fastcall SetUniqueEnforcement(const bool AValue);
	System::UnicodeString __fastcall GetCollation();
	void __fastcall SetCollation(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetDateFormat();
	void __fastcall SetDateFormat(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetConnectionPath();
	bool __fastcall DoProgress(System::Word usPercent);
	void __fastcall SetOnProgress(const TADSProgressCallback AValue);
	
public:
	__fastcall TADSConnection(TADSLib* ALib, System::TObject* AOwningObj, const Firedac::Stan::Intf::_di_IFDMoniClient AMonitor);
	__fastcall TADSConnection(TADSLib* ALib, NativeUInt AHandle, System::TObject* AOwningObj, const Firedac::Stan::Intf::_di_IFDMoniClient AMonitor);
	__fastcall virtual ~TADSConnection();
	void __fastcall Connect101(const System::UnicodeString AConnStr);
	void __fastcall Connect60(const System::UnicodeString AConnPath, System::Word AServerTypes, System::UnicodeString AUserName, System::UnicodeString APassword, unsigned AOptions);
	void __fastcall Disconnect();
	bool __fastcall Ping();
	void __fastcall BeginTransaction(const System::UnicodeString AName);
	void __fastcall Commit();
	void __fastcall Rollback(const System::UnicodeString AName);
	void __fastcall EnableProgress();
	void __fastcall DisableProgress();
	void __fastcall Abort();
	__property unsigned TransactionCount = {read=GetTransactionCount, nodefault};
	__property unsigned __int64 ServerVersion = {read=FServerVersion};
	__property System::UnicodeString ServerVersionStr = {read=FServerVersionStr};
	__property unsigned LastAutoInc = {read=FLastAutoInc, nodefault};
	__property System::UnicodeString ConnectionPath = {read=GetConnectionPath};
	__property bool AutoIncEnforcement = {read=FAutoIncEnforcement, write=SetAutoIncEnforcement, nodefault};
	__property bool RIEnforcement = {read=FRIEnforcement, write=SetRIEnforcement, nodefault};
	__property bool UniqueEnforcement = {read=FUniqueEnforcement, write=SetUniqueEnforcement, nodefault};
	__property System::UnicodeString Collation = {read=GetCollation, write=SetCollation};
	__property System::UnicodeString DateFormat = {read=GetDateFormat, write=SetDateFormat};
	__property Firedac::Stan::Intf::_di_IFDMoniClient Monitor = {read=FMonitor, write=FMonitor};
	__property bool Tracing = {read=FTracing, write=FTracing, nodefault};
	__property TADSProgressCallback OnProgress = {read=FOnProgress, write=SetOnProgress};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TADSColumnDef : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TADSCursor* FCursor;
	System::Word FPosition;
	unsigned FLength;
	System::UnicodeString FName;
	System::Word FFieldType;
	unsigned FPrecision;
	System::Word FScale;
	System::Word FMemoType;
	
public:
	__fastcall TADSColumnDef(TADSCursor* ACursor, int AIndex);
	__property System::UnicodeString Name = {read=FName};
	__property System::Word Position = {read=FPosition, nodefault};
	__property System::Word FieldType = {read=FFieldType, nodefault};
	__property System::Word MemoType = {read=FMemoType, nodefault};
	__property unsigned Precision = {read=FPrecision, nodefault};
	__property System::Word Scale = {read=FScale, nodefault};
	__property unsigned Length = {read=FLength, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TADSColumnDef() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TADSBLOBStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	TADSHandle* FObj;
	TADSVariable* FVariable;
	__int64 FPosition;
	__int64 FSize;
	Firedac::Stan::Intf::TFDStreamMode FMode;
	bool FModified;
	
protected:
	__fastcall TADSBLOBStream(TADSHandle* AObj, TADSVariable* AVariable, Firedac::Stan::Intf::TFDStreamMode AMode);
	virtual void __fastcall SetSize(int NewSize)/* overload */;
	
public:
	__fastcall virtual ~TADSBLOBStream();
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
	virtual int __fastcall Seek(int Offset, System::Word Origin)/* overload */;
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	void __fastcall SaveToFile(const System::UnicodeString AFileName);
	void __fastcall LoadFromFile(const System::UnicodeString AFileName);
	void __fastcall Flush();
	__property TADSHandle* Obj = {read=FObj};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  SetSize(const __int64 NewSize){ System::Classes::TStream::SetSize(NewSize); }
	
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
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TADSVariable : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TADSHandle* FObj;
	TADSVariables* FVars;
	System::Int8 *FField;
	System::Word FValueType;
	bool FIsImage;
	System::UnicodeString FName;
	System::RawByteString FNameBytes;
	bool __fastcall GetIsNull();
	System::Word __fastcall GetPosition();
	void __fastcall SetName(const System::UnicodeString AValue);
	void __fastcall SetPosition(const System::Word AValue);
	System::UnicodeString __fastcall GetAsString();
	void __fastcall SetAsString(const System::UnicodeString AValue);
	System::UnicodeString __fastcall DumpSQLDataType();
	System::UnicodeString __fastcall DumpValue();
	System::UnicodeString __fastcall DumpLabel();
	
public:
	__fastcall TADSVariable(TADSVariables* AVars, TADSHandle* AObj);
	bool __fastcall GetData(void * AValue, int &ASize);
	void __fastcall SetData(void * AValue, int ASize);
	TADSBLOBStream* __fastcall CreateBlobStream(Firedac::Stan::Intf::TFDStreamMode AMode);
	unsigned __fastcall GetDataLength();
	void __fastcall Clear();
	__property bool IsNull = {read=GetIsNull, nodefault};
	__property System::UnicodeString AsString = {read=GetAsString, write=SetAsString};
	__property System::Word Position = {read=GetPosition, write=SetPosition, nodefault};
	__property System::UnicodeString Name = {read=FName, write=SetName};
	__property System::Word ValueType = {read=FValueType, write=FValueType, nodefault};
	__property bool IsImage = {read=FIsImage, write=FIsImage, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TADSVariable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TADSVariables : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TADSVariable* operator[](int AIndex) { return this->Items[AIndex]; }
	
private:
	TADSStatement* FStmt;
	TADSHandle* FObj;
	System::Classes::TList* FList;
	TADSVariable* __fastcall GetItems(int AIndex);
	int __fastcall GetCount();
	void __fastcall SetCount(const int AValue);
	
public:
	__fastcall TADSVariables(TADSStatement* AStmt, TADSHandle* AObj);
	__fastcall virtual ~TADSVariables();
	void __fastcall Clear();
	TADSVariable* __fastcall Add();
	TADSVariable* __fastcall FindVar(const System::UnicodeString AName);
	TADSVariable* __fastcall VarByName(const System::UnicodeString AName);
	__property int Count = {read=GetCount, write=SetCount, nodefault};
	__property TADSVariable* Items[int AIndex] = {read=GetItems/*, default*/};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TADSLockType : unsigned int { ltProprietary, ltCompatible };

enum DECLSPEC_DENUM TADSTableType : unsigned int { ttDefault, ttCDX, ttVFP, ttADT, ttNTX };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TADSStatement : public TADSHandle
{
	typedef TADSHandle inherited;
	
private:
	NativeUInt FCursorHandle;
	unsigned FTimeout;
	System::Word FCharType;
	System::UnicodeString FCollation;
	TADSLockType FLockType;
	bool FReadOnly;
	TADSTableType FTableType;
	bool FStrsTrim;
	bool FStrsEmpty2Null;
	TADSVariables* FParams;
	unsigned __fastcall GetLastAutoInc();
	void __fastcall SetTimeout(const unsigned AValue);
	void __fastcall SetCharType(const System::Word AValue);
	void __fastcall SetCollation(const System::UnicodeString AValue);
	void __fastcall SetLockType(const TADSLockType AValue);
	void __fastcall SetReadOnly(const bool AValue);
	void __fastcall SetTableType(const TADSTableType AValue);
	unsigned __fastcall GetRecordCount();
	
public:
	__fastcall TADSStatement(TADSConnection* AConn, System::TObject* AOwningObj);
	__fastcall virtual ~TADSStatement();
	void __fastcall Prepare(const System::UnicodeString ASQL);
	void __fastcall Unprepare();
	void __fastcall ExecuteDirect(const System::UnicodeString ASQL);
	void __fastcall Execute();
	void __fastcall Close();
	TADSCursor* __fastcall GetCursor();
	void __fastcall SetTablePassword(const System::UnicodeString ATableName, const System::UnicodeString APassword);
	__property unsigned LastAutoInc = {read=GetLastAutoInc, nodefault};
	__property unsigned RecordCount = {read=GetRecordCount, nodefault};
	__property TADSVariables* Params = {read=FParams};
	__property unsigned Timeout = {read=FTimeout, write=SetTimeout, nodefault};
	__property System::Word CharType = {read=FCharType, write=SetCharType, nodefault};
	__property System::UnicodeString Collation = {read=FCollation, write=SetCollation};
	__property TADSLockType LockType = {read=FLockType, write=SetLockType, nodefault};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, nodefault};
	__property TADSTableType TableType = {read=FTableType, write=SetTableType, nodefault};
	__property bool StrsTrim = {read=FStrsTrim, write=FStrsTrim, nodefault};
	__property bool StrsEmpty2Null = {read=FStrsEmpty2Null, write=FStrsEmpty2Null, nodefault};
public:
	/* TADSHandle.CreateUsingHandle */ inline __fastcall TADSStatement(NativeUInt AHandle) : TADSHandle(AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TADSCursor : public TADSHandle
{
	typedef TADSHandle inherited;
	
private:
	TADSStatement* FStmt;
	TADSVariables* FColumns;
	int FCacheRecords;
	System::Word FColumnDefsCount;
	bool __fastcall GetBof();
	bool __fastcall GetEof();
	void __fastcall SetCacheRecords(const int AValue);
	unsigned __fastcall GetRecordCount();
	TADSColumnDef* __fastcall GetColumnDefs(int AIndex);
	unsigned __fastcall GetRecNo();
	void __fastcall SetRecNo(const unsigned AValue);
	System::UnicodeString __fastcall GetKeyColumns();
	System::TDateTime __fastcall GetLastUpdate();
	bool __fastcall GetDeleted();
	TADSTableType __fastcall GetTableType();
	System::Word __fastcall GetCharType();
	System::Word __fastcall GetCheckRights();
	TADSLockType __fastcall GetLockType();
	void __fastcall UpdateFieldsNum();
	void __fastcall DumpColumns();
	
protected:
	System::Word FCharType;
	System::Word FCheckRights;
	TADSLockType FLockType;
	TADSTableType FTableType;
	__fastcall TADSCursor(System::TObject* AParent, NativeUInt AHandle, System::TObject* AOwningObj);
	
public:
	__fastcall virtual ~TADSCursor();
	void __fastcall AddColumns();
	void __fastcall Close();
	void __fastcall Skip(int ARecs = 0x1);
	void __fastcall Top();
	void __fastcall Bottom();
	void __fastcall CopyTable(const System::UnicodeString AFile, System::Word AFilterOptions);
	void __fastcall EnableEncryption(const System::UnicodeString APassword);
	void __fastcall Append();
	void __fastcall Delete();
	void __fastcall Recall();
	void __fastcall Post();
	void __fastcall Lock(unsigned ARec, unsigned AWaitTimeout = (unsigned)(0x0));
	void __fastcall UnLock(unsigned ARec);
	__property TADSVariables* Columns = {read=FColumns};
	__property System::Word ColumnDefsCount = {read=FColumnDefsCount, nodefault};
	__property TADSColumnDef* ColumnDefs[int AIndex] = {read=GetColumnDefs};
	__property bool Bof = {read=GetBof, nodefault};
	__property bool Eof = {read=GetEof, nodefault};
	__property bool IsDeleted = {read=GetDeleted, nodefault};
	__property System::UnicodeString KeyColumns = {read=GetKeyColumns};
	__property System::TDateTime LastUpdate = {read=GetLastUpdate};
	__property unsigned RecordCount = {read=GetRecordCount, nodefault};
	__property unsigned RecNo = {read=GetRecNo, write=SetRecNo, nodefault};
	__property int CacheRecords = {read=FCacheRecords, write=SetCacheRecords, nodefault};
	__property System::Word CharType = {read=GetCharType, nodefault};
	__property System::Word CheckRights = {read=GetCheckRights, nodefault};
	__property TADSLockType LockType = {read=GetLockType, nodefault};
	__property TADSTableType TableType = {read=GetTableType, nodefault};
public:
	/* TADSHandle.CreateUsingHandle */ inline __fastcall TADSCursor(NativeUInt AHandle) : TADSHandle(AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TADSTable : public TADSCursor
{
	typedef TADSCursor inherited;
	
private:
	System::UnicodeString FTableName;
	System::UnicodeString FAlias;
	unsigned FOptions;
	System::Word FMemoSize;
	bool __fastcall GetIsEncrypted();
	
public:
	__fastcall TADSTable(TADSConnection* AConn, System::TObject* AOwningObj);
	void __fastcall Open();
	void __fastcall Open101();
	void __fastcall CreateTable(const System::UnicodeString AFields, System::Word AMemoSize);
	void __fastcall Pack();
	void __fastcall Zap();
	void __fastcall RecallAll();
	void __fastcall CreateIndex(const System::UnicodeString AFileName, const System::UnicodeString ATag, const System::UnicodeString AKeyExpr, const System::UnicodeString ACondition, const System::UnicodeString AWhile, unsigned AOptions);
	void __fastcall Reindex();
	void __fastcall Encrypt();
	void __fastcall Decrypt();
	__property bool IsEncrypted = {read=GetIsEncrypted, nodefault};
	__property System::UnicodeString TableName = {read=FTableName, write=FTableName};
	__property System::UnicodeString Alias = {read=FAlias, write=FAlias};
	__property TableType = {write=FTableType};
	__property CharType = {write=FCharType};
	__property LockType = {write=FLockType};
	__property CheckRights = {write=FCheckRights};
	__property unsigned Options = {read=FOptions, write=FOptions, nodefault};
	__property System::Word MemoSize = {read=FMemoSize, write=FMemoSize, nodefault};
public:
	/* TADSCursor.Destroy */ inline __fastcall virtual ~TADSTable() { }
	
public:
	/* TADSHandle.CreateUsingHandle */ inline __fastcall TADSTable(NativeUInt AHandle) : TADSCursor(AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TADSDictionary : public TADSHandle
{
	typedef TADSHandle inherited;
	
private:
	bool FHasDictionary;
	System::UnicodeString __fastcall GetString(int AIndex);
	unsigned __fastcall GetLongWord(int AIndex);
	System::Word __fastcall GetWord(int AIndex);
	void __fastcall SetString(int AIndex, const System::UnicodeString AValue);
	void __fastcall SetLongWord(int AIndex, const unsigned AValue);
	void __fastcall SetWord(int AIndex, const System::Word AValue);
	
public:
	__fastcall TADSDictionary(TADSConnection* AConnection);
	__property bool HasDictionary = {read=FHasDictionary, nodefault};
	__property System::UnicodeString Comment = {read=GetString, write=SetString, index=1};
	__property System::UnicodeString VersionMajor = {read=GetString, write=SetString, index=111};
	__property System::UnicodeString VersionMinor = {read=GetString, write=SetString, index=112};
	__property System::UnicodeString UserDefinedProp = {read=GetString, write=SetString, index=3};
	__property System::UnicodeString DefaultTablePath = {read=GetString, write=SetString, index=100};
	__property System::UnicodeString TempTablePath = {read=GetString, write=SetString, index=102};
	__property System::Word LoginRequired = {read=GetWord, write=SetWord, index=103, nodefault};
	__property System::Word VerifyAccessRights = {read=GetWord, write=SetWord, index=104, nodefault};
	__property System::UnicodeString EncryptTablePassword = {read=GetString, write=SetString, index=105};
	__property System::Word EncryptNewTable = {read=GetWord, write=SetWord, index=106, nodefault};
	__property unsigned DataEncryptType = {read=GetLongWord, write=SetLongWord, index=126, nodefault};
	__property System::UnicodeString FtsDelimiters = {read=GetString, write=SetString, index=115};
	__property System::UnicodeString FtsNoise = {read=GetString, write=SetString, index=116};
	__property System::UnicodeString FtsDropChars = {read=GetString, write=SetString, index=117};
	__property System::UnicodeString FtsConditionalChars = {read=GetString, write=SetString, index=118};
	__property System::Word LoginsDisabled = {read=GetWord, write=SetWord, index=113, nodefault};
	__property System::UnicodeString LoginsDisabledErrStr = {read=GetString, write=SetString, index=114};
	__property System::Word Encrypted = {read=GetWord, write=SetWord, index=119, nodefault};
	__property System::Word EncryptIndexes = {read=GetWord, write=SetWord, index=120, nodefault};
	__property System::Word EncryptCommunication = {read=GetWord, write=SetWord, index=122, nodefault};
public:
	/* TADSHandle.CreateUsingHandle */ inline __fastcall TADSDictionary(NativeUInt AHandle) : TADSHandle(AHandle) { }
	/* TADSHandle.Destroy */ inline __fastcall virtual ~TADSDictionary() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Adswrapper */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ADSWRAPPER)
using namespace Firedac::Phys::Adswrapper;
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
#endif	// Firedac_Phys_AdswrapperHPP
