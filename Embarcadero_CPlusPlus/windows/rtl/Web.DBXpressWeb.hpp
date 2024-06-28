// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.DBXpressWeb.pas' rev: 34.00 (Windows)

#ifndef Web_DbxpresswebHPP
#define Web_DbxpresswebHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <Web.HTTPProd.hpp>
#include <Data.DB.hpp>
#include <Web.DBWeb.hpp>
#include <Data.SqlExpr.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Dbxpressweb
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSQLQueryTableProducer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSQLQueryTableProducer : public Web::Dbweb::TDSTableProducer
{
	typedef Web::Dbweb::TDSTableProducer inherited;
	
private:
	Data::Sqlexpr::TSQLQuery* FQuery;
	void __fastcall SetQuery(Data::Sqlexpr::TSQLQuery* AQuery);
	
protected:
	virtual Data::Db::TDataSet* __fastcall GetDataSet();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall SetDataSet(Data::Db::TDataSet* ADataSet);
	
public:
	virtual System::UnicodeString __fastcall Content();
	
__published:
	__property Caption = {default=0};
	__property CaptionAlignment = {default=0};
	__property Columns;
	__property Footer;
	__property Header;
	__property MaxRows = {default=20};
	__property Data::Sqlexpr::TSQLQuery* Query = {read=FQuery, write=SetQuery};
	__property RowAttributes;
	__property TableAttributes;
	__property OnCreateContent;
	__property OnFormatCell;
	__property OnGetTableCaption;
public:
	/* TDSTableProducer.Create */ inline __fastcall virtual TSQLQueryTableProducer(System::Classes::TComponent* AOwner) : Web::Dbweb::TDSTableProducer(AOwner) { }
	/* TDSTableProducer.Destroy */ inline __fastcall virtual ~TSQLQueryTableProducer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxpressweb */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_DBXPRESSWEB)
using namespace Web::Dbxpressweb;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_DbxpresswebHPP
