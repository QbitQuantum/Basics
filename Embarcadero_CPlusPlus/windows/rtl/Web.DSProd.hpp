// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.DSProd.pas' rev: 34.00 (Windows)

#ifndef Web_DsprodHPP
#define Web_DsprodHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <Web.HTTPProd.hpp>
#include <Data.DB.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Dsprod
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomDataSetPageProducer;
class DELPHICLASS TDataSetPageProducer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomDataSetPageProducer : public Web::Httpprod::TCustomPageProducer
{
	typedef Web::Httpprod::TCustomPageProducer inherited;
	
private:
	Data::Db::TDataSet* FDataSet;
	
protected:
	virtual Data::Db::TDataSet* __fastcall GetDataSet();
	virtual void __fastcall SetDataSet(Data::Db::TDataSet* ADataSet);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	DYNAMIC void __fastcall DoTagEvent(Web::Httpprod::TTag Tag, const System::UnicodeString TagString, System::Classes::TStrings* TagParams, System::UnicodeString &ReplaceText);
	
public:
	virtual System::UnicodeString __fastcall Content();
	__property Data::Db::TDataSet* DataSet = {read=GetDataSet, write=SetDataSet};
public:
	/* TCustomPageProducer.Create */ inline __fastcall virtual TCustomDataSetPageProducer(System::Classes::TComponent* AOwner) : Web::Httpprod::TCustomPageProducer(AOwner) { }
	/* TCustomPageProducer.Destroy */ inline __fastcall virtual ~TCustomDataSetPageProducer() { }
	
};


class PASCALIMPLEMENTATION TDataSetPageProducer : public TCustomDataSetPageProducer
{
	typedef TCustomDataSetPageProducer inherited;
	
__published:
	__property HTMLDoc;
	__property HTMLFile = {default=0};
	__property DataSet;
	__property OnHTMLTag;
public:
	/* TCustomPageProducer.Create */ inline __fastcall virtual TDataSetPageProducer(System::Classes::TComponent* AOwner) : TCustomDataSetPageProducer(AOwner) { }
	/* TCustomPageProducer.Destroy */ inline __fastcall virtual ~TDataSetPageProducer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsprod */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_DSPROD)
using namespace Web::Dsprod;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_DsprodHPP
