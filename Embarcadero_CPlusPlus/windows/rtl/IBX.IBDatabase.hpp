// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBDatabase.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbdatabaseHPP
#define Ibx_IbdatabaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBExternals.hpp>
#include <Data.DB.hpp>
#include <IBX.IB.hpp>
#include <IBX.IBUtils.hpp>
#include <IBX.IBIntf.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibdatabase
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IIBEventNotifier;
typedef System::DelphiInterface<IIBEventNotifier> _di_IIBEventNotifier;
class DELPHICLASS TIBSchema;
struct TIBTablespaceFileSpec;
struct TIBTablespace;
struct TIBSecondaryFile;
class DELPHICLASS TIBDatabase;
class DELPHICLASS TIBTransaction;
class DELPHICLASS TIBBase;
//-- type declarations -------------------------------------------------------
typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,int>* TDPBConstantNames;

typedef System::DynamicArray<TIBBase*> __dummy_TIBBase_array;

typedef System::DynamicArray<TIBTransaction*> __dummy_TIBTransaction_array;

typedef System::DynamicArray<TIBDatabase*> __dummy_TIBDatabase_array;

typedef void __fastcall (__closure *TIBDatabaseLoginEvent)(TIBDatabase* Database, System::Classes::TStrings* LoginParams);

__interface  INTERFACE_UUID("{9427DE09-46F7-4E1D-8B92-C1F88B47BF6D}") IIBEventNotifier  : public System::IInterface 
{
	virtual void __fastcall RegisterEvents() = 0 ;
	virtual void __fastcall UnRegisterEvents() = 0 ;
	virtual bool __fastcall GetAutoRegister() = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIBSchema : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall FreeNodes() = 0 ;
	virtual bool __fastcall Has_DEFAULT_VALUE(TIBDatabase* ADatabase, System::UnicodeString Relation, System::UnicodeString Field) = 0 ;
	virtual bool __fastcall Has_COMPUTED_BLR(TIBDatabase* ADatabase, System::UnicodeString Relation, System::UnicodeString Field) = 0 ;
	virtual bool __fastcall In_Key(TIBDatabase* ADatabase, System::UnicodeString Relation, System::UnicodeString Field) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TIBSchema() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIBSchema() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::UnicodeString TIBFileName;

typedef System::Generics::Collections::TList__1<TIBBase*>* TSQLObjectsList;

typedef System::Generics::Collections::TList__1<TIBTransaction*>* TTransactionsList;

struct DECLSPEC_DRECORD TIBTablespaceFileSpec
{
public:
	System::UnicodeString FileName;
	__int64 Length;
	__int64 Start;
};


struct DECLSPEC_DRECORD TIBTablespace
{
public:
	System::UnicodeString TablespaceName;
	int PageSize;
	int Length;
	int Preallocate;
	bool ReserveSpace;
	bool IsEncrypted;
	System::UnicodeString EncryptionKey;
	System::UnicodeString Description;
	int PageCache;
#ifndef _WIN64
	System::DynamicArray<TIBTablespaceFileSpec> Files;
#else /* _WIN64 */
	System::TArray__1<TIBTablespaceFileSpec> Files;
#endif /* _WIN64 */
};


#ifndef _WIN64
typedef System::DynamicArray<TIBTablespace> TIBTableSpaces;
#else /* _WIN64 */
typedef System::TArray__1<TIBTablespace> TIBTableSpaces;
#endif /* _WIN64 */

struct DECLSPEC_DRECORD TIBSecondaryFile
{
public:
	System::UnicodeString FileSpec;
	System::UnicodeString __fastcall AsSQL();
	
public:
	bool IsStarting;
	union
	{
		struct 
		{
			int Length;
		};
		struct 
		{
			int StartingAt;
		};
		
	};
};


typedef System::Generics::Collections::TList__1<TIBSecondaryFile>* TIBTSSecondaryFiles;

class PASCALIMPLEMENTATION TIBDatabase : public Data::Db::TCustomConnection
{
	typedef Data::Db::TCustomConnection inherited;
	
private:
	System::UnicodeString FHiddenPassword;
	TIBDatabaseLoginEvent FOnLogin;
	Ibx::Ib::TTraceFlags FTraceFlags;
	int FDBSQLDialect;
	int FSQLDialect;
	System::Classes::TNotifyEvent FOnDialectDowngradeWarning;
	bool FCanTimeout;
	System::Generics::Collections::TList__1<TIBBase*>* FSQLObjects;
	System::Generics::Collections::TList__1<TIBTransaction*>* FTransactions;
	TIBFileName FDBName;
	System::Classes::TStrings* FDBParams;
	bool FDBParamsChanged;
	System::Byte *FDPB;
	short FDPBLength;
	void * *FHandle;
	bool FHandleIsShared;
	System::Classes::TNotifyEvent FOnIdleTimer;
	TIBTransaction* FDefaultTransaction;
	TIBTransaction* FInternalTransaction;
	TIBTransaction* FPreCommitted;
	Ibx::Ibutils::TIBTimer* FTimer;
	System::Classes::TStringList* FUserNames;
	System::Generics::Collections::TList__1<_di_IIBEventNotifier>* FEventNotifiers;
	bool FAllowStreamedConnected;
	TIBSchema* FSchema;
	Ibx::Ibintf::_di_IGDSLibrary FGDSLibrary;
	System::UnicodeString FCharacterSet;
	int FCharacterSetCodePage;
	System::UnicodeString FServerType;
	System::Sysutils::TEncoding* FEncoding;
	System::Extended FFullODS;
	void __fastcall EnsureInactive();
	int __fastcall GetDBSQLDialect();
	int __fastcall GetSQLDialect();
	void __fastcall SetSQLDialect(const int Value);
	void __fastcall ValidateClientSQLDialect();
	void __fastcall DBParamsChange(System::TObject* Sender);
	void __fastcall DBParamsChanging(System::TObject* Sender);
	TIBBase* __fastcall GetSQLObject(int Index);
	int __fastcall GetSQLObjectCount();
	System::UnicodeString __fastcall GetDBParamByDPB(const int Idx);
	int __fastcall GetIdleTimer();
	TIBTransaction* __fastcall GetTransaction(int Index);
	int __fastcall GetTransactionCount();
	bool __fastcall Login();
	void __fastcall SetDatabaseName(const TIBFileName Value);
	void __fastcall SetDBParamByDPB(const int Idx, System::UnicodeString Value);
	void __fastcall SetDBParams(System::Classes::TStrings* Value);
	void __fastcall SetDefaultTransaction(TIBTransaction* Value);
	void __fastcall SetIdleTimer(int Value);
	void __fastcall TimeoutConnection(System::TObject* Sender);
	bool __fastcall GetIsReadOnly();
	int __fastcall AddSQLObject(TIBBase* ds);
	void __fastcall RemoveSQLObject(TIBBase* Value);
	void __fastcall RemoveSQLObjects();
	void __fastcall InternalClose(bool Force);
#ifndef _WIN64
	void __fastcall GenerateDPB(System::Classes::TStrings* sl, System::DynamicArray<System::Byte> &DPB, short &DPBLength);
#else /* _WIN64 */
	void __fastcall GenerateDPB(System::Classes::TStrings* sl, System::TArray__1<System::Byte> &DPB, short &DPBLength);
#endif /* _WIN64 */
	void __fastcall SetServerType(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSysEncryptPassword();
	void __fastcall SetSysEncryptPassword(const System::UnicodeString Value);
	TIBTransaction* __fastcall GetPrecommittedTransaction();
	
protected:
	virtual void __fastcall DoConnect();
	virtual void __fastcall DoDisconnect();
	virtual bool __fastcall GetConnected();
	virtual void __fastcall Loaded();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TIBDatabase(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBDatabase();
	void __fastcall AddEventNotifier(_di_IIBEventNotifier Notifier);
	void __fastcall RemoveEventNotifier(_di_IIBEventNotifier Notifier);
	void __fastcall ApplyUpdates(Data::Db::TDataSet* const *DataSets, const int DataSets_High);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall CloseDataSets();
	void __fastcall CheckActive();
	void __fastcall CheckInactive();
	void __fastcall CreateDatabase();
	void __fastcall DropDatabase();
	void __fastcall ForceClose();
	void __fastcall GetFieldNames(const System::UnicodeString TableName, System::Classes::TStrings* List);
	void __fastcall GetTableNames(System::Classes::TStrings* List, bool SystemTables = false);
	int __fastcall IndexOfDBConst(System::UnicodeString st);
	bool __fastcall TestConnected();
	void __fastcall CheckDatabaseName();
	NativeInt __fastcall Call(NativeInt ErrCode, bool RaiseError);
	int __fastcall AddTransaction(TIBTransaction* TR);
	int __fastcall FindTransaction(TIBTransaction* TR);
	TIBTransaction* __fastcall FindDefaultTransaction();
	void __fastcall RemoveTransaction(TIBTransaction* Value);
	void __fastcall RemoveTransactions();
	void __fastcall SetHandle(Ibx::Ibexternals::PVoid Value);
	void __fastcall OnlineDump(System::UnicodeString *Files, const int Files_High, int *Sizes, const int Sizes_High, bool Full, bool Overwrite);
	void __fastcall ExecuteImmediate(System::UnicodeString SQL, TIBTransaction* Transaction = (TIBTransaction*)(0x0));
	void __fastcall Sweep();
	void __fastcall Reclaim();
	void __fastcall Flush();
	void __fastcall CancelStatement(Ibx::Ibexternals::PVoid StmtHandle);
	__property Ibx::Ibexternals::PVoid Handle = {read=FHandle};
	__property bool IsReadOnly = {read=GetIsReadOnly, nodefault};
	__property System::UnicodeString DBParamByDPB[const int Idx] = {read=GetDBParamByDPB, write=SetDBParamByDPB};
	__property int SQLObjectCount = {read=GetSQLObjectCount, nodefault};
	__property TIBBase* SQLObjects[int Index] = {read=GetSQLObject};
	__property bool HandleIsShared = {read=FHandleIsShared, nodefault};
	__property int TransactionCount = {read=GetTransactionCount, nodefault};
	__property TIBTransaction* Transactions[int Index] = {read=GetTransaction};
	__property TIBTransaction* InternalTransaction = {read=FInternalTransaction};
	Ibx::Ibintf::_di_IGDSLibrary __fastcall GDSLibrary();
	void __fastcall EncryptionPassword(System::UnicodeString password, System::UnicodeString Encryption);
	void __fastcall ColumnEncryptionPassword(System::UnicodeString password, System::UnicodeString tablename, System::UnicodeString column);
	bool __fastcall Has_DEFAULT_VALUE(System::UnicodeString Relation, System::UnicodeString Field);
	bool __fastcall Has_COMPUTED_BLR(System::UnicodeString Relation, System::UnicodeString Field);
	bool __fastcall In_Key(System::UnicodeString Relation, System::UnicodeString Field);
	void __fastcall FlushSchema();
	__property System::UnicodeString CharacterSet = {read=FCharacterSet};
	__property int CharacterSetCodePage = {read=FCharacterSetCodePage, nodefault};
	__property System::Sysutils::TEncoding* Encoding = {read=FEncoding};
	__property System::UnicodeString SysEncryptPassword = {read=GetSysEncryptPassword, write=SetSysEncryptPassword};
	__property TIBTransaction* PrecommittedTransaction = {read=GetPrecommittedTransaction};
	void __fastcall CreateTablespace(System::UnicodeString TablespaceName, System::UnicodeString FileSpec, int PageSize = 0x0, int Length = 0x0, bool PreAllocate = false, bool ReserveSpace = false, System::UnicodeString Encrypt = System::UnicodeString(), System::UnicodeString Description = System::UnicodeString(), System::Generics::Collections::TList__1<TIBSecondaryFile>* SecondaryFiles = (System::Generics::Collections::TList__1<TIBSecondaryFile>*)(0x0));
	void __fastcall AlterTablespace(System::UnicodeString TablespaceName, int PageCache = 0x0, System::UnicodeString Description = System::UnicodeString(), System::UnicodeString Encrypt = System::UnicodeString(), System::UnicodeString Decrypt = System::UnicodeString(), System::Generics::Collections::TList__1<TIBSecondaryFile>* SecondaryFiles = (System::Generics::Collections::TList__1<TIBSecondaryFile>*)(0x0));
	void __fastcall DropTablespace(System::UnicodeString TablespaceName);
#ifndef _WIN64
	System::DynamicArray<TIBTablespace> __fastcall GetTablespaces(System::UnicodeString Tablespace = System::UnicodeString());
#else /* _WIN64 */
	System::TArray__1<TIBTablespace> __fastcall GetTablespaces(System::UnicodeString Tablespace = System::UnicodeString());
#endif /* _WIN64 */
	void __fastcall GetTablespaceNames(System::Classes::TStrings* const AList);
	void __fastcall GetTablesInTablespace(System::UnicodeString ForTablespace, System::Classes::TStrings* TableList);
	void __fastcall GetIndicesInTablespace(System::UnicodeString ForTablespace, System::Classes::TStrings* IndexList);
	void __fastcall MoveTableToTablespace(System::UnicodeString TableName, System::UnicodeString Tablespace = L"PRIMARY");
	void __fastcall MoveIndexToTablespace(System::UnicodeString TableName, System::UnicodeString Tablespace = L"PRIMARY");
	System::UnicodeString __fastcall QuoteIdentifier(const System::UnicodeString Value);
	__property System::Extended FullODS = {read=FFullODS};
	
__published:
	__property Connected = {default=0};
	__property TIBFileName DatabaseName = {read=FDBName, write=SetDatabaseName};
	__property System::Classes::TStrings* Params = {read=FDBParams, write=SetDBParams};
	__property LoginPrompt = {default=0};
	__property TIBTransaction* DefaultTransaction = {read=FDefaultTransaction, write=SetDefaultTransaction};
	__property System::UnicodeString ServerType = {read=FServerType, write=SetServerType};
	__property int IdleTimer = {read=GetIdleTimer, write=SetIdleTimer, nodefault};
	__property int SQLDialect = {read=GetSQLDialect, write=SetSQLDialect, nodefault};
	__property int DBSQLDialect = {read=FDBSQLDialect, nodefault};
	__property Ibx::Ib::TTraceFlags TraceFlags = {read=FTraceFlags, write=FTraceFlags, default=0};
	__property bool AllowStreamedConnected = {read=FAllowStreamedConnected, write=FAllowStreamedConnected, nodefault};
	__property AfterConnect;
	__property AfterDisconnect;
	__property BeforeConnect;
	__property BeforeDisconnect;
	__property TIBDatabaseLoginEvent OnLogin = {read=FOnLogin, write=FOnLogin};
	__property System::Classes::TNotifyEvent OnIdleTimer = {read=FOnIdleTimer, write=FOnIdleTimer};
	__property System::Classes::TNotifyEvent OnDialectDowngradeWarning = {read=FOnDialectDowngradeWarning, write=FOnDialectDowngradeWarning};
};


enum DECLSPEC_DENUM TIBTransactionAction : unsigned char { TARollback, TACommit, TARollbackRetaining, TACommitRetaining };

enum DECLSPEC_DENUM TAutoStopAction : unsigned char { saNone, saRollback, saCommit, saRollbackRetaining, saCommitRetaining };

typedef System::Generics::Collections::TList__1<TIBDatabase*>* TDatabaseList;

enum DECLSPEC_DENUM TIBTransactionLevel : unsigned char { ibtrSnapshot, ibtrReadCommitted, ibtrReadOnlyTableStability, ibtrReadWriteTableStability, ibtrPrecommitted };

class PASCALIMPLEMENTATION TIBTransaction : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FCanTimeout;
	System::Generics::Collections::TList__1<TIBDatabase*>* FDatabases;
	System::Generics::Collections::TList__1<TIBBase*>* FSQLObjects;
	TIBDatabase* FDefaultDatabase;
	void * *FHandle;
	bool FHandleIsShared;
	System::Classes::TNotifyEvent FOnIdleTimer;
	bool FStreamedActive;
	System::Byte *FTPB;
	short FTPBLength;
	Ibx::Ibutils::TIBTimer* FTimer;
	TIBTransactionAction FDefaultAction;
	System::Classes::TStrings* FTRParams;
	bool FTRParamsChanged;
	bool FAutoStarted;
	TAutoStopAction FAutoStopAction;
	bool FAllowAutoStart;
	__int64 FTransactionID;
	void __fastcall EnsureNotInTransaction();
	void __fastcall EndTransaction(TIBTransactionAction Action, bool Force);
	TIBDatabase* __fastcall GetDatabase(int Index);
	int __fastcall GetDatabaseCount();
	TIBBase* __fastcall GetSQLObject(int Index);
	int __fastcall GetSQLObjectCount();
	bool __fastcall GetInTransaction();
	int __fastcall GetIdleTimer();
	void __fastcall BeforeDatabaseDisconnect(TIBDatabase* DB);
	void __fastcall SetActive(bool Value);
	void __fastcall SetDefaultAction(TIBTransactionAction Value);
	void __fastcall SetDefaultDatabase(TIBDatabase* Value);
	void __fastcall SetIdleTimer(int Value);
	void __fastcall SetTRParams(System::Classes::TStrings* Value);
	void __fastcall TimeoutTransaction(System::TObject* Sender);
	void __fastcall TRParamsChange(System::TObject* Sender);
	void __fastcall TRParamsChanging(System::TObject* Sender);
	void __fastcall AddSQLObject(TIBBase* ds);
	void __fastcall RemoveSQLObject(TIBBase* Item);
	void __fastcall RemoveSQLObjects();
	__int64 __fastcall GetTransactionID();
	TIBDatabase* __fastcall GetPrimaryDatabase();
	
protected:
	virtual void __fastcall Loaded();
	void __fastcall SetHandle(Ibx::Ibexternals::PVoid Value);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TIBTransaction(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall TIBTransaction(System::Classes::TComponent* AOwner, TIBTransactionLevel TransactionLevel)/* overload */;
	__fastcall virtual ~TIBTransaction();
	NativeInt __fastcall Call(NativeInt ErrCode, bool RaiseError);
	void __fastcall Commit();
	void __fastcall CommitRetaining();
	void __fastcall Rollback();
	void __fastcall RollbackRetaining();
	void __fastcall StartTransaction();
	void __fastcall AutoStartTransaction();
	void __fastcall ReleaseSavepoint(System::UnicodeString Name);
	void __fastcall RollbackSavepoint(System::UnicodeString Name);
	void __fastcall StartSavepoint(System::UnicodeString Name);
	void __fastcall CheckInTransaction();
	void __fastcall CheckNotInTransaction();
	void __fastcall CheckAutoStop();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	int __fastcall AddDatabase(TIBDatabase* db);
	int __fastcall FindDatabase(TIBDatabase* db);
	TIBDatabase* __fastcall FindDefaultDatabase();
	bool __fastcall IsReadOnly();
	void __fastcall RemoveDatabase(TIBDatabase* Value);
	void __fastcall RemoveDatabases();
	void __fastcall CheckDatabasesInList();
	void __fastcall SetTransactionLevel(TIBTransactionLevel Level);
	__property int DatabaseCount = {read=GetDatabaseCount, nodefault};
	__property TIBDatabase* Databases[int Index] = {read=GetDatabase};
	__property int SQLObjectCount = {read=GetSQLObjectCount, nodefault};
	__property TIBBase* SQLObjects[int Index] = {read=GetSQLObject};
	__property Ibx::Ibexternals::PVoid Handle = {read=FHandle};
	__property bool HandleIsShared = {read=FHandleIsShared, nodefault};
	__property bool InTransaction = {read=GetInTransaction, nodefault};
	__property System::PByte TPB = {read=FTPB};
	__property short TPBLength = {read=FTPBLength, nodefault};
	__property __int64 TransactionID = {read=GetTransactionID};
	
__published:
	__property bool Active = {read=GetInTransaction, write=SetActive, default=0};
	__property bool AllowAutoStart = {read=FAllowAutoStart, write=FAllowAutoStart, default=1};
	__property TIBDatabase* DefaultDatabase = {read=FDefaultDatabase, write=SetDefaultDatabase};
	__property int IdleTimer = {read=GetIdleTimer, write=SetIdleTimer, default=0};
	__property TIBTransactionAction DefaultAction = {read=FDefaultAction, write=SetDefaultAction, default=1};
	__property System::Classes::TStrings* Params = {read=FTRParams, write=SetTRParams};
	__property TAutoStopAction AutoStopAction = {read=FAutoStopAction, write=FAutoStopAction, default=0};
	__property System::Classes::TNotifyEvent OnIdleTimer = {read=FOnIdleTimer, write=FOnIdleTimer};
};


class PASCALIMPLEMENTATION TIBBase : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TIBDatabase* FDatabase;
	int FIndexInDatabase;
	TIBTransaction* FTransaction;
	System::TObject* FOwner;
	System::Classes::TNotifyEvent FBeforeDatabaseDisconnect;
	System::Classes::TNotifyEvent FAfterDatabaseDisconnect;
	System::Classes::TNotifyEvent FOnDatabaseFree;
	System::Classes::TNotifyEvent FBeforeTransactionEnd;
	System::Classes::TNotifyEvent FAfterTransactionEnd;
	System::Classes::TNotifyEvent FOnTransactionFree;
	virtual void __fastcall DoBeforeDatabaseDisconnect();
	virtual void __fastcall DoAfterDatabaseDisconnect();
	virtual void __fastcall DoDatabaseFree();
	virtual void __fastcall DoBeforeTransactionEnd();
	virtual void __fastcall DoAfterTransactionEnd();
	virtual void __fastcall DoTransactionFree();
	virtual Ibx::Ibheader::PISC_DB_HANDLE __fastcall GetDBHandle();
	virtual Ibx::Ibheader::PISC_TR_HANDLE __fastcall GetTRHandle();
	virtual void __fastcall SetDatabase(TIBDatabase* Value);
	virtual void __fastcall SetTransaction(TIBTransaction* Value);
	
public:
	__fastcall TIBBase(System::TObject* AOwner);
	__fastcall virtual ~TIBBase();
	virtual void __fastcall CheckDatabase();
	virtual void __fastcall CheckTransaction();
	__property System::Classes::TNotifyEvent BeforeDatabaseDisconnect = {read=FBeforeDatabaseDisconnect, write=FBeforeDatabaseDisconnect};
	__property System::Classes::TNotifyEvent AfterDatabaseDisconnect = {read=FAfterDatabaseDisconnect, write=FAfterDatabaseDisconnect};
	__property System::Classes::TNotifyEvent OnDatabaseFree = {read=FOnDatabaseFree, write=FOnDatabaseFree};
	__property System::Classes::TNotifyEvent BeforeTransactionEnd = {read=FBeforeTransactionEnd, write=FBeforeTransactionEnd};
	__property System::Classes::TNotifyEvent AfterTransactionEnd = {read=FAfterTransactionEnd, write=FAfterTransactionEnd};
	__property System::Classes::TNotifyEvent OnTransactionFree = {read=FOnTransactionFree, write=FOnTransactionFree};
	__property TIBDatabase* Database = {read=FDatabase, write=SetDatabase};
	__property Ibx::Ibheader::PISC_DB_HANDLE DBHandle = {read=GetDBHandle};
	__property System::TObject* Owner = {read=FOwner};
	__property Ibx::Ibheader::PISC_TR_HANDLE TRHandle = {read=GetTRHandle};
	__property TIBTransaction* Transaction = {read=FTransaction, write=SetTransaction};
};


//-- var, const, procedure ---------------------------------------------------
#define DPBPrefix L"isc_dpb_"
#define TPBPrefix L"isc_tpb_"
extern DELPHI_PACKAGE System::Generics::Collections::TDictionary__2<System::UnicodeString,int>* DPBConstantNames;
extern DELPHI_PACKAGE System::Generics::Collections::TDictionary__2<System::UnicodeString,int>* TPBConstantNames;
extern DELPHI_PACKAGE System::Generics::Collections::TDictionary__2<System::UnicodeString,int>* CodePages;
#ifndef _WIN64
extern DELPHI_PACKAGE void __fastcall GenerateTPB(System::Classes::TStrings* sl, System::DynamicArray<System::Byte> &TPB, short &TPBLength);
#else /* _WIN64 */
extern DELPHI_PACKAGE void __fastcall GenerateTPB(System::Classes::TStrings* sl, System::TArray__1<System::Byte> &TPB, short &TPBLength);
#endif /* _WIN64 */
}	/* namespace Ibdatabase */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBDATABASE)
using namespace Ibx::Ibdatabase;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbdatabaseHPP
