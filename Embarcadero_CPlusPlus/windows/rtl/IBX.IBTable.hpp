// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBTable.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbtableHPP
#define Ibx_IbtableHPP

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
#include <IBX.IB.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBCustomDataSet.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibtable
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBTable;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIBTableType : unsigned char { ttSystem, ttView };

typedef System::Set<TIBTableType, TIBTableType::ttSystem, TIBTableType::ttView> TIBTableTypes;

typedef System::UnicodeString TIndexName;

class PASCALIMPLEMENTATION TIBTable : public Ibx::Ibcustomdataset::TIBCustomDataSet
{
	typedef Ibx::Ibcustomdataset::TIBCustomDataSet inherited;
	
private:
	bool FSystemTable;
	bool FMultiTableView;
	Data::Db::TMasterDataLink* FMasterLink;
	System::Classes::TStringList* FMasterFieldsList;
	System::Classes::TStringList* FDetailFieldsList;
	bool FStoreDefs;
	Data::Db::TIndexDefs* FIndexDefs;
	bool FDefaultIndex;
	bool FReadOnly;
	bool FFieldsIndex;
	System::UnicodeString FTableName;
	System::UnicodeString FIndexName;
	bool FRegenerateSQL;
	System::Classes::TStrings* FNameList;
	bool FSwitchingIndex;
	System::UnicodeString FPrimaryIndexFields;
	TIBTableTypes FTableTypes;
	System::Classes::TStrings* WhereAllRefreshSQL;
	System::Classes::TStrings* WhereDBKeyRefreshSQL;
	System::Classes::TStrings* WherePrimaryRefreshSQL;
	int __fastcall GetIndexFieldCount();
	Data::Db::TField* __fastcall GetIndexField(int Index);
	void __fastcall MasterChanged(System::TObject* Sender);
	void __fastcall MasterDisabled(System::TObject* Sender);
	HIDESBASE void __fastcall SetDataSource(Data::Db::TDataSource* Value);
	void __fastcall SetIndexField(int Index, Data::Db::TField* Value);
	void __fastcall SetIndexFieldNames(const System::UnicodeString Value);
	void __fastcall GenerateSQL();
	void __fastcall GenerateUpdateSQL();
	void __fastcall SwitchToIndex();
	void __fastcall InternalTableRefresh();
	System::Classes::TStrings* __fastcall GetTableNames();
	void __fastcall GetTableNamesFromServer();
	void __fastcall SetTableTypes(const TIBTableTypes Value);
	bool __fastcall InternalGotoDBKey(const Ibx::Ibcustomdataset::TIBDBKey &DBKey);
	System::UnicodeString __fastcall FormatFieldsList(System::UnicodeString Value);
	Ibx::Ibcustomdataset::TIBDBKey __fastcall GetCurrentDBKey();
	bool __fastcall InternalGetUpdatable();
	bool __fastcall GetExists();
	void __fastcall SetIndexDefs(Data::Db::TIndexDefs* Value);
	void __fastcall ExtractLinkFields();
	bool __fastcall FieldDefsStored();
	bool __fastcall IndexDefsStored();
	System::UnicodeString __fastcall GetMasterFields();
	void __fastcall SetMasterFields(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetIndexFieldNames();
	System::UnicodeString __fastcall GetIndexName();
	void __fastcall SetIndexName(const System::UnicodeString Value);
	void __fastcall SetParams();
	void __fastcall SetReadOnly(bool Value);
	void __fastcall SetTableName(System::UnicodeString Value);
	void __fastcall SetIndex(const System::UnicodeString Value, bool FieldsIndex);
	void __fastcall ResetSQLStatements();
	void __fastcall Reopen();
	HIDESBASE bool __fastcall InternalLocate(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options);
	
protected:
	virtual Data::Db::TIndexDef* __fastcall PSGetDefaultOrder();
	virtual System::UnicodeString __fastcall PSGetKeyFields();
	virtual System::UnicodeString __fastcall PSGetTableName();
	virtual Data::Db::TIndexDefs* __fastcall PSGetIndexDefs(Data::Db::TIndexOptions IndexTypes);
	virtual void __fastcall PSSetCommandText(const System::UnicodeString CommandText);
	virtual void __fastcall PSSetParams(Data::Db::TParams* AParams);
	virtual System::UnicodeString __fastcall PSGetCommandText();
	virtual Data::Db::TPSCommandType __fastcall PSGetCommandType();
	virtual void __fastcall DoOnNewRecord();
	void __fastcall GetIndexParams(const System::UnicodeString IndexName, bool FieldsIndex, System::UnicodeString &IndexedName);
	virtual bool __fastcall GetCanModify();
	virtual void __fastcall UpdateIndexDefs();
	virtual void __fastcall DataEvent(Data::Db::TDataEvent Event, NativeInt Info);
	virtual void __fastcall DefChanged(System::TObject* Sender);
	virtual Data::Db::TDataSource* __fastcall GetDataSource();
	virtual void __fastcall InitFieldDefs();
	virtual void __fastcall InternalClose();
	virtual void __fastcall InternalOpen();
	virtual void __fastcall InternalRefresh();
	virtual void __fastcall SetFiltered(bool Value);
	virtual void __fastcall SetFilterText(const System::UnicodeString Value);
	virtual void __fastcall SetFilterOptions(Data::Db::TFilterOptions Value);
	virtual void __fastcall InternalRefreshRow();
	
public:
	__fastcall virtual TIBTable(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBTable();
	void __fastcall AddIndex(const System::UnicodeString Name, const System::UnicodeString Fields, Data::Db::TIndexOptions Options, const System::UnicodeString DescFields = System::UnicodeString());
	void __fastcall CreateTable();
	void __fastcall DeleteIndex(const System::UnicodeString Name);
	void __fastcall DeleteTable();
	void __fastcall EmptyTable();
	virtual void __fastcall GetDetailLinkFields(System::Generics::Collections::TList__1<Data::Db::TField*>* MasterFields, System::Generics::Collections::TList__1<Data::Db::TField*>* DetailFields)/* overload */;
	void __fastcall GetIndexNames(System::Classes::TStrings* List);
	void __fastcall GotoCurrent(TIBTable* Table);
	virtual bool __fastcall Locate(const System::UnicodeString KeyFields, const System::Variant &KeyValues, Data::Db::TLocateOptions Options);
	__property LiveMode;
	__property Ibx::Ibcustomdataset::TIBDBKey CurrentDBKey = {read=GetCurrentDBKey};
	__property bool Exists = {read=GetExists, nodefault};
	__property int IndexFieldCount = {read=GetIndexFieldCount, nodefault};
	__property Data::Db::TField* IndexFields[int Index] = {read=GetIndexField, write=SetIndexField};
	__property System::Classes::TStrings* TableNames = {read=GetTableNames};
	
__published:
	__property Active = {default=0};
	__property BufferChunks;
	__property CachedUpdates;
	__property Constraints = {stored=ConstraintsStored};
	__property bool DefaultIndex = {read=FDefaultIndex, write=FDefaultIndex, default=1};
	__property FieldDefs = {stored=FieldDefsStored};
	__property Filter = {default=0};
	__property Filtered = {default=0};
	__property Data::Db::TIndexDefs* IndexDefs = {read=FIndexDefs, write=SetIndexDefs, stored=IndexDefsStored};
	__property System::UnicodeString IndexFieldNames = {read=GetIndexFieldNames, write=SetIndexFieldNames};
	__property System::UnicodeString IndexName = {read=GetIndexName, write=SetIndexName};
	__property System::UnicodeString MasterFields = {read=GetMasterFields, write=SetMasterFields};
	__property Data::Db::TDataSource* MasterSource = {read=GetDataSource, write=SetDataSource};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, default=0};
	__property bool StoreDefs = {read=FStoreDefs, write=FStoreDefs, default=0};
	__property System::UnicodeString TableName = {read=FTableName, write=SetTableName};
	__property TIBTableTypes TableTypes = {read=FTableTypes, write=SetTableTypes, default=0};
	__property UpdateObject;
	__property UniDirectional;
	__property BeforeDatabaseDisconnect;
	__property AfterDatabaseDisconnect;
	__property DatabaseFree;
	__property BeforeTransactionEnd;
	__property AfterTransactionEnd;
	__property TransactionFree;
	__property OnFilterRecord;
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  GetDetailLinkFields _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::Classes::TList* MasterFields, System::Classes::TList* DetailFields){ Data::Db::TDataSet::GetDetailLinkFields(MasterFields, DetailFields); }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibtable */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBTABLE)
using namespace Ibx::Ibtable;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbtableHPP
