// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ODBCWrapper.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_OdbcwrapperHPP
#define Firedac_Phys_OdbcwrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.FmtBcd.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Phys.ODBCCli.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Odbcwrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDODBCNativeError;
class DELPHICLASS EODBCNativeException;
class DELPHICLASS TODBCTracer;
class DELPHICLASS TODBCLib;
class DELPHICLASS TODBCHandle;
class DELPHICLASS TODBCEnvironment;
class DELPHICLASS TODBCConnection;
class DELPHICLASS TODBCSelectItem;
class DELPHICLASS TODBCVariable;
class DELPHICLASS TODBCParameter;
class DELPHICLASS TODBCLongDataStream;
class DELPHICLASS TODBCColumn;
class DELPHICLASS TODBCVariableList;
class DELPHICLASS TODBCPageBuffer;
class DELPHICLASS TODBCStatementBase;
class DELPHICLASS TODBCCommandStatement;
class DELPHICLASS TODBCMetaInfoStatement;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
typedef System::TMetaClass* EODBCNativeExceptionClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, EODBCNativeExceptionClass);
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TODBCLibClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TODBCLibClass);
#endif /* _WIN64 */

typedef void __fastcall (__closure *TODBCParseErrorEvent)(TODBCHandle* AHandle, short ARecNum, const System::UnicodeString ASQLState, int ANativeError, const System::UnicodeString ADiagMessage, const System::UnicodeString ACommandText, System::UnicodeString &AObj, Firedac::Stan::Error::TFDCommandExceptionKind &AKind, int &ACmdOffset);

typedef void __fastcall (__closure *TODBCGetMaxSizesEvent)(short AStrDataType, bool AFixedLen, /* out */ int &ACharSize, /* out */ int &AByteSize);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDODBCNativeError : public Firedac::Stan::Error::TFDDBError
{
	typedef Firedac::Stan::Error::TFDDBError inherited;
	
private:
	System::UnicodeString FSQLState;
	System::UnicodeString FDiagMessage;
	
protected:
	virtual void __fastcall Assign(Firedac::Stan::Error::TFDDBError* ASrc);
	virtual void __fastcall LoadFromStorage(const Firedac::Stan::Intf::_di_IFDStanStorage AStorage);
	virtual void __fastcall SaveToStorage(const Firedac::Stan::Intf::_di_IFDStanStorage AStorage);
	
public:
	__property System::UnicodeString SQLState = {read=FSQLState};
	__property System::UnicodeString DiagMessage = {read=FDiagMessage};
public:
	/* TFDDBError.Create */ inline __fastcall virtual TFDODBCNativeError()/* overload */ : Firedac::Stan::Error::TFDDBError() { }
	/* TFDDBError.Create */ inline __fastcall virtual TFDODBCNativeError(int ALevel, int AErrorCode, const System::UnicodeString AMessage, const System::UnicodeString AObjName, Firedac::Stan::Error::TFDCommandExceptionKind AKind, int ACmdOffset, int ARowIndex)/* overload */ : Firedac::Stan::Error::TFDDBError(ALevel, AErrorCode, AMessage, AObjName, AKind, ACmdOffset, ARowIndex) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDODBCNativeError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EODBCNativeException : public Firedac::Stan::Error::EFDDBEngineException
{
	typedef Firedac::Stan::Error::EFDDBEngineException inherited;
	
public:
	TFDODBCNativeError* operator[](int Index) { return this->Errors[Index]; }
	
private:
	HIDESBASE TFDODBCNativeError* __fastcall GetErrors(int AIndex);
	
protected:
	virtual Firedac::Stan::Error::TFDDBErrorClass __fastcall GetErrorClass();
	
public:
	__fastcall virtual EODBCNativeException(short AStatus, TODBCHandle* AOwner)/* overload */;
	HIDESBASE virtual Firedac::Stan::Error::TFDDBError* __fastcall AppendError(TODBCHandle* AHandle, short ARecNum, const System::UnicodeString ASQLState, int ANativeError, const System::UnicodeString ADiagMessage, const System::UnicodeString AResultMessage, const System::UnicodeString ACommandText, const System::UnicodeString AObject, Firedac::Stan::Error::TFDCommandExceptionKind AKind, int ACmdOffset, int ARowIndex);
	__property TFDODBCNativeError* Errors[int Index] = {read=GetErrors/*, default*/};
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual EODBCNativeException()/* overload */ : Firedac::Stan::Error::EFDDBEngineException() { }
	/* EFDDBEngineException.Create */ inline __fastcall EODBCNativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~EODBCNativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EODBCNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EODBCNativeException(NativeUInt Ident)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EODBCNativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EODBCNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EODBCNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EODBCNativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EODBCNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EODBCNativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EODBCNativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EODBCNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EODBCNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High, AHelpContext) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TODBCTracer : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	Firedac::Stan::Intf::_di_IFDMoniClient FMonitor;
	TODBCLib* FLib;
	int FLockOutput;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	
protected:
	virtual void __fastcall Execute();
	
public:
	__fastcall TODBCTracer(const Firedac::Stan::Intf::_di_IFDMoniClient AMonitor, TODBCLib* ALib);
	__fastcall virtual ~TODBCTracer();
};


class PASCALIMPLEMENTATION TODBCLib : public Firedac::Stan::Util::TFDLibrary
{
	typedef Firedac::Stan::Util::TFDLibrary inherited;
	
private:
	TODBCTracer* FTracer;
	System::Classes::TList* FTraceClients;
	bool FTracing;
	NativeUInt FhCPLib;
	bool __fastcall GetTRACE();
	System::UnicodeString __fastcall GetTRACEFILE();
	void __fastcall SetTRACE(bool AValue);
	void __fastcall SetTRACEFILE(const System::UnicodeString AValue);
	
protected:
	void * __fastcall GetODBCTextProcAddress(const System::UnicodeString AProcName, bool ARequired = true);
	virtual void __fastcall LoadLibrary(const System::UnicodeString *ADLLNames, const int ADLLNames_High, bool ARequired);
	virtual void __fastcall LoadEntries();
	
public:
	Firedac::Phys::Odbccli::TSQLAllocHandle SQLAllocHandle;
	Firedac::Phys::Odbccli::TSQLBindCol SQLBindCol;
	Firedac::Phys::Odbccli::TSQLBindParameter SQLBindParameter;
	Firedac::Phys::Odbccli::TSQLCancel SQLCancel;
	Firedac::Phys::Odbccli::TSQLColAttribute SQLColAttribute;
	Firedac::Phys::Odbccli::TSQLColAttributeInt SQLColAttributeInt;
	Firedac::Phys::Odbccli::TSQLColAttributeString SQLColAttributeString;
	Firedac::Phys::Odbccli::TSQLColumns SQLColumns;
	Firedac::Phys::Odbccli::TSQLConnect SQLConnect;
	Firedac::Phys::Odbccli::TSQLDataSources SQLDataSources;
	Firedac::Phys::Odbccli::TSQLDescribeCol SQLDescribeCol;
	Firedac::Phys::Odbccli::TSQLDescribeParam SQLDescribeParam;
	Firedac::Phys::Odbccli::TSQLDisconnect SQLDisconnect;
	Firedac::Phys::Odbccli::TSQLDriverConnect SQLDriverConnect;
	Firedac::Phys::Odbccli::TSQLBrowseConnect SQLBrowseConnect;
	Firedac::Phys::Odbccli::TSQLDrivers SQLDrivers;
	Firedac::Phys::Odbccli::TSQLEndTran SQLEndTran;
	Firedac::Phys::Odbccli::TSQLExecDirect SQLExecDirect;
	Firedac::Phys::Odbccli::TSQLExecute SQLExecute;
	Firedac::Phys::Odbccli::TSQLFetch SQLFetch;
	Firedac::Phys::Odbccli::TSQLForeignKeys SQLForeignKeys;
	Firedac::Phys::Odbccli::TSQLFreeHandle SQLFreeHandle;
	Firedac::Phys::Odbccli::TSQLFreeStmt SQLFreeStmt;
	Firedac::Phys::Odbccli::TSQLGetConnectAttr SQLGetConnectAttr;
	Firedac::Phys::Odbccli::TSQLGetCursorName SQLGetCursorName;
	Firedac::Phys::Odbccli::TSQLGetData SQLGetData;
	Firedac::Phys::Odbccli::TSQLGetDescField SQLGetDescField;
	Firedac::Phys::Odbccli::TSQLGetDescRec SQLGetDescRec;
	Firedac::Phys::Odbccli::TSQLGetDiagRec SQLGetDiagRec;
	Firedac::Phys::Odbccli::TSQLGetDiagField SQLGetDiagField;
	Firedac::Phys::Odbccli::TSQLGetEnvAttr SQLGetEnvAttr;
	Firedac::Phys::Odbccli::TSQLGetFunctions SQLGetFunctions;
	Firedac::Phys::Odbccli::TSQLGetInfo SQLGetInfo;
	Firedac::Phys::Odbccli::TSQLGetInfoSQLLen SQLGetInfoSQLLen;
	Firedac::Phys::Odbccli::TSQLGetInfoInt SQLGetInfoInt;
	Firedac::Phys::Odbccli::TSQLGetInfoSmallint SQLGetInfoSmallint;
	Firedac::Phys::Odbccli::TSQLGetInfoString SQLGetInfoString;
	Firedac::Phys::Odbccli::TSQLGetStmtAttr SQLGetStmtAttr;
	Firedac::Phys::Odbccli::TSQLGetTypeInfo SQLGetTypeInfo;
	Firedac::Phys::Odbccli::TSQLMoreResults SQLMoreResults;
	Firedac::Phys::Odbccli::TSQLNumParams SQLNumParams;
	Firedac::Phys::Odbccli::TSQLNumResultCols SQLNumResultCols;
	Firedac::Phys::Odbccli::TSQLParamData SQLParamData;
	Firedac::Phys::Odbccli::TSQLPrepare SQLPrepare;
	Firedac::Phys::Odbccli::TSQLPrimaryKeys SQLPrimaryKeys;
	Firedac::Phys::Odbccli::TSQLProcedureColumns SQLProcedureColumns;
	Firedac::Phys::Odbccli::TSQLProcedures SQLProcedures;
	Firedac::Phys::Odbccli::TSQLPutData SQLPutData;
	Firedac::Phys::Odbccli::TSQLRowCount SQLRowCount;
	Firedac::Phys::Odbccli::TSQLSetConnectAttr SQLSetConnectAttr;
	Firedac::Phys::Odbccli::TSQLSetCursorName SQLSetCursorName;
	Firedac::Phys::Odbccli::TSQLSetDescField SQLSetDescField;
	Firedac::Phys::Odbccli::TSQLSetDescRec SQLSetDescRec;
	Firedac::Phys::Odbccli::TSQLSetEnvAttr SQLSetEnvAttr;
	Firedac::Phys::Odbccli::TSQLSetPos SQLSetPos;
	Firedac::Phys::Odbccli::TSQLSetStmtAttr SQLSetStmtAttr;
	Firedac::Phys::Odbccli::TSQLSpecialColumns SQLSpecialColumns;
	Firedac::Phys::Odbccli::TSQLStatistics SQLStatistics;
	Firedac::Phys::Odbccli::TSQLTablePrivileges SQLTablePrivileges;
	Firedac::Phys::Odbccli::TSQLTables SQLTables;
	Firedac::Phys::Odbccli::TSQLConfigDataSource SQLConfigDataSource;
	Firedac::Phys::Odbccli::TSQLInstallerError SQLInstallerError;
	__fastcall TODBCLib(System::TObject* AOwningObj);
	__fastcall virtual ~TODBCLib();
	HIDESBASE void __fastcall Load(const System::UnicodeString AHome, const System::UnicodeString ALib);
	virtual void __fastcall Unload();
	__classmethod TODBCLib* __fastcall Allocate(const System::UnicodeString AHome, const System::UnicodeString ALib, System::TObject* AOwningObj = (System::TObject*)(0x0));
	__classmethod void __fastcall Release(TODBCLib* ALib);
	__classmethod System::UnicodeString __fastcall DecorateKeyValue(const System::UnicodeString AValue);
	__property bool Tracing = {read=FTracing, nodefault};
	void __fastcall ActivateTracing(const Firedac::Stan::Intf::_di_IFDMoniClient AMonitor, System::TObject* AClient);
	void __fastcall DeactivateTracing(System::TObject* AClient);
	__property bool TRACE = {read=GetTRACE, write=SetTRACE, nodefault};
	__property System::UnicodeString TRACEFILE = {read=GetTRACEFILE, write=SetTRACEFILE};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCHandle : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	void *FHandle;
	short FHandleType;
	bool FOwnHandle;
	TODBCLib* FODBCLib;
	TODBCHandle* FOwner;
	System::TObject* FOwningObj;
	bool FIgnoreErrors;
	TODBCConnection* __fastcall GetConnection();
	void __fastcall ProcessError(short AStatus);
	bool __fastcall GetTracing();
	
protected:
	virtual void __fastcall GetNonStrAttribute(int AAttr, void * ApValue);
	virtual void __fastcall GetStrAttribute(int AAttr, /* out */ System::UnicodeString &AValue);
	System::UnicodeString __fastcall GetCharAttribute(int AAttr);
	int __fastcall GetIntAttribute(int AAttr);
	void * __fastcall GetPSQLPAttribute(int AAttr);
	Firedac::Phys::Odbccli::PSQLUInteger __fastcall GetPUIntAttribute(int AAttr);
	Firedac::Phys::Odbccli::PSQLUSmallint __fastcall GetPUSmIntAttribute(int AAttr);
	int __fastcall GetUIntAttribute(int AAttr);
	System::Word __fastcall GetUSmIntAttribute(int AAttr);
	void * __fastcall GetPtrAttribute(int AAttr);
#ifndef _WIN64
	int __fastcall GetSQLLenAttribute(int AAttr);
	int __fastcall GetSQLULenAttribute(int AAttr);
#else /* _WIN64 */
	__int64 __fastcall GetSQLLenAttribute(int AAttr);
	unsigned __int64 __fastcall GetSQLULenAttribute(int AAttr);
#endif /* _WIN64 */
	Firedac::Phys::Odbccli::PSQLULen __fastcall GetPSQLULenAttribute(int AAttr);
	virtual void __fastcall SetAttribute(int AAttr, void * ApValue, int AType);
	void __fastcall SetPtrAttribute(int AAttr, void * AValue);
	void __fastcall SetCharAttribute(int AAttr, const System::UnicodeString AValue);
	void __fastcall SetIntAttribute(int AAttr, int AValue);
	void __fastcall SetPUIntAttribute(int AAttr, Firedac::Phys::Odbccli::PSQLUInteger AValue);
	void __fastcall SetPUSmIntAttribute(int AAttr, Firedac::Phys::Odbccli::PSQLUSmallint AValue);
	void __fastcall SetUIntAttribute(int AAttr, int AValue);
	void __fastcall SetUSmIntAttribute(int AAttr, System::Word AValue);
#ifndef _WIN64
	void __fastcall SetSQLLenAttribute(int AAttr, int AValue);
	void __fastcall SetSQLULenAttribute(int AAttr, int AValue);
#else /* _WIN64 */
	void __fastcall SetSQLLenAttribute(int AAttr, __int64 AValue);
	void __fastcall SetSQLULenAttribute(int AAttr, unsigned __int64 AValue);
#endif /* _WIN64 */
	void __fastcall SetPSQLULenAttribute(int AAttr, Firedac::Phys::Odbccli::PSQLULen AValue);
	void __fastcall AllocHandle();
	void __fastcall FreeHandle();
	void __fastcall Trace(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High);
	__property bool Tracing = {read=GetTracing, nodefault};
	void __fastcall FilterServerOuput(TODBCConnection* AConn, EODBCNativeException* AExc);
	
public:
	__fastcall TODBCHandle();
	__fastcall TODBCHandle(void * AHandle);
	__fastcall virtual ~TODBCHandle();
	void __fastcall Check(short AStatus);
	__property void * Handle = {read=FHandle};
	__property short HandleType = {read=FHandleType, nodefault};
	__property bool IgnoreErrors = {read=FIgnoreErrors, write=FIgnoreErrors, nodefault};
	__property TODBCLib* Lib = {read=FODBCLib};
	__property TODBCConnection* Connection = {read=GetConnection};
	__property TODBCHandle* Owner = {read=FOwner};
	__property System::TObject* OwningObj = {read=FOwningObj};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCEnvironment : public TODBCHandle
{
	typedef TODBCHandle inherited;
	
private:
	bool __fastcall DoDrivers(System::Word ADirection, /* out */ System::UnicodeString &ADriverDesc, /* out */ System::UnicodeString &ADriverAttr);
	bool __fastcall DoDSNs(System::Word ADirection, /* out */ System::UnicodeString &AServerName, /* out */ System::UnicodeString &ADescription);
	
protected:
	virtual void __fastcall GetNonStrAttribute(int AAttr, void * ApValue);
	virtual void __fastcall GetStrAttribute(int AAttr, /* out */ System::UnicodeString &AValue);
	virtual void __fastcall SetAttribute(int AAttr, void * ApValue, int AType);
	
public:
	__fastcall TODBCEnvironment(TODBCLib* ALib, System::TObject* AOwningObj, int AODBCVer);
	__fastcall TODBCEnvironment(TODBCLib* ALib, void * AHandle, System::TObject* AOwningObj);
	__fastcall virtual ~TODBCEnvironment();
	bool __fastcall DriverFirst(/* out */ System::UnicodeString &ADriverDesc, /* out */ System::UnicodeString &ADriverAttr);
	bool __fastcall DriverNext(/* out */ System::UnicodeString &ADriverDesc, /* out */ System::UnicodeString &ADriverAttr);
	bool __fastcall DSNFirst(/* out */ System::UnicodeString &AServerName, /* out */ System::UnicodeString &ADescription);
	bool __fastcall DSNNext(/* out */ System::UnicodeString &AServerName, /* out */ System::UnicodeString &ADescription);
	void __fastcall GetDrivers(System::Classes::TStrings* AList, bool ADecorate = false);
	void __fastcall GetDSNs(System::Classes::TStrings* AList, bool AWithDescription = false, bool ADecorate = false);
	__property int CONNECTION_POOLING = {read=GetUIntAttribute, write=SetUIntAttribute, index=201, nodefault};
	__property int CP_MATCH = {read=GetUIntAttribute, write=SetUIntAttribute, index=202, nodefault};
	__property int ODBC_VERSION = {read=GetUIntAttribute, write=SetUIntAttribute, index=200, nodefault};
	__property int OUTPUT_NTS = {read=GetIntAttribute, write=SetIntAttribute, index=10001, nodefault};
	__property int APP_UNICODE_TYPE = {read=GetIntAttribute, write=SetIntAttribute, index=1064, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TODBCDriverKind : unsigned int { dkOther, dkSQLSrv, dkSQLNC, dkSQLOdbc, dkFreeTDS, dkSQLSrvOther, dkDB2, dkMySQL, dkOracleOra, dkOracleMS, dkOracleOther, dkMSAccessJet, dkMSAccessACE, dkFirebird, dkInterbase, dkSQLAnywhere, dkSQLite, dkPostgreSQL, dkAdvantage, dkNexusDB, dkSybaseASE, dkInformix, dkPWMicroFocus, dkDBF, dkSQLBase, dkElevateDB, dkDBISAM, dkSolidDB, dkCache, dkTeradata, dkPervasive, dkDB2_400, dkQuickBooks };

class PASCALIMPLEMENTATION TODBCConnection : public TODBCHandle
{
	typedef TODBCHandle inherited;
	
private:
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	EODBCNativeException* FInfo;
	TODBCParseErrorEvent FOnParseError;
	TODBCGetMaxSizesEvent FOnGetMaxSizes;
	Firedac::Stan::Intf::TFDRDBMSKind FRdbmsKind;
	TODBCDriverKind FDriverKind;
	bool FConnected;
	System::WideChar FDecimalSepPar;
	System::WideChar FDecimalSepCol;
	System::UnicodeString FLastCommandText;
	EODBCNativeExceptionClass FExceptionClass;
	unsigned FTransID;
	System::Word FMaxColumnNameLen;
	unsigned __int64 FDriverVersion;
	unsigned __int64 FDriverODBCVersion;
	unsigned __int64 FDriverEnvVersion;
	bool FMSSQLVariantBinary;
	bool FTracing;
	HIDESBASE bool __fastcall GetTracing();
	System::Word __fastcall GetInfoOptionSmInt(int AInfoType);
	int __fastcall GetInfoOptionUInt(int AInfoType);
#ifndef _WIN64
	int __fastcall GetInfoOptionULen(int AInfoType);
#else /* _WIN64 */
	unsigned __int64 __fastcall GetInfoOptionULen(int AInfoType);
#endif /* _WIN64 */
	System::UnicodeString __fastcall GetInfoOptionStr(int AInfoType);
	System::UnicodeString __fastcall GetKeywords();
	short __fastcall GetInfoBase(System::Word AInfoType, System::UnicodeString &AInfoValue);
	void __fastcall AfterConnect();
	void __fastcall EndTran(short AType);
	int __fastcall GetIsolation();
	void __fastcall SetIsolation(const int AValue);
	
protected:
	virtual void __fastcall GetNonStrAttribute(int AAttr, void * ApValue);
	virtual void __fastcall GetStrAttribute(int AAttr, /* out */ System::UnicodeString &AValue);
	virtual void __fastcall SetAttribute(int AAttr, void * ApValue, int AType);
	void __fastcall GetInfo(System::Word AInfoType, System::UnicodeString &AInfoValue)/* overload */;
#ifdef _WIN64
	void __fastcall GetInfo(System::Word AInfoType, unsigned __int64 &AInfoValue)/* overload */;
#endif /* _WIN64 */
	void __fastcall GetInfo(System::Word AInfoType, int &AInfoValue)/* overload */;
	void __fastcall GetInfo(System::Word AInfoType, System::Word &AInfoValue)/* overload */;
	void __fastcall ClearInfo();
	
public:
	__fastcall TODBCConnection(TODBCEnvironment* AOwner, System::TObject* AOwningObj);
	__fastcall TODBCConnection(TODBCEnvironment* AOwner, void * AHandle, System::TObject* AOwningObj);
	__fastcall virtual ~TODBCConnection();
	System::UnicodeString __fastcall DriverConnect(const System::UnicodeString AConnString, System::Word ADriverCompletion, NativeUInt AParentWnd);
	System::UnicodeString __fastcall Connect(const System::UnicodeString AConnString);
	void __fastcall Disconnect();
	System::Word __fastcall GetFunctions(System::Word AFuncID);
	System::UnicodeString __fastcall EncodeName(const System::UnicodeString ACat, const System::UnicodeString ASch, const System::UnicodeString AObj);
	void __fastcall ListServers(const System::UnicodeString AConnString, System::Classes::TStrings* AList);
	void __fastcall Commit();
	void __fastcall Rollback();
	void __fastcall StartTransaction();
	__property Firedac::Stan::Intf::TFDRDBMSKind RdbmsKind = {read=FRdbmsKind, write=FRdbmsKind, nodefault};
	__property System::WideChar DecimalSepCol = {read=FDecimalSepCol, write=FDecimalSepCol, nodefault};
	__property System::WideChar DecimalSepPar = {read=FDecimalSepPar, write=FDecimalSepPar, nodefault};
	__property bool MSSQLVariantBinary = {read=FMSSQLVariantBinary, write=FMSSQLVariantBinary, nodefault};
	__property unsigned TransID = {read=FTransID, write=FTransID, nodefault};
	__property EODBCNativeExceptionClass ExceptionClass = {read=FExceptionClass, write=FExceptionClass};
	__property EODBCNativeException* Info = {read=FInfo, write=FInfo};
	__property bool Tracing = {read=GetTracing, write=FTracing, nodefault};
	__property Firedac::Stan::Util::TFDEncoder* Encoder = {read=FEncoder};
	__property bool Connected = {read=FConnected, nodefault};
	__property System::UnicodeString LastCommandText = {read=FLastCommandText};
	__property TODBCDriverKind DriverKind = {read=FDriverKind, nodefault};
	__property unsigned __int64 DriverVersion = {read=FDriverVersion};
	__property unsigned __int64 DriverODBCVersion = {read=FDriverODBCVersion};
	__property unsigned __int64 DriverEnvVersion = {read=FDriverEnvVersion};
	__property int ACCESS_MODE = {read=GetUIntAttribute, write=SetUIntAttribute, index=101, nodefault};
	__property int AUTOCOMMIT = {read=GetUIntAttribute, write=SetUIntAttribute, index=102, nodefault};
	__property int CONCURRENCY = {read=GetIntAttribute, write=SetIntAttribute, index=7, nodefault};
	__property System::UnicodeString CURRENT_CATALOG = {read=GetCharAttribute, write=SetCharAttribute, index=109};
	__property int CURSOR_TYPE = {read=GetIntAttribute, write=SetIntAttribute, index=6, nodefault};
	__property int LOGIN_TIMEOUT = {read=GetUIntAttribute, write=SetUIntAttribute, index=103, nodefault};
	__property int TXN_ISOLATION = {read=GetIsolation, write=SetIsolation, nodefault};
	__property int SS_PRESERVE_CURSORS = {read=GetUIntAttribute, write=SetUIntAttribute, index=1204, nodefault};
	__property System::UnicodeString SS_OLDPWD = {read=GetCharAttribute, write=SetCharAttribute, index=1226};
	__property int SS_BROWSE_CONNECT = {read=GetUIntAttribute, write=SetUIntAttribute, index=1241, nodefault};
	__property void * REGISTER_MESSAGE_CALLBACK = {read=GetPtrAttribute, write=SetPtrAttribute, index=1904};
	__property System::Word LONGDATA_COMPAT = {read=GetUSmIntAttribute, write=SetUSmIntAttribute, index=1253, nodefault};
	__property System::Word MAPCHAR = {read=GetUSmIntAttribute, write=SetUSmIntAttribute, index=2546, nodefault};
	__property int DESCRIBE_OUTPUT_LEVEL = {read=GetIntAttribute, write=SetIntAttribute, index=2506, nodefault};
	__property int USE_TRUSTED_CONTEXT = {read=GetUIntAttribute, write=SetUIntAttribute, index=2561, nodefault};
	__property int INFX_LO_AUTOMATIC = {read=GetUIntAttribute, write=SetUIntAttribute, index=2262, nodefault};
	__property int INFX_ODBC_TYPES_ONLY = {read=GetUIntAttribute, write=SetUIntAttribute, index=2257, nodefault};
	__property int INFX_DEFAULT_UDT_FETCH_TYPE = {read=GetUIntAttribute, write=SetUIntAttribute, index=2253, nodefault};
	__property int INFX_IDSISAMERRMSG = {read=GetUIntAttribute, write=SetUIntAttribute, index=2283, nodefault};
	__property int CATALOG_USAGE = {read=GetInfoOptionUInt, index=92, nodefault};
	__property System::UnicodeString CATALOG_NAME_SEPARATOR = {read=GetInfoOptionStr, index=41};
	__property System::Word CATALOG_LOCATION = {read=GetInfoOptionSmInt, index=114, nodefault};
	__property System::UnicodeString CATALOG_TERM = {read=GetInfoOptionStr, index=42};
#ifndef _WIN64
	__property int DRIVER_HENV = {read=GetInfoOptionULen, index=4, nodefault};
#else /* _WIN64 */
	__property unsigned __int64 DRIVER_HENV = {read=GetInfoOptionULen, index=4};
#endif /* _WIN64 */
	__property System::Word FILE_USAGE = {read=GetInfoOptionSmInt, index=84, nodefault};
	__property int GETDATA_EXTENSIONS = {read=GetInfoOptionUInt, index=81, nodefault};
	__property System::Word IDENTIFIER_CASE = {read=GetInfoOptionSmInt, index=28, nodefault};
	__property System::UnicodeString IDENTIFIER_QUOTE_CHAR = {read=GetInfoOptionStr, index=29};
	__property System::Word QUOTED_IDENTIFIER_CASE = {read=GetInfoOptionSmInt, index=93, nodefault};
	__property System::Word MAX_CATALOG_NAME_LEN = {read=GetInfoOptionSmInt, index=34, nodefault};
	__property System::Word MAX_SCHEMA_NAME_LEN = {read=GetInfoOptionSmInt, index=32, nodefault};
	__property System::Word MAX_TABLE_NAME_LEN = {read=GetInfoOptionSmInt, index=35, nodefault};
	__property System::Word MAX_COL_NAME_LEN = {read=FMaxColumnNameLen, nodefault};
	__property System::Word MAX_CONCURRENT_ACTIVITIES = {read=GetInfoOptionSmInt, index=1, nodefault};
	__property System::Word MAX_IDENTIFIER_LEN = {read=GetInfoOptionSmInt, index=10005, nodefault};
	__property System::Word MAX_ROW_SIZE = {read=GetInfoOptionSmInt, index=104, nodefault};
	__property System::UnicodeString MULTIPLE_ACTIVE_TXN = {read=GetInfoOptionStr, index=37};
	__property int SCHEMA_USAGE = {read=GetInfoOptionUInt, index=91, nodefault};
	__property System::Word TXN_CAPABLE = {read=GetInfoOptionSmInt, index=46, nodefault};
	__property int TXN_ISOLATION_OPTION = {read=GetInfoOptionUInt, index=72, nodefault};
	__property System::UnicodeString DM_VER = {read=GetInfoOptionStr, index=171};
	__property System::UnicodeString DM_ODBC_VER = {read=GetInfoOptionStr, index=10};
	__property System::UnicodeString DBMS_NAME = {read=GetInfoOptionStr, index=17};
	__property System::UnicodeString DBMS_VER = {read=GetInfoOptionStr, index=18};
	__property System::UnicodeString DRIVER_NAME = {read=GetInfoOptionStr, index=6};
	__property System::UnicodeString DRIVER_VER = {read=GetInfoOptionStr, index=7};
	__property System::UnicodeString DRIVER_ODBC_VER = {read=GetInfoOptionStr, index=77};
	__property int INTERFACE_CONFORMANCE = {read=GetInfoOptionUInt, index=152, nodefault};
	__property int API_CONFORMANCE = {read=GetInfoOptionUInt, index=9, nodefault};
	__property int PARAM_ARRAY_ROW_COUNTS = {read=GetInfoOptionUInt, index=153, nodefault};
	__property int PARAM_ARRAY_SELECTS = {read=GetInfoOptionUInt, index=154, nodefault};
	__property System::UnicodeString KEYWORDS = {read=GetKeywords};
	__property System::UnicodeString USER_NAME = {read=GetInfoOptionStr, index=47};
	__property System::UnicodeString DATABASE_NAME = {read=GetInfoOptionStr, index=16};
	__property System::Word CURSOR_COMMIT_BEHAVIOR = {read=GetInfoOptionSmInt, index=23, nodefault};
	__property System::Word CURSOR_ROLLBACK_BEHAVIOR = {read=GetInfoOptionSmInt, index=24, nodefault};
	__property System::Word NULL_COLLATION = {read=GetInfoOptionSmInt, index=85, nodefault};
	__property TODBCParseErrorEvent OnParseError = {read=FOnParseError, write=FOnParseError};
	__property TODBCGetMaxSizesEvent OnGetMaxSizes = {read=FOnGetMaxSizes, write=FOnGetMaxSizes};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCSelectItem : public System::TObject
{
	typedef System::TObject inherited;
	
private:
#ifndef _WIN64
	int FColumnSize;
#else /* _WIN64 */
	unsigned __int64 FColumnSize;
#endif /* _WIN64 */
	System::UnicodeString FName;
	short FNullable;
	short FPosition;
	short FScale;
	short FSQLDataType;
	TODBCStatementBase* FStmt;
	System::UnicodeString __fastcall GetStrAttr(int AIndex);
	int __fastcall GetIntAttr(int AIndex);
	int __fastcall GetIntAttrSilent(int AIndex);
	short __fastcall GetSmallintAttr(int AIndex);
	short __fastcall GetSmallintAttrSilent(int AIndex);
	bool __fastcall GetIsFixedLen();
#ifndef _WIN64
	int __fastcall GetROWVER();
#else /* _WIN64 */
	__int64 __fastcall GetROWVER();
#endif /* _WIN64 */
	
public:
	__fastcall TODBCSelectItem(TODBCStatementBase* AOwner, short AColNum);
	__property int AUTO_UNIQUE_VALUE = {read=GetIntAttr, index=11, nodefault};
#ifndef _WIN64
	__property int ColumnSize = {read=FColumnSize, nodefault};
#else /* _WIN64 */
	__property unsigned __int64 ColumnSize = {read=FColumnSize};
#endif /* _WIN64 */
	__property int FIXED_PREC_SCALE = {read=GetIntAttr, index=9, nodefault};
	__property bool IsFixedLen = {read=GetIsFixedLen, nodefault};
	__property System::UnicodeString Name = {read=FName};
	__property short NULLABLE = {read=FNullable, nodefault};
	__property short Position = {read=FPosition, nodefault};
#ifndef _WIN64
	__property int ROWVER = {read=GetROWVER, nodefault};
#else /* _WIN64 */
	__property __int64 ROWVER = {read=GetROWVER};
#endif /* _WIN64 */
	__property short Scale = {read=FScale, nodefault};
	__property int SEARCHABLE = {read=GetIntAttr, index=13, nodefault};
	__property short SQLDataType = {read=FSQLDataType, nodefault};
	__property int UNSIGNED = {read=GetIntAttr, index=8, nodefault};
	__property int UPDATABLE = {read=GetIntAttr, index=10, nodefault};
	__property System::UnicodeString BASE_CATALOG_NAME = {read=GetStrAttr, index=17};
	__property System::UnicodeString BASE_SCHEMA_NAME = {read=GetStrAttr, index=16};
	__property System::UnicodeString BASE_TABLE_NAME = {read=GetStrAttr, index=23};
	__property System::UnicodeString BASE_COLUMN_NAME = {read=GetStrAttr, index=22};
	__property int DATETIME_INTERVAL_PRECISION = {read=GetIntAttrSilent, index=26, nodefault};
	__property short DATETIME_INTERVAL_CODE = {read=GetSmallintAttrSilent, index=1007, nodefault};
	__property short PRECISION = {read=GetSmallintAttr, index=1005, nodefault};
	__property System::UnicodeString TYPE_NAME = {read=GetStrAttr, index=14};
	__property System::UnicodeString XML_SCHEMACOLLECTION_CATALOG_NAME = {read=GetStrAttr, index=1222};
	__property System::UnicodeString XML_SCHEMACOLLECTION_SCHEMA_NAME = {read=GetStrAttr, index=1223};
	__property System::UnicodeString XML_SCHEMACOLLECTION_NAME = {read=GetStrAttr, index=1224};
	__property System::UnicodeString UDT_CATALOG_NAME = {read=GetStrAttr, index=1218};
	__property System::UnicodeString UDT_SCHEMA_NAME = {read=GetStrAttr, index=1219};
	__property System::UnicodeString UDT_TYPE_NAME = {read=GetStrAttr, index=1220};
	__property System::UnicodeString UDT_ASSEMBLY_TYPE_NAME = {read=GetStrAttr, index=1221};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TODBCSelectItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCVariable : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	short FCDataType;
#ifndef _WIN64
	int FColumnSize;
	int FDataSize;
	int FLastDataSize;
#else /* _WIN64 */
	unsigned __int64 FColumnSize;
	__int64 FDataSize;
	__int64 FLastDataSize;
#endif /* _WIN64 */
	void *FLocalBuffer;
#ifndef _WIN64
	int *FLocalBufIndicator;
#else /* _WIN64 */
	__int64 *FLocalBufIndicator;
#endif /* _WIN64 */
	short FParamType;
	short FPosition;
	System::UnicodeString FName;
	int FScale;
	short FSQLDataType;
	short FCVariantSbType;
	TODBCVariableList* FList;
	bool FForceLongData;
	bool FLongData;
	bool FBinded;
	bool FStreamed;
	bool FFlagsUpdated;
	bool FForceLateBinding;
	bool FLateBinding;
	bool FIsParameter;
	bool FIsCurrency;
	bool FMSAccBoolean;
	bool FMSSQLVariantBinary;
	System::_di_IInterface FDataReader;
	System::UnicodeString FDumpLabel;
	TODBCConnection* __fastcall GetConnection();
	TODBCStatementBase* __fastcall GetStatement();
	System::UnicodeString __fastcall GetDumpLabel();
#ifndef _WIN64
	int __fastcall CalcDataSize(int AColumnSize);
#else /* _WIN64 */
	__int64 __fastcall CalcDataSize(unsigned __int64 AColumnSize);
#endif /* _WIN64 */
	void __fastcall VarTypeUnsup(short ACType);
	void __fastcall SetCDataType(const short AValue);
#ifndef _WIN64
	void __fastcall SetDataSize(const int AValue);
#else /* _WIN64 */
	void __fastcall SetDataSize(const __int64 AValue);
#endif /* _WIN64 */
	void __fastcall SetSQLDataType(const short AValue);
	void __fastcall SetForceLongData(const bool AValue);
	void __fastcall SetForceLateBinding(const bool AValue);
#ifndef _WIN64
	Firedac::Phys::Odbccli::PSQLPointer __fastcall AllocLongData(int AIndex, int ASize);
	void __fastcall FreeLongData(int AIndex);
	System::UnicodeString __fastcall GetAsStrings(int AIndex);
	void __fastcall SetColumnSize(const int AValue);
#else /* _WIN64 */
	Firedac::Phys::Odbccli::PSQLPointer __fastcall AllocLongData(unsigned __int64 AIndex, __int64 ASize);
	void __fastcall FreeLongData(unsigned __int64 AIndex);
	System::UnicodeString __fastcall GetAsStrings(unsigned __int64 AIndex);
	void __fastcall SetColumnSize(const unsigned __int64 AValue);
#endif /* _WIN64 */
	void __fastcall SetBindAttributes(int ADescKind);
	
protected:
#ifndef _WIN64
	Firedac::Phys::Odbccli::PSQLPointer __fastcall GetDataInd(int AIndex, /* out */ void * &ApData, /* out */ Firedac::Phys::Odbccli::PSQLLen &ApInd);
	Firedac::Phys::Odbccli::PSQLPointer __fastcall GetDataPtr(int AIndex, /* out */ void * &ApData, /* out */ int &ASize, /* out */ Firedac::Phys::Odbccli::PSQLLen &ApInd);
#else /* _WIN64 */
	Firedac::Phys::Odbccli::PSQLPointer __fastcall GetDataInd(unsigned __int64 AIndex, /* out */ void * &ApData, /* out */ Firedac::Phys::Odbccli::PSQLLen &ApInd);
	Firedac::Phys::Odbccli::PSQLPointer __fastcall GetDataPtr(unsigned __int64 AIndex, /* out */ void * &ApData, /* out */ __int64 &ASize, /* out */ Firedac::Phys::Odbccli::PSQLLen &ApInd);
#endif /* _WIN64 */
	virtual void __fastcall InternalBind() = 0 ;
	virtual System::WideChar __fastcall GetDecimalSeparator() = 0 ;
	virtual __classmethod short __fastcall GetDescriptorType() = 0 ;
	__property void * LocalBuffer = {read=FLocalBuffer, write=FLocalBuffer};
	__property Firedac::Phys::Odbccli::PSQLLen LocalBufIndicator = {read=FLocalBufIndicator, write=FLocalBufIndicator};
	
public:
	__fastcall TODBCVariable();
	__fastcall virtual ~TODBCVariable();
	void __fastcall UpdateFlags();
	void __fastcall ResetFlagsUpdated();
	void __fastcall Bind();
#ifndef _WIN64
	bool __fastcall GetData(int AIndex, void * &ApData, int &ASize, bool AByRef = false);
	void __fastcall SetData(int AIndex, void * ApData, int ASize);
	void __fastcall SetDataReader(int AIndex, void * ApData);
	System::UnicodeString __fastcall DumpValue(int AIndex, int &ASize)/* overload */;
	System::UnicodeString __fastcall DumpValue(int AIndex)/* overload */;
#else /* _WIN64 */
	bool __fastcall GetData(unsigned __int64 AIndex, void * &ApData, __int64 &ASize, bool AByRef = false);
	void __fastcall SetData(unsigned __int64 AIndex, void * ApData, __int64 ASize);
	void __fastcall SetDataReader(unsigned __int64 AIndex, void * ApData);
	System::UnicodeString __fastcall DumpValue(unsigned __int64 AIndex, __int64 &ASize)/* overload */;
	System::UnicodeString __fastcall DumpValue(unsigned __int64 AIndex)/* overload */;
#endif /* _WIN64 */
	System::UnicodeString __fastcall DumpCDataType();
	System::UnicodeString __fastcall DumpParamType();
	__property TODBCConnection* Connection = {read=GetConnection};
	__property TODBCStatementBase* Statement = {read=GetStatement};
	__property bool Binded = {read=FBinded, nodefault};
	__property bool IsParameter = {read=FIsParameter, nodefault};
	__property short ParamType = {read=FParamType, nodefault};
	__property bool LongData = {read=FLongData, nodefault};
	__property bool LateBinding = {read=FLateBinding, nodefault};
	__property System::WideChar DecimalSeparator = {read=GetDecimalSeparator, nodefault};
	__property short DescriptorType = {read=GetDescriptorType, nodefault};
	__property bool IsCurrency = {read=FIsCurrency, nodefault};
#ifndef _WIN64
	__property System::UnicodeString AsStrings[int AIndex] = {read=GetAsStrings};
#else /* _WIN64 */
	__property System::UnicodeString AsStrings[unsigned __int64 AIndex] = {read=GetAsStrings};
#endif /* _WIN64 */
	__property System::_di_IInterface DataReader = {read=FDataReader};
	__property short SQLDataType = {read=FSQLDataType, write=SetSQLDataType, nodefault};
	__property short CDataType = {read=FCDataType, write=SetCDataType, nodefault};
#ifndef _WIN64
	__property int DataSize = {read=FDataSize, write=SetDataSize, nodefault};
	__property int ColumnSize = {read=FColumnSize, write=SetColumnSize, nodefault};
#else /* _WIN64 */
	__property __int64 DataSize = {read=FDataSize, write=SetDataSize};
	__property unsigned __int64 ColumnSize = {read=FColumnSize, write=SetColumnSize};
#endif /* _WIN64 */
	__property int Scale = {read=FScale, write=FScale, nodefault};
	__property short CVariantSbType = {read=FCVariantSbType, write=FCVariantSbType, nodefault};
	__property short Position = {read=FPosition, write=FPosition, nodefault};
	__property bool ForceLongData = {read=FForceLongData, write=SetForceLongData, nodefault};
	__property bool ForceLateBinding = {read=FForceLateBinding, write=SetForceLateBinding, nodefault};
	__property bool Streamed = {read=FStreamed, write=FStreamed, nodefault};
	__property bool MSAccBoolean = {read=FMSAccBoolean, write=FMSAccBoolean, nodefault};
	__property bool MSSQLVariantBinary = {read=FMSSQLVariantBinary, write=FMSSQLVariantBinary, nodefault};
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::UnicodeString DumpLabel = {read=GetDumpLabel, write=FDumpLabel};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCParameter : public TODBCVariable
{
	typedef TODBCVariable inherited;
	
private:
	TODBCVariableList* FColumnList;
	System::UnicodeString FDataTypeName;
	void __fastcall SetParamType(const short AValue);
	TODBCVariableList* __fastcall GetColumnList();
	
protected:
	virtual void __fastcall InternalBind();
	virtual System::WideChar __fastcall GetDecimalSeparator();
	__classmethod virtual short __fastcall GetDescriptorType();
	
public:
	__fastcall TODBCParameter();
	__fastcall virtual ~TODBCParameter();
	__property ParamType = {write=SetParamType};
	__property TODBCVariableList* ColumnList = {read=GetColumnList};
	__property System::UnicodeString DataTypeName = {read=FDataTypeName, write=FDataTypeName};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCLongDataStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	TODBCParameter* FParam;
	Firedac::Stan::Intf::TFDStreamMode FMode;
#ifndef _WIN64
	int FPosition;
#else /* _WIN64 */
	__int64 FPosition;
#endif /* _WIN64 */
	int FState;
#ifndef _WIN64
	int FSize;
#else /* _WIN64 */
	__int64 FSize;
#endif /* _WIN64 */
	bool FModified;
	void __fastcall CheckMode(Firedac::Stan::Intf::TFDStreamMode AMode, const System::UnicodeString AMsg);
	TODBCCommandStatement* __fastcall GetStmt();
	
protected:
	virtual __int64 __fastcall GetSize();
	
public:
	__fastcall TODBCLongDataStream(TODBCParameter* AParam, Firedac::Stan::Intf::TFDStreamMode AMode);
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	void __fastcall Flush();
	__property TODBCParameter* Param = {read=FParam};
	__property TODBCCommandStatement* Stmt = {read=GetStmt};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TODBCLongDataStream() { }
	
	/* Hoisted overloads: */
	
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
class PASCALIMPLEMENTATION TODBCColumn : public TODBCVariable
{
	typedef TODBCVariable inherited;
	
protected:
	virtual void __fastcall InternalBind();
	virtual System::WideChar __fastcall GetDecimalSeparator();
	__classmethod virtual short __fastcall GetDescriptorType();
	
public:
	__fastcall TODBCColumn();
public:
	/* TODBCVariable.Destroy */ inline __fastcall virtual ~TODBCColumn() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCVariableList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TODBCVariable* operator[](int Index) { return this->Items[Index]; }
	
private:
	System::Classes::TList* FList;
	TODBCStatementBase* FOwner;
	bool FParameters;
	TODBCPageBuffer* FBuffer;
	bool FHasLateBindedVars;
	bool FChildList;
	int __fastcall GetCount();
	TODBCVariable* __fastcall GetItems(int AIndex);
	void __fastcall Rebind(bool AFixedLenOnly = false);
	void __fastcall UpdateHasLateBindedVars();
	
public:
	__fastcall TODBCVariableList(TODBCStatementBase* AOwner, bool AParams, bool AChildList);
	__fastcall virtual ~TODBCVariableList();
	TODBCVariable* __fastcall Add(TODBCVariable* AVar);
#ifndef _WIN64
	void __fastcall Bind(int ARowCount, bool AFixedLenOnly);
#else /* _WIN64 */
	void __fastcall Bind(unsigned __int64 ARowCount, bool AFixedLenOnly);
#endif /* _WIN64 */
	TODBCVariable* __fastcall FindByToken(void * ApToken);
	void __fastcall Clear();
	void __fastcall ResetDataReaders();
	__property int Count = {read=GetCount, nodefault};
	__property TODBCVariable* Items[int Index] = {read=GetItems/*, default*/};
	__property TODBCStatementBase* Owner = {read=FOwner};
	__property bool Parameters = {read=FParameters, nodefault};
	__property bool HasLateBindedVars = {read=FHasLateBindedVars, nodefault};
	__property bool ChildList = {read=FChildList, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCPageBuffer : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<System::Word> _TODBCPageBuffer__1;
	
	typedef System::DynamicArray<System::Word> _TODBCPageBuffer__2;
	
	
private:
	bool FIsAllocated;
#ifndef _WIN64
	int FRowCount;
	int FRowsProcessed;
#else /* _WIN64 */
	unsigned __int64 FRowCount;
	unsigned __int64 FRowsProcessed;
#endif /* _WIN64 */
	_TODBCPageBuffer__1 FRowStatusArr;
	_TODBCPageBuffer__2 FRowOperationArr;
	TODBCVariableList* FVariableList;
#ifndef _WIN64
	int FShifted;
	int __fastcall GetPageSize();
	int __fastcall GetRowSize();
	System::Word __fastcall GetRowStatusArr(int AIndex);
	System::Word __fastcall GetRowOperationArr(int AIndex);
#else /* _WIN64 */
	__int64 FShifted;
	unsigned __int64 __fastcall GetPageSize();
	unsigned __int64 __fastcall GetRowSize();
	System::Word __fastcall GetRowStatusArr(unsigned __int64 AIndex);
	System::Word __fastcall GetRowOperationArr(unsigned __int64 AIndex);
#endif /* _WIN64 */
	
protected:
	void __fastcall SetStmtAttributes();
	void __fastcall AllocBuffers();
	void __fastcall FreeBuffers();
#ifndef _WIN64
	void __fastcall GetDataPtr(TODBCVariable* AVar, int AIndex, /* out */ void * &ApData, /* out */ Firedac::Phys::Odbccli::PSQLLen &ApInd);
	void __fastcall ShiftBuffersPtr(int ARowCount);
#else /* _WIN64 */
	void __fastcall GetDataPtr(TODBCVariable* AVar, unsigned __int64 AIndex, /* out */ void * &ApData, /* out */ Firedac::Phys::Odbccli::PSQLLen &ApInd);
	void __fastcall ShiftBuffersPtr(__int64 ARowCount);
#endif /* _WIN64 */
	void __fastcall UnShift();
#ifndef _WIN64
	void __fastcall SetOperationRange(int ARowCount, int AOffset);
#else /* _WIN64 */
	void __fastcall SetOperationRange(unsigned __int64 ARowCount, unsigned __int64 AOffset);
#endif /* _WIN64 */
	
public:
	__fastcall TODBCPageBuffer(TODBCVariableList* AVarList);
	__fastcall virtual ~TODBCPageBuffer();
#ifndef _WIN64
	__property int Shifted = {read=FShifted, nodefault};
	__property int PageSize = {read=GetPageSize, nodefault};
	__property int RowCount = {read=FRowCount, nodefault};
	__property int RowSize = {read=GetRowSize, nodefault};
	__property int RowsProcessed = {read=FRowsProcessed, nodefault};
	__property System::Word RowStatusArr[int AIndex] = {read=GetRowStatusArr};
	__property System::Word RowOperationArr[int AIndex] = {read=GetRowOperationArr};
#else /* _WIN64 */
	__property __int64 Shifted = {read=FShifted};
	__property unsigned __int64 PageSize = {read=GetPageSize};
	__property unsigned __int64 RowCount = {read=FRowCount};
	__property unsigned __int64 RowSize = {read=GetRowSize};
	__property unsigned __int64 RowsProcessed = {read=FRowsProcessed};
	__property System::Word RowStatusArr[unsigned __int64 AIndex] = {read=GetRowStatusArr};
	__property System::Word RowOperationArr[unsigned __int64 AIndex] = {read=GetRowOperationArr};
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCStatementBase : public TODBCHandle
{
	typedef TODBCHandle inherited;
	
private:
	TODBCVariableList* FColumnList;
	int FMaxStringSize;
	bool FStrsTrim;
	bool FStrsEmpty2Null;
	bool FStrsTrim2Len;
	bool FExecuted;
	bool FNoMoreResults;
	short FResultCols;
	int FPieceBuffLen;
	bool FMoneySupported;
#ifndef _WIN64
	int FQueryTimeout;
#else /* _WIN64 */
	unsigned __int64 FQueryTimeout;
#endif /* _WIN64 */
	bool FRowSetSupported;
#ifndef _WIN64
	short __fastcall GetLongVarPiece(TODBCVariable* AVar, void * ApData, int ASize, Firedac::Phys::Odbccli::PSQLLen ApInd)/* overload */;
	short __fastcall GetLongVarPiece(TODBCVariable* AVar, int AIndex, int ASize)/* overload */;
	bool __fastcall GetLongVarFinished(int ASize, short ARet, int AInd);
#else /* _WIN64 */
	short __fastcall GetLongVarPiece(TODBCVariable* AVar, void * ApData, __int64 ASize, Firedac::Phys::Odbccli::PSQLLen ApInd)/* overload */;
	short __fastcall GetLongVarPiece(TODBCVariable* AVar, int AIndex, __int64 ASize)/* overload */;
	bool __fastcall GetLongVarFinished(__int64 ASize, short ARet, __int64 AInd);
#endif /* _WIN64 */
	void __fastcall GetLongVar(TODBCVariable* AVar, int AIndex);
#ifndef _WIN64
	void __fastcall FetchLateBindedColumns(int AIndex);
#else /* _WIN64 */
	void __fastcall FetchLateBindedColumns(unsigned __int64 AIndex);
#endif /* _WIN64 */
	System::UnicodeString __fastcall GetCursorName();
	void __fastcall SetCursorName(const System::UnicodeString AValue);
#ifndef _WIN64
	void __fastcall DumpColumns(int ARows, bool AEof);
	int __fastcall GetSQLLenDiag(int ARecNo, int ADiagID);
#else /* _WIN64 */
	void __fastcall DumpColumns(unsigned __int64 ARows, bool AEof);
	__int64 __fastcall GetSQLLenDiag(int ARecNo, int ADiagID);
#endif /* _WIN64 */
	int __fastcall GetIntDiag(int ARecNo, int ADiagID);
	System::UnicodeString __fastcall GetStrDiag(int ARecNo, int ADiagID);
	System::Word __fastcall GetUSmallIntDiag(int ARecNo, int ADiagID);
#ifndef _WIN64
	void __fastcall SetQueryTimeout(const int AValue);
	int __fastcall GetQueryTimeout();
#else /* _WIN64 */
	void __fastcall SetQueryTimeout(const unsigned __int64 AValue);
	unsigned __int64 __fastcall GetQueryTimeout();
#endif /* _WIN64 */
	
protected:
#ifndef _WIN64
	void __fastcall ColAttributeInt(System::Word AColNum, System::Word AFieldId, int &AAttr);
	void __fastcall ColAttributeIntSilent(System::Word AColNum, System::Word AFieldId, int &AAttr);
#else /* _WIN64 */
	void __fastcall ColAttributeInt(System::Word AColNum, System::Word AFieldId, __int64 &AAttr);
	void __fastcall ColAttributeIntSilent(System::Word AColNum, System::Word AFieldId, __int64 &AAttr);
#endif /* _WIN64 */
	void __fastcall ColAttributeSmallint(System::Word AColNum, System::Word AFieldId, short &AAttr);
	void __fastcall ColAttributeSmallintSilent(System::Word AColNum, System::Word AFieldId, short &AAttr);
	void __fastcall ColAttributeString(System::Word AColNum, System::Word AFieldId, System::UnicodeString &AAttr);
	virtual void __fastcall GetNonStrAttribute(int AAttr, void * ApValue);
	virtual void __fastcall GetStrAttribute(int AAttr, /* out */ System::UnicodeString &AValue);
	virtual void __fastcall SetAttribute(int AAttr, void * ApValue, int AType);
	
public:
	__fastcall TODBCStatementBase(TODBCConnection* AOwner, System::TObject* AOwningObj);
	__fastcall virtual ~TODBCStatementBase();
	short __fastcall NumResultCols();
	bool __fastcall ResultColsExists();
#ifndef _WIN64
	void __fastcall BindColumns(int ARowCount);
#else /* _WIN64 */
	void __fastcall BindColumns(unsigned __int64 ARowCount);
#endif /* _WIN64 */
	void __fastcall UnbindColumns();
#ifndef _WIN64
	TODBCColumn* __fastcall AddCol(short APos, short ASQLType, short ACType, int ALen = 0x7fffffff);
	int __fastcall Fetch(int ARowCount = 0xffffffff);
#else /* _WIN64 */
	TODBCColumn* __fastcall AddCol(short APos, short ASQLType, short ACType, unsigned __int64 ALen = (unsigned __int64)(0x000000007fffffffULL));
	unsigned __int64 __fastcall Fetch(__int64 ARowCount = (__int64)(-1LL));
#endif /* _WIN64 */
	bool __fastcall MoreResults();
	void __fastcall Cancel();
	void __fastcall Close();
	virtual void __fastcall Unprepare();
	__property TODBCVariableList* ColumnList = {read=FColumnList};
	__property bool Executed = {read=FExecuted, nodefault};
	__property bool NoMoreResults = {read=FNoMoreResults, nodefault};
	__property int MaxStringSize = {read=FMaxStringSize, write=FMaxStringSize, nodefault};
	__property bool StrsTrim = {read=FStrsTrim, write=FStrsTrim, nodefault};
	__property bool StrsEmpty2Null = {read=FStrsEmpty2Null, write=FStrsEmpty2Null, nodefault};
	__property bool StrsTrim2Len = {read=FStrsTrim2Len, write=FStrsTrim2Len, nodefault};
	__property int PieceBuffLen = {read=FPieceBuffLen, write=FPieceBuffLen, nodefault};
	__property bool MoneySupported = {read=FMoneySupported, write=FMoneySupported, nodefault};
	__property bool RowSetSupported = {read=FRowSetSupported, write=FRowSetSupported, nodefault};
#ifndef _WIN64
	__property int CURSOR_TYPE = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=6, nodefault};
#else /* _WIN64 */
	__property unsigned __int64 CURSOR_TYPE = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=6};
#endif /* _WIN64 */
	__property System::UnicodeString CURSOR_NAME = {read=GetCursorName, write=SetCursorName};
#ifndef _WIN64
	__property int CONCURRENCY = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=7, nodefault};
#else /* _WIN64 */
	__property unsigned __int64 CONCURRENCY = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=7};
#endif /* _WIN64 */
	__property void * IMP_PARAM_DESC = {read=GetPSQLPAttribute, index=10013};
#ifndef _WIN64
	__property int MAX_ROWS = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=1, nodefault};
	__property int NOSCAN = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=2, nodefault};
	__property int QUERY_TIMEOUT = {read=GetQueryTimeout, write=SetQueryTimeout, nodefault};
#else /* _WIN64 */
	__property unsigned __int64 MAX_ROWS = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=1};
	__property unsigned __int64 NOSCAN = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=2};
	__property unsigned __int64 QUERY_TIMEOUT = {read=GetQueryTimeout, write=SetQueryTimeout};
#endif /* _WIN64 */
	__property Firedac::Phys::Odbccli::PSQLULen ROWS_FETCHED_PTR = {read=GetPSQLULenAttribute, write=SetPSQLULenAttribute, index=26};
#ifndef _WIN64
	__property int ROW_ARRAY_SIZE = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=27, nodefault};
	__property int ROW_BIND_TYPE = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=5, nodefault};
#else /* _WIN64 */
	__property unsigned __int64 ROW_ARRAY_SIZE = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=27};
	__property unsigned __int64 ROW_BIND_TYPE = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=5};
#endif /* _WIN64 */
	__property Firedac::Phys::Odbccli::PSQLUSmallint ROW_STATUS_PTR = {read=GetPUSmIntAttribute, write=SetPUSmIntAttribute, index=25};
	__property Firedac::Phys::Odbccli::PSQLUSmallint ROW_OPERATION_PTR = {read=GetPUSmIntAttribute, write=SetPUSmIntAttribute, index=24};
#ifndef _WIN64
	__property int SS_NOCOUNT_STATUS = {read=GetSQLLenAttribute, write=SetSQLLenAttribute, index=1231, nodefault};
	__property int SS_CURSOR_OPTIONS = {read=GetSQLLenAttribute, write=SetSQLLenAttribute, index=1230, nodefault};
	__property int SS_QUERYNOTIFICATION_TIMEOUT = {read=GetSQLLenAttribute, write=SetSQLLenAttribute, index=1233, nodefault};
#else /* _WIN64 */
	__property __int64 SS_NOCOUNT_STATUS = {read=GetSQLLenAttribute, write=SetSQLLenAttribute, index=1231};
	__property __int64 SS_CURSOR_OPTIONS = {read=GetSQLLenAttribute, write=SetSQLLenAttribute, index=1230};
	__property __int64 SS_QUERYNOTIFICATION_TIMEOUT = {read=GetSQLLenAttribute, write=SetSQLLenAttribute, index=1233};
#endif /* _WIN64 */
	__property System::UnicodeString SS_QUERYNOTIFICATION_MSGTEXT = {read=GetCharAttribute, write=SetCharAttribute, index=1234};
	__property System::UnicodeString SS_QUERYNOTIFICATION_OPTIONS = {read=GetCharAttribute, write=SetCharAttribute, index=1235};
	__property int INFX_LO_AUTOMATIC = {read=GetUIntAttribute, write=SetUIntAttribute, index=2262, nodefault};
	__property int INFX_ODBC_TYPES_ONLY = {read=GetUIntAttribute, write=SetUIntAttribute, index=2257, nodefault};
	__property int INFX_DEFAULT_UDT_FETCH_TYPE = {read=GetUIntAttribute, write=SetUIntAttribute, index=2253, nodefault};
	__property int TDATA_AGKR = {read=GetUIntAttribute, write=SetUIntAttribute, index=13004, nodefault};
	__property System::UnicodeString DIAG_SQLSTATE[int ARecNo] = {read=GetStrDiag, index=4};
#ifndef _WIN64
	__property int DIAG_ROW_NUMBER[int ARecNo] = {read=GetSQLLenDiag, index=-1248};
#else /* _WIN64 */
	__property __int64 DIAG_ROW_NUMBER[int ARecNo] = {read=GetSQLLenDiag, index=-1248};
#endif /* _WIN64 */
	__property int DIAG_COLUMN_NUMBER[int ARecNo] = {read=GetIntDiag, index=-1247};
	__property System::Word DIAG_SS_LINE[int ARecNo] = {read=GetUSmallIntDiag, index=-1154};
	__property int DIAG_SS_MSGSTATE[int ARecNo] = {read=GetIntDiag, index=-1150};
	__property int DIAG_SS_SEVERITY[int ARecNo] = {read=GetIntDiag, index=-1151};
	__property System::UnicodeString DIAG_SS_PROCNAME[int ARecNo] = {read=GetStrDiag, index=-1153};
	__property System::UnicodeString DIAG_SS_SRVNAME[int ARecNo] = {read=GetStrDiag, index=-1152};
	__property int DIAG_INFX_ISAM_ERROR[int ARecNo] = {read=GetIntDiag, index=13};
public:
	/* TODBCHandle.CreateUsingHandle */ inline __fastcall TODBCStatementBase(void * AHandle) : TODBCHandle(AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCCommandStatement : public TODBCStatementBase
{
	typedef TODBCStatementBase inherited;
	
private:
	TODBCVariableList* FParamList;
	bool FParamSetSupported;
	TODBCParameter* FFocusedParam;
	short FFocusedResult;
	void __fastcall PutBlobParam(TODBCParameter* AParam, int AIndex);
	void __fastcall PutTableParam(TODBCParameter* AParam, int AIndex, bool AFirst);
	void __fastcall PutStreamParam(TODBCParameter* AParam, int AIndex);
	short __fastcall PutLongParams();
	void __fastcall GetStreamParam(TODBCParameter* AParam, int AIndex);
	short __fastcall GetLongParams();
	void __fastcall DumpParameters(bool AInput, int AOffset, int ATimes);
#ifndef _WIN64
	int __fastcall GetPARAMSET_SIZE();
	void __fastcall SetPARAMSET_SIZE(const int AValue);
#else /* _WIN64 */
	unsigned __int64 __fastcall GetPARAMSET_SIZE();
	void __fastcall SetPARAMSET_SIZE(const unsigned __int64 AValue);
#endif /* _WIN64 */
	
public:
	__fastcall TODBCCommandStatement(TODBCConnection* AOwner, System::TObject* AOwningObj);
	__fastcall virtual ~TODBCCommandStatement();
	void __fastcall BindParameters(int ARowCount, bool AFixedLenOnly);
	void __fastcall UnbindParameters();
#ifndef _WIN64
	void __fastcall UpdateRowsAffected(int &ACount);
	void __fastcall Execute(int ARowCount, int AOffset, int &ACount, bool AExact, const System::UnicodeString AExecDirectCommand);
#else /* _WIN64 */
	void __fastcall UpdateRowsAffected(__int64 &ACount);
	void __fastcall Execute(int ARowCount, int AOffset, __int64 &ACount, bool AExact, const System::UnicodeString AExecDirectCommand);
#endif /* _WIN64 */
	void __fastcall FlushLongData();
	void __fastcall Open(int ARowCount, const System::UnicodeString AExecDirectCommand);
	short __fastcall NumParams();
	void __fastcall Prepare(const System::UnicodeString ACommandText);
	virtual void __fastcall Unprepare();
	__property TODBCParameter* FocusedParam = {read=FFocusedParam};
	__property short FocusedResult = {read=FFocusedResult, nodefault};
	__property TODBCVariableList* ParamList = {read=FParamList};
	__property bool ParamSetSupported = {read=FParamSetSupported, write=FParamSetSupported, nodefault};
#ifndef _WIN64
	__property int PARAMSET_SIZE = {read=GetPARAMSET_SIZE, write=SetPARAMSET_SIZE, nodefault};
#else /* _WIN64 */
	__property unsigned __int64 PARAMSET_SIZE = {read=GetPARAMSET_SIZE, write=SetPARAMSET_SIZE};
#endif /* _WIN64 */
	__property Firedac::Phys::Odbccli::PSQLULen PARAMS_PROCESSED_PTR = {read=GetPSQLULenAttribute, write=SetPSQLULenAttribute, index=21};
#ifndef _WIN64
	__property int PARAM_BIND_TYPE = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=18, nodefault};
#else /* _WIN64 */
	__property unsigned __int64 PARAM_BIND_TYPE = {read=GetSQLULenAttribute, write=SetSQLULenAttribute, index=18};
#endif /* _WIN64 */
	__property Firedac::Phys::Odbccli::PSQLUSmallint PARAM_STATUS_PTR = {read=GetPUSmIntAttribute, write=SetPUSmIntAttribute, index=20};
	__property Firedac::Phys::Odbccli::PSQLUSmallint PARAM_OPERATION_PTR = {read=GetPUSmIntAttribute, write=SetPUSmIntAttribute, index=19};
	__property int PARAMOPT_ATOMIC = {read=GetIntAttribute, write=SetIntAttribute, index=1260, nodefault};
	__property int SS_PARAM_FOCUS = {read=GetUIntAttribute, write=SetUIntAttribute, index=1236, nodefault};
public:
	/* TODBCHandle.CreateUsingHandle */ inline __fastcall TODBCCommandStatement(void * AHandle) : TODBCStatementBase(AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TODBCMetaInfoStatement : public TODBCStatementBase
{
	typedef TODBCStatementBase inherited;
	
private:
	int FMode;
	System::UnicodeString FCatalog;
	System::UnicodeString FSchema;
	System::UnicodeString FObject;
	System::UnicodeString FColumn;
	System::UnicodeString FFKCatalog;
	System::UnicodeString FFKSchema;
	System::UnicodeString FFKTable;
	System::Word FIdentifierType;
	System::Word FUnique;
	System::UnicodeString FTableTypes;
	
public:
	void __fastcall Columns(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString AColumn);
	void __fastcall TypeColumns(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString AColumn);
	void __fastcall ForeignKeys(const System::UnicodeString APKCatalog, const System::UnicodeString APKSchema, const System::UnicodeString APKTable, const System::UnicodeString AFKCatalog, const System::UnicodeString AFKSchema, const System::UnicodeString AFKTable);
	void __fastcall PrimaryKeys(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable);
	void __fastcall Procedures(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString AProc);
	void __fastcall ProcedureColumns(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString AProc, const System::UnicodeString AColumn);
	void __fastcall SpecialColumns(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, System::Word AIdentifierType);
	void __fastcall Statistics(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, System::Word AUnique);
	void __fastcall Tables(const System::UnicodeString ACatalog, const System::UnicodeString ASchema, const System::UnicodeString ATable, const System::UnicodeString ATableTypes);
	void __fastcall Catalogs();
	void __fastcall Schemas();
	void __fastcall Execute();
	__property int SS_NAME_SCOPE = {read=GetUIntAttribute, write=SetUIntAttribute, index=1237, nodefault};
public:
	/* TODBCStatementBase.Create */ inline __fastcall TODBCMetaInfoStatement(TODBCConnection* AOwner, System::TObject* AOwningObj) : TODBCStatementBase(AOwner, AOwningObj) { }
	/* TODBCStatementBase.Destroy */ inline __fastcall virtual ~TODBCMetaInfoStatement() { }
	
public:
	/* TODBCHandle.CreateUsingHandle */ inline __fastcall TODBCMetaInfoStatement(void * AHandle) : TODBCStatementBase(AHandle) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 C_DEF_NUM_PREC = System::Int8(0x1f);
static const System::Int8 C_DEF_NUM_SCALE = System::Int8(0x6);
extern DELPHI_PACKAGE void __fastcall ODBCNumeric2BCD(const Firedac::Phys::Odbccli::TSQLNumericRec &ANum, /* out */ Data::Fmtbcd::TBcd &ABcd);
extern DELPHI_PACKAGE void __fastcall ODBCBcd2Numeric(const Data::Fmtbcd::TBcd &ABcd, /* out */ Firedac::Phys::Odbccli::TSQLNumericRec &ANum);
extern DELPHI_PACKAGE void __fastcall ODBCNumeric2Currency(const Firedac::Phys::Odbccli::TSQLNumericRec &ANum, /* out */ System::Currency &ACurr);
extern DELPHI_PACKAGE void __fastcall ODBCCurrency2Numeric(System::Currency ACurr, /* out */ Firedac::Phys::Odbccli::TSQLNumericRec &ANum);
}	/* namespace Odbcwrapper */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ODBCWRAPPER)
using namespace Firedac::Phys::Odbcwrapper;
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
#endif	// Firedac_Phys_OdbcwrapperHPP
