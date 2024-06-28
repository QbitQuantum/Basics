// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.SqlExpr.pas' rev: 34.00 (Android)

#ifndef Data_SqlexprHPP
#define Data_SqlexprHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.DBCommon.hpp>
#include <Data.DBCommonTypes.hpp>
#include <Data.DBXCommon.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Sqlexpr
{
//-- forward type declarations -----------------------------------------------
struct TTransactionDesc;
class DELPHICLASS SPParamDesc;
class DELPHICLASS TSQLBlobStream;
class DELPHICLASS TSQLMonitor;
class DELPHICLASS TTransactionItem;
class DELPHICLASS TConnectionData;
class DELPHICLASS TSQLConnection;
class DELPHICLASS TSQLDataLink;
class DELPHICLASS TFLDDesc;
struct TSQLSchemaInfo;
class DELPHICLASS TCustomSQLDataSet;
class DELPHICLASS TSQLDataSet;
class DELPHICLASS TSQLQuery;
class DELPHICLASS TSQLStoredProc;
class DELPHICLASS TSQLTable;
class DELPHICLASS TSqlServerMethod;
//-- type declarations -------------------------------------------------------
typedef System::Classes::TList TFieldList;

typedef void * TLocale;

#ifndef __aarch64__
typedef int SQLResult;
#else /* __aarch64__ */
typedef long SQLResult;
#endif /* __aarch64__ */

typedef int TLocaleCode;

enum DECLSPEC_DENUM TSQLExceptionType : unsigned char { exceptConnection, exceptCommand, exceptCursor, exceptMetaData, exceptUseLast };

enum DECLSPEC_DENUM TTransIsolationLevel : unsigned char { xilREADCOMMITTED, xilREPEATABLEREAD, xilDIRTYREAD, xilCUSTOM };

#pragma pack(push,1)
struct DECLSPEC_DRECORD TTransactionDesc
{
public:
#ifndef __aarch64__
	unsigned TransactionID;
	unsigned GlobalID;
#else /* __aarch64__ */
	unsigned long TransactionID;
	unsigned long GlobalID;
#endif /* __aarch64__ */
	TTransIsolationLevel IsolationLevel;
#ifndef __aarch64__
	unsigned CustomIsolation;
#else /* __aarch64__ */
	unsigned long CustomIsolation;
#endif /* __aarch64__ */
};
#pragma pack(pop)


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION SPParamDesc : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::Word iParamNum;
	System::UnicodeString szName;
	Data::Db::TParamType iArgType;
	Data::Db::TFieldType iDataType;
	short iUnits1;
	short iUnits2;
#ifndef __aarch64__
	unsigned iLen;
#else /* __aarch64__ */
	unsigned long iLen;
#endif /* __aarch64__ */
public:
	/* TObject.Create */ inline __fastcall SPParamDesc() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~SPParamDesc() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::Generics::Collections::TList__1<SPParamDesc*>* TProcParamList;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSQLBlobStream : public System::Classes::TMemoryStream
{
	typedef System::Classes::TMemoryStream inherited;
	
private:
	TCustomSQLDataSet* FDataSet;
	Data::Db::TBlobField* FField;
	int FFieldNo;
	bool FHasData;
	
protected:
	void __fastcall ReadBlobSize();
	
public:
	__fastcall TSQLBlobStream(Data::Db::TBlobField* Field, Data::Db::TBlobStreamMode Mode);
	__fastcall virtual ~TSQLBlobStream();
	void __fastcall ReadBlobData();
#ifndef __aarch64__
	virtual int __fastcall Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count)/* overload */;
	virtual int __fastcall Read _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (void *Buffer, int Count)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
	virtual long __fastcall Read _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (void *Buffer, long Count)/* overload */;
#endif /* __aarch64__ */
	/* Hoisted overloads: */
	
public:
#ifndef __aarch64__
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
#else /* __aarch64__ */
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
#endif /* __aarch64__ */
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TConnectionUserType : unsigned char { eUserMonitor, eUserDataSet };

typedef void __fastcall (__closure *TTraceEvent)(System::TObject* Sender, const Data::Dbxcommon::TDBXTraceInfo &TraceInfo, bool &LogTrace);

typedef void __fastcall (__closure *TTraceLogEvent)(System::TObject* Sender, const Data::Dbxcommon::TDBXTraceInfo &TraceInfo);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSQLMonitor : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FActive;
	bool FAutoSave;
	System::UnicodeString FFileName;
	bool FKeepConnection;
	int FMaxTraceCount;
	TTraceEvent FOnTrace;
	TTraceLogEvent FOnLogTrace;
	TSQLConnection* FSQLConnection;
	bool FStreamedActive;
	int FTraceFlags;
	System::Classes::TStrings* FTraceList;
	void __fastcall CheckInactive();
	int __fastcall GetTraceCount();
	
protected:
	Data::Dbcommontypes::CBRType __fastcall InvokeCallBack(const Data::Dbxcommon::TDBXTraceInfo &TraceInfo);
	void __fastcall SetActive(bool Value);
	void __fastcall SetSQLConnection(TSQLConnection* Value);
	void __fastcall SetStreamedActive();
	void __fastcall SetTraceList(System::Classes::TStrings* Value);
	void __fastcall SetFileName(const System::UnicodeString Value);
	void __fastcall SwitchConnection(TSQLConnection* const Value);
	virtual void __fastcall Trace(const Data::Dbxcommon::TDBXTraceInfo &TraceInfo, bool LogTrace);
	void __fastcall UpdateTraceCallBack();
	
public:
	__fastcall virtual TSQLMonitor(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSQLMonitor();
	void __fastcall LoadFromFile(System::UnicodeString AFileName);
	void __fastcall SaveToFile(System::UnicodeString AFileName);
	__property int MaxTraceCount = {read=FMaxTraceCount, write=FMaxTraceCount, nodefault};
	__property int TraceCount = {read=GetTraceCount, nodefault};
	
__published:
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property bool AutoSave = {read=FAutoSave, write=FAutoSave, default=0};
	__property System::UnicodeString FileName = {read=FFileName, write=SetFileName};
	__property TTraceLogEvent OnLogTrace = {read=FOnLogTrace, write=FOnLogTrace};
	__property TTraceEvent OnTrace = {read=FOnTrace, write=FOnTrace};
	__property System::Classes::TStrings* TraceList = {read=FTraceList, write=SetTraceList, stored=false};
	__property TSQLConnection* SQLConnection = {read=FSQLConnection, write=SetSQLConnection};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM EConnectFlag : unsigned char { eConnect, eReconnect, eDisconnect };

enum DECLSPEC_DENUM TSchemaType : unsigned char { stNoSchema, stTables, stSysTables, stProcedures, stColumns, stProcedureParams, stIndexes, stPackages, stUserNames };

enum DECLSPEC_DENUM TConnectionState : unsigned char { csStateClosed, csStateOpen, csStateConnecting, csStateExecuting, csStateFetching, csStateDisconnecting };

enum DECLSPEC_DENUM TTableScope : unsigned char { tsSynonym, tsSysTable, tsTable, tsView };

typedef System::Set<TTableScope, TTableScope::tsSynonym, TTableScope::tsView> TTableScopes;

typedef void __fastcall (__closure *TSQLConnectionLoginEvent)(TSQLConnection* Database, System::Classes::TStrings* LoginParams);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TTransactionItem _DEPRECATED_ATTRIBUTE0  : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	Data::Dbxcommon::TDBXTransaction* FTransaction _DEPRECATED_ATTRIBUTE0 ;
	TTransactionDesc FTransactionDesc _DEPRECATED_ATTRIBUTE0 ;
	TTransactionItem* FNext _DEPRECATED_ATTRIBUTE0 ;
public:
	/* TObject.Create */ inline __fastcall TTransactionItem() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTransactionItem() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TConnectionData : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TSQLConnection* FConnection;
	TConnectionData* FParentData;
	Data::Dbxcommon::TDBXProperties* FProperties;
	Data::Dbxcommon::TDBXProperties* FOriginalProperties;
	System::UnicodeString FConnectionName;
	System::UnicodeString FDriverName;
	TConnectionData* FDelegateConnection;
	bool FChanging;
	bool FHasIsModified;
	bool FIsModified;
	void __fastcall DoChange(System::TObject* Sender);
	bool __fastcall IsMyProperty(const System::UnicodeString PropertyName);
	System::UnicodeString __fastcall GetPrefix();
	System::UnicodeString __fastcall GetConnectionName();
	Data::Dbxcommon::TDBXProperties* __fastcall GetProperties();
	void __fastcall SetConnectionName(const System::UnicodeString Value);
	void __fastcall SetProperties(Data::Dbxcommon::TDBXProperties* const Value);
	void __fastcall SetDelegateConnection(TConnectionData* const Value);
	bool __fastcall GetIsModified();
	Data::Dbxcommon::TDBXProperties* __fastcall GetOriginalProperties();
	System::UnicodeString __fastcall GetDriverName();
	void __fastcall SetDriverName(const System::UnicodeString Value);
	
protected:
	void __fastcall GetFullParams(System::Classes::TStrings* Params);
	
public:
	__fastcall TConnectionData(TSQLConnection* AConnection)/* overload */;
	__fastcall TConnectionData(TConnectionData* AParentData)/* overload */;
	void __fastcall UpdateProperties(System::Classes::TStrings* NewProperties);
	void __fastcall AddProperties(System::Classes::TStrings* NewProperties);
	bool __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	void __fastcall ReloadProperties();
	void __fastcall RefreshProperties();
	__fastcall virtual ~TConnectionData();
	
__published:
	__property System::UnicodeString ConnectionName = {read=GetConnectionName, write=SetConnectionName};
	__property System::UnicodeString DriverName = {read=GetDriverName, write=SetDriverName};
	__property Data::Dbxcommon::TDBXProperties* Properties = {read=GetProperties, write=SetProperties};
	__property TConnectionData* DelegateConnection = {read=FDelegateConnection, write=SetDelegateConnection};
	__property bool IsModified = {read=GetIsModified, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSQLConnection : public Data::Db::TCustomConnection
{
	typedef Data::Db::TCustomConnection inherited;
	
private:
	Data::Dbxcommon::TDBXTransaction* __fastcall BeginTransaction(const TTransactionDesc &TransDesc, int Isolation)/* overload */;
	
private:
#ifndef __aarch64__
	unsigned FSelectStatements;
	unsigned FActiveStatements;
#else /* __aarch64__ */
	unsigned long FSelectStatements;
	unsigned long FActiveStatements;
#endif /* __aarch64__ */
	bool FAutoClone;
	TSQLConnection* FCloneParent;
	TConnectionState FConnectionState;
	System::UnicodeString FConnectionName;
	System::UnicodeString FConnectionRegistryFile;
	System::UnicodeString FDriverName;
	System::UnicodeString FGetDriverFunc;
	int FTransactionCount;
	bool FIsCloned;
	Data::Dbxcommon::TDBXConnection* FDBXConnection;
	bool FKeepConnection;
	System::UnicodeString FLibraryName;
	bool FLoadParamsOnConnect;
	System::Generics::Collections::TList__1<TSQLMonitor*>* FMonitorUsers;
	TSQLConnectionLoginEvent FOnLogin;
	System::Classes::TStrings* FParams;
	bool FParamsLoaded;
#ifndef __aarch64__
	unsigned FMaxStmtsPerConn;
#else /* __aarch64__ */
	unsigned long FMaxStmtsPerConn;
#endif /* __aarch64__ */
	System::UnicodeString FQuoteChar;
	System::UnicodeString FProcedureQuoteChar;
	System::UnicodeString FDefaultSchemaName;
	int FRefCount;
	NativeUInt FSQLDllHandle;
	bool FSQLHourGlass;
	System::LongBool FSupportsNestedTrans;
	TTableScopes FTableScope;
	Data::Dbxcommon::TDBXTraceEvent FTraceCallbackEvent;
	System::LongBool FTransactionsSupported;
	System::UnicodeString FVendorLib;
	System::UnicodeString FLoginUsername;
	TTransactionItem* FTransactionStack;
	System::UnicodeString FDefaultSchema;
	TConnectionData* FConnectionData;
	System::UnicodeString FUniqueID;
	Data::Dbxcommon::TValidateCertificate FValidateCertificate;
	void __fastcall CheckActive();
	void __fastcall CheckInactive();
	void __fastcall CheckLoginParams();
	void __fastcall ClearConnectionUsers();
	void __fastcall ClearMonitors();
	void __fastcall FreeSchemaTable(TCustomSQLDataSet* DataSet);
	TSQLConnection* __fastcall GetConnectionForStatement();
	System::UnicodeString __fastcall GetConnectionName();
	int __fastcall GetLocaleCode();
	bool __fastcall GetInTransaction();
	System::UnicodeString __fastcall GetLibraryName();
	void __fastcall GetLoginParams(System::Classes::TStrings* LoginParams);
	System::UnicodeString __fastcall GetQuoteChar();
	System::UnicodeString __fastcall GetVendorLib();
	Data::Dbxcommon::TDBXDatabaseMetaData* __fastcall GetMetaData();
	void __fastcall Login(System::Classes::TStrings* ConnectionProps);
	TCustomSQLDataSet* __fastcall OpenSchemaTable(TSchemaType eKind, System::UnicodeString SInfo, System::UnicodeString SQualifier = System::UnicodeString(), System::UnicodeString SPackage = System::UnicodeString())/* overload */;
	TCustomSQLDataSet* __fastcall OpenSchemaTable(TSchemaType eKind, System::UnicodeString SInfo, System::UnicodeString SQualifier = System::UnicodeString(), System::UnicodeString SPackage = System::UnicodeString(), System::UnicodeString SSchemaName = System::UnicodeString())/* overload */;
	void __fastcall RegisterTraceMonitor(System::TObject* Client);
	void __fastcall RegisterTraceCallback(bool Value);
	void __fastcall SetConnectionName(System::UnicodeString Value);
	void __fastcall SetDriverName(System::UnicodeString Value);
	void __fastcall SetKeepConnection(bool Value);
	void __fastcall SetParams(System::Classes::TStrings* Value);
	void __fastcall SetCursor(int CursorType);
	void __fastcall SetLocaleCode(int Value);
	void __fastcall DoParamsChange(System::TObject* Sender);
	void __fastcall UnregisterTraceMonitor(System::TObject* Client);
	void __fastcall EndFreeAndNilTransaction(Data::Dbxcommon::TDBXTransaction* &Transaction, bool Commit)/* overload */;
	void __fastcall EndAndFreeTransaction(bool Commit)/* overload */;
	void __fastcall EndAndFreeTransaction(const TTransactionDesc &TransDesc, bool Commit)/* overload */;
	void __fastcall ReadUniqueId(System::Classes::TReader* Reader);
	void __fastcall WriteUniqueId(System::Classes::TWriter* Writer);
	void __fastcall ReadGetDriverFunc(System::Classes::TReader* Reader);
	void __fastcall ReadLibraryName(System::Classes::TReader* Reader);
	void __fastcall ReadVendorLib(System::Classes::TReader* Reader);
	__property System::UnicodeString DefaultSchema = {read=FDefaultSchema};
	
protected:
	void __fastcall CheckConnection(EConnectFlag eFlag);
	virtual void __fastcall CheckDisconnect();
	virtual void __fastcall ConnectionOptions();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall DoConnect();
	virtual void __fastcall DoDisconnect();
	virtual bool __fastcall GetConnected();
	HIDESBASE TCustomSQLDataSet* __fastcall GetDataSet(int Index);
	virtual void __fastcall Loaded();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall OpenSchema(TSchemaType eKind, System::UnicodeString sInfo, System::Classes::TStrings* List)/* overload */;
	void __fastcall OpenSchema(TSchemaType eKind, System::UnicodeString sInfo, System::UnicodeString SSchemaName, System::Classes::TStrings* List)/* overload */;
	virtual void __fastcall RegisterClient(System::TObject* Client, Data::Db::TConnectChangeEvent Event = 0x0);
	__property System::UnicodeString ConnectionRegistryFile = {read=FConnectionRegistryFile};
	__property System::UnicodeString QuoteChar = {read=FQuoteChar};
#ifndef __aarch64__
	__property NativeUInt SQLDllHandle = {read=FSQLDllHandle, write=FSQLDllHandle, nodefault};
#else /* __aarch64__ */
	__property NativeUInt SQLDllHandle = {read=FSQLDllHandle, write=FSQLDllHandle};
#endif /* __aarch64__ */
	
public:
	__fastcall virtual TSQLConnection(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSQLConnection();
	void __fastcall AddConnectNotification(System::TObject* Listener, Data::Db::TConnectChangeEvent Event);
	void __fastcall RemoveConnectNotification(System::TObject* Listener);
	TSQLConnection* __fastcall CloneConnection();
	void __fastcall CloseDataSets();
	void __fastcall Commit _DEPRECATED_ATTRIBUTE0 (const TTransactionDesc &TransDesc);
	void __fastcall CommitFreeAndNil(Data::Dbxcommon::TDBXTransaction* &Transaction);
	int __fastcall Execute(const System::UnicodeString SQL, Data::Db::TParams* Params)/* overload */;
	int __fastcall Execute(const System::UnicodeString SQL, Data::Db::TParams* Params, Data::Db::TDataSet* &ResultSet)/* overload */;
	int __fastcall Execute _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (const System::UnicodeString SQL, Data::Db::TParams* Params, void * ResultSet)/* overload */;
	int __fastcall ExecuteDirect(const System::UnicodeString SQL);
	void __fastcall GetFieldNames(const System::UnicodeString TableName, System::Classes::TStrings* List)/* overload */;
	void __fastcall GetFieldNames(const System::UnicodeString TableName, System::UnicodeString SchemaName, System::Classes::TStrings* List)/* overload */;
	void __fastcall GetIndexNames(const System::UnicodeString TableName, System::Classes::TStrings* List)/* overload */;
	void __fastcall GetIndexNames(const System::UnicodeString TableName, const System::UnicodeString SchemaName, System::Classes::TStrings* List)/* overload */;
	void __fastcall GetProcedureNames(System::Classes::TStrings* List)/* overload */;
	void __fastcall GetProcedureNames(const System::UnicodeString PackageName, System::Classes::TStrings* List)/* overload */;
	void __fastcall GetProcedureNames(const System::UnicodeString PackageName, const System::UnicodeString SchemaName, System::Classes::TStrings* List)/* overload */;
	void __fastcall GetPackageNames(System::Classes::TStrings* List)/* overload */;
	void __fastcall GetSchemaNames(System::Classes::TStrings* List)/* overload */;
	void __fastcall GetCommandTypes(System::Classes::TStrings* List);
	void __fastcall GetServerMethodNames(System::Classes::TStrings* List);
	System::UnicodeString __fastcall GetDefaultSchemaName();
	void __fastcall GetProcedureParams(System::UnicodeString ProcedureName, System::Generics::Collections::TList__1<SPParamDesc*>* List)/* overload */;
	void __fastcall GetProcedureParams(System::UnicodeString ProcedureName, System::UnicodeString PackageName, System::Generics::Collections::TList__1<SPParamDesc*>* List)/* overload */;
	void __fastcall GetProcedureParams(System::UnicodeString ProcedureName, System::UnicodeString PackageName, System::UnicodeString SchemaName, System::Generics::Collections::TList__1<SPParamDesc*>* List)/* overload */;
	void __fastcall GetTableNames(System::Classes::TStrings* List, bool SystemTables = false)/* overload */;
	void __fastcall GetTableNames(System::Classes::TStrings* List, System::UnicodeString SchemaName, bool SystemTables = false)/* overload */;
	void __fastcall LoadParamsFromIniFile(System::UnicodeString FFileName = System::UnicodeString());
	void __fastcall Rollback _DEPRECATED_ATTRIBUTE0 (const TTransactionDesc &TransDesc);
	void __fastcall RollbackFreeAndNil(Data::Dbxcommon::TDBXTransaction* &Transaction);
	void __fastcall RollbackIncompleteFreeAndNil(Data::Dbxcommon::TDBXTransaction* &Transaction);
	bool __fastcall HasTransaction(Data::Dbxcommon::TDBXTransaction* Transaction);
	void __fastcall SetTraceEvent(Data::Dbxcommon::TDBXTraceEvent Event);
	Data::Dbxcommon::TDBXTransaction* __fastcall BeginTransaction()/* overload */;
	Data::Dbxcommon::TDBXTransaction* __fastcall BeginTransaction(int Isolation)/* overload */;
	void __fastcall StartTransaction _DEPRECATED_ATTRIBUTE0 (const TTransactionDesc &TransDesc);
	System::UnicodeString __fastcall GetLoginUsername();
#ifndef __aarch64__
	__property unsigned ActiveStatements = {read=FActiveStatements, nodefault};
#else /* __aarch64__ */
	__property unsigned long ActiveStatements = {read=FActiveStatements};
#endif /* __aarch64__ */
	__property bool AutoClone = {read=FAutoClone, write=FAutoClone, default=1};
	__property TConnectionState ConnectionState = {read=FConnectionState, write=FConnectionState, nodefault};
	__property TCustomSQLDataSet* DataSets[int Index] = {read=GetDataSet};
	__property bool InTransaction = {read=GetInTransaction, nodefault};
	__property int LocaleCode = {read=GetLocaleCode, write=SetLocaleCode, default=0};
#ifndef __aarch64__
	__property unsigned MaxStmtsPerConn = {read=FMaxStmtsPerConn, nodefault};
#else /* __aarch64__ */
	__property unsigned long MaxStmtsPerConn = {read=FMaxStmtsPerConn};
#endif /* __aarch64__ */
	__property Data::Dbxcommon::TDBXDatabaseMetaData* MetaData = {read=GetMetaData};
	__property System::LongBool MultipleTransactionsSupported = {read=FSupportsNestedTrans, nodefault};
	__property bool ParamsLoaded = {read=FParamsLoaded, write=FParamsLoaded, nodefault};
	__property Data::Dbxcommon::TDBXConnection* DBXConnection = {read=FDBXConnection};
	__property bool SQLHourGlass = {read=FSQLHourGlass, write=FSQLHourGlass, default=1};
	__property Data::Dbxcommon::TDBXTraceEvent TraceCallbackEvent = {read=FTraceCallbackEvent};
	__property System::LongBool TransactionsSupported = {read=FTransactionsSupported, nodefault};
	__property TConnectionData* ConnectionData = {read=FConnectionData};
	__property System::UnicodeString UniqueID = {read=FUniqueID, write=FUniqueID};
	__property System::UnicodeString GetDriverFunc = {read=FGetDriverFunc, write=FGetDriverFunc};
	__property System::UnicodeString LibraryName = {read=GetLibraryName, write=FLibraryName};
	__property System::UnicodeString VendorLib = {read=GetVendorLib, write=FVendorLib};
	
__published:
	__property System::UnicodeString ConnectionName = {read=GetConnectionName, write=SetConnectionName};
	__property System::UnicodeString DriverName = {read=FDriverName, write=SetDriverName};
	__property bool KeepConnection = {read=FKeepConnection, write=SetKeepConnection, default=1};
	__property bool LoadParamsOnConnect = {read=FLoadParamsOnConnect, write=FLoadParamsOnConnect, default=0};
	__property LoginPrompt = {default=1};
	__property System::Classes::TStrings* Params = {read=FParams, write=SetParams};
	__property TTableScopes TableScope = {read=FTableScope, write=FTableScope, default=12};
	__property Data::Dbxcommon::TValidateCertificate ValidatePeerCertificate = {read=FValidateCertificate, write=FValidateCertificate};
	__property AfterConnect;
	__property AfterDisconnect;
	__property BeforeConnect;
	__property BeforeDisconnect;
	__property TSQLConnectionLoginEvent OnLogin = {read=FOnLogin, write=FOnLogin};
	__property Connected = {default=0};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSQLDataLink : public Data::Db::TDetailDataLink
{
	typedef Data::Db::TDetailDataLink inherited;
	
private:
	TCustomSQLDataSet* FSQLDataSet;
	
protected:
	virtual void __fastcall ActiveChanged();
	virtual void __fastcall CheckBrowseMode();
	virtual Data::Db::TDataSet* __fastcall GetDetailDataSet();
	virtual void __fastcall RecordChanged(Data::Db::TField* Field);
	
public:
	__fastcall TSQLDataLink(TCustomSQLDataSet* ADataSet);
public:
	/* TDataLink.Destroy */ inline __fastcall virtual ~TSQLDataLink() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFLDDesc : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::Word FFldNum;
	System::UnicodeString FName;
	System::Word FFldType;
	System::Word FSubType;
	short FUnits1;
	short FUnits2;
	System::Word FOffset;
#ifndef __aarch64__
	unsigned FLen;
#else /* __aarch64__ */
	unsigned long FLen;
#endif /* __aarch64__ */
	System::Word FNullOffset;
	Data::Dbcommontypes::FLDVchk FFLDVchk;
	Data::Dbcommontypes::FLDRights FFLDRights;
	System::WordBool FCalcField;
	__property System::Word iFldNum = {read=FFldNum, write=FFldNum, nodefault};
	__property System::UnicodeString szName = {read=FName, write=FName};
	__property System::Word iFldType = {read=FFldType, write=FFldType, nodefault};
	__property System::Word iSubType = {read=FSubType, write=FSubType, nodefault};
	__property short iUnits1 = {read=FUnits1, write=FUnits1, nodefault};
	__property short iUnits2 = {read=FUnits2, write=FUnits2, nodefault};
	__property System::Word iOffset = {read=FOffset, write=FOffset, nodefault};
#ifndef __aarch64__
	__property unsigned iLen = {read=FLen, write=FLen, nodefault};
#else /* __aarch64__ */
	__property unsigned long iLen = {read=FLen, write=FLen};
#endif /* __aarch64__ */
	__property System::Word iNullOffset = {read=FNullOffset, write=FNullOffset, nodefault};
	__property Data::Dbcommontypes::FLDVchk efldvVchk = {read=FFLDVchk, write=FFLDVchk, nodefault};
	__property Data::Dbcommontypes::FLDRights efldrRights = {read=FFLDRights, write=FFLDRights, nodefault};
	__property System::WordBool bCalcField = {read=FCalcField, write=FCalcField, nodefault};
public:
	/* TObject.Create */ inline __fastcall TFLDDesc() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFLDDesc() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TSQLSchemaInfo
{
public:
	TSchemaType FType;
	System::UnicodeString ObjectName;
	System::UnicodeString Pattern;
	System::UnicodeString PackageName;
};


typedef System::DynamicArray<TFLDDesc*> TFieldDescList;

typedef void __fastcall (__closure *TParseSqlEvent)(System::Classes::TStrings* &FieldNames, System::UnicodeString SQL, System::UnicodeString &TableName);

typedef void __fastcall (__closure *TParseInsertSqlEvent)(System::Classes::TStrings* &FieldNames, System::UnicodeString SQL, bool &BindAllFields, System::UnicodeString &TableName);

class PASCALIMPLEMENTATION TCustomSQLDataSet : public Data::Db::TDataSet
{
	typedef Data::Db::TDataSet inherited;
	
private:
	System::TArray__1<System::Byte> FFieldBuffer;
	bool FRefreshing;
	
private:
	System::TArray__1<System::Byte> FBlobBuffer;
	System::TArray__1<System::Byte> FCalcFieldsBuffer;
	bool FCheckRowsAffected;
	TSQLConnection* FClonedConnection;
	System::UnicodeString FCommandText;
	Data::Db::TPSCommandType FCommandType;
	System::UnicodeString FDbxCommandType;
	__int64 FCurrentBlobSize;
	Data::Db::TDataLink* FDataLink;
	System::UnicodeString FDesignerData;
	bool FGetNextRecordSet;
	bool FProvidedDBXReader;
	bool FOwnsProvidedDBXReader;
	Data::Db::TIndexDefs* FIndexDefs;
	bool FIndexDefsLoaded;
	int FMaxBlobSize;
#ifndef __aarch64__
	unsigned FMaxColSize;
#else /* __aarch64__ */
	unsigned long FMaxColSize;
#endif /* __aarch64__ */
	System::UnicodeString FNativeCommand;
	bool FGetMetadata;
	bool FNumericMapping;
	bool FParamCheck;
	int FParamCount;
	Data::Db::TParams* FParams;
	bool FPrepared;
	System::Generics::Collections::TList__1<SPParamDesc*>* FProcParams;
	int FRecords;
	int FRowsAffected;
	TSQLSchemaInfo FSchemaInfo;
	TParseSqlEvent FParseSelectSql;
	TParseSqlEvent FParseUpdateSql;
	TParseSqlEvent FParseDeleteSql;
	TParseInsertSqlEvent FParseInsertSql;
	System::UnicodeString FSortFieldNames;
	Data::Dbxcommon::TDBXCommand* FDBXCommand;
	TSQLConnection* FSQLConnection;
	Data::Dbxcommon::TDBXReader* FDBXReader;
	bool FStatementOpen;
	System::UnicodeString FSchemaName;
	bool __fastcall CheckFieldNames(const System::UnicodeString FieldNames);
	void __fastcall CheckConnection(EConnectFlag eFlag);
	virtual System::UnicodeString __fastcall CheckDetail(const System::UnicodeString SQL);
	void __fastcall CheckStatement(bool ForSchema = false);
	bool __fastcall GetCalculatedField(Data::Db::TField* Field, void * Buffer);
	TCustomSQLDataSet* __fastcall GetDataSetFromSQL(System::UnicodeString TableName);
	System::Generics::Collections::TList__1<SPParamDesc*>* __fastcall GetProcParams();
	TSQLConnection* __fastcall GetInternalConnection();
	virtual int __fastcall GetObjectProcParamCount();
	virtual int __fastcall GetParamCount();
	virtual System::UnicodeString __fastcall GetQueryFromType();
	int __fastcall GetRowsAffected();
	System::UnicodeString __fastcall AddMetadataQuotes(System::UnicodeString Identifier, bool StoredProc);
	System::UnicodeString __fastcall QuoteIdentifier(System::UnicodeString Identifier, bool StoredProc);
	void __fastcall InitBuffers();
	void __fastcall LoadFieldDef(System::Word FieldID, TFLDDesc* &FldDesc)/* overload */;
	void __fastcall ReadDesignerData(System::Classes::TReader* Reader);
	void __fastcall RefreshParams();
	virtual void __fastcall SetConnection(TSQLConnection* const Value);
	void __fastcall SetCurrentBlobSize(__int64 Value);
	void __fastcall SetDataSource(Data::Db::TDataSource* Value);
	void __fastcall SetParameters(Data::Db::TParams* const Value);
	void __fastcall SetParamsFromProcedure();
	void __fastcall SetParamsFromServerMethod();
	void __fastcall SetParamsFromSQL(Data::Db::TDataSet* DataSet, bool bFromFields);
	void __fastcall SetPrepared(bool Value);
	virtual void __fastcall SetCommandType(const Data::Db::TSQLCommandType Value);
	virtual void __fastcall SetDbxCommandType(const System::UnicodeString Value);
	void __fastcall WriteDesignerData(System::Classes::TWriter* Writer);
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	void __fastcall SetSchemaOption(System::UnicodeString &ACatalogName, System::UnicodeString &ASchemaName);
	void __fastcall ParseIdentifier(System::UnicodeString Identifier, System::UnicodeString &Catalog, System::UnicodeString &Schema, System::UnicodeString &Name);
	void __fastcall GetParamsOutputParam(Data::Db::TParam* Param, Data::Dbxcommon::TDBXValue* Value);
	void __fastcall GetDataSetOutputParam(Data::Db::TParam* Param, Data::Dbxcommon::TDBXValue* Value);
	bool __fastcall IsDbxCommandTypeStored();
	
protected:
	virtual void __fastcall PSEndTransaction(bool Commit);
	virtual void __fastcall PSExecute();
	virtual int __fastcall PSExecuteStatement(const System::UnicodeString ASQL, Data::Db::TParams* AParams)/* overload */;
	virtual int __fastcall PSExecuteStatement(const System::UnicodeString ASQL, Data::Db::TParams* AParams, Data::Db::TDataSet* &ResultSet)/* overload */;
	virtual int __fastcall PSExecuteStatement _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (const System::UnicodeString ASQL, Data::Db::TParams* AParams, void * ResultSet)/* overload */;
	virtual void __fastcall PSGetAttributes(System::Classes::TList* List);
	virtual Data::Db::TIndexDef* __fastcall PSGetDefaultOrder();
	virtual System::UnicodeString __fastcall PSGetKeyFields();
	virtual System::UnicodeString __fastcall PSGetQuoteChar();
	virtual System::UnicodeString __fastcall PSGetTableName();
	virtual Data::Db::TIndexDefs* __fastcall PSGetIndexDefs(Data::Db::TIndexOptions IndexTypes);
	virtual Data::Db::TParams* __fastcall PSGetParams();
	virtual Data::Db::EUpdateError* __fastcall PSGetUpdateException(System::Sysutils::Exception* E, Data::Db::EUpdateError* Prev);
	virtual bool __fastcall PSInTransaction();
	virtual bool __fastcall PSIsSQLBased();
	virtual bool __fastcall PSIsSQLSupported();
	virtual void __fastcall PSReset();
	virtual void __fastcall PSSetCommandText(const System::UnicodeString ACommandText);
	virtual void __fastcall PSSetParams(Data::Db::TParams* AParams);
	virtual void __fastcall PSStartTransaction();
	virtual bool __fastcall PSUpdateRecord(Data::Db::TUpdateKind UpdateKind, Data::Db::TDataSet* Delta);
	virtual System::UnicodeString __fastcall PSGetCommandText();
	virtual Data::Db::TPSCommandType __fastcall PSGetCommandType();
	virtual void __fastcall InternalClose();
	virtual void __fastcall InternalHandleException();
	virtual void __fastcall InternalInitFieldDefs();
	virtual void __fastcall InternalOpen();
	virtual bool __fastcall IsCursorOpen();
	void __fastcall AddFieldDesc(TFieldDescList FieldDescs, int DescNo, int &FieldID, System::Classes::TBits* RequiredFields, Data::Db::TFieldDefs* FieldDefs);
	void __fastcall AddIndexDefs(TCustomSQLDataSet* SourceDS, System::UnicodeString IndexName = System::UnicodeString());
	void __fastcall CheckPrepareError();
	void __fastcall ClearIndexDefs();
	virtual void __fastcall CloseCursor();
	void __fastcall CloseStatement();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual int __fastcall ExecSQL(bool ExecDirect = false);
	void __fastcall ExecuteStatement();
	void __fastcall FreeReader();
	void __fastcall FreeBuffers();
	void __fastcall InternalFreeCommand();
	void __fastcall FreeCommand();
	virtual bool __fastcall GetCanModify();
	virtual bool __fastcall GetCanRefresh();
	virtual Data::Db::TDataSource* __fastcall GetDataSource();
	void __fastcall GetObjectTypeNames(Data::Db::TFields* Fields);
	void __fastcall GetOutputParams(System::Generics::Collections::TList__1<SPParamDesc*>* AProcParams = (System::Generics::Collections::TList__1<SPParamDesc*>*)(0x0));
	virtual Data::Db::TGetResult __fastcall GetRecord(NativeInt Buffer, Data::Db::TGetMode GetMode, bool DoCheck)/* overload */;
	virtual Data::Db::TGetResult __fastcall GetRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, Data::Db::TGetMode GetMode, bool DoCheck)/* overload */;
	System::UnicodeString __fastcall GetSortFieldNames();
	virtual void __fastcall InitRecord(NativeInt Buffer)/* overload */;
	virtual void __fastcall InitRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer)/* overload */;
	virtual void __fastcall InternalRefresh();
	virtual void __fastcall Loaded();
	bool __fastcall LocateRecord(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options, bool SyncCursor);
	virtual void __fastcall OpenCursor(bool InfoQuery);
	virtual void __fastcall OpenSchema();
	void __fastcall PropertyChanged();
	virtual void __fastcall SetBufListSize(int Value);
	virtual void __fastcall SetCommandText(const System::UnicodeString Value);
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer)/* overload */;
	virtual void __fastcall SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer)/* overload */;
	void __fastcall SetParamsFromCursor();
	void __fastcall SetSortFieldNames(System::UnicodeString Value);
	virtual void __fastcall UpdateIndexDefs();
	__property System::TArray__1<System::Byte> BlobBuffer = {read=FBlobBuffer, write=FBlobBuffer};
	__property __int64 CurrentBlobSize = {read=FCurrentBlobSize, write=SetCurrentBlobSize};
	__property Data::Db::TDataLink* DataLink = {read=FDataLink};
	__property TSQLConnection* InternalConnection = {read=GetInternalConnection};
	__property System::UnicodeString NativeCommand = {read=FNativeCommand, write=FNativeCommand};
	__property System::Generics::Collections::TList__1<SPParamDesc*>* ProcParams = {read=GetProcParams, write=FProcParams};
	__property int RowsAffected = {read=GetRowsAffected, nodefault};
	void __fastcall SetMaxBlobSize(int MaxSize);
	void __fastcall SetFCommandText(const System::UnicodeString Value);
	__property int ParamCount = {read=GetParamCount, nodefault};
	__property TSQLSchemaInfo SchemaInfo = {read=FSchemaInfo, write=FSchemaInfo};
	__property Data::Db::TSQLCommandType CommandType = {read=FCommandType, write=SetCommandType, default=1};
	__property System::UnicodeString DbxCommandType = {read=FDbxCommandType, write=SetDbxCommandType, stored=IsDbxCommandTypeStored};
	__property Data::Db::TDataSource* DataSource = {read=GetDataSource, write=SetDataSource};
	__property int MaxBlobSize = {read=FMaxBlobSize, write=SetMaxBlobSize, default=0};
	virtual int __fastcall GetRecordCount();
	__property Data::Db::TParams* Params = {read=FParams, write=SetParameters};
	__property bool ParamCheck = {read=FParamCheck, write=FParamCheck, default=1};
	__property System::UnicodeString SortFieldNames = {read=GetSortFieldNames, write=SetSortFieldNames};
	
public:
	__fastcall virtual TCustomSQLDataSet(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall TCustomSQLDataSet(System::Classes::TComponent* AOwner, Data::Dbxcommon::TDBXReader* DBXReader, bool AOwnsInstance)/* overload */;
	__fastcall virtual ~TCustomSQLDataSet();
	__property System::UnicodeString CommandText = {read=FCommandText, write=SetCommandText};
	virtual System::Classes::TStream* __fastcall CreateBlobStream(Data::Db::TField* Field, Data::Db::TBlobStreamMode Mode);
	virtual int __fastcall GetBlobFieldData(int FieldNo, System::TArray__1<System::Byte> &Buffer);
	void __fastcall GetCommandNames(System::Classes::TStrings* List);
	virtual void __fastcall GetDetailLinkFields(System::Generics::Collections::TList__1<Data::Db::TField*>* MasterFields, System::Generics::Collections::TList__1<Data::Db::TField*>* DetailFields)/* overload */;
	virtual bool __fastcall GetFieldData(int FieldNo, System::TArray__1<System::Byte> &Buffer)/* overload */;
	virtual bool __fastcall GetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> &Buffer)/* overload */;
	virtual void __fastcall GetDetailLinkFields _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::Classes::TList* MasterFields, System::Classes::TList* DetailFields)/* overload */;
	virtual bool __fastcall GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (int FieldNo, void * Buffer)/* overload */;
	virtual bool __fastcall GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer)/* overload */;
	int __fastcall GetKeyFieldNames(System::Classes::TStrings* List);
	virtual System::UnicodeString __fastcall GetQuoteChar();
	Data::Db::TParam* __fastcall ParamByName(const System::UnicodeString Value);
	virtual void __fastcall PrepareStatement();
	__property Data::Db::TIndexDefs* IndexDefs = {read=FIndexDefs, write=FIndexDefs};
	virtual bool __fastcall IsSequenced();
	virtual bool __fastcall Locate(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options);
	virtual System::Variant __fastcall Lookup(const System::UnicodeString KeyFields, const System::Variant &KeyValues, const System::UnicodeString ResultFields);
	void __fastcall SetSchemaInfo(TSchemaType SchemaType, System::UnicodeString SchemaObjectName, System::UnicodeString SchemaPattern, System::UnicodeString PackageName = System::UnicodeString());
	__property bool Prepared = {read=FPrepared, write=SetPrepared, default=0};
	__property System::UnicodeString DesignerData = {read=FDesignerData, write=FDesignerData};
	__property int RecordCount = {read=GetRecordCount, nodefault};
	__property TSQLConnection* SQLConnection = {read=FSQLConnection, write=SetConnection};
	
__published:
	__property TParseSqlEvent ParseSelectSql = {read=FParseSelectSql, write=FParseSelectSql};
	__property TParseSqlEvent ParseDeleteSql = {read=FParseDeleteSql, write=FParseDeleteSql};
	__property TParseSqlEvent ParseUpdateSql = {read=FParseUpdateSql, write=FParseUpdateSql};
	__property TParseInsertSqlEvent ParseInsertSql = {read=FParseInsertSql, write=FParseInsertSql};
	__property System::UnicodeString SchemaName = {read=FSchemaName, write=SetSchemaName};
	__property bool GetMetadata = {read=FGetMetadata, write=FGetMetadata, default=1};
	__property bool NumericMapping = {read=FNumericMapping, write=FNumericMapping, default=0};
	__property ObjectView = {default=0};
	__property BeforeOpen;
	__property AfterOpen;
	__property BeforeClose;
	__property AfterClose;
	__property BeforeScroll;
	__property AfterScroll;
	__property BeforeRefresh;
	__property AfterRefresh;
	__property OnCalcFields;
	__property Active = {default=0};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer, bool NativeFormat){ Data::Db::TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
	inline void __fastcall  SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat){ Data::Db::TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
	
public:
	inline bool __fastcall  GetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> &Buffer, bool NativeFormat){ return Data::Db::TDataSet::GetFieldData(Field, Buffer, NativeFormat); }
	inline bool __fastcall  GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat){ return Data::Db::TDataSet::GetFieldData(Field, Buffer, NativeFormat); }
	
};


class PASCALIMPLEMENTATION TSQLDataSet : public TCustomSQLDataSet
{
	typedef TCustomSQLDataSet inherited;
	
public:
	__fastcall virtual TSQLDataSet(System::Classes::TComponent* AOwner)/* overload */;
	virtual int __fastcall ExecSQL(bool ExecDirect = false);
	
__published:
	__property CommandText = {default=0};
	__property CommandType = {default=1};
	__property DbxCommandType;
	__property DataSource;
	__property MaxBlobSize = {default=0};
	__property ParamCheck = {default=1};
	__property Params;
	__property SortFieldNames = {default=0};
	__property SQLConnection;
public:
	/* TCustomSQLDataSet.Create */ inline __fastcall TSQLDataSet(System::Classes::TComponent* AOwner, Data::Dbxcommon::TDBXReader* DBXReader, bool AOwnsInstance)/* overload */ : TCustomSQLDataSet(AOwner, DBXReader, AOwnsInstance) { }
	/* TCustomSQLDataSet.Destroy */ inline __fastcall virtual ~TSQLDataSet() { }
	
};


class PASCALIMPLEMENTATION TSQLQuery : public TCustomSQLDataSet
{
	typedef TCustomSQLDataSet inherited;
	
private:
	System::Classes::TStrings* FSQL;
	System::UnicodeString FText;
	void __fastcall QueryChanged(System::TObject* Sender);
	void __fastcall SetSQL(System::Classes::TStrings* Value);
	
public:
	__fastcall virtual TSQLQuery(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TSQLQuery();
	virtual int __fastcall ExecSQL(bool ExecDirect = false);
	virtual void __fastcall PrepareStatement();
	__property RowsAffected;
	__property System::UnicodeString Text = {read=FText};
	
__published:
	__property DataSource;
	__property GetMetadata = {default=0};
	__property MaxBlobSize = {default=0};
	__property ParamCheck = {default=1};
	__property Params;
	__property System::Classes::TStrings* SQL = {read=FSQL, write=SetSQL};
	__property SQLConnection;
public:
	/* TCustomSQLDataSet.Create */ inline __fastcall TSQLQuery(System::Classes::TComponent* AOwner, Data::Dbxcommon::TDBXReader* DBXReader, bool AOwnsInstance)/* overload */ : TCustomSQLDataSet(AOwner, DBXReader, AOwnsInstance) { }
	
};


class PASCALIMPLEMENTATION TSQLStoredProc : public TCustomSQLDataSet
{
	typedef TCustomSQLDataSet inherited;
	
private:
	System::UnicodeString FStoredProcName;
	System::UnicodeString FPackageName;
	void __fastcall SetStoredProcName(System::UnicodeString Value);
	void __fastcall SetPackageName(System::UnicodeString Value);
	
public:
	__fastcall virtual TSQLStoredProc(System::Classes::TComponent* AOwner)/* overload */;
	virtual int __fastcall ExecProc();
	TCustomSQLDataSet* __fastcall NextRecordSet();
	virtual void __fastcall PrepareStatement();
	
__published:
	__property MaxBlobSize = {default=0};
	__property ParamCheck = {default=1};
	__property Params;
	__property System::UnicodeString PackageName = {read=FPackageName, write=SetPackageName};
	__property SQLConnection;
	__property System::UnicodeString StoredProcName = {read=FStoredProcName, write=SetStoredProcName};
public:
	/* TCustomSQLDataSet.Create */ inline __fastcall TSQLStoredProc(System::Classes::TComponent* AOwner, Data::Dbxcommon::TDBXReader* DBXReader, bool AOwnsInstance)/* overload */ : TCustomSQLDataSet(AOwner, DBXReader, AOwnsInstance) { }
	/* TCustomSQLDataSet.Destroy */ inline __fastcall virtual ~TSQLStoredProc() { }
	
};


class PASCALIMPLEMENTATION TSQLTable : public TCustomSQLDataSet
{
	typedef TCustomSQLDataSet inherited;
	
private:
	bool FIsDetail;
	System::Generics::Collections::TList__1<Data::Db::TField*>* FIndexFields;
	System::UnicodeString FIndexFieldNames;
	System::UnicodeString FIndexName;
	Data::Db::TMasterDataLink* FMasterLink;
	System::UnicodeString FTableName;
	int FIndexFieldCount;
	void __fastcall AddParamsToQuery();
	System::UnicodeString __fastcall GetMasterFields();
	Data::Db::TField* __fastcall GetIndexField(int Index);
	int __fastcall GetIndexFieldCount();
	int __fastcall RefreshIndexFields();
	void __fastcall SetIndexFieldNames(System::UnicodeString Value);
	void __fastcall SetIndexName(System::UnicodeString Value);
	void __fastcall SetMasterFields(System::UnicodeString Value);
	void __fastcall SetTableName(System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetQueryFromType();
	HIDESBASE void __fastcall SetDataSource(Data::Db::TDataSource* Value);
	
protected:
	virtual void __fastcall OpenCursor(bool InfoQuery);
	void __fastcall SetIndexField(int Index, Data::Db::TField* Value);
	__property Data::Db::TMasterDataLink* MasterLink = {read=FMasterLink};
	
public:
	__fastcall virtual TSQLTable(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TSQLTable();
	void __fastcall DeleteRecords();
	void __fastcall GetIndexNames(System::Classes::TStrings* List);
	virtual void __fastcall PrepareStatement();
	__property Data::Db::TField* IndexFields[int Index] = {read=GetIndexField, write=SetIndexField};
	__property int IndexFieldCount = {read=GetIndexFieldCount, nodefault};
	
__published:
	__property Active = {default=0};
	__property System::UnicodeString IndexFieldNames = {read=FIndexFieldNames, write=SetIndexFieldNames};
	__property System::UnicodeString IndexName = {read=FIndexName, write=SetIndexName};
	__property System::UnicodeString MasterFields = {read=GetMasterFields, write=SetMasterFields};
	__property Data::Db::TDataSource* MasterSource = {read=GetDataSource, write=SetDataSource};
	__property MaxBlobSize = {default=0};
	__property SQLConnection;
	__property System::UnicodeString TableName = {read=FTableName, write=SetTableName};
public:
	/* TCustomSQLDataSet.Create */ inline __fastcall TSQLTable(System::Classes::TComponent* AOwner, Data::Dbxcommon::TDBXReader* DBXReader, bool AOwnsInstance)/* overload */ : TCustomSQLDataSet(AOwner, DBXReader, AOwnsInstance) { }
	
};


class PASCALIMPLEMENTATION TSqlServerMethod : public TCustomSQLDataSet
{
	typedef TCustomSQLDataSet inherited;
	
private:
	System::UnicodeString FServerMethodName;
	void __fastcall SetServerMethodName(System::UnicodeString Value);
	virtual System::UnicodeString __fastcall CheckDetail(const System::UnicodeString SQL);
	
public:
	__fastcall virtual TSqlServerMethod(System::Classes::TComponent* AOwner)/* overload */;
	void __fastcall ExecuteMethod();
	
__published:
	__property GetMetadata = {default=0};
	__property Params;
	__property SQLConnection;
	__property System::UnicodeString ServerMethodName = {read=FServerMethodName, write=SetServerMethodName};
public:
	/* TCustomSQLDataSet.Create */ inline __fastcall TSqlServerMethod(System::Classes::TComponent* AOwner, Data::Dbxcommon::TDBXReader* DBXReader, bool AOwnsInstance)/* overload */ : TCustomSQLDataSet(AOwner, DBXReader, AOwnsInstance) { }
	/* TCustomSQLDataSet.Destroy */ inline __fastcall virtual ~TSqlServerMethod() { }
	
};


#ifndef __aarch64__
typedef int __stdcall (*TGetDriverFunc)(System::WideChar * SVendorLib, System::WideChar * SResourceFile, /* out */ void *Obj);
#else /* __aarch64__ */
typedef long __stdcall (*TGetDriverFunc)(System::WideChar * SVendorLib, System::WideChar * SResourceFile, /* out */ void *Obj);
#endif /* __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 eSQLTable = System::Int8(0x1);
static constexpr System::Int8 eSQLView = System::Int8(0x2);
static constexpr System::Int8 eSQLSystemTable = System::Int8(0x4);
static constexpr System::Int8 eSQLSynonym = System::Int8(0x8);
static constexpr System::Int8 eSQLTempTable = System::Int8(0x10);
static constexpr System::Int8 eSQLLocal = System::Int8(0x20);
static constexpr System::Int8 eSQLProcedure = System::Int8(0x1);
static constexpr System::Int8 eSQLFunction = System::Int8(0x2);
static constexpr System::Int8 eSQLPackage = System::Int8(0x4);
static constexpr System::Int8 eSQLSysProcedure = System::Int8(0x8);
static constexpr System::Int8 eSQLRowId = System::Int8(0x1);
static constexpr System::Int8 eSQLRowVersion = System::Int8(0x2);
static constexpr System::Int8 eSQLAutoIncr = System::Int8(0x4);
static constexpr System::Int8 eSQLDefault = System::Int8(0x8);
static constexpr System::Int8 eSQLNonUnique = System::Int8(0x1);
static constexpr System::Int8 eSQLUnique = System::Int8(0x2);
static constexpr System::Int8 eSQLPrimaryKey = System::Int8(0x4);
#define SSelect u"select"
#define SSelectStar u" select * "
#define SSelectStarFrom u" select * from "
#define SSelectSpaces u" select "
#define SWhere u" where "
#define SAnd u" and "
#define SOrderBy u" order by "
static constexpr System::WideChar SParam = (System::WideChar)(0x3f);
static constexpr System::Int8 DefaultCursor = System::Int8(0x0);
static constexpr System::Int8 HourGlassCursor = System::Int8(-11);
static constexpr System::Int8 DefaultMaxBlobSize = System::Int8(-1);
static constexpr System::Int8 DefaultRowsetSize = System::Int8(0x14);
static constexpr System::Word TErrorMessageSize = System::Word(0x800);
extern DELPHI_PACKAGE Data::Dbcommon::TFieldMap FldTypeMap;
extern DELPHI_PACKAGE System::StaticArray<System::Word, 52> FldSubTypeMap;
extern DELPHI_PACKAGE System::StaticArray<Data::Db::TFieldType, 39> DataTypeMap;
static constexpr System::Int8 SUB_TYPE_MEMO = System::Int8(0x16);
extern DELPHI_PACKAGE System::StaticArray<Data::Db::TFieldType, 15> BlobTypeMap;
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetDriverRegistryFile(bool DesignMode = false);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetConnectionRegistryFile(bool DesignMode = false);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetDisplayDriverName(const System::UnicodeString ADriverName);
extern DELPHI_PACKAGE void __fastcall GetDisplayDriverNames(System::Classes::TStrings* List, bool DesignMode = true);
extern DELPHI_PACKAGE void __fastcall GetDriverNames(System::Classes::TStrings* List, bool DesignMode = true);
extern DELPHI_PACKAGE void __fastcall GetDelegateDriverNames(System::Classes::TStrings* List, bool DesignMode = true);
extern DELPHI_PACKAGE void __fastcall GetConnectionNames(System::Classes::TStrings* List, System::UnicodeString Driver = System::UnicodeString(), bool DesignMode = true);
extern DELPHI_PACKAGE void __fastcall RegisterDriver(const System::UnicodeString DriverName);
extern DELPHI_PACKAGE void __fastcall UnregisterDriver(const System::UnicodeString DriverName);
extern DELPHI_PACKAGE void __fastcall FreeProcParams(System::Generics::Collections::TList__1<SPParamDesc*>* &ProcParams);
extern DELPHI_PACKAGE void __fastcall LoadParamListItems(Data::Db::TParams* Params, System::Generics::Collections::TList__1<SPParamDesc*>* ProcParams);
}	/* namespace Sqlexpr */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_SQLEXPR)
using namespace Data::Sqlexpr;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_SqlexprHPP
