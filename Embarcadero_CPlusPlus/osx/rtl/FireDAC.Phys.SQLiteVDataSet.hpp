// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.SQLiteVDataSet.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_SqlitevdatasetHPP
#define Firedac_Phys_SqlitevdatasetHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Comp.Client.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Sqlitevdataset
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDLocalSQL;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDLocalSQL : public Firedac::Comp::Client::TFDCustomLocalSQL
{
	typedef Firedac::Comp::Client::TFDCustomLocalSQL inherited;
	
private:
	bool FMultipleCursors;
	bool FDisableControls;
	bool FIncludeHiddenFields;
	bool FApplyUpdatesOnCommit;
	bool FUseTransactions;
	System::Classes::TStringList* FSchemaNames;
	System::UnicodeString __fastcall GetObjName(Firedac::Comp::Client::TFDLocalSQLDataSet* ADataSet);
	
protected:
	virtual void __fastcall InternalAttachToSQL();
	virtual void __fastcall InternalDetachFromSQL();
	virtual void __fastcall InternalDataSetAdded(Firedac::Comp::Client::TFDLocalSQLDataSet* ADataSet);
	virtual void __fastcall InternalDataSetRemoving(Firedac::Comp::Client::TFDLocalSQLDataSet* ADataSet);
	
public:
	__fastcall virtual TFDLocalSQL(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDLocalSQL();
	
__published:
	__property bool MultipleCursors = {read=FMultipleCursors, write=FMultipleCursors, default=1};
	__property bool DisableControls = {read=FDisableControls, write=FDisableControls, default=1};
	__property bool IncludeHiddenFields = {read=FIncludeHiddenFields, write=FIncludeHiddenFields, default=1};
	__property bool ApplyUpdatesOnCommit = {read=FApplyUpdatesOnCommit, write=FApplyUpdatesOnCommit, default=0};
	__property bool UseTransactions = {read=FUseTransactions, write=FUseTransactions, default=1};
	__property SchemaName = {default=0};
	__property DataSets;
	__property Connection;
	__property Active = {default=0};
	__property OnGetDataSet;
	__property OnReleaseDataSet;
	__property OnOpenDataSet;
	__property OnCloseDataSet;
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sqlitevdataset */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_SQLITEVDATASET)
using namespace Firedac::Phys::Sqlitevdataset;
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
#endif	// Firedac_Phys_SqlitevdatasetHPP
