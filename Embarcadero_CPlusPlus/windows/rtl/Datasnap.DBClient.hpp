// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DBClient.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DbclientHPP
#define Datasnap_DbclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DSIntf.hpp>
#include <Data.DBCommon.hpp>
#include <Data.DBCommonTypes.hpp>
#include <Datasnap.Midas.hpp>
#include <Data.SqlTimSt.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dbclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EDBClient;
class DELPHICLASS EReconcileError;
class DELPHICLASS TCustomRemoteServer;
class DELPHICLASS TConnectionBroker;
class DELPHICLASS TAggregate;
class DELPHICLASS TAggregates;
struct TRecInfo;
struct TKeyBuffer;
struct TReconcileInfo;
class DELPHICLASS TCustomClientDataSet;
class DELPHICLASS TClientDataSet;
class DELPHICLASS TClientBlobStream;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EDBClient : public Data::Db::EDatabaseError
{
	typedef Data::Db::EDatabaseError inherited;
	
private:
	System::Word FErrorCode;
	
public:
	__fastcall EDBClient(System::UnicodeString Message, System::Word ErrorCode);
	__property System::Word ErrorCode = {read=FErrorCode, nodefault};
public:
	/* Exception.CreateFmt */ inline __fastcall EDBClient(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Data::Db::EDatabaseError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDBClient(NativeUInt Ident)/* overload */ : Data::Db::EDatabaseError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDBClient(System::PResStringRec ResStringRec)/* overload */ : Data::Db::EDatabaseError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDBClient(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Data::Db::EDatabaseError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDBClient(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Data::Db::EDatabaseError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDBClient(const System::UnicodeString Msg, int AHelpContext) : Data::Db::EDatabaseError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDBClient(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Data::Db::EDatabaseError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDBClient(NativeUInt Ident, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDBClient(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDBClient(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDBClient(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDBClient() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EReconcileError : public EDBClient
{
	typedef EDBClient inherited;
	
private:
	System::UnicodeString FContext;
	System::Word FPreviousError;
	
public:
	__fastcall EReconcileError(System::UnicodeString NativeError, System::UnicodeString Context, System::Word ErrorCode, System::Word PreviousError);
	__property System::UnicodeString Context = {read=FContext};
	__property System::Word PreviousError = {read=FPreviousError, nodefault};
public:
	/* Exception.CreateFmt */ inline __fastcall EReconcileError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDBClient(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EReconcileError(NativeUInt Ident)/* overload */ : EDBClient(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EReconcileError(System::PResStringRec ResStringRec)/* overload */ : EDBClient(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EReconcileError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDBClient(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EReconcileError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDBClient(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EReconcileError(const System::UnicodeString Msg, int AHelpContext) : EDBClient(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EReconcileError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDBClient(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EReconcileError(NativeUInt Ident, int AHelpContext)/* overload */ : EDBClient(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EReconcileError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDBClient(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EReconcileError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDBClient(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EReconcileError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDBClient(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EReconcileError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TGetUsernameEvent)(System::TObject* Sender, System::UnicodeString &Username);

class PASCALIMPLEMENTATION TCustomRemoteServer : public Data::Db::TCustomConnection
{
	typedef Data::Db::TCustomConnection inherited;
	
private:
	System::Variant FAppServer;
	TGetUsernameEvent FOnGetUsername;
	
protected:
	virtual System::Variant __fastcall GetAppServer();
	virtual void __fastcall SetAppServer(const System::Variant &Value);
	__property TGetUsernameEvent OnGetUsername = {read=FOnGetUsername, write=FOnGetUsername};
	
public:
	__fastcall virtual TCustomRemoteServer(System::Classes::TComponent* AOwner);
	virtual Datasnap::Midas::_di_IAppServer __fastcall GetServer();
	virtual System::OleVariant __fastcall GetServerList();
	virtual void __fastcall GetProviderNames(System::Classes::TGetStrProc Proc);
	__property System::Variant AppServer = {read=GetAppServer};
public:
	/* TCustomConnection.Destroy */ inline __fastcall virtual ~TCustomRemoteServer() { }
	
};


class PASCALIMPLEMENTATION TConnectionBroker : public TCustomRemoteServer
{
	typedef TCustomRemoteServer inherited;
	
private:
	TCustomRemoteServer* FConnection;
	bool FStreamedConnected;
	void __fastcall SetConnection(TCustomRemoteServer* const Value);
	
protected:
	virtual System::Variant __fastcall GetAppServer();
	virtual bool __fastcall GetConnected();
	virtual void __fastcall Loaded();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall SetConnected(bool Value);
	
public:
	__fastcall virtual TConnectionBroker(System::Classes::TComponent* AOwner);
	virtual Datasnap::Midas::_di_IAppServer __fastcall GetServer();
	
__published:
	__property Connected = {default=0};
	__property TCustomRemoteServer* Connection = {read=FConnection, write=SetConnection};
	__property LoginPrompt = {default=0};
	__property AfterConnect;
	__property AfterDisconnect;
	__property BeforeConnect;
	__property BeforeDisconnect;
	__property OnGetUsername;
	__property OnLogin;
public:
	/* TCustomConnection.Destroy */ inline __fastcall virtual ~TConnectionBroker() { }
	
};


typedef void __fastcall (__closure *TAggUpdateEvent)(TAggregate* Agg);

class PASCALIMPLEMENTATION TAggregate : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FExpression;
	Datasnap::Dsintf::DSFLDDesc FFldDesc;
	Datasnap::Dsintf::hDSAggregate FHAggregate;
	System::UnicodeString FAggregateName;
	int FGroupingLevel;
	TCustomClientDataSet* FDataSet;
	System::UnicodeString FIndexName;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FDataBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FDataBuffer;
#endif /* _WIN64 */
	Data::Db::TFieldType FDataType;
	int FDataSize;
	System::Classes::TBits* FDependentFields;
	int FRecBufOfs;
	bool FInUse;
	bool FActive;
	bool FVisible;
	bool FOutOfDate;
	TAggUpdateEvent FOnUpdate;
	void __fastcall SetActive(bool Value);
	void __fastcall SetExpression(const System::UnicodeString Text);
	void __fastcall SetGroupingLevel(int GroupingLevel);
	void __fastcall SetIndexName(System::UnicodeString Value);
	
protected:
	void __fastcall Activate();
	__property System::Classes::TBits* DependentFields = {read=FDependentFields};
	__property int RecBufOfs = {read=FRecBufOfs, write=FRecBufOfs, nodefault};
	
public:
	__fastcall TAggregate(TAggregates* Aggregates, TCustomClientDataSet* ADataSet)/* overload */;
	__fastcall virtual ~TAggregate();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual System::UnicodeString __fastcall GetDisplayName();
	System::Variant __fastcall Value();
	__property Datasnap::Dsintf::hDSAggregate AggHandle = {read=FHAggregate, write=FHAggregate, nodefault};
	__property bool InUse = {read=FInUse, write=FInUse, default=0};
	__property TCustomClientDataSet* DataSet = {read=FDataSet};
	__property int DataSize = {read=FDataSize, nodefault};
	__property Data::Db::TFieldType DataType = {read=FDataType, nodefault};
	
__published:
	__property bool Active = {read=FActive, write=SetActive, default=0};
	__property System::UnicodeString AggregateName = {read=FAggregateName, write=FAggregateName};
	__property System::UnicodeString Expression = {read=FExpression, write=SetExpression};
	__property int GroupingLevel = {read=FGroupingLevel, write=SetGroupingLevel, default=0};
	__property System::UnicodeString IndexName = {read=FIndexName, write=SetIndexName};
	__property bool Visible = {read=FVisible, write=FVisible, default=1};
	__property TAggUpdateEvent OnUpdate = {read=FOnUpdate, write=FOnUpdate};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAggregates : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TAggregate* operator[](int Index) { return this->Items[Index]; }
	
private:
	System::Classes::TPersistent* FOwner;
	HIDESBASE TAggregate* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TAggregate* Value);
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	
public:
	__fastcall TAggregates(System::Classes::TPersistent* Owner);
	HIDESBASE TAggregate* __fastcall Add();
	HIDESBASE void __fastcall Clear();
	TAggregate* __fastcall Find(const System::UnicodeString DisplayName);
	int __fastcall IndexOf(const System::UnicodeString DisplayName);
	__property TAggregate* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TAggregates() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<Datasnap::Dsintf::DSFLDDesc> TFieldDescList;

typedef TRecInfo *PRecInfo;

#ifndef _WIN64
#pragma pack(push,1)
#endif /* not _WIN64 */
struct DECLSPEC_DRECORD TRecInfo
{
public:
	int RecordNumber;
	Data::Db::TBookmarkFlag BookmarkFlag;
	Datasnap::Dsintf::DSAttr Attribute;
};
#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */


typedef TRecInfo TCDSRecInfo;

typedef TKeyBuffer *PKeyBuffer;

struct DECLSPEC_DRECORD TKeyBuffer
{
	
private:
	struct DECLSPEC_DRECORD _TKeyBuffer__1
	{
	};
	
	
	
public:
	bool Modified;
	bool Exclusive;
	int FieldCount;
	_TKeyBuffer__1 Data;
};


typedef TKeyBuffer TCDSKeyBuffer;

enum DECLSPEC_DENUM TDataPacketFormat : unsigned char { dfBinary, dfXML, dfXMLUTF8 };

enum DECLSPEC_DENUM TReconcileAction : unsigned char { raSkip, raAbort, raMerge, raCorrect, raCancel, raRefresh };

typedef void __fastcall (__closure *TReconcileErrorEvent)(TCustomClientDataSet* DataSet, EReconcileError* E, Data::Db::TUpdateKind UpdateKind, TReconcileAction &Action);

typedef void __fastcall (__closure *TRemoteEvent)(System::TObject* Sender, System::OleVariant &OwnerData);

struct DECLSPEC_DRECORD TReconcileInfo
{
public:
	Data::Db::TDataSet* DataSet;
	Data::Db::TUpdateKind UpdateKind;
	EReconcileError* ReconcileError;
	TReconcileAction *ActionRef;
};


enum DECLSPEC_DENUM TDataSetOption : unsigned char { doDisableInserts, doDisableDeletes, doDisableEdits, doNoResetCall };

typedef System::Set<TDataSetOption, TDataSetOption::doDisableInserts, TDataSetOption::doNoResetCall> TDataSetOptions;

enum DECLSPEC_DENUM TFetchOption : unsigned char { foRecord, foBlobs, foDetails };

typedef System::Set<TFetchOption, TFetchOption::foRecord, TFetchOption::foDetails> TFetchOptions;

class PASCALIMPLEMENTATION TCustomClientDataSet : public Data::Db::TDataSet
{
	typedef Data::Db::TDataSet inherited;
	
	
public:
	class DELPHICLASS TPersistDataPacket;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TPersistDataPacket : public System::Classes::TPersistent
	{
		typedef System::Classes::TPersistent inherited;
		
	private:
		TCustomClientDataSet* FDataSet;
		
	protected:
		virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
		
	public:
		__fastcall TPersistDataPacket(TCustomClientDataSet* const ADataSet);
	public:
		/* TPersistent.Destroy */ inline __fastcall virtual ~TPersistDataPacket() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	TPersistDataPacket* FPersistDataPacket;
	System::Generics::Collections::TList__1<System::Classes::TList*>* FActiveAggLists;
	System::Classes::TBits* FAggFieldsUpdated;
	bool FAggFieldsInit;
	int FAggFieldsSize;
	int FAggGrpIndOfs;
	int FAggFieldsOfs;
	int FAggGrpIndSize;
	TAggregates* FAggregates;
	bool FAggregatesActive;
	System::WideString FCommandText;
	bool FDisableStringTrim;
	Datasnap::Dsintf::_di_IDSBase FDSBase;
	Datasnap::Dsintf::_di_IDSCursor FDSCursor;
	TDataSetOptions FDSOptions;
	Datasnap::Dsintf::_di_IDSCursor FFindCursor;
	TCustomClientDataSet* FCloneSource;
	TCustomClientDataSet* FReconcileDataSet;
	System::TVarArray *FSavedPacket;
	System::TVarArray *FDeltaPacket;
	Data::Db::TParams* FParams;
	Data::Db::TIndexDefs* FIndexDefs;
	System::UnicodeString FIndexName;
	void *FExprFilter;
	void *FFuncFilter;
	System::UnicodeString FFileName;
	NativeInt FFilterBuffer;
	int FGroupingLevel;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FLastParentBM;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FLastParentBM;
#endif /* _WIN64 */
	Data::Db::TMasterDataLink* FMasterLink;
	Datasnap::Dsintf::DSKEY FIndexFieldMap;
	System::StaticArray<PKeyBuffer, 6> FKeyBuffers;
	TKeyBuffer *FKeyBuffer;
	NativeInt FNewValueBuffer;
	NativeInt FOldValueBuffer;
	NativeInt FCurValueBuffer;
	int FIndexFieldCount;
	int FIndexGroupingLevel;
	Datasnap::Midas::_di_IAppServer FAppServer;
	System::UnicodeString FProviderName;
	TCustomRemoteServer* FRemoteServer;
	int FPacketRecords;
	int FConstDisableCount;
	int FMaxAggGroupingLevel;
	TCustomClientDataSet* FParentDataSet;
	System::Word FKeySize;
	int FRecordSize;
	int FBookmarkOfs;
	int FRecInfoOfs;
	int FRecBufSize;
	bool FReadOnly;
	bool FFieldsIndex;
	bool FCanModify;
	bool FInReconcileCallback;
	bool FNotifyCallback;
	bool FOpeningFile;
	bool FProviderEOF;
	bool FFetchOnDemand;
	bool FStoreDefs;
	bool FSavePacketOnClose;
	TReconcileErrorEvent FOnReconcileError;
	Data::Db::TUpdateStatusSet FStatusFilter;
	TRemoteEvent FBeforeApplyUpdates;
	TRemoteEvent FAfterApplyUpdates;
	TRemoteEvent FBeforeGetRecords;
	TRemoteEvent FAfterGetRecords;
	TRemoteEvent FBeforeRowRequest;
	TRemoteEvent FAfterRowRequest;
	TRemoteEvent FBeforeExecute;
	TRemoteEvent FAfterExecute;
	TRemoteEvent FBeforeGetParams;
	TRemoteEvent FAfterGetParams;
	TConnectionBroker* FConnectionBroker;
	bool FRanged;
	bool FIncludeBlobsInDelta;
	void __fastcall AddExprFilter(const System::UnicodeString Expr, Data::Db::TFilterOptions Options);
	void __fastcall AddFuncFilter();
	System::Word __stdcall CalcFieldsCallBack(NativeInt RecBuf);
	void __fastcall CheckFieldProps();
	void __fastcall CheckMasterRange();
	void __fastcall ClearActiveAggs();
	void __fastcall ClearSavedPacket();
	void __fastcall CloseAggs();
	Datasnap::Dsintf::_di_IDSBase __fastcall CreateDSBase();
	Datasnap::Dsintf::_di_IDSCursor __fastcall CreateDSCursor(Datasnap::Dsintf::_di_IDSCursor SourceCursor);
	void __fastcall DecodeIndexDesc(const Datasnap::Dsintf::DSIDXDesc &IndexDesc, System::UnicodeString &Name, System::UnicodeString &Fields, System::UnicodeString &DescFields, System::UnicodeString &CaseInsFields, Data::Db::TIndexOptions &Options);
	void __fastcall EncodeFieldDesc(Datasnap::Dsintf::DSFLDDesc &FieldDesc, const System::UnicodeString Name, Data::Db::TFieldType DataType, int Size, int Precision, bool Calculated, Data::Db::TFieldAttributes Attributes);
	void __fastcall EncodeIndexDesc(Datasnap::Dsintf::DSIDXDesc &IndexDesc, const System::UnicodeString Name, const System::UnicodeString Fields, const System::UnicodeString DescFields, const System::UnicodeString CaseInsFields, Data::Db::TIndexOptions Options);
	System::LongBool __stdcall FilterCallback(NativeInt RecBuf);
	void __fastcall DoAggUpdates(bool IsUpdate);
	System::Classes::TList* __fastcall GetActiveAggs(int Index);
	bool __fastcall GetActiveRecBuf(NativeInt &RecBuf);
	void __fastcall GetAggFieldData(NativeInt Buffer);
	__int64 __fastcall GetChangeCount();
	bool __fastcall GetUpdatesPending();
	System::OleVariant __fastcall GetData();
	int __fastcall GetDataSize();
	System::OleVariant __fastcall GetDelta();
	HIDESBASE Data::Db::TIndexDefs* __fastcall GetIndexDefs();
	System::UnicodeString __fastcall GetIndexFieldNames();
	System::UnicodeString __fastcall GetIndexName();
	bool __fastcall GetLogChanges();
	System::UnicodeString __fastcall GetMasterFields();
	bool __fastcall GetProviderEOF();
	__int64 __fastcall GetSavePoint();
	bool __fastcall GetHasAppServer();
	void __fastcall InitBufferPointers(bool GetProps);
	Data::Db::TGroupPosInds __fastcall InternalGetGroupState(int Level);
	void __fastcall InternalCheck(System::Word Status);
	void __fastcall InternalFetch(TFetchOptions Options);
	void __fastcall MasterChanged(System::TObject* Sender);
	void __fastcall MasterDisabled(System::TObject* Sender);
	void __stdcall NotifyCallback();
	void __fastcall ReadData(System::Classes::TStream* Stream);
	int __stdcall ReconcileCallback(int iRslt, Datasnap::Dsintf::DSAttr iUpdateKind, int iResAction, int iErrCode, void * pErrMessage, void * pErrContext, void * pRecUpd, void * pRecOrg, void * pRecConflict, int iLevels, System::PInteger piFieldIDs);
	void __fastcall ResetAgg(TAggregate* Agg, bool DeleteFirst);
	void __fastcall ResetAllAggs(bool Value);
	void __fastcall ResetGrouping();
	void __fastcall SetAggsActive(bool Value);
	void __fastcall SetConnectionBroker(TConnectionBroker* const Value);
	void __fastcall SaveDataPacket(TDataPacketFormat Format = (TDataPacketFormat)(0x0));
	void __fastcall SetData(const System::OleVariant &Value);
	void __fastcall SetDataSource(Data::Db::TDataSource* Value);
	void __fastcall SetDisableStringTrim(bool Value);
	void __fastcall SetIndex(const System::UnicodeString Value, bool FieldsIndex);
	void __fastcall SetIndexDefs(Data::Db::TIndexDefs* Value);
	void __fastcall SetFileName(const System::UnicodeString Value);
	void __fastcall SetIndexFieldNames(const System::UnicodeString Value);
	void __fastcall SetIndexName(const System::UnicodeString Value);
	void __fastcall SetLogChanges(bool Value);
	void __fastcall SetMasterFields(const System::UnicodeString Value);
	void __fastcall SetNotifyCallback();
	void __fastcall SetParams(Data::Db::TParams* Value);
	void __fastcall SetProviderName(const System::UnicodeString Value);
	void __fastcall SetReadOnly(bool Value);
	void __fastcall SetSavePoint(__int64 Value);
	void __fastcall SortOnFields(Datasnap::Dsintf::_di_IDSCursor Cursor, const System::UnicodeString Fields, bool CaseInsensitive, bool Descending);
	void __fastcall SetupConstraints();
	void __fastcall SetupInternalCalcFields(bool Add);
	void __fastcall WriteData(System::Classes::TStream* Stream);
	void __fastcall SetStatusFilter(const Data::Db::TUpdateStatusSet Value);
	System::UnicodeString __fastcall GetXMLData();
	void __fastcall SetXMLData(const System::UnicodeString Value);
	void __fastcall SetPersistDataPacket(TPersistDataPacket* const Value);
	bool __fastcall DataStored(TCustomClientDataSet* const AAncestor);
	void __fastcall SetIncludeBlobsInDelta(bool Value);
	
protected:
	virtual System::UnicodeString __fastcall PSGetCommandText();
	virtual Data::Db::TPSCommandType __fastcall PSGetCommandType();
	virtual Data::Db::TIndexDefs* __fastcall PSGetIndexDefs(Data::Db::TIndexOptions IndexTypes);
	virtual Data::Db::TDataSetCommandStates __fastcall GetCommandStates(const System::UnicodeString ACommand);
	virtual void __fastcall ExecuteCommand(const System::UnicodeString ACommand, const System::TVarRec *Args, const int Args_High);
	virtual void __fastcall DoAfterApplyUpdates(System::OleVariant &OwnerData);
	virtual void __fastcall DoBeforeApplyUpdates(System::OleVariant &OwnerData);
	virtual System::OleVariant __fastcall DoApplyUpdates(const System::OleVariant &Delta, int MaxErrors, /* out */ int &ErrorCount);
	virtual void __fastcall DoAfterGetParams(System::OleVariant &OwnerData);
	virtual void __fastcall DoBeforeGetParams(System::OleVariant &OwnerData);
	virtual void __fastcall DoAfterGetRecords(System::OleVariant &OwnerData);
	virtual void __fastcall DoBeforeGetRecords(System::OleVariant &OwnerData);
	virtual System::OleVariant __fastcall DoGetRecords(int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, const System::OleVariant &Params);
	virtual void __fastcall DoAfterRowRequest(System::OleVariant &OwnerData);
	virtual void __fastcall DoBeforeRowRequest(System::OleVariant &OwnerData);
	virtual System::OleVariant __fastcall DoRowRequest(const System::OleVariant &Row, int RequestType);
	virtual void __fastcall DoAfterExecute(System::OleVariant &OwnerData);
	virtual void __fastcall DoBeforeExecute(System::OleVariant &OwnerData);
	virtual void __fastcall DoExecute(const System::OleVariant &Params);
	void __fastcall ActivateFilters();
	virtual void __fastcall AddDataPacket(const System::OleVariant &Data, bool HitEOF);
	void __fastcall AddFieldDesc(TFieldDescList FieldDescs, int &DescNo, int &FieldID, Data::Db::TFieldDefs* FieldDefs);
	void __fastcall AllocKeyBuffers();
	virtual System::PByte __fastcall AllocRecordBuffer();
	void __fastcall Check(System::Word Status);
	virtual void __fastcall CheckDetailRecords();
	virtual void __fastcall CheckProviderEOF();
	void __fastcall CheckSetKeyMode();
	virtual void __fastcall ClearCalcFields(NativeInt Buffer)/* overload */;
	virtual void __fastcall ClearCalcFields _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer)/* overload */;
	virtual void __fastcall CloseCursor();
#ifndef _WIN64
	virtual void __fastcall DataConvert(Data::Db::TField* Field, System::DynamicArray<System::Byte> Source, System::DynamicArray<System::Byte> &Dest, bool ToNative)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall DataConvert(Data::Db::TField* Field, System::TArray__1<System::Byte> Source, System::TArray__1<System::Byte> &Dest, bool ToNative)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall DataConvert _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Source, void * Dest, bool ToNative)/* overload */;
	virtual void __fastcall DataEvent(Data::Db::TDataEvent Event, NativeInt Info);
	void __fastcall DeactivateFilters();
	virtual void __fastcall DefChanged(System::TObject* Sender);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall DestroyLookupCursor();
	virtual void __fastcall DoBeforeInsert();
	virtual void __fastcall DoOnNewRecord();
	virtual void __fastcall FetchMoreData(bool All);
	virtual bool __fastcall FindRecord(bool Restart, bool GoForward);
	void __fastcall FreeKeyBuffers();
	virtual void __fastcall FreeRecordBuffer(System::PByte &Buffer);
	virtual System::Variant __fastcall GetAggregateValue(Data::Db::TField* Field);
	virtual Datasnap::Midas::_di_IAppServer __fastcall GetAppServer();
#ifndef _WIN64
	virtual void __fastcall GetBookmarkData(NativeInt Buffer, System::DynamicArray<System::Byte> Data)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall GetBookmarkData(NativeInt Buffer, System::TArray__1<System::Byte> Data)/* overload */;
#endif /* _WIN64 */
	virtual Data::Db::TBookmarkFlag __fastcall GetBookmarkFlag(NativeInt Buffer)/* overload */;
#ifndef _WIN64
	virtual void __fastcall GetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, System::DynamicArray<System::Byte> Data)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall GetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, System::TArray__1<System::Byte> Data)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall GetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, void * Data)/* overload */;
	virtual Data::Db::TBookmarkFlag __fastcall GetBookmarkFlag _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer)/* overload */;
	virtual bool __fastcall GetCanModify();
	virtual bool __fastcall GetCanRefresh();
	virtual Data::Db::TDataSource* __fastcall GetDataSource();
	Data::Db::TField* __fastcall GetIndexField(int Index);
	int __fastcall GetIndexFieldCount();
	virtual bool __fastcall GetIsClone();
	virtual bool __fastcall GetIsIndexField(Data::Db::TField* Field);
	PKeyBuffer __fastcall GetKeyBuffer(Data::Dbcommontypes::TKeyIndex KeyIndex);
	bool __fastcall GetKeyExclusive();
	int __fastcall GetKeyFieldCount();
	virtual bool __fastcall GetModifiedBlobCached();
	virtual Data::Db::TGetResult __fastcall GetRecord(NativeInt Buffer, Data::Db::TGetMode GetMode, bool DoCheck)/* overload */;
	virtual Data::Db::TGetResult __fastcall GetRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, Data::Db::TGetMode GetMode, bool DoCheck)/* overload */;
	virtual int __fastcall GetRecordCount();
	virtual int __fastcall GetRecNo();
	virtual System::Word __fastcall GetRecordSize();
	virtual TCustomRemoteServer* __fastcall GetRemoteServer();
	virtual System::Variant __fastcall GetStateFieldValue(Data::Db::TDataSetState State, Data::Db::TField* Field);
	PKeyBuffer __fastcall InitKeyBuffer(PKeyBuffer Buffer);
	virtual void __fastcall InitRecord(NativeInt Buffer)/* overload */;
	virtual void __fastcall InternalAddRecord(NativeInt Buffer, bool Append)/* overload */;
	virtual void __fastcall InitRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer)/* overload */;
	virtual void __fastcall InternalAddRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, bool Append)/* overload */;
	virtual void __fastcall InternalAddRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (void * Buffer, bool Append)/* overload */;
	virtual void __fastcall InternalCancel();
	virtual void __fastcall InternalClose();
	virtual void __fastcall InternalDelete();
	virtual void __fastcall InternalEdit();
	virtual void __fastcall InternalFirst();
	System::OleVariant __fastcall InternalGetOptionalParam(const System::UnicodeString ParamName, int FieldNo = 0x0);
	void __fastcall InternalSetOptionalParam(const System::UnicodeString ParamName, const System::OleVariant &Value, bool IncludeInDelta = false, int FieldNo = 0x0);
#ifndef _WIN64
	virtual void __fastcall InternalGotoBookmark(System::DynamicArray<System::Byte> Bookmark)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall InternalGotoBookmark(System::TArray__1<System::Byte> Bookmark)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall InternalGotoBookmark _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (void * Bookmark)/* overload */;
	virtual void __fastcall InternalHandleException();
	virtual void __fastcall InternalInitFieldDefs();
	virtual void __fastcall InternalInitRecord(NativeInt Buffer)/* overload */;
	virtual void __fastcall InternalInitRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer)/* overload */;
	virtual void __fastcall InternalInsert();
	virtual void __fastcall InternalLast();
	virtual void __fastcall InternalOpen();
	virtual void __fastcall InternalRefresh();
	virtual void __fastcall InternalPost();
	virtual void __fastcall InternalSetToRecord(NativeInt Buffer)/* overload */;
	virtual void __fastcall InternalSetToRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer)/* overload */;
	virtual bool __fastcall IsCursorOpen();
	virtual void __fastcall Loaded();
	bool __fastcall LocateRecord(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options, bool SyncCursor);
	virtual void __fastcall OpenCursor(bool InfoQuery);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall PostKeyBuffer(bool Commit);
	virtual void __fastcall RefreshInternalCalcFields(NativeInt Buffer)/* overload */;
	virtual void __fastcall RefreshInternalCalcFields _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer)/* overload */;
	void __fastcall ReadDataPacket(System::Classes::TStream* Stream, bool ReadSize);
	virtual void __fastcall ResetAggField(Data::Db::TField* Field);
	bool __fastcall ResetCursorRange();
	virtual void __fastcall SetAggregates(TAggregates* Value);
	void __fastcall SetAltRecBuffers(NativeInt Old, NativeInt New, NativeInt Cur);
	virtual void __fastcall SetAppServer(Datasnap::Midas::_di_IAppServer Value);
#ifndef _WIN64
	virtual void __fastcall SetBookmarkData(NativeInt Buffer, System::DynamicArray<System::Byte> Data)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall SetBookmarkData(NativeInt Buffer, System::TArray__1<System::Byte> Data)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall SetBookmarkFlag(NativeInt Buffer, Data::Db::TBookmarkFlag Value)/* overload */;
#ifndef _WIN64
	virtual void __fastcall SetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, System::DynamicArray<System::Byte> Data)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall SetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, System::TArray__1<System::Byte> Data)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall SetBookmarkData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, void * Data)/* overload */;
	virtual void __fastcall SetBookmarkFlag _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer, Data::Db::TBookmarkFlag Value)/* overload */;
	virtual void __fastcall SetCommandText(System::WideString Value);
	bool __fastcall SetCursorRange();
	virtual void __fastcall SetDataSetField(Data::Db::TDataSetField* const Value);
#ifndef _WIN64
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::DynamicArray<System::Byte> Buffer)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer)/* overload */;
	void __fastcall SetFilterData(const System::UnicodeString Text, Data::Db::TFilterOptions Options);
	virtual void __fastcall SetFiltered(bool Value);
	virtual void __fastcall SetFilterOptions(Data::Db::TFilterOptions Value);
	virtual void __fastcall SetFilterText(const System::UnicodeString Value);
	void __fastcall SetIndexField(int Index, Data::Db::TField* Value);
	void __fastcall SetKeyBuffer(Data::Dbcommontypes::TKeyIndex KeyIndex, bool Clear);
	void __fastcall SetKeyExclusive(bool Value);
	void __fastcall SetKeyFieldCount(int Value);
	void __fastcall SetKeyFields(Data::Dbcommontypes::TKeyIndex KeyIndex, const System::TVarRec *Values, const int Values_High);
	void __fastcall SetLinkRanges(System::Generics::Collections::TList__1<Data::Db::TField*>* MasterFields);
	virtual void __fastcall SetOnFilterRecord(const Data::Db::TFilterRecordEvent Value);
	virtual void __fastcall SetProviderEOF(bool Value);
	virtual void __fastcall SetRecNo(int Value);
	virtual void __fastcall SetRemoteServer(TCustomRemoteServer* Value);
	void __fastcall SwitchToIndex(const System::UnicodeString IndexName);
	void __fastcall SyncCursors(Datasnap::Dsintf::_di_IDSCursor Cursor1, Datasnap::Dsintf::_di_IDSCursor Cursor2);
	virtual void __fastcall UpdateIndexDefs();
	void __fastcall WriteDataPacket(System::Classes::TStream* Stream, bool WriteSize, TDataPacketFormat Format = (TDataPacketFormat)(0x0));
	bool __fastcall ConstraintsStored();
	__property TAggregates* Aggregates = {read=FAggregates, write=SetAggregates};
	__property bool AggregatesActive = {read=FAggregatesActive, write=SetAggsActive, default=0};
	__property AutoCalcFields = {default=1};
	__property System::WideString CommandText = {read=FCommandText, write=SetCommandText};
	__property Constraints = {stored=ConstraintsStored};
	__property bool DisableStringTrim = {read=FDisableStringTrim, write=SetDisableStringTrim, default=0};
	__property Datasnap::Dsintf::_di_IDSBase DSBase = {read=FDSBase, write=FDSBase};
	__property Datasnap::Dsintf::_di_IDSCursor DSCursor = {read=FDSCursor};
	__property Filter = {default=0};
	__property Filtered = {default=0};
	__property FilterOptions = {default=0};
	__property FieldDefs = {stored=FStoreDefs};
	__property bool IncludeBlobsInDelta = {read=FIncludeBlobsInDelta, write=SetIncludeBlobsInDelta, default=0};
	__property Data::Db::TIndexDefs* IndexDefs = {read=GetIndexDefs, write=SetIndexDefs, stored=FStoreDefs};
	__property System::UnicodeString IndexName = {read=GetIndexName, write=SetIndexName};
	__property bool IsClone = {read=GetIsClone, nodefault};
	__property bool FetchOnDemand = {read=FFetchOnDemand, write=FFetchOnDemand, default=1};
	__property Data::Db::TDataSource* MasterSource = {read=GetDataSource, write=SetDataSource};
	__property ObjectView = {default=1};
	__property Data::Db::TParams* Params = {read=FParams, write=SetParams};
	__property bool ProviderEOF = {read=GetProviderEOF, write=SetProviderEOF, nodefault};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, default=0};
	__property bool StoreDefs = {read=FStoreDefs, write=FStoreDefs, default=0};
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
	__property TReconcileErrorEvent OnReconcileError = {read=FOnReconcileError, write=FOnReconcileError};
	__property TRemoteEvent BeforeApplyUpdates = {read=FBeforeApplyUpdates, write=FBeforeApplyUpdates};
	__property TRemoteEvent AfterApplyUpdates = {read=FAfterApplyUpdates, write=FAfterApplyUpdates};
	__property TRemoteEvent BeforeGetRecords = {read=FBeforeGetRecords, write=FBeforeGetRecords};
	__property TRemoteEvent AfterGetRecords = {read=FAfterGetRecords, write=FAfterGetRecords};
	__property TRemoteEvent BeforeRowRequest = {read=FBeforeRowRequest, write=FBeforeRowRequest};
	__property TRemoteEvent AfterRowRequest = {read=FAfterRowRequest, write=FAfterRowRequest};
	__property TRemoteEvent BeforeExecute = {read=FBeforeExecute, write=FBeforeExecute};
	__property TRemoteEvent AfterExecute = {read=FAfterExecute, write=FAfterExecute};
	__property TRemoteEvent BeforeGetParams = {read=FBeforeGetParams, write=FBeforeGetParams};
	__property TRemoteEvent AfterGetParams = {read=FAfterGetParams, write=FAfterGetParams};
	
public:
	__fastcall virtual TCustomClientDataSet(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomClientDataSet();
	__property TPersistDataPacket* PersistDataPacket = {read=FPersistDataPacket, write=SetPersistDataPacket};
	__property Active = {default=0};
	__property DataSetField;
	__property System::UnicodeString ProviderName = {read=FProviderName, write=SetProviderName};
	__property System::UnicodeString FileName = {read=FFileName, write=SetFileName};
	__property TConnectionBroker* ConnectionBroker = {read=FConnectionBroker, write=SetConnectionBroker};
	__property System::UnicodeString IndexFieldNames = {read=GetIndexFieldNames, write=SetIndexFieldNames};
	__property System::UnicodeString MasterFields = {read=GetMasterFields, write=SetMasterFields};
	__property int PacketRecords = {read=FPacketRecords, write=FPacketRecords, default=-1};
	__property TCustomRemoteServer* RemoteServer = {read=GetRemoteServer, write=SetRemoteServer};
	void __fastcall AddIndex(const System::UnicodeString Name, const System::UnicodeString Fields, Data::Db::TIndexOptions Options, const System::UnicodeString DescFields = System::UnicodeString(), const System::UnicodeString CaseInsFields = System::UnicodeString(), const int GroupingLevel = 0x0);
	void __fastcall AppendData(const System::OleVariant &Data, bool HitEOF);
	void __fastcall ApplyRange();
	virtual int __fastcall ApplyUpdates(int MaxErrors);
#ifndef _WIN64
	virtual bool __fastcall BookmarkValid(System::DynamicArray<System::Byte> Bookmark);
#else /* _WIN64 */
	virtual bool __fastcall BookmarkValid(System::TArray__1<System::Byte> Bookmark);
#endif /* _WIN64 */
	virtual void __fastcall Cancel();
	void __fastcall CancelRange();
	void __fastcall CancelUpdates();
	virtual System::Classes::TStream* __fastcall CreateBlobStream(Data::Db::TField* Field, Data::Db::TBlobStreamMode Mode);
	void __fastcall CreateDataSet();
	virtual void __fastcall CloneCursor(TCustomClientDataSet* Source, bool Reset, bool KeepSettings = false);
	virtual Data::Db::TDataSet* __fastcall GetClonedDataSet(bool WithSettings);
#ifndef _WIN64
	virtual int __fastcall CompareBookmarks(System::DynamicArray<System::Byte> Bookmark1, System::DynamicArray<System::Byte> Bookmark2);
#else /* _WIN64 */
	virtual int __fastcall CompareBookmarks(System::TArray__1<System::Byte> Bookmark1, System::TArray__1<System::Byte> Bookmark2);
#endif /* _WIN64 */
	bool __fastcall ConstraintsDisabled();
	virtual System::OleVariant __fastcall DataRequest(const System::OleVariant &Data);
	void __fastcall DeleteIndex(const System::UnicodeString Name);
	void __fastcall DisableConstraints();
	void __fastcall EnableConstraints();
	void __fastcall EditKey();
	void __fastcall EditRangeEnd();
	void __fastcall EditRangeStart();
	virtual void __fastcall EmptyDataSet();
	virtual void __fastcall Execute();
	void __fastcall FetchBlobs();
	void __fastcall FetchDetails();
	void __fastcall RefreshRecord();
	void __fastcall FetchParams();
	virtual bool __fastcall FindKey(const System::TVarRec *KeyValues, const int KeyValues_High);
	void __fastcall FindNearest(const System::TVarRec *KeyValues, const int KeyValues_High);
	virtual bool __fastcall GetCurrentRecord(NativeInt Buffer)/* overload */;
	virtual bool __fastcall GetCurrentRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer)/* overload */;
	virtual void __fastcall GetDetailLinkFields(System::Generics::Collections::TList__1<Data::Db::TField*>* MasterFields, System::Generics::Collections::TList__1<Data::Db::TField*>* DetailFields)/* overload */;
#ifndef _WIN64
	virtual bool __fastcall GetFieldData(Data::Db::TField* Field, System::DynamicArray<System::Byte> &Buffer)/* overload */;
	virtual bool __fastcall GetFieldData(int FieldNo, System::DynamicArray<System::Byte> &Buffer)/* overload */;
#else /* _WIN64 */
	virtual bool __fastcall GetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> &Buffer)/* overload */;
	virtual bool __fastcall GetFieldData(int FieldNo, System::TArray__1<System::Byte> &Buffer)/* overload */;
#endif /* _WIN64 */
	virtual bool __fastcall GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer)/* overload */;
	virtual bool __fastcall GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (int FieldNo, void * Buffer)/* overload */;
	Data::Db::TGroupPosInds __fastcall GetGroupState(int Level);
	void __fastcall GetIndexInfo(System::UnicodeString IndexName);
	void __fastcall GetIndexNames(System::Classes::TStrings* List);
	virtual int __fastcall GetNextPacket();
	System::OleVariant __fastcall GetOptionalParam(const System::UnicodeString ParamName);
	void __fastcall GotoCurrent(TCustomClientDataSet* DataSet);
	bool __fastcall GotoKey();
	void __fastcall GotoNearest();
	__property bool HasAppServer = {read=GetHasAppServer, nodefault};
	virtual bool __fastcall Locate(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options);
	virtual System::Variant __fastcall Lookup(const System::UnicodeString KeyFields, const System::Variant &KeyValues, const System::UnicodeString ResultFields);
	void __fastcall LoadFromFile(const System::UnicodeString FileName = System::UnicodeString());
	void __fastcall LoadFromStream(System::Classes::TStream* Stream);
	void __fastcall MergeChangeLog();
	Data::Db::TParam* __fastcall ParamByName(const System::UnicodeString Value);
	virtual void __fastcall Post();
	bool __fastcall Reconcile(const System::OleVariant &Results);
	void __fastcall RevertRecord();
	void __fastcall SaveToFile(const System::UnicodeString FileName = System::UnicodeString(), TDataPacketFormat Format = (TDataPacketFormat)(0x0));
	void __fastcall SaveToStream(System::Classes::TStream* Stream, TDataPacketFormat Format = (TDataPacketFormat)(0x0));
	void __fastcall SetKey();
	virtual void __fastcall SetOptionalParam(const System::UnicodeString ParamName, const System::OleVariant &Value, bool IncludeInDelta = false);
	void __fastcall SetProvider(System::Classes::TComponent* Provider);
	void __fastcall SetRange(const System::TVarRec *StartValues, const int StartValues_High, const System::TVarRec *EndValues, const int EndValues_High);
	void __fastcall SetRangeEnd();
	void __fastcall SetRangeStart();
	bool __fastcall UndoLastChange(bool FollowChange);
	virtual Data::Db::TUpdateStatus __fastcall UpdateStatus();
	__property System::Classes::TList* ActiveAggs[int Index] = {read=GetActiveAggs};
	__property __int64 ChangeCount = {read=GetChangeCount};
	__property bool UpdatesPending = {read=GetUpdatesPending, nodefault};
	__property TCustomClientDataSet* CloneSource = {read=FCloneSource};
	__property System::OleVariant Data = {read=GetData, write=SetData};
	__property System::UnicodeString XMLData = {read=GetXMLData, write=SetXMLData};
	__property Datasnap::Midas::_di_IAppServer AppServer = {read=GetAppServer, write=SetAppServer};
	__property int DataSize = {read=GetDataSize, nodefault};
	__property System::OleVariant Delta = {read=GetDelta};
	__property int GroupingLevel = {read=FGroupingLevel, nodefault};
	__property int IndexFieldCount = {read=GetIndexFieldCount, nodefault};
	__property Data::Db::TField* IndexFields[int Index] = {read=GetIndexField, write=SetIndexField};
	__property bool KeyExclusive = {read=GetKeyExclusive, write=SetKeyExclusive, nodefault};
	__property int KeyFieldCount = {read=GetKeyFieldCount, write=SetKeyFieldCount, nodefault};
	__property System::Word KeySize = {read=FKeySize, nodefault};
	__property bool LogChanges = {read=GetLogChanges, write=SetLogChanges, nodefault};
	__property __int64 SavePoint = {read=GetSavePoint, write=SetSavePoint};
	__property Data::Db::TUpdateStatusSet StatusFilter = {read=FStatusFilter, write=SetStatusFilter, nodefault};
	__property bool Ranged = {read=FRanged, nodefault};
	/* Hoisted overloads: */
	
protected:
#ifndef _WIN64
	inline void __fastcall  SetFieldData(Data::Db::TField* Field, System::DynamicArray<System::Byte> Buffer, bool NativeFormat){ Data::Db::TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
#else /* _WIN64 */
	inline void __fastcall  SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer, bool NativeFormat){ Data::Db::TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
#endif /* _WIN64 */
	inline void __fastcall  SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat){ Data::Db::TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
	
public:
	inline void __fastcall  GetDetailLinkFields _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::Classes::TList* MasterFields, System::Classes::TList* DetailFields){ Data::Db::TDataSet::GetDetailLinkFields(MasterFields, DetailFields); }
#ifndef _WIN64
	inline bool __fastcall  GetFieldData(Data::Db::TField* Field, System::DynamicArray<System::Byte> &Buffer, bool NativeFormat){ return Data::Db::TDataSet::GetFieldData(Field, Buffer, NativeFormat); }
#else /* _WIN64 */
	inline bool __fastcall  GetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> &Buffer, bool NativeFormat){ return Data::Db::TDataSet::GetFieldData(Field, Buffer, NativeFormat); }
#endif /* _WIN64 */
	inline bool __fastcall  GetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat){ return Data::Db::TDataSet::GetFieldData(Field, Buffer, NativeFormat); }
	
private:
	void *__IDataSetCommandSupport;	// Data::Db::IDataSetCommandSupport 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {285C0B2D-C123-444A-9FD3-9C6D1DE3762B}
	operator Data::Db::_di_IDataSetCommandSupport()
	{
		Data::Db::_di_IDataSetCommandSupport intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Db::IDataSetCommandSupport*(void) { return (Data::Db::IDataSetCommandSupport*)&__IDataSetCommandSupport; }
	#endif
	
};


class PASCALIMPLEMENTATION TClientDataSet : public TCustomClientDataSet
{
	typedef TCustomClientDataSet inherited;
	
__published:
	__property PersistDataPacket;
	__property Active = {default=0};
	__property Aggregates;
	__property AggregatesActive = {default=0};
	__property AutoCalcFields = {default=1};
	__property CommandText = {default=0};
	__property ConnectionBroker;
	__property Constraints;
	__property DataSetField;
	__property DisableStringTrim = {default=0};
	__property FieldOptions;
	__property FileName = {default=0};
	__property Filter = {default=0};
	__property Filtered = {default=0};
	__property FilterOptions = {default=0};
	__property FieldDefs;
	__property IncludeBlobsInDelta = {default=0};
	__property IndexDefs;
	__property IndexFieldNames = {default=0};
	__property IndexName = {default=0};
	__property FetchOnDemand = {default=1};
	__property MasterFields = {default=0};
	__property MasterSource;
	__property ObjectView = {default=1};
	__property PacketRecords = {default=-1};
	__property Params;
	__property ProviderName = {default=0};
	__property ReadOnly = {default=0};
	__property RemoteServer;
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
	__property BeforeRefresh;
	__property AfterRefresh;
	__property OnCalcFields;
	__property OnDeleteError;
	__property OnEditError;
	__property OnFilterRecord;
	__property OnNewRecord;
	__property OnPostError;
	__property OnReconcileError;
	__property BeforeApplyUpdates;
	__property AfterApplyUpdates;
	__property BeforeGetRecords;
	__property AfterGetRecords;
	__property BeforeRowRequest;
	__property AfterRowRequest;
	__property BeforeExecute;
	__property AfterExecute;
	__property BeforeGetParams;
	__property AfterGetParams;
public:
	/* TCustomClientDataSet.Create */ inline __fastcall virtual TClientDataSet(System::Classes::TComponent* AOwner) : TCustomClientDataSet(AOwner) { }
	/* TCustomClientDataSet.Destroy */ inline __fastcall virtual ~TClientDataSet() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TClientBlobStream : public System::Classes::TMemoryStream
{
	typedef System::Classes::TMemoryStream inherited;
	
private:
	Data::Db::TBlobField* FField;
	TCustomClientDataSet* FDataSet;
	NativeInt FBuffer;
	int FFieldNo;
	bool FModified;
	bool FWritten;
	void __fastcall ReadBlobData();
	
public:
	__fastcall TClientBlobStream(Data::Db::TBlobField* Field, Data::Db::TBlobStreamMode Mode);
	__fastcall virtual ~TClientBlobStream();
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
#ifndef _WIN64
	virtual int __fastcall Write(const System::DynamicArray<System::Byte> ABuffer, int AOffset, int ACount)/* overload */;
#else /* _WIN64 */
	virtual int __fastcall Write(const System::TArray__1<System::Byte> ABuffer, int AOffset, int ACount)/* overload */;
#endif /* _WIN64 */
	void __fastcall Truncate();
	/* Hoisted overloads: */
	
public:
#ifndef _WIN64
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* _WIN64 */
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* _WIN64 */
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define AllParamTypes (System::Set<Data::Db::TParamType, Data::Db::TParamType::ptUnknown, Data::Db::TParamType::ptResult>() << Data::Db::TParamType::ptUnknown << Data::Db::TParamType::ptInput << Data::Db::TParamType::ptOutput << Data::Db::TParamType::ptInputOutput << Data::Db::TParamType::ptResult )
static const System::Int8 AllRecords = System::Int8(-1);
extern DELPHI_PACKAGE System::OleVariant __fastcall PackageParams(Data::Db::TParams* Params, Data::Db::TParamTypes Types = (Data::Db::TParamTypes() << Data::Db::TParamType::ptUnknown << Data::Db::TParamType::ptInput << Data::Db::TParamType::ptOutput << Data::Db::TParamType::ptInputOutput << Data::Db::TParamType::ptResult ));
extern DELPHI_PACKAGE void __fastcall UnpackParams(const System::OleVariant &Source, Data::Db::TParams* Dest);
}	/* namespace Dbclient */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DBCLIENT)
using namespace Datasnap::Dbclient;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DbclientHPP
