// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Win.ADODB.pas' rev: 34.00 (Windows)

#ifndef Data_Win_AdodbHPP
#define Data_Win_AdodbHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Types.hpp>
#include <System.Variants.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.TypInfo.hpp>
#include <Data.DB.hpp>
#include <Winapi.OleDB.hpp>
#include <Winapi.ADOInt.hpp>
#include <System.Generics.Defaults.hpp>
#include <Data.DBCommonTypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Win
{
namespace Adodb
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EADOError;
class DELPHICLASS TADOConnection;
class DELPHICLASS TRDSConnection;
class DELPHICLASS TParameter;
class DELPHICLASS TParameters;
class DELPHICLASS TADOCommand;
class DELPHICLASS TCustomADODataSet;
class DELPHICLASS TADODataSet;
class DELPHICLASS TADOTable;
class DELPHICLASS TADOQuery;
class DELPHICLASS TADOStoredProc;
class DELPHICLASS TADOBlobStream;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EADOError : public Data::Db::EDatabaseError
{
	typedef Data::Db::EDatabaseError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EADOError(const System::UnicodeString Msg) : Data::Db::EDatabaseError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EADOError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Data::Db::EDatabaseError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EADOError(NativeUInt Ident)/* overload */ : Data::Db::EDatabaseError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EADOError(System::PResStringRec ResStringRec)/* overload */ : Data::Db::EDatabaseError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EADOError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Data::Db::EDatabaseError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EADOError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Data::Db::EDatabaseError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EADOError(const System::UnicodeString Msg, int AHelpContext) : Data::Db::EDatabaseError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EADOError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Data::Db::EDatabaseError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EADOError(NativeUInt Ident, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EADOError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EADOError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EADOError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EADOError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TConnectMode : unsigned char { cmUnknown, cmRead, cmWrite, cmReadWrite, cmShareDenyRead, cmShareDenyWrite, cmShareExclusive, cmShareDenyNone };

enum DECLSPEC_DENUM TConnectOption : unsigned char { coConnectUnspecified, coAsyncConnect };

enum DECLSPEC_DENUM TCursorLocation : unsigned char { clUseServer, clUseClient };

enum DECLSPEC_DENUM TCursorType : unsigned char { ctUnspecified, ctOpenForwardOnly, ctKeyset, ctDynamic, ctStatic };

enum DECLSPEC_DENUM TEventStatus : unsigned char { esOK, esErrorsOccured, esCantDeny, esCancel, esUnwantedEvent };

enum DECLSPEC_DENUM TExecuteOption : unsigned char { eoAsyncExecute, eoAsyncFetch, eoAsyncFetchNonBlocking, eoExecuteNoRecords };

typedef System::Set<TExecuteOption, TExecuteOption::eoAsyncExecute, TExecuteOption::eoExecuteNoRecords> TExecuteOptions;

enum DECLSPEC_DENUM TIsolationLevel : unsigned char { ilUnspecified, ilChaos, ilReadUncommitted, ilBrowse, ilCursorStability, ilReadCommitted, ilRepeatableRead, ilSerializable, ilIsolated };

enum DECLSPEC_DENUM TADOLockType : unsigned char { ltUnspecified, ltReadOnly, ltPessimistic, ltOptimistic, ltBatchOptimistic };

enum DECLSPEC_DENUM TObjectState : unsigned char { stClosed, stOpen, stConnecting, stExecuting, stFetching };

typedef System::Set<TObjectState, TObjectState::stClosed, TObjectState::stFetching> TObjectStates;

enum DECLSPEC_DENUM TSchemaInfo : unsigned char { siAsserts, siCatalogs, siCharacterSets, siCollations, siColumns, siCheckConstraints, siConstraintColumnUsage, siConstraintTableUsage, siKeyColumnUsage, siReferentialConstraints, siTableConstraints, siColumnsDomainUsage, siIndexes, siColumnPrivileges, siTablePrivileges, siUsagePrivileges, siProcedures, siSchemata, siSQLLanguages, siStatistics, siTables, siTranslations, siProviderTypes, siViews, siViewColumnUsage, siViewTableUsage, siProcedureParameters, siForeignKeys, siPrimaryKeys, siProcedureColumns, siDBInfoKeywords, siDBInfoLiterals, siCubes, siDimensions, siHierarchies, siLevels, siMeasures, siProperties, siMembers, siProviderSpecific };

enum DECLSPEC_DENUM TXactAttribute : unsigned char { xaCommitRetaining, xaAbortRetaining };

typedef System::Set<TXactAttribute, TXactAttribute::xaCommitRetaining, TXactAttribute::xaAbortRetaining> TXactAttributes;

typedef void __fastcall (__closure *TBeginTransCompleteEvent)(TADOConnection* Connection, int TransactionLevel, const Winapi::Adoint::_di_Error Error, TEventStatus &EventStatus);

enum DECLSPEC_DENUM TCommandType : unsigned char { cmdUnknown, cmdText, cmdTable, cmdStoredProc, cmdFile, cmdTableDirect };

typedef void __fastcall (__closure *TConnectErrorEvent)(TADOConnection* Connection, const Winapi::Adoint::_di_Error Error, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TDisconnectEvent)(TADOConnection* Connection, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TExecuteCompleteEvent)(TADOConnection* Connection, int RecordsAffected, const Winapi::Adoint::_di_Error Error, TEventStatus &EventStatus, const Winapi::Adoint::_di__Command Command, const Winapi::Adoint::_di__Recordset Recordset);

typedef void __fastcall (__closure *TWillConnectEvent)(TADOConnection* Connection, System::WideString &ConnectionString, System::WideString &UserID, System::WideString &Password, TConnectOption &ConnectOptions, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TWillExecuteEvent)(TADOConnection* Connection, System::WideString &CommandText, TCursorType &CursorType, TADOLockType &LockType, TCommandType &CommandType, TExecuteOptions &ExecuteOptions, TEventStatus &EventStatus, const Winapi::Adoint::_di__Command Command, const Winapi::Adoint::_di__Recordset Recordset);

typedef void __fastcall (__closure *TInfoMessageEvent)(TADOConnection* Connection, const Winapi::Adoint::_di_Error Error, TEventStatus &EventStatus);

class PASCALIMPLEMENTATION TADOConnection : public Data::Db::TCustomConnection
{
	typedef Data::Db::TCustomConnection inherited;
	
private:
	System::Classes::TList* FCommands;
	Winapi::Adoint::_di__Connection FConnectionObject;
	int FConnEventsID;
	System::WideString FConnectionString;
	System::WideString FDefaultDatabase;
	System::WideString FUserID;
	System::WideString FPassword;
	TConnectOption FConnectOptions;
	TIsolationLevel FIsolationLevel;
	int FTransactionLevel;
	bool FKeepConnection;
	TBeginTransCompleteEvent FOnBeginTransComplete;
	TConnectErrorEvent FOnConnectComplete;
	TConnectErrorEvent FOnCommitTransComplete;
	TConnectErrorEvent FOnRollbackTransComplete;
	TDisconnectEvent FOnDisconnect;
	TInfoMessageEvent FOnInfoMessage;
	TWillConnectEvent FOnWillConnect;
	TExecuteCompleteEvent FOnExecuteComplete;
	TWillExecuteEvent FOnWillExecute;
	void __fastcall ClearRefs();
	bool __fastcall IsProviderStored();
	bool __fastcall IsDefaultDatabaseStored();
	TCustomADODataSet* __fastcall GetADODataSet(int Index);
	TXactAttributes __fastcall GetAttributes();
	TADOCommand* __fastcall GetCommand(int Index);
	int __fastcall GetCommandCount();
	int __fastcall GetCommandTimeout();
	System::WideString __fastcall GetConnectionString();
	int __fastcall GetConnectionTimeout();
	TCursorLocation __fastcall GetCursorLocation();
	System::WideString __fastcall GetDefaultDatabase();
	TIsolationLevel __fastcall GetIsolationLevel();
	TConnectMode __fastcall GetMode();
	Winapi::Adoint::_di_Properties __fastcall GetProperties();
	System::WideString __fastcall GetProvider();
	TObjectStates __fastcall GetState();
	System::WideString __fastcall GetVersion();
	void __fastcall SetAttributes(const TXactAttributes Value);
	void __fastcall SetCommandTimeout(const int Value);
	void __fastcall SetConnectionString(const System::WideString Value);
	void __fastcall SetConnectionTimeout(const int Value);
	void __fastcall SetCursorLocation(const TCursorLocation Value);
	void __fastcall SetDefaultDatabase(const System::WideString Value);
	void __fastcall SetIsolationLevel(const TIsolationLevel Value);
	void __fastcall SetMode(const TConnectMode Value);
	void __fastcall SetProvider(const System::WideString Value);
	void __fastcall SetConnectOptions(const TConnectOption Value);
	bool __fastcall GetInTransaction();
	void __fastcall SetConnectionObject(const Winapi::Adoint::_di__Connection Value);
	void __fastcall SetKeepConnection(const bool Value);
	
protected:
	_di_IConnectionPoint __fastcall ConnectionPoint();
	HRESULT __safecall InfoMessage(const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Connection pConnection);
	HRESULT __safecall BeginTransComplete(int TransactionLevel, const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Connection pConnection);
	HRESULT __safecall CommitTransComplete(const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Connection pConnection);
	HRESULT __safecall RollbackTransComplete(const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Connection pConnection);
	HRESULT __safecall WillExecute(System::WideString &Source, Winapi::Activex::TOleEnum &CursorType, Winapi::Activex::TOleEnum &LockType, int &Options, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Command pCommand, const Winapi::Adoint::_di__Recordset pRecordset, const Winapi::Adoint::_di__Connection pConnection);
	HRESULT __safecall ExecuteComplete(int RecordsAffected, const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Command pCommand, const Winapi::Adoint::_di__Recordset pRecordset, const Winapi::Adoint::_di__Connection pConnection);
	HRESULT __safecall WillConnect(System::WideString &ConnectionString, System::WideString &UserID, System::WideString &Password, int &Options, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Connection pConnection);
	HRESULT __safecall ConnectComplete(const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Connection pConnection);
	HRESULT __safecall Disconnect(Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Connection pConnection);
	void __fastcall CheckActive();
	virtual void __fastcall CheckDisconnect();
	void __fastcall CheckInactive();
	virtual void __fastcall DoConnect();
	virtual void __fastcall DoDisconnect();
	virtual bool __fastcall GetConnected();
	Winapi::Adoint::_di_Errors __fastcall GetErrors();
	virtual void __fastcall Loaded();
	virtual void __fastcall RegisterClient(System::TObject* Client, Data::Db::TConnectChangeEvent Event = 0x0);
	virtual void __fastcall UnRegisterClient(System::TObject* Client);
	virtual void __fastcall WaitForConnectComplete();
	
public:
	__fastcall virtual TADOConnection(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TADOConnection();
	int __fastcall BeginTrans();
	void __fastcall Cancel();
	void __fastcall CommitTrans();
	void __fastcall Execute(const System::WideString CommandText, int &RecordsAffected, const TExecuteOptions ExecuteOptions = (TExecuteOptions() << TExecuteOption::eoExecuteNoRecords ))/* overload */;
	Winapi::Adoint::_di__Recordset __fastcall Execute(const System::WideString CommandText, const TCommandType CommandType = (TCommandType)(0x1), const TExecuteOptions ExecuteOptions = TExecuteOptions() )/* overload */;
	void __fastcall GetProcedureNames(System::Classes::TStrings* List);
	void __fastcall GetFieldNames(const System::UnicodeString TableName, System::Classes::TStrings* List);
	void __fastcall GetTableNames(System::Classes::TStrings* List, bool SystemTables = false);
	HIDESBASE void __fastcall Open(const System::WideString UserID, const System::WideString Password)/* overload */;
	void __fastcall OpenSchema(const TSchemaInfo Schema, const System::OleVariant &Restrictions, const System::OleVariant &SchemaID, TADODataSet* DataSet);
	void __fastcall RollbackTrans();
	__property Winapi::Adoint::_di__Connection ConnectionObject = {read=FConnectionObject, write=SetConnectionObject};
	__property int CommandCount = {read=GetCommandCount, nodefault};
	__property TADOCommand* Commands[int Index] = {read=GetCommand};
	__property TCustomADODataSet* DataSets[int Index] = {read=GetADODataSet};
	__property Winapi::Adoint::_di_Errors Errors = {read=GetErrors};
	__property bool InTransaction = {read=GetInTransaction, nodefault};
	__property Winapi::Adoint::_di_Properties Properties = {read=GetProperties};
	__property TObjectStates State = {read=GetState, nodefault};
	__property System::WideString Version = {read=GetVersion};
	
__published:
	__property TXactAttributes Attributes = {read=GetAttributes, write=SetAttributes, default=0};
	__property int CommandTimeout = {read=GetCommandTimeout, write=SetCommandTimeout, default=30};
	__property Connected = {default=0};
	__property System::WideString ConnectionString = {read=GetConnectionString, write=SetConnectionString};
	__property int ConnectionTimeout = {read=GetConnectionTimeout, write=SetConnectionTimeout, default=15};
	__property TConnectOption ConnectOptions = {read=FConnectOptions, write=SetConnectOptions, default=0};
	__property TCursorLocation CursorLocation = {read=GetCursorLocation, write=SetCursorLocation, default=1};
	__property System::WideString DefaultDatabase = {read=GetDefaultDatabase, write=SetDefaultDatabase, stored=IsDefaultDatabaseStored};
	__property TIsolationLevel IsolationLevel = {read=GetIsolationLevel, write=SetIsolationLevel, default=4};
	__property bool KeepConnection = {read=FKeepConnection, write=SetKeepConnection, default=1};
	__property LoginPrompt = {default=1};
	__property TConnectMode Mode = {read=GetMode, write=SetMode, default=0};
	__property System::WideString Provider = {read=GetProvider, write=SetProvider, stored=IsProviderStored};
	__property AfterConnect;
	__property BeforeConnect;
	__property AfterDisconnect;
	__property BeforeDisconnect;
	__property TDisconnectEvent OnDisconnect = {read=FOnDisconnect, write=FOnDisconnect};
	__property TInfoMessageEvent OnInfoMessage = {read=FOnInfoMessage, write=FOnInfoMessage};
	__property TBeginTransCompleteEvent OnBeginTransComplete = {read=FOnBeginTransComplete, write=FOnBeginTransComplete};
	__property TConnectErrorEvent OnCommitTransComplete = {read=FOnCommitTransComplete, write=FOnCommitTransComplete};
	__property TConnectErrorEvent OnRollbackTransComplete = {read=FOnRollbackTransComplete, write=FOnRollbackTransComplete};
	__property TConnectErrorEvent OnConnectComplete = {read=FOnConnectComplete, write=FOnConnectComplete};
	__property TWillConnectEvent OnWillConnect = {read=FOnWillConnect, write=FOnWillConnect};
	__property TExecuteCompleteEvent OnExecuteComplete = {read=FOnExecuteComplete, write=FOnExecuteComplete};
	__property TWillExecuteEvent OnWillExecute = {read=FOnWillExecute, write=FOnWillExecute};
	__property OnLogin;
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Open(){ Data::Db::TCustomConnection::Open(); }
	
private:
	void *__ConnectionEventsVt;	// Winapi::Adoint::ConnectionEventsVt 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000402-0000-0010-8000-00AA006D2EA4}
	operator Winapi::Adoint::_di_ConnectionEventsVt()
	{
		Winapi::Adoint::_di_ConnectionEventsVt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Winapi::Adoint::ConnectionEventsVt*(void) { return (Winapi::Adoint::ConnectionEventsVt*)&__ConnectionEventsVt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__ConnectionEventsVt; }
	#endif
	
};


class PASCALIMPLEMENTATION TRDSConnection : public Data::Db::TCustomConnection
{
	typedef Data::Db::TCustomConnection inherited;
	
private:
	Winapi::Adoint::_di_IDataspace FDataSpace;
	System::WideString FComputerName;
	System::WideString FServerName;
	System::OleVariant FAppServer;
	int FInternetTimeout;
	bool FIsAppServer;
	void __fastcall CheckInactive();
	void __fastcall ClearRefs();
	void __fastcall SetServerName(const System::WideString Value);
	void __fastcall SetComputerName(const System::WideString Value);
	
protected:
	virtual void __fastcall DoConnect();
	virtual void __fastcall DoDisconnect();
	virtual bool __fastcall GetConnected();
	
public:
	__fastcall virtual TRDSConnection(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TRDSConnection();
	Winapi::Adoint::_di__Recordset __fastcall GetRecordset(const System::WideString CommandText, System::WideString ConnectionString = System::WideString());
	__property System::OleVariant AppServer = {read=FAppServer};
	__property Winapi::Adoint::_di_IDataspace DataSpaceObject = {read=FDataSpace};
	
__published:
	__property System::WideString ComputerName = {read=FComputerName, write=SetComputerName};
	__property Connected = {default=0};
	__property int InternetTimeout = {read=FInternetTimeout, write=FInternetTimeout, default=0};
	__property System::WideString ServerName = {read=FServerName, write=SetServerName, stored=FIsAppServer};
	__property AfterConnect;
	__property AfterDisconnect;
	__property BeforeConnect;
	__property BeforeDisconnect;
};


typedef Data::Db::TFieldType TDataType;

enum DECLSPEC_DENUM TParameterAttribute : unsigned char { paSigned, paNullable, paLong };

typedef System::Set<TParameterAttribute, TParameterAttribute::paSigned, TParameterAttribute::paLong> TParameterAttributes;

enum DECLSPEC_DENUM TParameterDirection : unsigned char { pdUnknown, pdInput, pdOutput, pdInputOutput, pdReturnValue };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TParameter : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	Winapi::Adoint::_di__Parameter FParameter;
	TParameterAttributes __fastcall GetAttributes();
	Data::Db::TFieldType __fastcall GetDataType();
	System::WideString __fastcall GetName();
	System::Byte __fastcall GetNumericScale();
	Winapi::Adoint::_di__Parameter __fastcall GetParameter();
	TParameterDirection __fastcall GetParameterDirection();
	System::Byte __fastcall GetPrecision();
	Winapi::Adoint::_di_Properties __fastcall GetProperties();
	int __fastcall GetSize();
	System::Variant __fastcall GetValue();
	void __fastcall SetAttributes(const TParameterAttributes Value);
	void __fastcall SetDataType(const Data::Db::TFieldType Value);
	void __fastcall SetName(const System::WideString Value);
	void __fastcall SetNumericScale(const System::Byte Value);
	void __fastcall SetParameterDirection(const TParameterDirection Value);
	void __fastcall SetPrecision(const System::Byte Value);
	void __fastcall SetSize(const int Value);
	void __fastcall SetValue(const System::Variant &Value);
	TParameters* __fastcall GetParameters();
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual System::UnicodeString __fastcall GetDisplayName();
	bool __fastcall IsEqual(TParameter* Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall AppendChunk(const System::OleVariant &Val);
	void __fastcall LoadFromFile(const System::UnicodeString FileName, Data::Db::TFieldType DataType);
	void __fastcall LoadFromStream(System::Classes::TStream* Stream, Data::Db::TFieldType DataType);
	__property Winapi::Adoint::_di__Parameter ParameterObject = {read=GetParameter};
	__property TParameters* Parameters = {read=GetParameters};
	__property Winapi::Adoint::_di_Properties Properties = {read=GetProperties};
	
__published:
	__property System::WideString Name = {read=GetName, write=SetName};
	__property TParameterAttributes Attributes = {read=GetAttributes, write=SetAttributes, default=0};
	__property Data::Db::TFieldType DataType = {read=GetDataType, write=SetDataType, default=0};
	__property TParameterDirection Direction = {read=GetParameterDirection, write=SetParameterDirection, default=1};
	__property System::Byte NumericScale = {read=GetNumericScale, write=SetNumericScale, default=0};
	__property System::Byte Precision = {read=GetPrecision, write=SetPrecision, default=0};
	__property int Size = {read=GetSize, write=SetSize, default=0};
	__property System::Variant Value = {read=GetValue, write=SetValue};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TParameter(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TParameter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<System::Typinfo::PPropInfo> TPropList;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TParameters : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TParameter* operator[](int Index) { return this->Items[Index]; }
	
private:
	bool FModified;
	TADOCommand* __fastcall GetCommand();
	HIDESBASE TParameter* __fastcall GetItem(int Index);
	Winapi::Adoint::_di_Parameters __fastcall GetParamCollection();
	System::Variant __fastcall GetParamValue(const System::WideString ParamName);
	HIDESBASE void __fastcall SetItem(int Index, TParameter* const Value);
	void __fastcall SetParamValue(const System::WideString ParamName, const System::Variant &Value);
	
protected:
	Winapi::Adoint::_di__Parameter __fastcall Create_Parameter(const System::WideString Name, Data::Db::TFieldType DataType, TParameterDirection Direction = (TParameterDirection)(0x1), int Size = 0x0);
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	bool __fastcall InternalRefresh();
	void __fastcall AppendParameters();
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	__property bool Modified = {read=FModified, nodefault};
	
public:
	TParameter* __fastcall AddParameter();
	void __fastcall AssignValues(TParameters* Value);
	TParameter* __fastcall CreateParameter(const System::WideString Name, Data::Db::TFieldType DataType, TParameterDirection Direction, int Size, const System::OleVariant &Value);
	TParameter* __fastcall FindParam(const System::WideString Value);
	void __fastcall GetParamList(System::Classes::TList* List, const System::WideString ParamNames);
	bool __fastcall IsEqual(TParameters* Value);
	TParameter* __fastcall ParamByName(const System::WideString Value);
	System::WideString __fastcall ParseSQL(const System::WideString SQL, bool DoCreate);
	bool __fastcall Refresh();
	__property System::Variant ParamValues[const System::WideString ParamName] = {read=GetParamValue, write=SetParamValue};
	__property TADOCommand* Command = {read=GetCommand};
	__property TParameter* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
	__property Winapi::Adoint::_di_Parameters ParameterCollection = {read=GetParamCollection};
public:
	/* TOwnedCollection.Create */ inline __fastcall TParameters(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TParameters() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TADOCommand : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Winapi::Adoint::_di__Command FCommandObject;
	TADOConnection* FConnection;
	System::WideString FConnectionString;
	System::WideString FCommandText;
	System::UnicodeString FCommandTextAlias;
	System::Classes::TComponent* FComponentRef;
	TExecuteOptions FExecuteOptions;
	TParameters* FParameters;
	System::Set<System::Int8, 1, 8> FConnectionFlags;
	bool FParamCheck;
	int __fastcall GetCommandTimeOut();
	TCommandType __fastcall GetCommandType();
	System::WordBool __fastcall GetPrepared();
	Winapi::Adoint::_di_Properties __fastcall GetProperties();
	TObjectStates __fastcall GetState();
	void __fastcall SetCommandTimeOut(const int Value);
	void __fastcall SetCommandType(const TCommandType Value);
	void __fastcall SetConnection(TADOConnection* const Value);
	void __fastcall SetConnectionString(const System::WideString Value);
	void __fastcall SetParameters(TParameters* const Value);
	void __fastcall SetPrepared(const System::WordBool Value);
	Winapi::Adoint::_di__Connection __fastcall GetActiveConnection();
	
protected:
	void __fastcall AssignCommandText(const System::WideString Value, bool Loading = false);
	void __fastcall CheckCommandText();
	void __fastcall ClearActiveConnection();
	bool __fastcall ComponentLoading();
	void __fastcall ConnectionStateChange(System::TObject* Sender, bool Connecting);
	virtual void __fastcall Initialize(bool DoAppend = true);
	virtual void __fastcall OpenConnection();
	virtual void __fastcall SetCommandText(const System::WideString Value);
	virtual bool __fastcall SetConnectionFlag(int Flag, bool Value);
	__property Winapi::Adoint::_di__Connection ActiveConnection = {read=GetActiveConnection};
	__property System::UnicodeString CommandTextAlias = {read=FCommandTextAlias, write=FCommandTextAlias};
	__property System::Classes::TComponent* ComponentRef = {read=FComponentRef, write=FComponentRef};
	
public:
	__fastcall virtual TADOCommand(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TADOCommand();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall Cancel();
	Winapi::Adoint::_di__Recordset __fastcall Execute()/* overload */;
	Winapi::Adoint::_di__Recordset __fastcall Execute(const System::OleVariant &Parameters)/* overload */;
	Winapi::Adoint::_di__Recordset __fastcall Execute(int &RecordsAffected, const System::OleVariant &Parameters)/* overload */;
	__property Winapi::Adoint::_di__Command CommandObject = {read=FCommandObject};
	__property Winapi::Adoint::_di_Properties Properties = {read=GetProperties};
	__property TObjectStates States = {read=GetState, nodefault};
	
__published:
	__property System::WideString CommandText = {read=FCommandText, write=SetCommandText};
	__property int CommandTimeout = {read=GetCommandTimeOut, write=SetCommandTimeOut, default=30};
	__property TCommandType CommandType = {read=GetCommandType, write=SetCommandType, default=1};
	__property TADOConnection* Connection = {read=FConnection, write=SetConnection};
	__property System::WideString ConnectionString = {read=FConnectionString, write=SetConnectionString};
	__property TExecuteOptions ExecuteOptions = {read=FExecuteOptions, write=FExecuteOptions, default=0};
	__property System::WordBool Prepared = {read=GetPrepared, write=SetPrepared, default=0};
	__property TParameters* Parameters = {read=FParameters, write=SetParameters};
	__property bool ParamCheck = {read=FParamCheck, write=FParamCheck, default=1};
};


enum DECLSPEC_DENUM TCursorOption : unsigned char { coHoldRecords, coMovePrevious, coAddNew, coDelete, coUpdate, coBookmark, coApproxPosition, coUpdateBatch, coResync, coNotify, coFind, coSeek, coIndex };

typedef System::Set<TCursorOption, TCursorOption::coHoldRecords, TCursorOption::coIndex> TCursorOptions;

enum DECLSPEC_DENUM TEventReason : unsigned char { erAddNew, erDelete, erUpdate, erUndoUpdate, erUndoAddNew, erUndoDelete, erRequery, erResynch, erClose, erMove, erFirstChange, erMoveFirst, erMoveNext, erMovePrevious, erMoveLast };

enum DECLSPEC_DENUM TFilterGroup : unsigned char { fgUnassigned, fgNone, fgPendingRecords, fgAffectedRecords, fgFetchedRecords, fgPredicate, fgConflictingRecords };

enum DECLSPEC_DENUM TMarshalOption : unsigned char { moMarshalAll, moMarshalModifiedOnly };

enum DECLSPEC_DENUM TRecordStatus : unsigned char { rsOK, rsNew, rsModified, rsDeleted, rsUnmodified, rsInvalid, rsMultipleChanges, rsPendingChanges, rsCanceled, rsCantRelease, rsConcurrencyViolation, rsIntegrityViolation, rsMaxChangesExceeded, rsObjectOpen, rsOutOfMemory, rsPermissionDenied, rsSchemaViolation, rsDBDeleted };

typedef System::Set<TRecordStatus, TRecordStatus::rsOK, TRecordStatus::rsDBDeleted> TRecordStatusSet;

enum DECLSPEC_DENUM TAffectRecords : unsigned char { arCurrent, arFiltered, arAll, arAllChapters };

enum DECLSPEC_DENUM TPersistFormat : unsigned char { pfADTG, pfXML };

enum DECLSPEC_DENUM TSeekOption : unsigned char { soFirstEQ, soLastEQ, soAfterEQ, soAfter, soBeforeEQ, soBefore };

typedef System::StaticArray<System::OleVariant, 1> TVariantList;

typedef TVariantList *PVariantList;

typedef void __fastcall (__closure *TWillChangeFieldEvent)(TCustomADODataSet* DataSet, const int FieldCount, const System::OleVariant &Fields, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TFieldChangeCompleteEvent)(TCustomADODataSet* DataSet, const int FieldCount, const System::OleVariant &Fields, const Winapi::Adoint::_di_Error Error, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TWillChangeRecordEvent)(TCustomADODataSet* DataSet, const TEventReason Reason, const int RecordCount, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TRecordChangeCompleteEvent)(TCustomADODataSet* DataSet, const TEventReason Reason, const int RecordCount, const Winapi::Adoint::_di_Error Error, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TEndOfRecordsetEvent)(TCustomADODataSet* DataSet, System::WordBool &MoreData, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TFetchProgressEvent)(TCustomADODataSet* DataSet, int Progress, int MaxProgress, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TRecordsetErrorEvent)(TCustomADODataSet* DataSet, const TEventReason Reason, const Winapi::Adoint::_di_Error Error, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TRecordsetReasonEvent)(TCustomADODataSet* DataSet, const TEventReason Reason, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TRecordsetEvent)(TCustomADODataSet* DataSet, const Winapi::Adoint::_di_Error Error, TEventStatus &EventStatus);

typedef void __fastcall (__closure *TRecordsetCreate)(TCustomADODataSet* DataSet, const Winapi::Adoint::_di__Recordset Recordset);

class PASCALIMPLEMENTATION TCustomADODataSet : public Data::Db::TDataSet
{
	typedef Data::Db::TDataSet inherited;
	
private:
	Winapi::Adoint::_di__Recordset FRecordsetObject;
	Winapi::Adoint::_di__Recordset FFindCursor;
	Winapi::Adoint::_di__Recordset FLookupCursor;
	Winapi::Adoint::_di__Recordset FLockCursor;
	Winapi::Oledb::_di_IRowset FRowset;
	Winapi::Oledb::_di_IAccessor FAccessor;
	Winapi::Oledb::_di_IRowsetFind FRowsetFind;
	NativeUInt FHAccessor;
	int FOleRecBufSize;
	int FEventsID;
	TADOCommand* FCommand;
	System::Byte *FFilterBuffer;
	int FRecBufSize;
	int FCacheSize;
	System::UnicodeString FDetailFilter;
	System::UnicodeString FIndexFieldNames;
	int FMaxRecords;
	System::Classes::TList* FModifiedFields;
	int FParentRecNo;
	System::Generics::Collections::TList__1<Data::Db::TField*>* FIndexFields;
	Data::Db::TIndexDefs* FIndexDefs;
	Data::Db::TParams* FParams;
	System::WideString FIndexName;
	System::UnicodeString FDesignerData;
	Data::Db::TMasterDataLink* FMasterDataLink;
	TFilterGroup FFilterGroup;
	TCursorLocation FCursorLocation;
	TCursorType FCursorType;
	TADOLockType FLockType;
	TMarshalOption FMarshalOptions;
	TCommandType FRSCommandType;
	TCustomADODataSet* FParentDataSet;
	void *FBlockReadInfo;
	bool FStoreDefs;
	bool FEnableBCD;
	void *FReserved;
	bool FConnectionChanged;
	TWillChangeFieldEvent FOnWillChangeField;
	TFieldChangeCompleteEvent FOnFieldChangeComplete;
	TWillChangeRecordEvent FOnWillChangeRecord;
	TRecordChangeCompleteEvent FOnRecordChangeComplete;
	TRecordsetReasonEvent FOnWillChangeRecordset;
	TRecordsetErrorEvent FOnRecordsetChangeComplete;
	TRecordsetReasonEvent FOnWillMove;
	TRecordsetErrorEvent FOnMoveComplete;
	TEndOfRecordsetEvent FOnEndOfRecordset;
	TRecordsetEvent FOnFetchComplete;
	TFetchProgressEvent FOnFetchProgress;
	TRecordsetCreate FOnRecordsetCreate;
	int __fastcall GetCacheSize();
	int __fastcall GetCommandTimeout();
	TCommandType __fastcall GetCommandType();
	TADOConnection* __fastcall GetConnection();
	System::WideString __fastcall GetConnectionString();
	TCursorLocation __fastcall GetCursorLocation();
	TCursorType __fastcall GetCursorType();
	TExecuteOptions __fastcall GetExecuteOptions();
	TFilterGroup __fastcall GetFilterGroup();
	Data::Db::TField* __fastcall GetIndexField(int Index);
	int __fastcall GetIndexFieldCount();
	System::UnicodeString __fastcall GetIndexFieldNames();
	System::WideString __fastcall GetIndexName();
	TADOLockType __fastcall GetLockType();
	TMarshalOption __fastcall GetMarshalOptions();
	System::WideString __fastcall GetMasterFields();
	int __fastcall GetMaxRecords();
	bool __fastcall GetParamCheck();
	TParameters* __fastcall GetParameters();
	bool __fastcall GetPrepared();
	Winapi::Adoint::_di_Properties __fastcall GetProperties();
	TObjectStates __fastcall GetRecordsetState();
	TRecordStatusSet __fastcall GetRecordStatus();
	System::WideString __fastcall GetSort();
	void __fastcall PropertyChanged();
	void __fastcall ReadDesignerData(System::Classes::TReader* Reader);
	void __fastcall RefreshIndexFields();
	void __fastcall SetCacheSize(const int Value);
	void __fastcall SetCommandTimeout(const int Value);
	void __fastcall SetCommandType(const TCommandType Value);
	void __fastcall SetConnectionString(const System::WideString Value);
	void __fastcall SetCursorLocation(const TCursorLocation Value);
	void __fastcall SetCursorType(const TCursorType Value);
	void __fastcall SetExecuteOptions(const TExecuteOptions Value);
	void __fastcall SetFilterGroup(const TFilterGroup Value);
	void __fastcall SetIndexField(int Index, Data::Db::TField* const Value);
	void __fastcall SetIndexFieldNames(const System::UnicodeString Value);
	void __fastcall SetIndexName(const System::WideString Value);
	void __fastcall SetLockType(const TADOLockType Value);
	void __fastcall SetMarshalOptions(const TMarshalOption Value);
	void __fastcall SetMasterFields(const System::WideString Value);
	void __fastcall SetMaxRecords(const int Value);
	void __fastcall SetParamCheck(const bool Value);
	void __fastcall SetParameters(TParameters* const Value);
	void __fastcall SetRecordset(const Winapi::Adoint::_di__Recordset Value);
	void __fastcall SetPrepared(const bool Value);
	void __fastcall SetSort(const System::WideString Value);
	void __fastcall WriteDesignerData(System::Classes::TWriter* Writer);
	
protected:
	virtual void __fastcall PSEndTransaction(bool Commit);
	virtual void __fastcall PSExecute();
	virtual int __fastcall PSExecuteStatement(const System::UnicodeString ASQL, Data::Db::TParams* AParams)/* overload */;
	virtual int __fastcall PSExecuteStatement(const System::UnicodeString ASQL, Data::Db::TParams* AParams, Data::Db::TDataSet* &ResultSet)/* overload */;
	virtual int __fastcall PSExecuteStatement _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (const System::UnicodeString ASQL, Data::Db::TParams* AParams, void * ResultSet)/* overload */;
	virtual void __fastcall PSGetAttributes(System::Classes::TList* List);
	virtual Data::Db::TIndexDef* __fastcall PSGetDefaultOrder();
	virtual System::UnicodeString __fastcall PSGetKeyFields();
	virtual Data::Db::TParams* __fastcall PSGetParams();
	virtual System::UnicodeString __fastcall PSGetQuoteChar();
	virtual System::UnicodeString __fastcall PSGetTableName();
	virtual Data::Db::TIndexDefs* __fastcall PSGetIndexDefs(Data::Db::TIndexOptions IndexTypes = (Data::Db::TIndexOptions() << Data::Db::TIndexOption::ixPrimary << Data::Db::TIndexOption::ixUnique << Data::Db::TIndexOption::ixDescending << Data::Db::TIndexOption::ixCaseInsensitive << Data::Db::TIndexOption::ixExpression << Data::Db::TIndexOption::ixNonMaintained ));
	virtual Data::Db::EUpdateError* __fastcall PSGetUpdateException(System::Sysutils::Exception* E, Data::Db::EUpdateError* Prev);
	virtual bool __fastcall PSInTransaction();
	virtual bool __fastcall PSIsSQLBased();
	virtual bool __fastcall PSIsSQLSupported();
	virtual void __fastcall PSReset();
	virtual void __fastcall PSSetParams(Data::Db::TParams* AParams);
	virtual void __fastcall PSSetCommandText(const System::UnicodeString CommandText);
	virtual void __fastcall PSStartTransaction();
	virtual bool __fastcall PSUpdateRecord(Data::Db::TUpdateKind UpdateKind, Data::Db::TDataSet* Delta);
	virtual System::UnicodeString __fastcall PSGetCommandText();
	virtual Data::Db::TPSCommandType __fastcall PSGetCommandType();
	void __fastcall ActivateTextFilter(const System::UnicodeString FilterText);
	virtual System::PByte __fastcall AllocRecordBuffer();
	virtual bool __fastcall AreParamsMasterDependent();
	virtual void __fastcall CheckActive();
	virtual void __fastcall CheckFieldCompatibility(Data::Db::TField* Field, Data::Db::TFieldDef* FieldDef);
	virtual void __fastcall ClearCalcFields(System::PByte Buffer)/* overload */;
	virtual void __fastcall DataEvent(Data::Db::TDataEvent Event, NativeInt Info);
	void __fastcall DeactivateFilters();
	virtual void __fastcall DefChanged(System::TObject* Sender);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall DestroyLookupCursor();
	virtual void __fastcall DoOnNewRecord();
	void __fastcall EnableEvents();
	virtual bool __fastcall FindRecord(bool Restart, bool GoForward);
	virtual void __fastcall FreeRecordBuffer(System::PByte &Buffer);
	bool __fastcall GetActiveRecBuf(System::PByte &RecBuf);
#ifndef _WIN64
	virtual void __fastcall GetBookmarkData(System::PByte Buffer, System::DynamicArray<System::Byte> Data)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall GetBookmarkData(System::PByte Buffer, System::TArray__1<System::Byte> Data)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall GetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, void * Data)/* overload */;
	virtual Data::Db::TBookmarkFlag __fastcall GetBookmarkFlag(System::PByte Buffer)/* overload */;
	virtual Data::Db::TFieldTypes __fastcall GetCalcFieldTypes();
	virtual bool __fastcall GetCanModify();
	System::WideString __fastcall GetCommandText();
	virtual Data::Db::TDataSource* __fastcall GetDataSource();
	virtual int __fastcall GetRecNo();
	virtual Data::Db::TGetResult __fastcall GetRecord(System::PByte Buffer, Data::Db::TGetMode GetMode, bool DoCheck)/* overload */;
	virtual int __fastcall GetRecordCount();
	virtual System::Word __fastcall GetRecordSize();
	virtual System::Variant __fastcall GetStateFieldValue(Data::Db::TDataSetState State, Data::Db::TField* Field);
	void __fastcall InitOleDBAccess(bool Initializing);
	virtual void __fastcall InitializeMasterFields();
	virtual void __fastcall InternalAddRecord(System::PByte Buffer, bool Append)/* overload */;
	virtual void __fastcall InternalAddRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (void * Buffer, bool Append)/* overload */;
	virtual void __fastcall InternalCancel();
	virtual void __fastcall InternalClose();
	virtual void __fastcall InternalDelete();
	virtual void __fastcall InternalEdit();
	virtual void __fastcall InternalFirst();
	Data::Db::TGetResult __fastcall InternalGetRecord(System::PByte Buffer, Data::Db::TGetMode GetMode, bool DoCheck);
#ifndef _WIN64
	virtual void __fastcall InternalGotoBookmark(System::DynamicArray<System::Byte> Bookmark)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall InternalGotoBookmark(System::TArray__1<System::Byte> Bookmark)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall InternalGotoBookmark _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (void * Bookmark)/* overload */;
	virtual void __fastcall InternalHandleException();
	virtual void __fastcall InternalInitFieldDefs();
	virtual void __fastcall InternalInitRecord(System::PByte Buffer)/* overload */;
	virtual void __fastcall InternalInsert();
	virtual void __fastcall InternalLast();
	virtual void __fastcall InternalOpen();
	virtual void __fastcall InternalPost();
	virtual void __fastcall InternalRefresh();
	void __fastcall InternalRequery(TExecuteOptions Options = TExecuteOptions() );
	void __fastcall InternalSetSort(System::WideString Value);
	virtual void __fastcall InternalSetToRecord(System::PByte Buffer)/* overload */;
	virtual bool __fastcall IsCursorOpen();
	virtual void __fastcall Loaded();
	bool __fastcall LocateRecord(const System::UnicodeString KeyFields, const System::OleVariant &KeyValues, Data::Db::TLocateOptions Options, bool SyncCursor);
	virtual void __fastcall MasterChanged(System::TObject* Sender);
	virtual void __fastcall MasterDisabled(System::TObject* Sender);
	virtual void __fastcall OpenCursor(bool InfoQuery);
	virtual void __fastcall PrepareCursor();
	void __fastcall RefreshParams();
	void __fastcall ReleaseLock();
	virtual void __fastcall SetBlockReadSize(int Value);
	virtual void __fastcall SetBookmarkFlag(System::PByte Buffer, Data::Db::TBookmarkFlag Value)/* overload */;
#ifndef _WIN64
	virtual void __fastcall SetBookmarkData(System::PByte Buffer, System::DynamicArray<System::Byte> Data)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall SetBookmarkData(System::PByte Buffer, System::TArray__1<System::Byte> Data)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall SetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, void * Data)/* overload */;
	void __fastcall SetCommandText(const System::WideString Value);
	virtual void __fastcall SetConnection(TADOConnection* const Value);
	virtual bool __fastcall SetConnectionFlag(int Flag, bool Value);
	virtual void __fastcall SetDataSource(Data::Db::TDataSource* const Value);
	bool __fastcall SetDetailFilter();
#ifndef _WIN64
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::DynamicArray<System::Byte> Buffer)/* overload */;
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::DynamicArray<System::Byte> Buffer, bool NativeFormat)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer)/* overload */;
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer, bool NativeFormat)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer)/* overload */;
	virtual void __fastcall SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat)/* overload */;
	virtual void __fastcall SetFiltered(bool Value);
	virtual void __fastcall SetFilterOptions(Data::Db::TFilterOptions Value);
	virtual void __fastcall SetFilterText(const System::UnicodeString Value);
	void __fastcall SetParamsFromCursor();
	virtual void __fastcall SetRecNo(int Value);
	virtual void __fastcall UpdateIndexDefs();
	void __fastcall UpdateRecordSetPosition(System::PByte Buffer);
	__property Data::Db::TMasterDataLink* MasterDataLink = {read=FMasterDataLink};
	__property TADOCommand* Command = {read=FCommand};
	__property System::WideString CommandText = {read=GetCommandText, write=SetCommandText};
	__property int CommandTimeout = {read=GetCommandTimeout, write=SetCommandTimeout, default=30};
	__property TCommandType CommandType = {read=GetCommandType, write=SetCommandType, default=1};
	__property Data::Db::TDataSource* DataSource = {read=GetDataSource, write=SetDataSource};
	__property FieldDefs = {stored=FStoreDefs};
	__property Data::Db::TIndexDefs* IndexDefs = {read=FIndexDefs, write=FIndexDefs};
	__property System::UnicodeString IndexFieldNames = {read=GetIndexFieldNames, write=SetIndexFieldNames};
	__property System::WideString MasterFields = {read=GetMasterFields, write=SetMasterFields};
	__property bool ParamCheck = {read=GetParamCheck, write=SetParamCheck, default=1};
	__property TParameters* Parameters = {read=GetParameters, write=SetParameters};
	__property bool Prepared = {read=GetPrepared, write=SetPrepared, default=0};
	__property void * Reserved = {read=FReserved, write=FReserved};
	__property bool StoreDefs = {read=FStoreDefs, write=FStoreDefs, default=0};
	_di_IConnectionPoint __fastcall ConnectionPoint();
	HRESULT __safecall WillChangeField(int cFields, System::OleVariant Fields, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	HRESULT __safecall FieldChangeComplete(int cFields, System::OleVariant Fields, const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	HRESULT __safecall WillChangeRecord(Winapi::Activex::TOleEnum adReason, int cRecords, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	HRESULT __safecall RecordChangeComplete(Winapi::Activex::TOleEnum adReason, int cRecords, const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	HRESULT __safecall WillChangeRecordset(Winapi::Activex::TOleEnum adReason, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	HRESULT __safecall RecordsetChangeComplete(Winapi::Activex::TOleEnum adReason, const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	HRESULT __safecall WillMove(Winapi::Activex::TOleEnum adReason, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	HRESULT __safecall MoveComplete(Winapi::Activex::TOleEnum adReason, const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	HRESULT __safecall EndOfRecordset(System::WordBool &fMoreData, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	HRESULT __safecall FetchProgress(int Progress, int MaxProgress, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	HRESULT __safecall FetchComplete(const Winapi::Adoint::_di_Error pError, Winapi::Activex::TOleEnum &adStatus, const Winapi::Adoint::_di__Recordset pRecordset);
	
public:
	__fastcall virtual TCustomADODataSet(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomADODataSet();
#ifndef _WIN64
	virtual bool __fastcall BookmarkValid(System::DynamicArray<System::Byte> Bookmark);
#else /* _WIN64 */
	virtual bool __fastcall BookmarkValid(System::TArray__1<System::Byte> Bookmark);
#endif /* _WIN64 */
	void __fastcall CancelBatch(TAffectRecords AffectRecords = (TAffectRecords)(0x2));
	void __fastcall CancelUpdates();
	void __fastcall Clone(TCustomADODataSet* Source, TADOLockType LockType = (TADOLockType)(0x0));
	virtual Data::Db::TDataSet* __fastcall GetClonedDataSet(bool WithSettings);
#ifndef _WIN64
	virtual int __fastcall CompareBookmarks(System::DynamicArray<System::Byte> Bookmark1, System::DynamicArray<System::Byte> Bookmark2);
#else /* _WIN64 */
	virtual int __fastcall CompareBookmarks(System::TArray__1<System::Byte> Bookmark1, System::TArray__1<System::Byte> Bookmark2);
#endif /* _WIN64 */
	virtual System::Classes::TStream* __fastcall CreateBlobStream(Data::Db::TField* Field, Data::Db::TBlobStreamMode Mode);
	void __fastcall DeleteRecords(TAffectRecords AffectRecords = (TAffectRecords)(0x2));
	__property bool EnableBCD = {read=FEnableBCD, write=FEnableBCD, default=1};
	void __fastcall FilterOnBookmarks(System::TVarRec *Bookmarks, const int Bookmarks_High);
#ifndef _WIN64
	virtual int __fastcall GetBlobFieldData(int FieldNo, System::DynamicArray<System::Byte> &Buffer);
#else /* _WIN64 */
	virtual int __fastcall GetBlobFieldData(int FieldNo, System::TArray__1<System::Byte> &Buffer);
#endif /* _WIN64 */
	virtual void __fastcall GetDetailLinkFields(System::Generics::Collections::TList__1<Data::Db::TField*>* MasterFields, System::Generics::Collections::TList__1<Data::Db::TField*>* DetailFields)/* overload */;
#ifndef _WIN64
	virtual bool __fastcall GetFieldData(Data::Db::TField* Field, System::DynamicArray<System::Byte> &Buffer)/* overload */;
	virtual bool __fastcall GetFieldData(Data::Db::TField* Field, System::DynamicArray<System::Byte> &Buffer, bool NativeFormat)/* overload */;
	virtual bool __fastcall GetFieldData(int FieldNo, System::DynamicArray<System::Byte> &Buffer)/* overload */;
#else /* _WIN64 */
	virtual bool __fastcall GetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> &Buffer)/* overload */;
	virtual bool __fastcall GetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> &Buffer, bool NativeFormat)/* overload */;
	virtual bool __fastcall GetFieldData(int FieldNo, System::TArray__1<System::Byte> &Buffer)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall GetDetailLinkFields _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::Classes::TList* MasterFields, System::Classes::TList* DetailFields)/* overload */;
	virtual bool __fastcall GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer)/* overload */;
	virtual bool __fastcall GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat)/* overload */;
	virtual bool __fastcall GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (int FieldNo, void * Buffer)/* overload */;
	virtual bool __fastcall IsSequenced();
	void __fastcall LoadFromFile(const System::WideString FileName);
	virtual bool __fastcall Locate(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options);
	virtual System::Variant __fastcall Lookup(const System::UnicodeString KeyFields, const System::Variant &KeyValues, const System::UnicodeString ResultFields);
	Winapi::Adoint::_di__Recordset __fastcall NextRecordset(int &RecordsAffected);
	void __fastcall Requery(TExecuteOptions Options = TExecuteOptions() );
	void __fastcall SaveToFile(const System::WideString FileName = System::WideString(), TPersistFormat Format = (TPersistFormat)(0x0));
	bool __fastcall Seek(const System::Variant &KeyValues, TSeekOption SeekOption = (TSeekOption)(0x0));
	bool __fastcall Supports(TCursorOptions CursorOptions);
	void __fastcall UpdateBatch(TAffectRecords AffectRecords = (TAffectRecords)(0x2));
	virtual Data::Db::TUpdateStatus __fastcall UpdateStatus();
	__property System::UnicodeString DesignerData = {read=FDesignerData, write=FDesignerData};
	__property System::WideString IndexName = {read=GetIndexName, write=SetIndexName};
	__property int IndexFieldCount = {read=GetIndexFieldCount, nodefault};
	__property Data::Db::TField* IndexFields[int Index] = {read=GetIndexField, write=SetIndexField};
	__property TFilterGroup FilterGroup = {read=GetFilterGroup, write=SetFilterGroup, nodefault};
	__property Winapi::Adoint::_di_Properties Properties = {read=GetProperties};
	__property Winapi::Adoint::_di__Recordset Recordset = {read=FRecordsetObject, write=SetRecordset};
	__property TObjectStates RecordsetState = {read=GetRecordsetState, nodefault};
	__property TRecordStatusSet RecordStatus = {read=GetRecordStatus, nodefault};
	__property System::WideString Sort = {read=GetSort, write=SetSort};
	
__published:
	__property Active = {default=0};
	__property AutoCalcFields = {default=1};
	__property int CacheSize = {read=GetCacheSize, write=SetCacheSize, default=1};
	__property TADOConnection* Connection = {read=GetConnection, write=SetConnection};
	__property System::WideString ConnectionString = {read=GetConnectionString, write=SetConnectionString};
	__property TCursorLocation CursorLocation = {read=GetCursorLocation, write=SetCursorLocation, default=1};
	__property TCursorType CursorType = {read=GetCursorType, write=SetCursorType, default=2};
	__property TExecuteOptions ExecuteOptions = {read=GetExecuteOptions, write=SetExecuteOptions, default=0};
	__property Filter = {default=0};
	__property Filtered = {default=0};
	__property TADOLockType LockType = {read=GetLockType, write=SetLockType, default=3};
	__property TMarshalOption MarshalOptions = {read=GetMarshalOptions, write=SetMarshalOptions, default=0};
	__property int MaxRecords = {read=GetMaxRecords, write=SetMaxRecords, default=0};
	__property BeforeOpen;
	__property AfterOpen;
	__property BeforeClose;
	__property AfterClose;
	__property BeforeInsert;
	__property AfterInsert;
	__property BeforeEdit;
	__property AfterEdit;
	__property BeforePost;
	__property AfterPost;
	__property BeforeCancel;
	__property AfterCancel;
	__property BeforeDelete;
	__property AfterDelete;
	__property BeforeScroll;
	__property AfterScroll;
	__property BeforeRefresh;
	__property AfterRefresh;
	__property OnCalcFields;
	__property OnDeleteError;
	__property OnEditError;
	__property OnFilterRecord;
	__property OnNewRecord;
	__property OnPostError;
	__property TWillChangeFieldEvent OnWillChangeField = {read=FOnWillChangeField, write=FOnWillChangeField};
	__property TFieldChangeCompleteEvent OnFieldChangeComplete = {read=FOnFieldChangeComplete, write=FOnFieldChangeComplete};
	__property TWillChangeRecordEvent OnWillChangeRecord = {read=FOnWillChangeRecord, write=FOnWillChangeRecord};
	__property TRecordChangeCompleteEvent OnRecordChangeComplete = {read=FOnRecordChangeComplete, write=FOnRecordChangeComplete};
	__property TRecordsetReasonEvent OnWillChangeRecordset = {read=FOnWillChangeRecordset, write=FOnWillChangeRecordset};
	__property TRecordsetErrorEvent OnRecordsetChangeComplete = {read=FOnRecordsetChangeComplete, write=FOnRecordsetChangeComplete};
	__property TRecordsetReasonEvent OnWillMove = {read=FOnWillMove, write=FOnWillMove};
	__property TRecordsetErrorEvent OnMoveComplete = {read=FOnMoveComplete, write=FOnMoveComplete};
	__property TEndOfRecordsetEvent OnEndOfRecordset = {read=FOnEndOfRecordset, write=FOnEndOfRecordset};
	__property TRecordsetEvent OnFetchComplete = {read=FOnFetchComplete, write=FOnFetchComplete};
	__property TFetchProgressEvent OnFetchProgress = {read=FOnFetchProgress, write=FOnFetchProgress};
	__property TRecordsetCreate OnRecordsetCreate = {read=FOnRecordsetCreate, write=FOnRecordsetCreate};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  ClearCalcFields(NativeInt Buffer){ Data::Db::TDataSet::ClearCalcFields(Buffer); }
#ifndef _WIN64
	inline void __fastcall  GetBookmarkData(NativeInt Buffer, System::DynamicArray<System::Byte> Data){ Data::Db::TDataSet::GetBookmarkData(Buffer, Data); }
#else /* _WIN64 */
	inline void __fastcall  GetBookmarkData(NativeInt Buffer, System::TArray__1<System::Byte> Data){ Data::Db::TDataSet::GetBookmarkData(Buffer, Data); }
#endif /* _WIN64 */
	inline Data::Db::TBookmarkFlag __fastcall  GetBookmarkFlag(NativeInt Buffer){ return Data::Db::TDataSet::GetBookmarkFlag(Buffer); }
	inline Data::Db::TGetResult __fastcall  GetRecord(NativeInt Buffer, Data::Db::TGetMode GetMode, bool DoCheck){ return Data::Db::TDataSet::GetRecord(Buffer, GetMode, DoCheck); }
	inline void __fastcall  InternalAddRecord(NativeInt Buffer, bool Append){ Data::Db::TDataSet::InternalAddRecord(Buffer, Append); }
	inline void __fastcall  InternalInitRecord(NativeInt Buffer){ Data::Db::TDataSet::InternalInitRecord(Buffer); }
	inline void __fastcall  InternalSetToRecord(NativeInt Buffer){ Data::Db::TDataSet::InternalSetToRecord(Buffer); }
	inline void __fastcall  SetBookmarkFlag(NativeInt Buffer, Data::Db::TBookmarkFlag Value){ Data::Db::TDataSet::SetBookmarkFlag(Buffer, Value); }
#ifndef _WIN64
	inline void __fastcall  SetBookmarkData(NativeInt Buffer, System::DynamicArray<System::Byte> Data){ Data::Db::TDataSet::SetBookmarkData(Buffer, Data); }
#else /* _WIN64 */
	inline void __fastcall  SetBookmarkData(NativeInt Buffer, System::TArray__1<System::Byte> Data){ Data::Db::TDataSet::SetBookmarkData(Buffer, Data); }
#endif /* _WIN64 */
	
private:
	void *__RecordsetEventsVt;	// Winapi::Adoint::RecordsetEventsVt 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000403-0000-0010-8000-00AA006D2EA4}
	operator Winapi::Adoint::_di_RecordsetEventsVt()
	{
		Winapi::Adoint::_di_RecordsetEventsVt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Winapi::Adoint::RecordsetEventsVt*(void) { return (Winapi::Adoint::RecordsetEventsVt*)&__RecordsetEventsVt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__RecordsetEventsVt; }
	#endif
	
};


class PASCALIMPLEMENTATION TADODataSet : public TCustomADODataSet
{
	typedef TCustomADODataSet inherited;
	
private:
	TRDSConnection* FRDSConnection;
	void __fastcall SetRDSConnection(TRDSConnection* Value);
	
protected:
	virtual void __fastcall DataEvent(Data::Db::TDataEvent Event, NativeInt Info);
	virtual void __fastcall OpenCursor(bool InfoQuery);
	virtual void __fastcall SetConnection(TADOConnection* const Value);
	virtual void __fastcall SetDataSetField(Data::Db::TDataSetField* const Value);
	
public:
	void __fastcall CreateDataSet();
	void __fastcall GetIndexNames(System::Classes::TStrings* List);
	__property IndexDefs;
	
__published:
	__property CommandText = {default=0};
	__property CommandTimeout = {default=30};
	__property CommandType = {default=1};
	__property DataSetField;
	__property DataSource;
	__property EnableBCD = {default=1};
	__property FieldDefs;
	__property IndexName = {default=0};
	__property IndexFieldNames = {default=0};
	__property MasterFields = {default=0};
	__property ParamCheck = {default=1};
	__property Parameters;
	__property Prepared = {default=0};
	__property TRDSConnection* RDSConnection = {read=FRDSConnection, write=SetRDSConnection};
	__property StoreDefs = {default=0};
	__property BeforeOpen;
	__property AfterOpen;
	__property BeforeClose;
	__property AfterClose;
	__property BeforeInsert;
	__property AfterInsert;
	__property BeforeEdit;
	__property AfterEdit;
	__property BeforePost;
	__property AfterPost;
	__property BeforeCancel;
	__property AfterCancel;
	__property BeforeDelete;
	__property AfterDelete;
	__property BeforeScroll;
	__property AfterScroll;
	__property OnCalcFields;
	__property OnDeleteError;
	__property OnEditError;
	__property OnNewRecord;
	__property OnPostError;
public:
	/* TCustomADODataSet.Create */ inline __fastcall virtual TADODataSet(System::Classes::TComponent* AOwner) : TCustomADODataSet(AOwner) { }
	/* TCustomADODataSet.Destroy */ inline __fastcall virtual ~TADODataSet() { }
	
};


class PASCALIMPLEMENTATION TADOTable : public TCustomADODataSet
{
	typedef TCustomADODataSet inherited;
	
private:
	bool __fastcall GetTableDirect();
	void __fastcall SetTableDirect(const bool Value);
	bool __fastcall GetReadOnly();
	void __fastcall SetReadOnly(const bool Value);
	
public:
	__fastcall virtual TADOTable(System::Classes::TComponent* AOwner);
	void __fastcall GetIndexNames(System::Classes::TStrings* List);
	__property IndexDefs;
	
__published:
	__property CommandTimeout = {default=30};
	__property EnableBCD = {default=1};
	__property IndexFieldNames = {default=0};
	__property IndexName = {default=0};
	__property MasterFields = {default=0};
	__property Data::Db::TDataSource* MasterSource = {read=GetDataSource, write=SetDataSource};
	__property bool ReadOnly = {read=GetReadOnly, write=SetReadOnly, stored=false, nodefault};
	__property bool TableDirect = {read=GetTableDirect, write=SetTableDirect, default=0};
	__property System::WideString TableName = {read=GetCommandText, write=SetCommandText};
public:
	/* TCustomADODataSet.Destroy */ inline __fastcall virtual ~TADOTable() { }
	
};


class PASCALIMPLEMENTATION TADOQuery : public TCustomADODataSet
{
	typedef TCustomADODataSet inherited;
	
private:
	System::Classes::TStrings* FSQL;
	int FRowsAffected;
	System::Classes::TStrings* __fastcall GetSQL();
	void __fastcall SetSQL(System::Classes::TStrings* const Value);
	
protected:
	void __fastcall QueryChanged(System::TObject* Sender);
	
public:
	__fastcall virtual TADOQuery(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TADOQuery();
	int __fastcall ExecSQL();
	__property int RowsAffected = {read=FRowsAffected, nodefault};
	
__published:
	__property CommandTimeout = {default=30};
	__property DataSource;
	__property EnableBCD = {default=1};
	__property ParamCheck = {default=1};
	__property Parameters;
	__property Prepared = {default=0};
	__property System::Classes::TStrings* SQL = {read=GetSQL, write=SetSQL};
};


class PASCALIMPLEMENTATION TADOStoredProc : public TCustomADODataSet
{
	typedef TCustomADODataSet inherited;
	
public:
	__fastcall virtual TADOStoredProc(System::Classes::TComponent* AOwner);
	void __fastcall ExecProc();
	
__published:
	__property CommandTimeout = {default=30};
	__property DataSource;
	__property EnableBCD = {default=1};
	__property System::WideString ProcedureName = {read=GetCommandText, write=SetCommandText};
	__property Parameters;
	__property Prepared = {default=0};
public:
	/* TCustomADODataSet.Destroy */ inline __fastcall virtual ~TADOStoredProc() { }
	
};


class PASCALIMPLEMENTATION TADOBlobStream : public System::Classes::TMemoryStream
{
	typedef System::Classes::TMemoryStream inherited;
	
private:
	Data::Db::TBlobField* FField;
	TCustomADODataSet* FDataSet;
	System::Byte *FBuffer;
	int FFieldNo;
	bool FModified;
	System::Variant FData;
	System::Variant FFieldData;
	bool FWritten;
	
protected:
	void __fastcall ReadBlobData();
	virtual void * __fastcall Realloc(int &NewCapacity);
	
public:
	__fastcall TADOBlobStream(Data::Db::TBlobField* Field, Data::Db::TBlobStreamMode Mode);
	__fastcall virtual ~TADOBlobStream();
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
	void __fastcall Truncate();
	/* Hoisted overloads: */
	
public:
#ifndef _WIN64
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TMemoryStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* _WIN64 */
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TMemoryStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* _WIN64 */
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall CreateUDLFile(const System::WideString FileName, const System::WideString ProviderName, const System::WideString DataSourceName);
extern DELPHI_PACKAGE void __fastcall GetProviderNames(System::Classes::TStrings* Names)/* overload */;
extern DELPHI_PACKAGE System::WideString __fastcall PromptDataSource(NativeUInt ParentHandle, System::WideString InitialString);
extern DELPHI_PACKAGE System::WideString __fastcall PromptDataLinkFile(NativeUInt ParentHandle, System::WideString InitialFile);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DataLinkDir(void);
extern DELPHI_PACKAGE int __fastcall GetDataLinkFiles(System::Classes::TStrings* FileNames, System::UnicodeString Directory = System::UnicodeString())/* overload */;
}	/* namespace Adodb */
}	/* namespace Win */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_WIN_ADODB)
using namespace Data::Win::Adodb;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_WIN)
using namespace Data::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_Win_AdodbHPP
