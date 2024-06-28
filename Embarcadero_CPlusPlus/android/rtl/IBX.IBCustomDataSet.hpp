// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBCustomDataSet.pas' rev: 34.00 (Android)

#ifndef Ibx_IbcustomdatasetHPP
#define Ibx_IbcustomdatasetHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <System.Types.hpp>
#include <IBX.IBExternals.hpp>
#include <IBX.IB.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBSQL.hpp>
#include <Data.DB.hpp>
#include <IBX.IBBlob.hpp>
#include <System.Generics.Collections.hpp>
#include <IBX.IBInputOutput.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibcustomdataset
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBDataSetUpdateObject;
struct TColumnData;
struct TRowData;
struct TFieldData;
struct TIBDBKey;
struct TRecordData;
class DELPHICLASS TIBStringField;
class DELPHICLASS TIBBCDField;
class DELPHICLASS TIBDataLink;
class DELPHICLASS TIBGeneratorField;
class DELPHICLASS TIBCustomDataSet;
class DELPHICLASS TIBDataSet;
class DELPHICLASS TIBDSBlobStream;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBDataSetUpdateObject : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Classes::TStrings* FRefreshSQL;
	void __fastcall SetRefreshSQL(System::Classes::TStrings* value);
	
protected:
	virtual TIBCustomDataSet* __fastcall GetDataSet() = 0 ;
	virtual void __fastcall SetDataSet(TIBCustomDataSet* ADataSet) = 0 ;
	virtual void __fastcall Apply(Data::Db::TUpdateKind UpdateKind) = 0 ;
	virtual System::Classes::TStrings* __fastcall GetSQL(Data::Db::TUpdateKind UpdateKind) = 0 ;
	__property TIBCustomDataSet* DataSet = {read=GetDataSet, write=SetDataSet};
	
public:
	__fastcall virtual TIBDataSetUpdateObject(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBDataSetUpdateObject();
	
__published:
	__property System::Classes::TStrings* RefreshSQL = {read=FRefreshSQL, write=SetRefreshSQL};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::StaticArray<Ibx::Ibblob::TIBBlobStream*, 1> TBlobDataArray;

typedef TBlobDataArray *PBlobDataArray;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TColumnData
{
public:
	short fdDataType;
	short fdDataScale;
	bool fdNullable;
	int fdDataOfs;
	short fdCharsetSize;
	bool fdPersistedFloatField;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD TRowData
{
public:
	short rdFieldCount;
	System::StaticArray<TColumnData, 1> rdColumns;
};
#pragma pack(pop)


typedef TRowData *PRowData;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TFieldData
{
public:
	bool fdIsNull;
	int fdDataSize;
	int fdDataLength;
	Ibx::Ibsql::TIBChangeState fdChangeStatus;
};
#pragma pack(pop)


typedef TFieldData *PFieldData;

enum DECLSPEC_DENUM TCachedUpdateStatus : unsigned char { cusUnmodified, cusModified, cusInserted, cusDeleted, cusUninserted };

struct DECLSPEC_DRECORD TIBDBKey
{
public:
	System::StaticArray<System::Byte, 8> DBKey;
};


typedef TIBDBKey *PIBDBKey;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TRecordData
{
public:
	Data::Db::TBookmarkFlag rdBookmarkFlag;
	int rdRecordNumber;
	TCachedUpdateStatus rdCachedUpdateStatus;
	Data::Db::TUpdateStatus rdUpdateStatus;
	__int64 rdSavedOffset;
	TIBDBKey rdDBKey;
	System::StaticArray<TFieldData, 1> rdFields;
};
#pragma pack(pop)


typedef TRecordData *PRecordData;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBStringField : public Data::Db::TWideStringField
{
	typedef Data::Db::TWideStringField inherited;
	
private:
	System::TArray__1<System::Byte> buffer;
	bool FEmptyAsNull;
	
public:
	__fastcall virtual TIBStringField(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBStringField();
	__classmethod virtual void __fastcall CheckTypeSize(int Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual System::Variant __fastcall GetAsVariant();
	HIDESBASE bool __fastcall GetValue(System::UnicodeString &Value);
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	__property System::UnicodeString Value = {read=GetAsWideString, write=SetAsWideString};
	
__published:
	__property bool EmptyAsNull = {read=FEmptyAsNull, write=FEmptyAsNull, default=1};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TIBBCDField : public Data::Db::TBCDField
{
	typedef Data::Db::TBCDField inherited;
	
protected:
	__classmethod virtual void __fastcall CheckTypeSize(int Value);
	virtual System::Currency __fastcall GetAsCurrency();
	virtual System::UnicodeString __fastcall GetAsString();
	virtual System::Variant __fastcall GetAsVariant();
	virtual int __fastcall GetDataSize();
	
public:
	__fastcall virtual TIBBCDField(System::Classes::TComponent* AOwner);
	
__published:
	__property Size = {default=8};
public:
	/* TField.Destroy */ inline __fastcall virtual ~TIBBCDField() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBDataLink : public Data::Db::TDetailDataLink
{
	typedef Data::Db::TDetailDataLink inherited;
	
private:
	TIBCustomDataSet* FDataSet;
	
protected:
	virtual void __fastcall ActiveChanged();
	virtual void __fastcall RecordChanged(Data::Db::TField* Field);
	virtual Data::Db::TDataSet* __fastcall GetDetailDataSet();
	virtual void __fastcall CheckBrowseMode();
	
public:
	__fastcall TIBDataLink(TIBCustomDataSet* ADataSet);
	__fastcall virtual ~TIBDataLink();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TIBGeneratorApplyEvent : unsigned char { gamOnNewRecord, gamOnPost, gamOnServer };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBGeneratorField : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::UnicodeString FField;
	System::UnicodeString FGenerator;
	int FIncrementBy;
	TIBCustomDataSet* DataSet;
	TIBGeneratorApplyEvent FApplyEvent;
	bool __fastcall IsComplete();
	
public:
	__fastcall TIBGeneratorField(TIBCustomDataSet* ADataSet);
	System::UnicodeString __fastcall ValueName();
	void __fastcall Apply();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::UnicodeString Field = {read=FField, write=FField};
	__property System::UnicodeString Generator = {read=FGenerator, write=FGenerator};
	__property int IncrementBy = {read=FIncrementBy, write=FIncrementBy, nodefault};
	__property TIBGeneratorApplyEvent ApplyEvent = {read=FApplyEvent, write=FApplyEvent, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIBGeneratorField() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TIBUpdateAction : unsigned char { uaFail, uaAbort, uaSkip, uaRetry, uaApply, uaApplied };

typedef void __fastcall (__closure *TIBUpdateErrorEvent)(Data::Db::TDataSet* DataSet, Data::Db::EDatabaseError* E, Data::Db::TUpdateKind UpdateKind, TIBUpdateAction &UpdateAction);

typedef void __fastcall (__closure *TIBUpdateRecordEvent)(Data::Db::TDataSet* DataSet, Data::Db::TUpdateKind UpdateKind, TIBUpdateAction &UpdateAction);

typedef System::Set<TCachedUpdateStatus, TCachedUpdateStatus::cusUnmodified, TCachedUpdateStatus::cusUninserted> TIBUpdateRecordTypes;

enum DECLSPEC_DENUM TLiveMode : unsigned char { lmInsert, lmModify, lmDelete, lmRefresh };

typedef System::Set<TLiveMode, TLiveMode::lmInsert, TLiveMode::lmRefresh> TLiveModes;

class PASCALIMPLEMENTATION TIBCustomDataSet : public Data::Db::TDataSet
{
	typedef Data::Db::TDataSet inherited;
	
	
private:
	typedef System::DynamicArray<int> _TIBCustomDataSet__1;
	
	
private:
	bool FNeedsRefresh;
	bool FForcedRefresh;
	Ibx::Ibdatabase::TIBBase* FBase;
	int FBlobCacheOffset;
	System::Generics::Collections::TObjectList__1<Ibx::Ibblob::TIBBlobStream*>* FBlobStreamList;
	__int64 FBufferChunks;
	NativeInt FBufferCache;
	NativeInt FOldBufferCache;
	NativeInt FFilterBuffer;
	NativeInt FModelBuffer;
	NativeInt FOldBuffer;
	NativeInt FTempBuffer;
	TRowData *FRowData;
	NativeInt FBufferChunkSize;
	NativeInt FCacheSize;
	NativeInt FOldCacheSize;
	NativeInt FBPos;
	NativeInt FOBPos;
	NativeInt FBEnd;
	NativeInt FOBEnd;
	bool FCachedUpdates;
	int FCalcFieldsOffset;
	int FCurrentRecord;
	int FDeletedRecords;
	bool FOpen;
	bool FInternalPrepared;
	Ibx::Ibsql::TIBSQL* FQDelete;
	Ibx::Ibsql::TIBSQL* FQInsert;
	Ibx::Ibsql::TIBSQL* FQRefresh;
	Ibx::Ibsql::TIBSQL* FQSelect;
	Ibx::Ibsql::TIBSQL* FQModify;
	int FRecordBufferSize;
	int FRecordCount;
	int FRecordSize;
	bool FUniDirectional;
	Data::Db::TUpdateMode FUpdateMode;
	TIBDataSetUpdateObject* FUpdateObject;
	bool FParamCheck;
	bool FUpdatesPending;
	TIBUpdateRecordTypes FUpdateRecordTypes;
	_TIBCustomDataSet__1 FMappedFieldPosition;
	TIBDataLink* FDataLink;
	bool FStreamedActive;
	TLiveModes FLiveMode;
	TIBGeneratorField* FGeneratorField;
	int FRowsAffected;
	System::Classes::TNotifyEvent FBeforeDatabaseDisconnect;
	System::Classes::TNotifyEvent FAfterDatabaseDisconnect;
	System::Classes::TNotifyEvent FDatabaseFree;
	TIBUpdateErrorEvent FOnUpdateError;
	TIBUpdateRecordEvent FOnUpdateRecord;
	System::Classes::TNotifyEvent FBeforeTransactionEnd;
	System::Classes::TNotifyEvent FAfterTransactionEnd;
	System::Classes::TNotifyEvent FTransactionFree;
	Ibx::Ibexternals::PVoid __fastcall GetSelectStmtHandle();
	void __fastcall SetUpdateMode(const Data::Db::TUpdateMode Value);
	void __fastcall SetUpdateObject(TIBDataSetUpdateObject* Value);
	Data::Db::TGetResult __fastcall AdjustCurrentRecord(NativeInt Buffer, Data::Db::TGetMode GetMode);
	void __fastcall AdjustRecordOnInsert(NativeInt Buffer);
	bool __fastcall CanEdit();
	bool __fastcall CanInsert();
	bool __fastcall CanDelete();
	HIDESBASE bool __fastcall CanRefresh();
	void __fastcall CheckEditState();
	void __fastcall ClearBlobCache();
	void __fastcall CopyRecordBuffer(NativeInt Source, NativeInt Dest);
	void __fastcall DoBeforeDatabaseDisconnect(System::TObject* Sender);
	void __fastcall DoAfterDatabaseDisconnect(System::TObject* Sender);
	void __fastcall DoDatabaseFree(System::TObject* Sender);
	void __fastcall DoBeforeTransactionEnd(System::TObject* Sender);
	void __fastcall DoAfterTransactionEnd(System::TObject* Sender);
	void __fastcall DoTransactionFree(System::TObject* Sender);
	void __fastcall FetchCurrentRecordToBuffer(Ibx::Ibsql::TIBSQL* Qry, int RecordNumber, NativeInt Buffer);
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	Ibx::Ibheader::PISC_DB_HANDLE __fastcall GetDBHandle();
	System::Classes::TStrings* __fastcall GetDeleteSQL();
	System::Classes::TStrings* __fastcall GetInsertSQL();
	Ibx::Ibsql::TIBXSQLDA* __fastcall GetSQLParams();
	System::Classes::TStrings* __fastcall GetRefreshSQL();
	System::Classes::TStrings* __fastcall GetSelectSQL();
	Ibx::Ibsql::TIBSQLTypes __fastcall GetStatementType();
	System::Classes::TStrings* __fastcall GetModifySQL();
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	Ibx::Ibheader::PISC_TR_HANDLE __fastcall GetTRHandle();
	void __fastcall InternalDeleteRecord(Ibx::Ibsql::TIBSQL* Qry, NativeInt Buff);
	bool __fastcall InternalLocate(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options);
	void __fastcall InternalPostRecord(Ibx::Ibsql::TIBSQL* Qry, NativeInt Buff);
	void __fastcall InternalRevertRecord(int RecordNumber);
	bool __fastcall IsVisible(NativeInt Buffer);
	void __fastcall SaveOldBuffer(NativeInt Buffer);
	void __fastcall SetBufferChunks(__int64 Value);
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* Value);
	void __fastcall SetDeleteSQL(System::Classes::TStrings* Value);
	void __fastcall SetInsertSQL(System::Classes::TStrings* Value);
	void __fastcall SetInternalSQLParams(Ibx::Ibsql::TIBSQL* Qry, NativeInt Buffer);
	void __fastcall SetRefreshSQL(System::Classes::TStrings* Value);
	void __fastcall SetSelectSQL(System::Classes::TStrings* Value);
	void __fastcall SetModifySQL(System::Classes::TStrings* Value);
	void __fastcall SetTransaction(Ibx::Ibdatabase::TIBTransaction* Value);
	void __fastcall SetUpdateRecordTypes(TIBUpdateRecordTypes Value);
	HIDESBASE void __fastcall SetUniDirectional(bool Value);
	void __fastcall RefreshParams();
	void __fastcall SQLChanging(System::TObject* Sender);
	NativeInt __fastcall AdjustPosition(NativeInt FCache, NativeInt Offset, int Origin);
	void __fastcall ReadCache(NativeInt FCache, NativeInt Offset, int Origin, NativeInt Buffer);
	void __fastcall ReadRecordCache(NativeInt RecordNumber, NativeInt Buffer, bool ReadOldBuffer);
	void __fastcall WriteCache(NativeInt FCache, NativeInt Offset, int Origin, NativeInt Buffer);
	void __fastcall WriteRecordCache(NativeInt RecordNumber, NativeInt Buffer);
	Data::Db::TGetResult __fastcall InternalGetRecord(NativeInt Buffer, Data::Db::TGetMode GetMode, bool DoCheck);
	void __fastcall SetGeneratorField(TIBGeneratorField* const Value);
	bool __fastcall InternalGetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer);
	virtual void __fastcall InternalSetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer);
	System::UnicodeString __fastcall GetPlan();
	bool __fastcall GetCanceled();
	
protected:
	void __fastcall ActivateConnection();
	bool __fastcall ActivateTransaction();
	void __fastcall DeactivateTransaction();
	void __fastcall CheckDatasetClosed();
	void __fastcall CheckDatasetOpen();
	NativeInt __fastcall GetActiveBuf();
	virtual void __fastcall InternalBatchInput(Ibx::Ibinputoutput::TIBBatchInput* InputObject);
	virtual void __fastcall InternalBatchOutput(Ibx::Ibinputoutput::TIBBatchOutput* OutputObject);
	virtual void __fastcall InternalPrepare();
	virtual void __fastcall InternalUnPrepare();
	virtual void __fastcall InternalExecQuery();
	virtual void __fastcall InternalRefreshRow();
	virtual void __fastcall InternalSetParamsFromCursor();
	void __fastcall CheckNotUniDirectional();
	virtual void __fastcall SetActive(bool Value);
	virtual void __fastcall PSEndTransaction(bool Commit);
	virtual void __fastcall PSExecute();
	virtual int __fastcall PSExecuteStatement(const System::UnicodeString ASQL, Data::Db::TParams* AParams)/* overload */;
	virtual int __fastcall PSExecuteStatement(const System::UnicodeString ASQL, Data::Db::TParams* AParams, Data::Db::TDataSet* &ResultSet)/* overload */;
	virtual System::UnicodeString __fastcall PSGetTableName();
	virtual System::UnicodeString __fastcall PSGetQuoteChar();
	virtual Data::Db::EUpdateError* __fastcall PSGetUpdateException(System::Sysutils::Exception* E, Data::Db::EUpdateError* Prev);
	virtual bool __fastcall PSInTransaction();
	virtual bool __fastcall PSIsSQLBased();
	virtual bool __fastcall PSIsSQLSupported();
	virtual void __fastcall PSStartTransaction();
	virtual void __fastcall PSReset();
	virtual bool __fastcall PSUpdateRecord(Data::Db::TUpdateKind UpdateKind, Data::Db::TDataSet* Delta);
	virtual void __fastcall InternalInsert();
	virtual void __fastcall InitRecord(NativeInt Buffer)/* overload */;
	virtual void __fastcall Disconnect();
	bool __fastcall ConstraintsStored();
	virtual void __fastcall ClearCalcFields(NativeInt Buffer)/* overload */;
	virtual void __fastcall ClearCalcFields(System::PByte Buffer)/* overload */;
	virtual void __fastcall CreateFields();
	virtual System::PByte __fastcall AllocRecordBuffer();
	virtual void __fastcall FreeRecordBuffer(System::PByte &Buffer);
	virtual void __fastcall DoBeforeDelete();
	virtual void __fastcall DoBeforeEdit();
	virtual void __fastcall DoBeforeInsert();
	virtual void __fastcall GetBookmarkData(NativeInt Buffer, System::TArray__1<System::Byte> Data)/* overload */;
	virtual Data::Db::TBookmarkFlag __fastcall GetBookmarkFlag(NativeInt Buffer)/* overload */;
	virtual bool __fastcall GetCanModify();
	virtual Data::Db::TDataSource* __fastcall GetDataSource();
	virtual Data::Db::TFieldClass __fastcall GetFieldClass(Data::Db::TFieldType FieldType)/* overload */;
	virtual int __fastcall GetRecNo();
	virtual Data::Db::TGetResult __fastcall GetRecord(NativeInt Buffer, Data::Db::TGetMode GetMode, bool DoCheck)/* overload */;
	virtual Data::Db::TGetResult __fastcall GetRecord(System::PByte Buffer, Data::Db::TGetMode GetMode, bool DoCheck)/* overload */;
	virtual int __fastcall GetRecordCount();
	virtual System::Word __fastcall GetRecordSize();
	virtual void __fastcall InternalAddRecord(NativeInt Buffer, bool Append)/* overload */;
	virtual void __fastcall InternalCancel();
	virtual void __fastcall InternalClose();
	virtual void __fastcall InternalDelete();
	virtual void __fastcall InternalFirst();
	virtual void __fastcall InternalGotoBookmark(System::TArray__1<System::Byte> Bookmark)/* overload */;
	virtual void __fastcall InternalGotoBookmark(void * Bookmark)/* overload */;
	virtual void __fastcall InternalHandleException();
	virtual void __fastcall InternalInitFieldDefs();
	virtual void __fastcall InternalInitRecord(NativeInt Buffer)/* overload */;
	virtual void __fastcall InternalLast();
	virtual void __fastcall InternalOpen();
	virtual void __fastcall InternalPost();
	virtual void __fastcall InternalRefresh();
	virtual void __fastcall InternalSetToRecord(NativeInt Buffer)/* overload */;
	virtual bool __fastcall IsCursorOpen();
	void __fastcall ReQuery();
	virtual void __fastcall SetBookmarkFlag(NativeInt Buffer, Data::Db::TBookmarkFlag Value)/* overload */;
	virtual void __fastcall SetBookmarkData(NativeInt Buffer, System::TArray__1<System::Byte> Data)/* overload */;
	void __fastcall SetCachedUpdates(bool Value);
	void __fastcall SetDataSource(Data::Db::TDataSource* Value);
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer)/* overload */;
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer, bool NativeFormat)/* overload */;
	virtual void __fastcall SetRecNo(int Value);
	virtual void __fastcall DoOnNewRecord();
	virtual void __fastcall Loaded();
	__property Ibx::Ibsql::TIBXSQLDA* SQLParams = {read=GetSQLParams};
	__property Ibx::Ibsql::TIBXSQLDA* Params = {read=GetSQLParams};
	__property bool InternalPrepared = {read=FInternalPrepared, nodefault};
	__property Ibx::Ibsql::TIBSQL* QDelete = {read=FQDelete};
	__property Ibx::Ibsql::TIBSQL* QInsert = {read=FQInsert};
	__property Ibx::Ibsql::TIBSQL* QRefresh = {read=FQRefresh};
	__property Ibx::Ibsql::TIBSQL* QSelect = {read=FQSelect};
	__property Ibx::Ibsql::TIBSQL* QModify = {read=FQModify};
	__property Ibx::Ibsql::TIBSQLTypes StatementType = {read=GetStatementType, nodefault};
	__property Ibx::Ibexternals::PVoid SelectStmtHandle = {read=GetSelectStmtHandle};
	__property TLiveModes LiveMode = {read=FLiveMode, nodefault};
	__property __int64 BufferChunks = {read=FBufferChunks, write=SetBufferChunks};
	__property bool CachedUpdates = {read=FCachedUpdates, write=SetCachedUpdates, nodefault};
	__property bool UniDirectional = {read=FUniDirectional, write=SetUniDirectional, nodefault};
	__property System::Classes::TStrings* DeleteSQL = {read=GetDeleteSQL, write=SetDeleteSQL};
	__property System::Classes::TStrings* InsertSQL = {read=GetInsertSQL, write=SetInsertSQL};
	__property System::Classes::TStrings* RefreshSQL = {read=GetRefreshSQL, write=SetRefreshSQL};
	__property System::Classes::TStrings* SelectSQL = {read=GetSelectSQL, write=SetSelectSQL};
	__property System::Classes::TStrings* ModifySQL = {read=GetModifySQL, write=SetModifySQL};
	__property Data::Db::TUpdateMode UpdateMode = {read=FUpdateMode, write=SetUpdateMode, nodefault};
	__property bool ParamCheck = {read=FParamCheck, write=FParamCheck, nodefault};
	__property TIBGeneratorField* GeneratorField = {read=FGeneratorField, write=SetGeneratorField};
	__property System::Classes::TNotifyEvent BeforeDatabaseDisconnect = {read=FBeforeDatabaseDisconnect, write=FBeforeDatabaseDisconnect};
	__property System::Classes::TNotifyEvent AfterDatabaseDisconnect = {read=FAfterDatabaseDisconnect, write=FAfterDatabaseDisconnect};
	__property System::Classes::TNotifyEvent DatabaseFree = {read=FDatabaseFree, write=FDatabaseFree};
	__property System::Classes::TNotifyEvent BeforeTransactionEnd = {read=FBeforeTransactionEnd, write=FBeforeTransactionEnd};
	__property System::Classes::TNotifyEvent AfterTransactionEnd = {read=FAfterTransactionEnd, write=FAfterTransactionEnd};
	__property System::Classes::TNotifyEvent TransactionFree = {read=FTransactionFree, write=FTransactionFree};
	
public:
	__fastcall virtual TIBCustomDataSet(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBCustomDataSet();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall ApplyUpdates();
	TCachedUpdateStatus __fastcall CachedUpdateStatus();
	void __fastcall CancelUpdates();
	void __fastcall FetchAll();
	bool __fastcall LocateNext(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options);
	void __fastcall RecordModified(bool Value);
	void __fastcall RevertRecord();
	void __fastcall Undelete();
	virtual void __fastcall Post();
	Ibx::Ibsql::TIBXSQLDA* __fastcall Current();
	Ibx::Ibsql::TIBSQLTypes __fastcall SQLType();
	virtual bool __fastcall BookmarkValid(System::TArray__1<System::Byte> Bookmark);
	virtual int __fastcall CompareBookmarks(System::TArray__1<System::Byte> Bookmark1, System::TArray__1<System::Byte> Bookmark2);
	virtual System::Classes::TStream* __fastcall CreateBlobStream(Data::Db::TField* Field, Data::Db::TBlobStreamMode Mode);
	virtual bool __fastcall GetCurrentRecord(NativeInt Buffer)/* overload */;
	virtual bool __fastcall GetFieldData _DEPRECATED_ATTRIBUTE0 (Data::Db::TField* Field, void * Buffer)/* overload */;
	virtual bool __fastcall GetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> &Buffer)/* overload */;
	virtual bool __fastcall GetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> &Buffer, bool NativeFormat)/* overload */;
	virtual bool __fastcall Locate(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options);
	virtual System::Variant __fastcall Lookup(const System::UnicodeString KeyFields, const System::Variant &KeyValues, const System::UnicodeString ResultFields);
	virtual Data::Db::TUpdateStatus __fastcall UpdateStatus();
	virtual bool __fastcall IsSequenced();
	void __fastcall OutputXML(Ibx::Ibinputoutput::TIBOutputXML* OutputObject);
	__property Ibx::Ibheader::PISC_DB_HANDLE DBHandle = {read=GetDBHandle};
	__property Ibx::Ibheader::PISC_TR_HANDLE TRHandle = {read=GetTRHandle};
	__property TIBDataSetUpdateObject* UpdateObject = {read=FUpdateObject, write=SetUpdateObject};
	__property bool UpdatesPending = {read=FUpdatesPending, nodefault};
	__property TIBUpdateRecordTypes UpdateRecordTypes = {read=FUpdateRecordTypes, write=SetUpdateRecordTypes, nodefault};
	__property int RowsAffected = {read=FRowsAffected, nodefault};
	__property System::UnicodeString Plan = {read=GetPlan};
	__property bool Canceled = {read=GetCanceled, nodefault};
	Ibx::Ibsql::TIBChangeState __fastcall ChangeState(Data::Db::TField* Field)/* overload */;
	Ibx::Ibsql::TIBChangeState __fastcall ChangeState(int Index)/* overload */;
	Ibx::Ibsql::TIBChangeState __fastcall ChangeState(System::UnicodeString FieldName)/* overload */;
	
__published:
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase, write=SetDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction, write=SetTransaction};
	__property bool ForcedRefresh = {read=FForcedRefresh, write=FForcedRefresh, nodefault};
	__property AutoCalcFields = {default=1};
	__property ObjectView;
	__property FieldOptions;
	__property AfterCancel;
	__property AfterClose;
	__property AfterDelete;
	__property AfterEdit;
	__property AfterInsert;
	__property AfterOpen;
	__property AfterPost;
	__property AfterRefresh;
	__property AfterScroll;
	__property BeforeCancel;
	__property BeforeClose;
	__property BeforeDelete;
	__property BeforeEdit;
	__property BeforeInsert;
	__property BeforeOpen;
	__property BeforePost;
	__property BeforeRefresh;
	__property BeforeScroll;
	__property OnCalcFields;
	__property OnDeleteError;
	__property OnEditError;
	__property OnNewRecord;
	__property OnPostError;
	__property TIBUpdateErrorEvent OnUpdateError = {read=FOnUpdateError, write=FOnUpdateError};
	__property TIBUpdateRecordEvent OnUpdateRecord = {read=FOnUpdateRecord, write=FOnUpdateRecord};
	/* Hoisted overloads: */
	
protected:
	inline int __fastcall  PSExecuteStatement _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (const System::UnicodeString ASQL, Data::Db::TParams* AParams, void * ResultSet){ return Data::Db::TDataSet::PSExecuteStatement(ASQL, AParams, ResultSet); }
	inline void __fastcall  InitRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer){ Data::Db::TDataSet::InitRecord(Buffer); }
	inline void __fastcall  GetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, System::TArray__1<System::Byte> Data){ Data::Db::TDataSet::GetBookmarkData(Buffer, Data); }
	inline void __fastcall  GetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, void * Data){ Data::Db::TDataSet::GetBookmarkData(Buffer, Data); }
	inline Data::Db::TBookmarkFlag __fastcall  GetBookmarkFlag _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer){ return Data::Db::TDataSet::GetBookmarkFlag(Buffer); }
	inline Data::Db::TFieldClass __fastcall  GetFieldClass(Data::Db::TFieldDef* FieldDef){ return Data::Db::TDataSet::GetFieldClass(FieldDef); }
	inline void __fastcall  InternalAddRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, bool Append){ Data::Db::TDataSet::InternalAddRecord(Buffer, Append); }
	inline void __fastcall  InternalAddRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (void * Buffer, bool Append){ Data::Db::TDataSet::InternalAddRecord(Buffer, Append); }
	inline void __fastcall  InternalInitRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer){ Data::Db::TDataSet::InternalInitRecord(Buffer); }
	inline void __fastcall  InternalSetToRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer){ Data::Db::TDataSet::InternalSetToRecord(Buffer); }
	inline void __fastcall  SetBookmarkFlag _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, Data::Db::TBookmarkFlag Value){ Data::Db::TDataSet::SetBookmarkFlag(Buffer, Value); }
	inline void __fastcall  SetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, System::TArray__1<System::Byte> Data){ Data::Db::TDataSet::SetBookmarkData(Buffer, Data); }
	inline void __fastcall  SetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, void * Data){ Data::Db::TDataSet::SetBookmarkData(Buffer, Data); }
	inline void __fastcall  SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer){ Data::Db::TDataSet::SetFieldData(Field, Buffer); }
	inline void __fastcall  SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat){ Data::Db::TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
	
public:
	inline bool __fastcall  GetCurrentRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer){ return Data::Db::TDataSet::GetCurrentRecord(Buffer); }
	inline bool __fastcall  GetFieldData(int FieldNo, System::TArray__1<System::Byte> &Buffer){ return Data::Db::TDataSet::GetFieldData(FieldNo, Buffer); }
	inline bool __fastcall  GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (int FieldNo, void * Buffer){ return Data::Db::TDataSet::GetFieldData(FieldNo, Buffer); }
	inline bool __fastcall  GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat){ return Data::Db::TDataSet::GetFieldData(Field, Buffer, NativeFormat); }
	
};


class PASCALIMPLEMENTATION TIBDataSet : public TIBCustomDataSet
{
	typedef TIBCustomDataSet inherited;
	
private:
	Data::Db::TParams* FPSParams;
	bool __fastcall GetPrepared();
	void __fastcall CreateParams();
	
protected:
	virtual Data::Db::TParams* __fastcall PSGetParams();
	virtual void __fastcall PSSetParams(Data::Db::TParams* AParams);
	virtual void __fastcall PSSetCommandText(const System::UnicodeString CommandText);
	virtual System::UnicodeString __fastcall PSGetCommandText();
	virtual Data::Db::TPSCommandType __fastcall PSGetCommandType();
	virtual void __fastcall SetFiltered(bool Value);
	virtual void __fastcall InternalOpen();
	
public:
	void __fastcall Prepare();
	void __fastcall UnPrepare();
	void __fastcall BatchInput(Ibx::Ibinputoutput::TIBBatchInput* InputObject);
	void __fastcall BatchOutput(Ibx::Ibinputoutput::TIBBatchOutput* OutputObject);
	void __fastcall ExecSQL();
	__fastcall virtual ~TIBDataSet();
	Ibx::Ibsql::TIBXSQLVAR* __fastcall ParamByName(System::UnicodeString Idx);
	__property Params;
	__property bool Prepared = {read=GetPrepared, nodefault};
	__property StatementType;
	__property SelectStmtHandle;
	__property LiveMode;
	
__published:
	__property BufferChunks;
	__property CachedUpdates;
	__property DeleteSQL;
	__property InsertSQL;
	__property RefreshSQL;
	__property SelectSQL;
	__property ModifySQL;
	__property ParamCheck;
	__property UniDirectional;
	__property Filtered = {default=0};
	__property GeneratorField;
	__property BeforeDatabaseDisconnect;
	__property AfterDatabaseDisconnect;
	__property DatabaseFree;
	__property BeforeTransactionEnd;
	__property AfterTransactionEnd;
	__property TransactionFree;
	__property UpdateObject;
	__property Active = {default=0};
	__property AutoCalcFields = {default=1};
	__property DataSource = {read=GetDataSource, write=SetDataSource};
	__property AfterCancel;
	__property AfterClose;
	__property AfterDelete;
	__property AfterEdit;
	__property AfterInsert;
	__property AfterOpen;
	__property AfterPost;
	__property AfterScroll;
	__property BeforeCancel;
	__property BeforeClose;
	__property BeforeDelete;
	__property BeforeEdit;
	__property BeforeInsert;
	__property BeforeOpen;
	__property BeforePost;
	__property BeforeScroll;
	__property OnCalcFields;
	__property OnDeleteError;
	__property OnEditError;
	__property OnFilterRecord;
	__property OnNewRecord;
	__property OnPostError;
public:
	/* TIBCustomDataSet.Create */ inline __fastcall virtual TIBDataSet(System::Classes::TComponent* AOwner) : TIBCustomDataSet(AOwner) { }
	
};


class PASCALIMPLEMENTATION TIBDSBlobStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
protected:
	Data::Db::TField* FField;
	Ibx::Ibblob::TIBBlobStream* FBlobStream;
	bool FModified;
	__int64 FConvertedPosition;
	
public:
	__fastcall TIBDSBlobStream(Data::Db::TField* AField, Ibx::Ibblob::TIBBlobStream* ABlobStream, Data::Db::TBlobStreamMode Mode);
	__fastcall virtual ~TIBDSBlobStream();
#ifndef __aarch64__
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
	virtual int __fastcall Seek(int Offset, System::Word Origin)/* overload */;
	virtual void __fastcall SetSize(int NewSize)/* overload */;
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall Read(void *Buffer, long Count)/* overload */;
	virtual long __fastcall Seek(long Offset, System::Word Origin)/* overload */;
	virtual void __fastcall SetSize(long NewSize)/* overload */;
	virtual long __fastcall Write(const void *Buffer, long Count)/* overload */;
#endif /* __aarch64__ */
	/* Hoisted overloads: */
	
public:
#ifndef __aarch64__
	inline int __fastcall  Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
#else /* __aarch64__ */
	inline long __fastcall  Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
#endif /* __aarch64__ */
	inline __int64 __fastcall  Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
	
protected:
	inline void __fastcall  SetSize(const __int64 NewSize){ System::Classes::TStream::SetSize(NewSize); }
	
public:
#ifndef __aarch64__
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* __aarch64__ */
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Offset, long Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* __aarch64__ */
	
};


typedef System::Generics::Collections::TDictionary__2<Data::Db::TFieldType,Data::Db::TFieldClass>* TIBDefaultFieldClasses;

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word BufferCacheSize = System::Word(0x3e8);
static constexpr System::Int8 UniCache = System::Int8(0x2);
extern DELPHI_PACKAGE System::Generics::Collections::TDictionary__2<Data::Db::TFieldType,Data::Db::TFieldClass>* DefaultFieldClasses;
extern DELPHI_PACKAGE Ibx::Ibsql::TIBChangeState __fastcall ChangeState(Data::Db::TField* Field);
}	/* namespace Ibcustomdataset */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBCUSTOMDATASET)
using namespace Ibx::Ibcustomdataset;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbcustomdatasetHPP
