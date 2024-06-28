// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SimpleDS.pas' rev: 34.00 (Windows)

#ifndef SimpledsHPP
#define SimpledsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.DB.hpp>

//-- user supplied -----------------------------------------------------------

namespace Simpleds
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TInternalSQLDataSet;
class DELPHICLASS TSimpleDataSet;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TInternalSQLDataSet : public Data::Sqlexpr::TCustomSQLDataSet
{
	typedef Data::Sqlexpr::TCustomSQLDataSet inherited;
	
__published:
	__property CommandText = {default=0};
	__property CommandType = {default=1};
	__property DataSource;
	__property GetMetadata = {default=0};
	__property MaxBlobSize = {default=0};
	__property ParamCheck = {default=1};
	__property Params;
	__property SortFieldNames = {default=0};
public:
	/* TCustomSQLDataSet.Create */ inline __fastcall virtual TInternalSQLDataSet(System::Classes::TComponent* AOwner)/* overload */ : Data::Sqlexpr::TCustomSQLDataSet(AOwner) { }
	/* TCustomSQLDataSet.Create */ inline __fastcall TInternalSQLDataSet(System::Classes::TComponent* AOwner, Data::Dbxcommon::TDBXReader* DBXReader, bool AOwnsInstance)/* overload */ : Data::Sqlexpr::TCustomSQLDataSet(AOwner, DBXReader, AOwnsInstance) { }
	/* TCustomSQLDataSet.Destroy */ inline __fastcall virtual ~TInternalSQLDataSet() { }
	
};


class PASCALIMPLEMENTATION TSimpleDataSet : public Datasnap::Dbclient::TCustomClientDataSet
{
	typedef Datasnap::Dbclient::TCustomClientDataSet inherited;
	
private:
	Data::Sqlexpr::TSQLConnection* FConnection;
	Data::Sqlexpr::TSQLConnection* FInternalConnection;
	TInternalSQLDataSet* FDataSet;
	Datasnap::Provider::TDataSetProvider* FProvider;
	
protected:
	virtual void __fastcall AllocConnection();
	virtual void __fastcall AllocDataSet();
	virtual void __fastcall AllocProvider();
	virtual void __fastcall Loaded();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall OpenCursor(bool InfoQuery);
	virtual void __fastcall SetConnection(Data::Sqlexpr::TSQLConnection* Value);
	virtual System::UnicodeString __fastcall PSGetCommandText();
	
public:
	__fastcall virtual TSimpleDataSet(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSimpleDataSet();
	HIDESBASE void __fastcall FetchParams();
	
__published:
	__property Active = {default=0};
	__property Aggregates;
	__property AggregatesActive = {default=0};
	__property AutoCalcFields = {default=1};
	__property Data::Sqlexpr::TSQLConnection* Connection = {read=FConnection, write=SetConnection};
	__property TInternalSQLDataSet* DataSet = {read=FDataSet};
	__property Constraints;
	__property DisableStringTrim = {default=0};
	__property FileName = {default=0};
	__property Filter = {default=0};
	__property Filtered = {default=0};
	__property FilterOptions = {default=0};
	__property FieldDefs;
	__property IndexDefs;
	__property IndexFieldNames = {default=0};
	__property IndexName = {default=0};
	__property FetchOnDemand = {default=1};
	__property MasterFields = {default=0};
	__property MasterSource;
	__property ObjectView = {default=1};
	__property PacketRecords = {default=-1};
	__property Params;
	__property ReadOnly = {default=0};
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
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Simpleds */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SIMPLEDS)
using namespace Simpleds;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SimpledsHPP
