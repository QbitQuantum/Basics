// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBQuery.pas' rev: 34.00 (iOS)

#ifndef Ibx_IbqueryHPP
#define Ibx_IbqueryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBCustomDataSet.hpp>
#include <IBX.IBSQL.hpp>
#include <System.Generics.Collections.hpp>
#include <IBX.IBInputOutput.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <IBX.IBExternals.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibquery
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBQuery;
class DELPHICLASS TIBXParam;
class DELPHICLASS TIBXParams;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIBQuery : public Ibx::Ibcustomdataset::TIBCustomDataSet
{
	typedef Ibx::Ibcustomdataset::TIBCustomDataSet inherited;
	
private:
	System::Classes::TStrings* FSQL;
	bool FPrepared;
	Data::Db::TParams* FParams;
	System::UnicodeString FText;
	int FRowsAffected;
	bool FCheckRowsAffected;
	bool FGenerateParamNames;
	int __fastcall GetRowsAffected();
	void __fastcall PrepareSQL(System::WideChar * Value);
	void __fastcall QueryChanged(System::TObject* Sender);
	void __fastcall ReadParamData(System::Classes::TReader* Reader);
	void __fastcall SetQuery(System::Classes::TStrings* Value);
	void __fastcall SetParamsList(Data::Db::TParams* Value);
	void __fastcall SetParams();
	void __fastcall SetParamsFromCursor();
	void __fastcall SetPrepared(bool Value);
	void __fastcall SetPrepare(bool Value);
	void __fastcall WriteParamData(System::Classes::TWriter* Writer);
	Ibx::Ibexternals::PVoid __fastcall GetStmtHandle();
	Data::Db::TParams* __fastcall GetParams();
	
protected:
	virtual void __fastcall PSExecute();
	virtual Data::Db::TParams* __fastcall PSGetParams();
	virtual System::UnicodeString __fastcall PSGetTableName();
	virtual void __fastcall PSSetCommandText(const System::UnicodeString CommandText);
	virtual void __fastcall PSSetParams(Data::Db::TParams* AParams);
	virtual System::UnicodeString __fastcall PSGetCommandText();
	virtual Data::Db::TPSCommandType __fastcall PSGetCommandType();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall InitFieldDefs();
	virtual void __fastcall InternalOpen();
	virtual void __fastcall Disconnect();
	System::Word __fastcall GetParamsCount();
	bool __fastcall GenerateQueryForLiveUpdate();
	virtual void __fastcall SetFiltered(bool Value);
	virtual Data::Db::TParamsClass __fastcall GetParamsClass();
	
public:
	__fastcall virtual TIBQuery(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBQuery();
	void __fastcall BatchInput(Ibx::Ibinputoutput::TIBBatchInput* InputObject);
	void __fastcall BatchOutput(Ibx::Ibinputoutput::TIBBatchOutput* OutputObject);
	void __fastcall ExecSQL();
	virtual void __fastcall GetDetailLinkFields(System::Generics::Collections::TList__1<Data::Db::TField*>* MasterFields, System::Generics::Collections::TList__1<Data::Db::TField*>* DetailFields)/* overload */;
	Data::Db::TParam* __fastcall ParamByName(const System::UnicodeString Value);
	void __fastcall Prepare();
	void __fastcall UnPrepare();
	void __fastcall SetBlobParamOrigin(System::UnicodeString ParamName, System::UnicodeString Relation, System::UnicodeString Column);
	__property LiveMode;
	__property bool Prepared = {read=FPrepared, write=SetPrepare, nodefault};
	__property System::Word ParamCount = {read=GetParamsCount, nodefault};
	__property Ibx::Ibexternals::PVoid StmtHandle = {read=GetStmtHandle};
	__property StatementType;
	__property System::UnicodeString Text = {read=FText};
	__property int RowsAffected = {read=GetRowsAffected, nodefault};
	__property bool GenerateParamNames = {read=FGenerateParamNames, write=FGenerateParamNames, nodefault};
	
__published:
	__property Active = {default=0};
	__property BufferChunks;
	__property CachedUpdates;
	__property DataSource = {read=GetDataSource, write=SetDataSource};
	__property Constraints = {stored=ConstraintsStored};
	__property ParamCheck;
	__property System::Classes::TStrings* SQL = {read=FSQL, write=SetQuery};
	__property Data::Db::TParams* Params = {read=GetParams, write=SetParamsList, stored=false};
	__property UniDirectional = {default=0};
	__property UpdateObject;
	__property Filtered = {default=0};
	__property GeneratorField;
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


class PASCALIMPLEMENTATION TIBXParam : public Data::Db::TParam
{
	typedef Data::Db::TParam inherited;
	
private:
	System::UnicodeString FDataTypeName;
	System::UnicodeString FColumnName;
	System::UnicodeString FRelationName;
	void __fastcall SetDataTypeName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetColumnName();
	System::UnicodeString __fastcall GetRelationName();
	
public:
	__property System::UnicodeString RelationName = {read=GetRelationName};
	__property System::UnicodeString ColumnName = {read=GetColumnName};
	
__published:
	__property System::UnicodeString DataTypeName = {read=FDataTypeName, write=SetDataTypeName};
public:
	/* TParam.Create */ inline __fastcall virtual TIBXParam(System::Classes::TCollection* Collection)/* overload */ : Data::Db::TParam(Collection) { }
	/* TParam.Create */ inline __fastcall TIBXParam(Data::Db::TParams* AParams, Data::Db::TParamType AParamType)/* overload */ : Data::Db::TParam(AParams, AParamType) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIBXParam() { }
	
};


class PASCALIMPLEMENTATION TIBXParams : public Data::Db::TParams
{
	typedef Data::Db::TParams inherited;
	
protected:
	virtual Data::Db::TParamClass __fastcall GetParamClass();
public:
	/* TParams.Create */ inline __fastcall TIBXParams(System::Classes::TPersistent* Owner)/* overload */ : Data::Db::TParams(Owner) { }
	/* TParams.Create */ inline __fastcall TIBXParams()/* overload */ : Data::Db::TParams() { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIBXParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Data::Db::TParamClass DefaultIBXParamClass;
extern DELPHI_PACKAGE Data::Db::TParamsClass DefaultIBXParamsClass;
}	/* namespace Ibquery */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBQUERY)
using namespace Ibx::Ibquery;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbqueryHPP
