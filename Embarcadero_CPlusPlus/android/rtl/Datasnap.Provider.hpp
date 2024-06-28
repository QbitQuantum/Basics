// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.Provider.pas' rev: 34.00 (Android)

#ifndef Datasnap_ProviderHPP
#define Datasnap_ProviderHPP

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
#include <Datasnap.DBClient.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DSIntf.hpp>
#include <Datasnap.Midas.hpp>
#include <Data.SqlTimSt.hpp>
#include <System.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Provider
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EDSWriter;
class DELPHICLASS TCustomPacketWriter;
struct TPutFieldInfo;
class DELPHICLASS TDataPacketWriter;
class DELPHICLASS TPacketDataSet;
class DELPHICLASS TCustomProvider;
class DELPHICLASS TBaseProvider;
class DELPHICLASS TDataSetProvider;
class DELPHICLASS TProvider;
class DELPHICLASS TUpdateTree;
class DELPHICLASS TCustomResolver;
class DELPHICLASS TDataSetResolver;
class DELPHICLASS TSQLResolver;
class DELPHICLASS TLocalAppServer;
__interface DELPHIINTERFACE IProviderContainer;
typedef System::DelphiInterface<IProviderContainer> _di_IProviderContainer;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EDSWriter : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
private:
	int FErrorCode;
	
public:
	__fastcall EDSWriter(System::UnicodeString ErrMsg, int Status, int Dummy);
	__property int ErrorCode = {read=FErrorCode, nodefault};
public:
	/* Exception.CreateFmt */ inline __fastcall EDSWriter(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDSWriter(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDSWriter(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDSWriter(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDSWriter(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDSWriter(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDSWriter(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDSWriter(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDSWriter(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDSWriter(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDSWriter(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDSWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomPacketWriter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Datasnap::Dsintf::_di_IDSWriter FIDSWriter;
	void __fastcall InternalCheck(int Status);
	
protected:
	System::TArray__1<System::Byte> FBuffer;
	virtual void __fastcall AddAttribute(Datasnap::Dsintf::TPcktAttrArea Area, const System::UnicodeString ParamName, const System::OleVariant &Value, bool IncludeInDelta);
	void __fastcall Check(int Status);
	void __fastcall SetDSWriter(const Datasnap::Dsintf::_di_IDSWriter Value);
	__property Datasnap::Dsintf::_di_IDSWriter DSWriter = {read=FIDSWriter};
	
public:
	__fastcall virtual TCustomPacketWriter();
	__fastcall virtual ~TCustomPacketWriter();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TGetRecordOption : unsigned char { grMetaData, grReset, grXML, grXMLUTF8 };

typedef System::Set<TGetRecordOption, TGetRecordOption::grMetaData, TGetRecordOption::grXMLUTF8> TGetRecordOptions;

typedef System::OleVariant __fastcall (__closure *TDataRequestEvent)(System::TObject* Sender, const System::OleVariant &Input);

enum DECLSPEC_DENUM TProviderOption : unsigned char { poFetchBlobsOnDemand, poFetchDetailsOnDemand, poIncFieldProps, poCascadeDeletes, poCascadeUpdates, poReadOnly, poAllowMultiRecordUpdates, poDisableInserts, poDisableEdits, poDisableDeletes, poNoReset, poAutoRefresh, poPropogateChanges, poAllowCommandText, poRetainServerOrder, poUseQuoteChar };

typedef System::Set<TProviderOption, TProviderOption::poFetchBlobsOnDemand, TProviderOption::poUseQuoteChar> TProviderOptions;

typedef TPutFieldInfo *PPutFieldInfo;

typedef void __fastcall (__closure *TPutFieldProc)(PPutFieldInfo Info);

struct DECLSPEC_DRECORD TPutFieldInfo
{
public:
	int FieldNo;
	Data::Db::TField* Field;
	Data::Db::TDataSet* DataSet;
	int Size;
	bool IsDetail;
	bool Opened;
	TPutFieldProc PutProc;
	int LocalFieldIndex;
	void *FieldInfos;
};


typedef System::DynamicArray<TPutFieldInfo> TInfoArray;

typedef void __fastcall (__closure *TGetParamsEvent)(Data::Db::TDataSet* DataSet, System::Classes::TList* Params);

typedef void __fastcall (__closure *TOnValidate)(const System::OleVariant &Delta);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDataPacketWriter : public TCustomPacketWriter
{
	typedef TCustomPacketWriter inherited;
	
private:
	bool FConstraints;
	TInfoArray FPutFieldInfo;
	TProviderOptions FOptions;
	TGetRecordOptions FPacketOptions;
	TGetParamsEvent FOnGetParams;
	
protected:
	virtual void __fastcall AddColumn(const TPutFieldInfo &Info);
	virtual void __fastcall AddConstraints(Data::Db::TDataSet* DataSet);
	virtual void __fastcall AddDataSetAttributes(Data::Db::TDataSet* DataSet);
	void __fastcall AddExtraFieldProps(Data::Db::TField* Field);
	virtual void __fastcall AddFieldLinks(const TInfoArray Info);
	virtual void __fastcall AddIndexDefs(Data::Db::TDataSet* DataSet, const TInfoArray Info);
	void __fastcall FreeInfoRecords(TInfoArray &Info);
	int __fastcall GetFieldIdx(const System::UnicodeString FieldName, const TInfoArray Info);
	TInfoArray __fastcall InitPutProcs(Data::Db::TDataSet* ADataSet, int &GlobalIdx);
	void __fastcall RefreshPutProcs(Data::Db::TDataSet* ADataSet, TInfoArray &Info);
	void __fastcall PutADTField(PPutFieldInfo Info);
	void __fastcall PutArrayField(PPutFieldInfo Info);
	void __fastcall PutBlobField(PPutFieldInfo Info);
	void __fastcall PutDataSetField(PPutFieldInfo Info);
	void __fastcall PutField(PPutFieldInfo Info);
	void __fastcall PutStringField(PPutFieldInfo Info);
	void __fastcall PutWideStringField(PPutFieldInfo Info);
	void __fastcall PutVarBytesField(PPutFieldInfo Info);
	virtual void __fastcall WriteMetaData(Data::Db::TDataSet* DataSet, const TInfoArray Info, bool IsReference = false);
	virtual int __fastcall WriteDataSet(Data::Db::TDataSet* DataSet, TInfoArray &Info, int RecsOut);
	
public:
	__fastcall virtual ~TDataPacketWriter();
	virtual void __fastcall GetDataPacket(Data::Db::TDataSet* DataSet, int &RecsOut, /* out */ System::OleVariant &Data);
	void __fastcall Reset();
	__property bool Constraints = {read=FConstraints, write=FConstraints, nodefault};
	__property TGetRecordOptions PacketOptions = {read=FPacketOptions, write=FPacketOptions, nodefault};
	__property TProviderOptions Options = {read=FOptions, write=FOptions, nodefault};
	__property TGetParamsEvent OnGetParams = {read=FOnGetParams, write=FOnGetParams};
public:
	/* TCustomPacketWriter.Create */ inline __fastcall virtual TDataPacketWriter() : TCustomPacketWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPacketDataSet : public Datasnap::Dbclient::TCustomClientDataSet
{
	typedef Datasnap::Dbclient::TCustomClientDataSet inherited;
	
private:
	NativeInt FOldRecBuf;
	NativeInt FCurRecBuf;
	NativeInt FCurValues;
	bool FUseCurValues;
	bool FWritingCurValues;
	bool FNewValuesModified;
	bool __fastcall GetStreamMetaData();
	void __fastcall SetStreamMetaData(bool Value);
	void __fastcall SetWritingCurValues(const bool Value);
	
protected:
	virtual void __fastcall DataEvent(Data::Db::TDataEvent Event, NativeInt Info);
	virtual System::Variant __fastcall GetStateFieldValue(Data::Db::TDataSetState State, Data::Db::TField* Field);
	virtual void __fastcall InternalClose();
	virtual void __fastcall InternalOpen();
	virtual void __fastcall InternalInitRecord(NativeInt Buffer)/* overload */;
	virtual void __fastcall InternalInitRecord _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::PByte Buffer)/* overload */;
	virtual void __fastcall SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer)/* overload */;
	virtual void __fastcall SetFieldData _DEPRECATED_ATTRIBUTE0 (Data::Db::TField* Field, void * Buffer)/* overload */;
	virtual void __fastcall SetStateFieldValue(Data::Db::TDataSetState State, Data::Db::TField* Field, const System::Variant &Value);
	__property bool WritingCurValues = {read=FWritingCurValues, write=SetWritingCurValues, nodefault};
	
public:
	__fastcall virtual TPacketDataSet(System::Classes::TComponent* AOwner);
	void __fastcall AssignCurValues(Data::Db::TDataSet* Source)/* overload */;
	void __fastcall AssignCurValues(const System::Variant &CurValues)/* overload */;
	void __fastcall CreateFromDelta(TPacketDataSet* Source);
	bool __fastcall HasCurValues();
	bool __fastcall HasMergeConflicts();
	void __fastcall InitAltRecBuffers(bool CheckModified = true);
	Data::Db::TUpdateKind __fastcall UpdateKind();
	__property bool NewValuesModified = {read=FNewValuesModified, nodefault};
	__property bool StreamMetaData = {read=GetStreamMetaData, write=SetStreamMetaData, nodefault};
	__property bool UseCurValues = {read=FUseCurValues, write=FUseCurValues, nodefault};
public:
	/* TCustomClientDataSet.Destroy */ inline __fastcall virtual ~TPacketDataSet() { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  SetFieldData(Data::Db::TField* Field, System::TArray__1<System::Byte> Buffer, bool NativeFormat){ Data::Db::TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
	inline void __fastcall  SetFieldData _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (Data::Db::TField* Field, void * Buffer, bool NativeFormat){ Data::Db::TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TCustomProvider : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FExported;
	System::OleVariant FOwnerData;
	System::Sysutils::Exception* FActiveUpdateAbortException;
	TDataRequestEvent FOnDataRequest;
	TOnValidate FOnValidate;
	Datasnap::Dbclient::TRemoteEvent FBeforeApplyUpdates;
	Datasnap::Dbclient::TRemoteEvent FAfterApplyUpdates;
	Datasnap::Dbclient::TRemoteEvent FBeforeGetRecords;
	Datasnap::Dbclient::TRemoteEvent FAfterGetRecords;
	Datasnap::Dbclient::TRemoteEvent FBeforeRowRequest;
	Datasnap::Dbclient::TRemoteEvent FAfterRowRequest;
	Datasnap::Dbclient::TRemoteEvent FBeforeExecute;
	Datasnap::Dbclient::TRemoteEvent FAfterExecute;
	Datasnap::Dbclient::TRemoteEvent FBeforeGetParams;
	Datasnap::Dbclient::TRemoteEvent FAfterGetParams;
	System::OleVariant __fastcall GetData();
	
protected:
	virtual System::OleVariant __fastcall DoApplyUpdates(const System::OleVariant &Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData);
	virtual System::OleVariant __fastcall DoGetRecords(int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	virtual System::OleVariant __fastcall InternalGetRecords(int Count, /* out */ int &RecsOut, TGetRecordOptions Options, const System::WideString CommandText, System::OleVariant &Params);
	virtual void __fastcall InternalExecute(const System::WideString CommandText, System::OleVariant &Params);
	virtual void __fastcall DoBeforeExecute(const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	virtual void __fastcall DoBeforeGetRecords(int Count, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	virtual System::OleVariant __fastcall InternalApplyUpdates(const System::OleVariant &Delta, int MaxErrors, /* out */ int &ErrorCount) = 0 ;
	virtual System::OleVariant __fastcall InternalRowRequest(const System::OleVariant &Row, Datasnap::Dbclient::TFetchOptions RequestType);
	virtual System::OleVariant __fastcall InternalGetParams(Data::Db::TParamTypes Types = (Data::Db::TParamTypes() << Data::Db::TParamType::ptUnknown << Data::Db::TParamType::ptInput << Data::Db::TParamType::ptOutput << Data::Db::TParamType::ptInputOutput << Data::Db::TParamType::ptResult ));
	virtual void __fastcall DoAfterApplyUpdates(System::OleVariant &OwnerData);
	virtual void __fastcall DoBeforeApplyUpdates(System::OleVariant &OwnerData);
	virtual void __fastcall DoAfterExecute(System::OleVariant &OwnerData);
	virtual void __fastcall DoAfterGetParams(System::OleVariant &OwnerData);
	virtual void __fastcall DoBeforeGetParams(System::OleVariant &OwnerData);
	virtual void __fastcall DoAfterGetRecords(System::OleVariant &OwnerData);
	virtual void __fastcall DoAfterRowRequest(System::OleVariant &OwnerData);
	virtual void __fastcall DoBeforeRowRequest(System::OleVariant &OwnerData);
	__property TDataRequestEvent OnDataRequest = {read=FOnDataRequest, write=FOnDataRequest};
	__property TOnValidate OnValidate = {read=FOnValidate, write=FOnValidate};
	__property Datasnap::Dbclient::TRemoteEvent BeforeApplyUpdates = {read=FBeforeApplyUpdates, write=FBeforeApplyUpdates};
	__property Datasnap::Dbclient::TRemoteEvent AfterApplyUpdates = {read=FAfterApplyUpdates, write=FAfterApplyUpdates};
	__property Datasnap::Dbclient::TRemoteEvent BeforeGetRecords = {read=FBeforeGetRecords, write=FBeforeGetRecords};
	__property Datasnap::Dbclient::TRemoteEvent AfterGetRecords = {read=FAfterGetRecords, write=FAfterGetRecords};
	__property Datasnap::Dbclient::TRemoteEvent BeforeRowRequest = {read=FBeforeRowRequest, write=FBeforeRowRequest};
	__property Datasnap::Dbclient::TRemoteEvent AfterRowRequest = {read=FAfterRowRequest, write=FAfterRowRequest};
	__property Datasnap::Dbclient::TRemoteEvent BeforeExecute = {read=FBeforeExecute, write=FBeforeExecute};
	__property Datasnap::Dbclient::TRemoteEvent AfterExecute = {read=FAfterExecute, write=FAfterExecute};
	__property Datasnap::Dbclient::TRemoteEvent BeforeGetParams = {read=FBeforeGetParams, write=FBeforeGetParams};
	__property Datasnap::Dbclient::TRemoteEvent AfterGetParams = {read=FAfterGetParams, write=FAfterGetParams};
	void __fastcall SetActiveUpdateException(System::Sysutils::Exception* E);
	__property System::Sysutils::Exception* ActiveUpdateException = {read=FActiveUpdateAbortException};
	__property System::OleVariant OwnerData = {read=FOwnerData, write=FOwnerData};
	
public:
	__fastcall virtual TCustomProvider(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomProvider();
	System::OleVariant __fastcall ApplyUpdates(const System::OleVariant &Delta, int MaxErrors, /* out */ int &ErrorCount)/* overload */;
	System::OleVariant __fastcall ApplyUpdates(const System::OleVariant &Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData)/* overload */;
	System::OleVariant __fastcall GetRecords(int Count, /* out */ int &RecsOut, int Options)/* overload */;
	System::OleVariant __fastcall GetRecords(int Count, /* out */ int &RecsOut, int Options, const System::UnicodeString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData)/* overload */;
	virtual System::OleVariant __fastcall RowRequest(const System::OleVariant &Row, int RequestType, System::OleVariant &OwnerData);
	virtual void __fastcall Execute(const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	virtual System::OleVariant __fastcall GetParams(System::OleVariant &OwnerData);
	virtual System::OleVariant __fastcall DataRequest(const System::OleVariant &Input);
	__property System::OleVariant Data = {read=GetData};
	__property bool Exported = {read=FExported, write=FExported, default=1};
};


enum DECLSPEC_DENUM TResolverResponse : unsigned char { rrSkip, rrAbort, rrMerge, rrApply, rrIgnore };

typedef void __fastcall (__closure *TProviderDataEvent)(System::TObject* Sender, Datasnap::Dbclient::TCustomClientDataSet* DataSet);

typedef void __fastcall (__closure *TBeforeUpdateRecordEvent)(System::TObject* Sender, Data::Db::TDataSet* SourceDS, Datasnap::Dbclient::TCustomClientDataSet* DeltaDS, Data::Db::TUpdateKind UpdateKind, bool &Applied);

typedef void __fastcall (__closure *TAfterUpdateRecordEvent)(System::TObject* Sender, Data::Db::TDataSet* SourceDS, Datasnap::Dbclient::TCustomClientDataSet* DeltaDS, Data::Db::TUpdateKind UpdateKind);

typedef void __fastcall (__closure *TResolverErrorEvent)(System::TObject* Sender, Datasnap::Dbclient::TCustomClientDataSet* DataSet, Data::Db::EUpdateError* E, Data::Db::TUpdateKind UpdateKind, TResolverResponse &Response);

typedef void __fastcall (__closure *TBeforeCommitEvent)(System::TObject* Sender, Datasnap::Dbclient::TCustomClientDataSet* DeltaDS, int ErrorCount, int MaxErrors, const System::OleVariant &ResultVar);

class PASCALIMPLEMENTATION TBaseProvider : public TCustomProvider
{
	typedef TCustomProvider inherited;
	
private:
	TPacketDataSet* FDataDS;
	Data::Db::TUpdateMode FUpdateMode;
	TCustomResolver* FResolver;
	TProviderDataEvent FOnGetData;
	TProviderDataEvent FOnUpdateData;
	TResolverErrorEvent FOnUpdateError;
	TBeforeUpdateRecordEvent FBeforeUpdateRecord;
	TAfterUpdateRecordEvent FAfterUpdateRecord;
	TBeforeCommitEvent FBeforeCommit;
	TProviderOptions FProviderOptions;
	
protected:
	void __fastcall CheckResolver();
	virtual TCustomResolver* __fastcall CreateResolver();
	void __fastcall FreeResolver();
	virtual void __fastcall CreateDataPacket(TGetRecordOptions PacketOpts, TProviderOptions ProvOpts, int &RecsOut, System::OleVariant &Data);
	virtual void __fastcall DoBeforeCommit(TPacketDataSet* Delta, int ErrorCount, int MaxErrors, const System::OleVariant &ReturnVar);
	virtual void __fastcall DoOnGetData(System::OleVariant &Data);
	virtual void __fastcall DoOnUpdateData(TPacketDataSet* Delta);
	virtual void __fastcall DoBeforeUpdateRecord(Data::Db::TDataSet* SourceDS, Datasnap::Dbclient::TCustomClientDataSet* DeltaDS, Data::Db::TUpdateKind UpdateKind, bool &Applied);
	virtual void __fastcall DoAfterUpdateRecord(Data::Db::TDataSet* SourceDS, Datasnap::Dbclient::TCustomClientDataSet* DeltaDS, Data::Db::TUpdateKind UpdateKind);
	virtual void __fastcall LocateRecord(Data::Db::TDataSet* Source, Data::Db::TDataSet* Delta);
	virtual void __fastcall UpdateRecord(Data::Db::TDataSet* Source, Data::Db::TDataSet* Delta, bool BlobsOnly, bool KeyOnly);
	virtual void __fastcall FetchDetails(Data::Db::TDataSet* Source, Data::Db::TDataSet* Delta);
	virtual System::OleVariant __fastcall InternalRowRequest(const System::OleVariant &Row, Datasnap::Dbclient::TFetchOptions RequestType);
	virtual System::OleVariant __fastcall InternalApplyUpdates(const System::OleVariant &Delta, int MaxErrors, /* out */ int &ErrorCount);
	virtual System::OleVariant __fastcall InternalGetRecords(int Count, /* out */ int &RecsOut, TGetRecordOptions Options, const System::WideString CommandText, System::OleVariant &Params);
	__property TPacketDataSet* PacketDataSet = {read=FDataDS, write=FDataDS};
	
public:
	__fastcall virtual TBaseProvider(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBaseProvider();
	__property TCustomResolver* Resolver = {read=FResolver};
	__property TProviderOptions Options = {read=FProviderOptions, write=FProviderOptions, default=32768};
	__property Data::Db::TUpdateMode UpdateMode = {read=FUpdateMode, write=FUpdateMode, default=0};
	__property OnDataRequest;
	__property TProviderDataEvent OnGetData = {read=FOnGetData, write=FOnGetData};
	__property TProviderDataEvent OnUpdateData = {read=FOnUpdateData, write=FOnUpdateData};
	__property TResolverErrorEvent OnUpdateError = {read=FOnUpdateError, write=FOnUpdateError};
	__property TBeforeUpdateRecordEvent BeforeUpdateRecord = {read=FBeforeUpdateRecord, write=FBeforeUpdateRecord};
	__property TAfterUpdateRecordEvent AfterUpdateRecord = {read=FAfterUpdateRecord, write=FAfterUpdateRecord};
};


typedef void __fastcall (__closure *TGetTableNameEvent)(System::TObject* Sender, Data::Db::TDataSet* DataSet, System::UnicodeString &TableName);

typedef void __fastcall (__closure *TGetDSProps)(System::TObject* Sender, Data::Db::TDataSet* DataSet, /* out */ System::OleVariant &Properties);

class PASCALIMPLEMENTATION TDataSetProvider : public TBaseProvider
{
	typedef TBaseProvider inherited;
	
private:
	Data::Db::TDataSet* FDataSet;
	bool FDataSetOpened;
	bool FDetailDataSetOpened;
	TDataPacketWriter* FDSWriter;
	TGetDSProps FGetDSProps;
	Data::Db::TParams* FParams;
	bool FResolveToDataSet;
	int FRecordsSent;
	bool FConstraints;
	bool FTransactionStarted;
	TGetTableNameEvent FGetTableName;
	void __fastcall SetDataSet(Data::Db::TDataSet* ADataSet);
	void __fastcall SetResolveToDataSet(bool Value);
	
protected:
	virtual void __fastcall DoGetTableName(Data::Db::TDataSet* DataSet, System::UnicodeString &TableName);
	virtual void __fastcall DoBeforeGetRecords(int Count, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	virtual void __fastcall DoBeforeExecute(const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	void __fastcall CheckDataSet();
	virtual void __fastcall DoGetProviderAttributes(Data::Db::TDataSet* DataSet, System::Classes::TList* List);
	virtual TCustomResolver* __fastcall CreateResolver();
	virtual void __fastcall CreateDataPacket(TGetRecordOptions PacketOpts, TProviderOptions ProvOpts, int &RecsOut, System::OleVariant &Data);
	virtual Data::Db::TDataSet* __fastcall GetDataSetFromDelta(TUpdateTree* ATree, Data::Db::TDataSet* Source, Data::Db::TDataSet* Delta, Data::Db::TUpdateMode Mode);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall LocateRecord(Data::Db::TDataSet* Source, Data::Db::TDataSet* Delta);
	virtual void __fastcall UpdateRecord(Data::Db::TDataSet* Source, Data::Db::TDataSet* Delta, bool BlobsOnly, bool KeyOnly);
	virtual void __fastcall FetchDetails(Data::Db::TDataSet* Source, Data::Db::TDataSet* Delta);
	virtual System::OleVariant __fastcall InternalRowRequest(const System::OleVariant &Row, Datasnap::Dbclient::TFetchOptions Options);
	virtual System::OleVariant __fastcall InternalGetParams(Data::Db::TParamTypes Types = (Data::Db::TParamTypes() << Data::Db::TParamType::ptUnknown << Data::Db::TParamType::ptInput << Data::Db::TParamType::ptOutput << Data::Db::TParamType::ptInputOutput << Data::Db::TParamType::ptResult ));
	virtual void __fastcall InternalExecute(const System::WideString CommandText, System::OleVariant &Params);
	virtual System::OleVariant __fastcall InternalGetRecords(int Count, /* out */ int &RecsOut, TGetRecordOptions Options, const System::WideString CommandText, System::OleVariant &Params);
	virtual void __fastcall SetCommandText(const System::WideString CommandText);
	virtual System::OleVariant __fastcall InternalApplyUpdates(const System::OleVariant &Delta, int MaxErrors, /* out */ int &ErrorCount);
	virtual bool __fastcall FindRecord(Data::Db::TDataSet* Source, Data::Db::TDataSet* Delta, Data::Db::TUpdateMode UpdateMode);
	void __fastcall Reset();
	virtual void __fastcall SetParams(const System::OleVariant &Values);
	__property bool TransactionStarted = {read=FTransactionStarted, write=FTransactionStarted, nodefault};
	
public:
	__fastcall virtual TDataSetProvider(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDataSetProvider();
	__property ActiveUpdateException;
	__property OwnerData = {default=0};
	__property Data::Db::TParams* Params = {read=FParams};
	
__published:
	__property Data::Db::TDataSet* DataSet = {read=FDataSet, write=SetDataSet};
	__property bool Constraints = {read=FConstraints, write=FConstraints, default=1};
	__property bool ResolveToDataSet = {read=FResolveToDataSet, write=SetResolveToDataSet, default=0};
	__property Exported = {default=1};
	__property Options = {default=32768};
	__property UpdateMode = {default=0};
	__property OnDataRequest;
	__property OnGetData;
	__property OnUpdateData;
	__property OnUpdateError;
	__property AfterUpdateRecord;
	__property BeforeUpdateRecord;
	__property OnValidate;
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
	__property TGetTableNameEvent OnGetTableName = {read=FGetTableName, write=FGetTableName};
	__property TGetDSProps OnGetDataSetProperties = {read=FGetDSProps, write=FGetDSProps};
};


class PASCALIMPLEMENTATION TProvider _DEPRECATED_ATTRIBUTE0  : public TDataSetProvider
{
	typedef TDataSetProvider inherited;
	
public:
	/* TDataSetProvider.Create */ inline __fastcall virtual TProvider(System::Classes::TComponent* AOwner) : TDataSetProvider(AOwner) { }
	/* TDataSetProvider.Destroy */ inline __fastcall virtual ~TProvider() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TUpdateTree : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TPacketDataSet* FDeltaDS;
	TPacketDataSet* FErrorDS;
	bool FOpened;
	Data::Db::TDataSet* FSourceDS;
	TUpdateTree* FParent;
	System::Generics::Collections::TList__1<TUpdateTree*>* FDetails;
	void *FData;
	TCustomResolver* FResolver;
	System::UnicodeString FName;
	int __fastcall GetDetailCount();
	TUpdateTree* __fastcall GetDetail(int Index);
	TPacketDataSet* __fastcall GetErrorDS();
	bool __fastcall GetHasErrors();
	bool __fastcall GetIsNested();
	TUpdateTree* __fastcall GetTree(const System::UnicodeString AName);
	
protected:
	__property bool Opened = {read=FOpened, write=FOpened, nodefault};
	__property System::Generics::Collections::TList__1<TUpdateTree*>* DetailList = {read=FDetails};
	
public:
	__fastcall TUpdateTree(TUpdateTree* AParent, TCustomResolver* AResolver);
	__fastcall virtual ~TUpdateTree();
	virtual void __fastcall Clear();
	virtual bool __fastcall DoUpdates();
	virtual void __fastcall InitData(Data::Db::TDataSet* ASource);
	virtual void __fastcall InitDelta(TPacketDataSet* ADelta)/* overload */;
	virtual void __fastcall InitDelta(const System::OleVariant &ADelta)/* overload */;
	virtual void __fastcall InitErrorPacket(Data::Db::EUpdateError* E, TResolverResponse Response);
	virtual void __fastcall RefreshData(Datasnap::Dbclient::TFetchOptions Options);
	__property void * Data = {read=FData, write=FData};
	__property TPacketDataSet* Delta = {read=FDeltaDS, write=FDeltaDS};
	__property int DetailCount = {read=GetDetailCount, nodefault};
	__property TUpdateTree* Details[int Index] = {read=GetDetail};
	__property TPacketDataSet* ErrorDS = {read=GetErrorDS, write=FErrorDS};
	__property bool HasErrors = {read=GetHasErrors, nodefault};
	__property bool IsNested = {read=GetIsNested, nodefault};
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property TUpdateTree* Parent = {read=FParent};
	__property TCustomResolver* Resolver = {read=FResolver};
	__property Data::Db::TDataSet* Source = {read=FSourceDS, write=FSourceDS};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomResolver : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TBaseProvider* FProvider;
	TResolverResponse FPrevResponse;
	int FErrorCount;
	int FMaxErrors;
	TUpdateTree* FUpdateTree;
	
protected:
	virtual bool __fastcall HandleUpdateError(TUpdateTree* Tree, Data::Db::EUpdateError* E, int &MaxErrors, int &ErrorCount);
	virtual void __fastcall LogUpdateRecord(TUpdateTree* Tree);
	virtual void __fastcall LogUpdateError(TUpdateTree* Tree, Data::Db::EUpdateError* E, TResolverResponse Response);
	virtual void __fastcall BeginUpdate();
	virtual void __fastcall EndUpdate();
	virtual void __fastcall DoUpdate(TUpdateTree* Tree) = 0 ;
	virtual void __fastcall DoDelete(TUpdateTree* Tree) = 0 ;
	virtual void __fastcall DoInsert(TUpdateTree* Tree) = 0 ;
	virtual void __fastcall InitializeConflictBuffer(TUpdateTree* Tree) = 0 ;
	
public:
	__fastcall TCustomResolver(TBaseProvider* AProvider);
	__fastcall virtual ~TCustomResolver();
	virtual System::OleVariant __fastcall ApplyUpdates(const System::OleVariant &Delta, int MaxErrors, /* out */ int &ErrorCount);
	virtual void __fastcall FreeTreeData(TUpdateTree* Tree);
	virtual void __fastcall InitKeyFields(TUpdateTree* Tree, TPacketDataSet* ADelta);
	virtual void __fastcall InitTreeData(TUpdateTree* Tree);
	virtual void __fastcall InternalBeforeResolve(TUpdateTree* Tree);
	virtual bool __fastcall InternalUpdateRecord(TUpdateTree* Tree);
	virtual System::OleVariant __fastcall RowRequest(const System::OleVariant &Row, Datasnap::Dbclient::TFetchOptions Options);
	__property TBaseProvider* Provider = {read=FProvider};
	__property TUpdateTree* UpdateTree = {read=FUpdateTree};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDataSetResolver : public TCustomResolver
{
	typedef TCustomResolver inherited;
	
private:
	System::TArray__1<System::Byte> FBookmark;
	bool FOpened;
	TDataSetProvider* __fastcall GetProvider();
	void __fastcall PutRecord(TUpdateTree* Tree);
	
protected:
	__property TDataSetProvider* Provider = {read=GetProvider};
	virtual void __fastcall BeginUpdate();
	virtual void __fastcall DoUpdate(TUpdateTree* Tree);
	virtual void __fastcall DoDelete(TUpdateTree* Tree);
	virtual void __fastcall DoInsert(TUpdateTree* Tree);
	virtual void __fastcall EndUpdate();
	virtual void __fastcall InitializeConflictBuffer(TUpdateTree* Tree);
	
public:
	__fastcall TDataSetResolver(TDataSetProvider* AProvider);
	virtual void __fastcall InternalBeforeResolve(TUpdateTree* Tree);
public:
	/* TCustomResolver.Destroy */ inline __fastcall virtual ~TDataSetResolver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSQLResolver : public TCustomResolver
{
	typedef TCustomResolver inherited;
	
private:
	System::Classes::TStringList* FSQL;
	Data::Db::TParams* FParams;
	
protected:
	virtual TDataSetProvider* __fastcall GetProvider();
	virtual void __fastcall GenWhereSQL(TUpdateTree* Tree, System::Classes::TStrings* SQL, Data::Db::TParams* Params, Data::Db::TUpdateMode GenUpdateMode, System::UnicodeString Alias);
	virtual void __fastcall GenInsertSQL(TUpdateTree* Tree, System::Classes::TStrings* SQL, Data::Db::TParams* Params);
	virtual void __fastcall GenDeleteSQL(TUpdateTree* Tree, System::Classes::TStrings* SQL, Data::Db::TParams* Params, System::UnicodeString Alias);
	virtual void __fastcall GenUpdateSQL(TUpdateTree* Tree, System::Classes::TStrings* SQL, Data::Db::TParams* Params, System::UnicodeString Alias);
	virtual void __fastcall GenSelectSQL(TUpdateTree* Tree, System::Classes::TStrings* SQL, Data::Db::TParams* Params, System::UnicodeString Alias, Data::Db::TUpdateMode Mode = (Data::Db::TUpdateMode)(0x2));
	virtual bool __fastcall UseFieldInUpdate(Data::Db::TField* Field);
	virtual bool __fastcall UseFieldInWhere(Data::Db::TField* Field, Data::Db::TUpdateMode Mode);
	virtual void __fastcall InternalDoUpdate(TUpdateTree* Tree, Data::Db::TUpdateKind UpdateKind);
	virtual void __fastcall DoExecSQL(System::Classes::TStringList* SQL, Data::Db::TParams* Params);
	virtual void __fastcall DoGetValues(System::Classes::TStringList* SQL, Data::Db::TParams* Params, Data::Db::TDataSet* DataSet);
	virtual void __fastcall DoUpdate(TUpdateTree* Tree);
	virtual void __fastcall DoDelete(TUpdateTree* Tree);
	virtual void __fastcall DoInsert(TUpdateTree* Tree);
	virtual void __fastcall InitializeConflictBuffer(TUpdateTree* Tree);
	__property TDataSetProvider* Provider = {read=GetProvider};
	
public:
	__fastcall TSQLResolver(TDataSetProvider* AProvider);
	__fastcall virtual ~TSQLResolver();
	virtual void __fastcall FreeTreeData(TUpdateTree* Tree);
	virtual void __fastcall InitTreeData(TUpdateTree* Tree);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLocalAppServer : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	TCustomProvider* FProvider;
	bool FProviderCreated;
	
protected:
	HRESULT __stdcall GetTypeInfoCount(/* out */ int &Count);
	HRESULT __stdcall GetTypeInfo(int Index, int LocaleID, /* out */ void *TypeInfo);
	HRESULT __stdcall GetIDsOfNames(const GUID IID, void * Names, int NameCount, int LocaleID, void * DispIDs);
	HRESULT __stdcall Invoke(int DispID, const GUID IID, int LocaleID, System::Word Flags, void *Params, void * VarResult, void * ExcepInfo, void * ArgErr);
	HRESULT __safecall AS_ApplyUpdates(const System::WideString ProviderName, System::OleVariant Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData, System::OleVariant &__AS_ApplyUpdates_result);
	HRESULT __safecall AS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData, System::OleVariant &__AS_GetRecords_result);
	HRESULT __safecall AS_DataRequest(const System::WideString ProviderName, System::OleVariant Data, System::OleVariant &__AS_DataRequest_result);
	HRESULT __safecall AS_GetProviderNames(System::OleVariant &__AS_GetProviderNames_result);
	HRESULT __safecall AS_GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData, System::OleVariant &__AS_GetParams_result);
	HRESULT __safecall AS_RowRequest(const System::WideString ProviderName, System::OleVariant Row, int RequestType, System::OleVariant &OwnerData, System::OleVariant &__AS_RowRequest_result);
	HRESULT __safecall AS_Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	HRESULT __stdcall InterfaceSupportsErrorInfo(const GUID iid);
	
public:
	__fastcall TLocalAppServer(TCustomProvider* AProvider)/* overload */;
	__fastcall TLocalAppServer(Data::Db::TDataSet* ADataset)/* overload */;
	__fastcall virtual ~TLocalAppServer();
	virtual HRESULT __fastcall SafeCallException(System::TObject* ExceptObject, void * ExceptAddr);
private:
	void *__IAppServer;	// Datasnap::Midas::IAppServer 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1AEFCC20-7A24-11D2-98B0-C69BEB4B5B6D}
	operator Datasnap::Midas::_di_IAppServer()
	{
		Datasnap::Midas::_di_IAppServer intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Datasnap::Midas::IAppServer*(void) { return (Datasnap::Midas::IAppServer*)&__IAppServer; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EEE9FFD4-752F-11D4-80DD-00C04F6BB88C}") IProviderContainer  : public System::IInterface 
{
	virtual void __fastcall RegisterProvider(TCustomProvider* Prov) = 0 ;
	virtual void __fastcall UnRegisterProvider(TCustomProvider* Prov) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool InformixLob;
extern DELPHI_PACKAGE int ResetOption;
extern DELPHI_PACKAGE int MetaDataOption;
extern DELPHI_PACKAGE int XMLOption;
extern DELPHI_PACKAGE int XMLUTF8Option;
extern DELPHI_PACKAGE System::TObject* __fastcall GetObjectProperty(System::Classes::TPersistent* Instance, const System::UnicodeString PropName);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetStringProperty(System::Classes::TPersistent* Instance, const System::UnicodeString PropName);
extern DELPHI_PACKAGE System::Variant __fastcall VarArrayFromStrings(System::Classes::TStrings* Strings);
}	/* namespace Provider */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_PROVIDER)
using namespace Datasnap::Provider;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_ProviderHPP
