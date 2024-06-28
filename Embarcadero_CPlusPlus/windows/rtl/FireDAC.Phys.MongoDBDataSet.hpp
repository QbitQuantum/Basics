// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MongoDBDataSet.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_MongodbdatasetHPP
#define Firedac_Phys_MongodbdatasetHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.JSON.Types.hpp>
#include <System.JSON.hpp>
#include <Data.DB.hpp>
#include <Data.DBJson.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.MongoDBWrapper.hpp>
#include <FireDAC.Phys.MongoDB.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Mongodbdataset
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDMongoCustomMemTable;
class DELPHICLASS TFDMongoCustomDataSet;
class DELPHICLASS TFDMongoDataSet;
class DELPHICLASS TFDMongoQuery;
class DELPHICLASS TFDMongoPipeline;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TFDMongoStringsMode : unsigned int { Strict, Clip, Full };

class PASCALIMPLEMENTATION TFDMongoCustomMemTable : public Firedac::Comp::Client::TFDCustomMemTable
{
	typedef Firedac::Comp::Client::TFDCustomMemTable inherited;
	
protected:
#ifndef _WIN64
	virtual void __fastcall DataConvert(Data::Db::TField* Field, System::DynamicArray<System::Byte> Source, System::DynamicArray<System::Byte> &Dest, bool ToNative)/* overload */;
#else /* _WIN64 */
	virtual void __fastcall DataConvert(Data::Db::TField* Field, System::TArray__1<System::Byte> Source, System::TArray__1<System::Byte> &Dest, bool ToNative)/* overload */;
#endif /* _WIN64 */
	virtual void __fastcall DataConvert(Data::Db::TField* Field, void * Source, void * Dest, bool ToNative)/* overload */;
	
public:
	__fastcall virtual TFDMongoCustomMemTable(System::Classes::TComponent* AOwner);
public:
	/* TFDCustomMemTable.Destroy */ inline __fastcall virtual ~TFDMongoCustomMemTable() { }
	
};


class PASCALIMPLEMENTATION TFDMongoCustomDataSet : public TFDMongoCustomMemTable
{
	typedef TFDMongoCustomMemTable inherited;
	
private:
	Firedac::Comp::Client::TFDCustomConnection* FConnection;
	Firedac::Phys::Mongodbwrapper::TMongoConnection* FMongoConnection;
	System::UnicodeString FCollectionName;
	System::UnicodeString FDatabaseName;
	Firedac::Phys::Mongodbwrapper::_di_IMongoCursor FCursor;
	bool FExternalCursor;
	System::Generics::Collections::TObjectList__1<Firedac::Phys::Mongodbwrapper::TMongoDocument*>* FPrefetchedDocs;
	int FRowsFetched;
	Data::Dbjson::TJSONToDataSetBridge* FBridge;
	void __fastcall SetConnection(Firedac::Comp::Client::TFDCustomConnection* const AValue);
	void __fastcall CheckConnectionActive();
	void __fastcall CheckConnection();
	void __fastcall CheckNames();
	void __fastcall SetCollectionName(const System::UnicodeString AValue);
	void __fastcall SetDatabaseName(const System::UnicodeString AValue);
	void __fastcall SetCursor(const Firedac::Phys::Mongodbwrapper::_di_IMongoCursor AValue);
	__classmethod bool __fastcall IsOidField(Data::Db::TField* AField, /* out */ System::Json::Types::TJsonOid &AOid);
	void __fastcall WriteFieldValues(Data::Db::TFields* AFields, Firedac::Phys::Mongodbwrapper::TMongoDocument* ADoc);
	void __fastcall BuildInsertDoc(Firedac::Phys::Mongodbwrapper::TMongoInsert::TExpression* AIns);
	void __fastcall BuildModifyDoc(Firedac::Phys::Mongodbwrapper::TMongoUpdate::TModifier* AMod);
	void __fastcall DefineFromDoc(Firedac::Phys::Mongodbwrapper::TMongoDocument* ADoc, int ASampleDocs);
	void __fastcall FetchFromDoc(Firedac::Phys::Mongodbwrapper::TMongoDocument* ADoc);
	void __fastcall ApplyToDoc(Firedac::Stan::Option::TFDUpdateRequest ARequest, Firedac::Phys::Mongodbwrapper::TMongoCollection* AColl);
	void __fastcall DoConnectChanged(System::TObject* Sender, bool Connecting);
	Firedac::Phys::Mongodbwrapper::TMongoCollection* __fastcall GetCollection();
	TFDMongoStringsMode __fastcall GetStringsMode();
	void __fastcall SetStringsMode(TFDMongoStringsMode AValue);
	Firedac::Stan::Intf::TFDMergeMetaMode __fastcall GetMetaMergeMode();
	void __fastcall SetMetaMergeMode(const Firedac::Stan::Intf::TFDMergeMetaMode AValue);
	
protected:
	System::UnicodeString __fastcall GetDefaultFieldName(System::Json::TJSONValue* const AJSON);
	int __fastcall GetScanDepth();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation AOperation);
	virtual bool __fastcall GetCanRefresh();
	virtual bool __fastcall GetCanModify();
	virtual void __fastcall OpenCursor(bool InfoQuery);
	virtual void __fastcall InternalClose();
	virtual void __fastcall DoDefineDatSManager();
	virtual void __fastcall DoOpenSource(bool ABlocked, bool AInfoQuery, bool AStructQuery);
	virtual int __fastcall DoFetch(Firedac::Dats::TFDDatSTable* ATable, bool AAll, Firedac::Comp::Dataset::TFDFetchDirection ADirection)/* overload */;
	virtual void __fastcall DoCloseSource();
	virtual void __fastcall DoResetDatSManager();
	virtual void __fastcall DoUpdateRecordHandler(Firedac::Dats::TFDDatSRow* ARow, Firedac::Stan::Option::TFDUpdateRequest ARequest, Firedac::Stan::Option::TFDUpdateRowOptions AOptions, Firedac::Stan::Intf::TFDErrorAction &AAction);
	virtual Firedac::Phys::Mongodbwrapper::_di_IMongoCursor __fastcall GetCursor(int ALimit, int ASkip);
	__property Firedac::Phys::Mongodbwrapper::_di_IMongoCursor Cursor = {read=FCursor, write=SetCursor};
	
public:
	__fastcall virtual TFDMongoCustomDataSet(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDMongoCustomDataSet();
	virtual void __fastcall ServerDeleteAll(bool ANoUndo = false);
	__property Firedac::Phys::Mongodbwrapper::TMongoCollection* Collection = {read=GetCollection};
	__property Firedac::Comp::Client::TFDCustomConnection* Connection = {read=FConnection, write=SetConnection};
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=SetDatabaseName};
	__property System::UnicodeString CollectionName = {read=FCollectionName, write=SetCollectionName};
	__property Firedac::Stan::Intf::TFDMergeMetaMode MetaMergeMode = {read=GetMetaMergeMode, write=SetMetaMergeMode, default=1};
	__property TFDMongoStringsMode StringsMode = {read=GetStringsMode, write=SetStringsMode, stored=false, default=0};
	/* Hoisted overloads: */
	
protected:
	inline bool __fastcall  DoFetch(Firedac::Dats::TFDDatSRow* ARow, int AColumn, Firedac::Phys::Intf::TFDPhysFillRowOptions ARowOptions){ return Firedac::Comp::Client::TFDAdaptedDataSet::DoFetch(ARow, AColumn, ARowOptions); }
	
private:
	void *__TJSONToDataSetBridge_IAdaptor;	// Data::Dbjson::TJSONToDataSetBridge::IAdaptor 
	
public:
	operator Data::Dbjson::TJSONToDataSetBridge::IAdaptor*(void) { return (Data::Dbjson::TJSONToDataSetBridge::IAdaptor*)&__TJSONToDataSetBridge_IAdaptor; }
	
};


class PASCALIMPLEMENTATION TFDMongoDataSet : public TFDMongoCustomDataSet
{
	typedef TFDMongoCustomDataSet inherited;
	
public:
	__property Cursor;
	
__published:
	__property ActiveStoredUsage = {default=3};
	__property Active = {default=0};
	__property AutoCalcFields = {default=1};
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
	__property OnNewRecord;
	__property OnPostError;
	__property FieldOptions;
	__property Filtered = {default=0};
	__property FilterOptions = {default=0};
	__property Filter = {default=0};
	__property OnFilterRecord;
	__property ObjectView = {default=1};
	__property Constraints;
	__property CachedUpdates = {default=0};
	__property FilterChanges = {default=11};
	__property Indexes;
	__property IndexesActive = {default=1};
	__property IndexName = {default=0};
	__property IndexFieldNames = {default=0};
	__property Aggregates;
	__property AggregatesActive = {default=0};
	__property ConstraintsEnabled = {default=0};
	__property MasterSource;
	__property MasterFields = {default=0};
	__property DetailFields = {default=0};
	__property OnUpdateRecord;
	__property OnUpdateError;
	__property OnReconcileError;
	__property BeforeApplyUpdates;
	__property AfterApplyUpdates;
	__property BeforeGetRecords;
	__property AfterGetRecords;
	__property AfterGetRecord;
	__property FetchOptions;
	__property FormatOptions;
	__property ResourceOptions;
	__property UpdateOptions;
	__property LocalSQL;
	__property Connection;
	__property DatabaseName = {default=0};
	__property CollectionName = {default=0};
	__property MetaMergeMode = {default=1};
	__property StringsMode = {default=0};
public:
	/* TFDMongoCustomDataSet.Create */ inline __fastcall virtual TFDMongoDataSet(System::Classes::TComponent* AOwner) : TFDMongoCustomDataSet(AOwner) { }
	/* TFDMongoCustomDataSet.Destroy */ inline __fastcall virtual ~TFDMongoDataSet() { }
	
};


class PASCALIMPLEMENTATION TFDMongoQuery : public TFDMongoCustomDataSet
{
	typedef TFDMongoCustomDataSet inherited;
	
private:
	Firedac::Phys::Mongodbwrapper::TMongoQuery* FQuery;
	System::UnicodeString FQProject;
	System::UnicodeString FQMatch;
	System::UnicodeString FQSort;
	Firedac::Phys::Mongodbwrapper::TMongoQuery* __fastcall GetQuery();
	void __fastcall SetQProject(const System::UnicodeString AValue);
	void __fastcall SetQMatch(const System::UnicodeString AValue);
	void __fastcall SetQSort(const System::UnicodeString AValue);
	void __fastcall PrepareQuery(int ALimit, int ASkip);
	
protected:
	virtual void __fastcall UpdateRecordCount();
	virtual Firedac::Phys::Mongodbwrapper::_di_IMongoCursor __fastcall GetCursor(int ALimit, int ASkip);
	
public:
	__fastcall virtual ~TFDMongoQuery();
	__property Firedac::Phys::Mongodbwrapper::TMongoQuery* Query = {read=GetQuery};
	
__published:
	__property ActiveStoredUsage = {default=3};
	__property Active = {default=0};
	__property AutoCalcFields = {default=1};
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
	__property OnNewRecord;
	__property OnPostError;
	__property FieldOptions;
	__property Filtered = {default=0};
	__property FilterOptions = {default=0};
	__property Filter = {default=0};
	__property OnFilterRecord;
	__property ObjectView = {default=1};
	__property Constraints;
	__property CachedUpdates = {default=0};
	__property FilterChanges = {default=11};
	__property Indexes;
	__property IndexesActive = {default=1};
	__property IndexName = {default=0};
	__property IndexFieldNames = {default=0};
	__property Aggregates;
	__property AggregatesActive = {default=0};
	__property ConstraintsEnabled = {default=0};
	__property MasterSource;
	__property MasterFields = {default=0};
	__property DetailFields = {default=0};
	__property OnUpdateRecord;
	__property OnUpdateError;
	__property OnReconcileError;
	__property BeforeApplyUpdates;
	__property AfterApplyUpdates;
	__property BeforeGetRecords;
	__property AfterGetRecords;
	__property AfterGetRecord;
	__property FetchOptions;
	__property FormatOptions;
	__property ResourceOptions;
	__property UpdateOptions;
	__property LocalSQL;
	__property Connection;
	__property DatabaseName = {default=0};
	__property CollectionName = {default=0};
	__property MetaMergeMode = {default=1};
	__property StringsMode = {default=0};
	__property System::UnicodeString QProject = {read=FQProject, write=SetQProject};
	__property System::UnicodeString QMatch = {read=FQMatch, write=SetQMatch};
	__property System::UnicodeString QSort = {read=FQSort, write=SetQSort};
public:
	/* TFDMongoCustomDataSet.Create */ inline __fastcall virtual TFDMongoQuery(System::Classes::TComponent* AOwner) : TFDMongoCustomDataSet(AOwner) { }
	
};


class PASCALIMPLEMENTATION TFDMongoPipeline : public TFDMongoCustomDataSet
{
	typedef TFDMongoCustomDataSet inherited;
	
private:
	Firedac::Phys::Mongodbwrapper::TMongoPipeline* FPipeline;
	System::UnicodeString FPUnwind;
	System::UnicodeString FPSort;
	System::UnicodeString FPMatch;
	System::UnicodeString FPGroup;
	System::UnicodeString FPRedact;
	System::UnicodeString FPProject;
	Firedac::Phys::Mongodbwrapper::TMongoPipeline* __fastcall GetPipeline();
	void __fastcall SetPProject(const System::UnicodeString AValue);
	void __fastcall SetPMatch(const System::UnicodeString AValue);
	void __fastcall SetPRedact(const System::UnicodeString AValue);
	void __fastcall SetPUnwind(const System::UnicodeString AValue);
	void __fastcall SetPGroup(const System::UnicodeString AValue);
	void __fastcall SetPSort(const System::UnicodeString AValue);
	void __fastcall PreparePipeline(int ALimit, int ASkip);
	
protected:
	virtual Firedac::Phys::Mongodbwrapper::_di_IMongoCursor __fastcall GetCursor(int ALimit, int ASkip);
	
public:
	__fastcall virtual ~TFDMongoPipeline();
	__property Firedac::Phys::Mongodbwrapper::TMongoPipeline* Pipeline = {read=GetPipeline};
	
__published:
	__property ActiveStoredUsage = {default=3};
	__property Active = {default=0};
	__property AutoCalcFields = {default=1};
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
	__property OnNewRecord;
	__property OnPostError;
	__property FieldOptions;
	__property Filtered = {default=0};
	__property FilterOptions = {default=0};
	__property Filter = {default=0};
	__property OnFilterRecord;
	__property ObjectView = {default=1};
	__property Constraints;
	__property CachedUpdates = {default=0};
	__property FilterChanges = {default=11};
	__property Indexes;
	__property IndexesActive = {default=1};
	__property IndexName = {default=0};
	__property IndexFieldNames = {default=0};
	__property Aggregates;
	__property AggregatesActive = {default=0};
	__property ConstraintsEnabled = {default=0};
	__property MasterSource;
	__property MasterFields = {default=0};
	__property DetailFields = {default=0};
	__property OnUpdateRecord;
	__property OnUpdateError;
	__property OnReconcileError;
	__property BeforeApplyUpdates;
	__property AfterApplyUpdates;
	__property BeforeGetRecords;
	__property AfterGetRecords;
	__property AfterGetRecord;
	__property FetchOptions;
	__property FormatOptions;
	__property ResourceOptions;
	__property UpdateOptions;
	__property LocalSQL;
	__property Connection;
	__property DatabaseName = {default=0};
	__property CollectionName = {default=0};
	__property MetaMergeMode = {default=1};
	__property StringsMode = {default=0};
	__property System::UnicodeString PProject = {read=FPProject, write=SetPProject};
	__property System::UnicodeString PMatch = {read=FPMatch, write=SetPMatch};
	__property System::UnicodeString PRedact = {read=FPRedact, write=SetPRedact};
	__property System::UnicodeString PUnwind = {read=FPUnwind, write=SetPUnwind};
	__property System::UnicodeString PGroup = {read=FPGroup, write=SetPGroup};
	__property System::UnicodeString PSort = {read=FPSort, write=SetPSort};
public:
	/* TFDMongoCustomDataSet.Create */ inline __fastcall virtual TFDMongoPipeline(System::Classes::TComponent* AOwner) : TFDMongoCustomDataSet(AOwner) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mongodbdataset */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MONGODBDATASET)
using namespace Firedac::Phys::Mongodbdataset;
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
#endif	// Firedac_Phys_MongodbdatasetHPP
