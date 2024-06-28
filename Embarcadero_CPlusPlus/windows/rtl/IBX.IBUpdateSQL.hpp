// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBUpdateSQL.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbupdatesqlHPP
#define Ibx_IbupdatesqlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <IBX.IB.hpp>
#include <IBX.IBCustomDataSet.hpp>
#include <IBX.IBQuery.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibupdatesql
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBUpdateSQL;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIBUpdateSQL : public Ibx::Ibcustomdataset::TIBDataSetUpdateObject
{
	typedef Ibx::Ibcustomdataset::TIBDataSetUpdateObject inherited;
	
private:
	Ibx::Ibcustomdataset::TIBCustomDataSet* FDataSet;
	System::StaticArray<Ibx::Ibquery::TIBQuery*, 3> FQueries;
	System::StaticArray<System::Classes::TStrings*, 3> FSQLText;
	Ibx::Ibquery::TIBQuery* __fastcall GetQuery(Data::Db::TUpdateKind UpdateKind);
	System::Classes::TStrings* __fastcall GetSQLIndex(int Index);
	void __fastcall SetSQL(Data::Db::TUpdateKind UpdateKind, System::Classes::TStrings* Value);
	void __fastcall SetSQLIndex(int Index, System::Classes::TStrings* Value);
	
protected:
	virtual System::Classes::TStrings* __fastcall GetSQL(Data::Db::TUpdateKind UpdateKind);
	virtual Ibx::Ibcustomdataset::TIBCustomDataSet* __fastcall GetDataSet();
	virtual void __fastcall SetDataSet(Ibx::Ibcustomdataset::TIBCustomDataSet* ADataSet);
	void __fastcall SQLChanged(System::TObject* Sender);
	
public:
	__fastcall virtual TIBUpdateSQL(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBUpdateSQL();
	virtual void __fastcall Apply(Data::Db::TUpdateKind UpdateKind);
	void __fastcall ExecSQL(Data::Db::TUpdateKind UpdateKind);
	void __fastcall SetParams(Data::Db::TUpdateKind UpdateKind);
	__property DataSet;
	__property Ibx::Ibquery::TIBQuery* Query[Data::Db::TUpdateKind UpdateKind] = {read=GetQuery};
	__property System::Classes::TStrings* SQL[Data::Db::TUpdateKind UpdateKind] = {read=GetSQL, write=SetSQL};
	
__published:
	__property System::Classes::TStrings* ModifySQL = {read=GetSQLIndex, write=SetSQLIndex, index=0};
	__property System::Classes::TStrings* InsertSQL = {read=GetSQLIndex, write=SetSQLIndex, index=1};
	__property System::Classes::TStrings* DeleteSQL = {read=GetSQLIndex, write=SetSQLIndex, index=2};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibupdatesql */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBUPDATESQL)
using namespace Ibx::Ibupdatesql;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbupdatesqlHPP
