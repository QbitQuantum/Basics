// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.CGIApp.pas' rev: 34.00 (Windows)

#ifndef Web_CgiappHPP
#define Web_CgiappHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Web.WebBroker.hpp>
#include <Web.CGIHTTP.hpp>
#include <Web.WebReq.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Cgiapp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCGIApplication;
class DELPHICLASS TCGIFactory;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCGIApplication : public Web::Webbroker::TWebApplication
{
	typedef Web::Webbroker::TWebApplication inherited;
	
private:
	System::UnicodeString FOutputFileName;
	TCGIFactory* FFactory;
	Web::Cgihttp::TCGIRequest* __fastcall NewRequest();
	Web::Cgihttp::TCGIResponse* __fastcall NewResponse(Web::Cgihttp::TCGIRequest* CGIRequest);
	void __fastcall SetFactory(TCGIFactory* Value);
	TCGIFactory* __fastcall GetFactory();
	void __fastcall CGIHandleException(System::TObject* Sender);
	
public:
	__fastcall virtual ~TCGIApplication();
	virtual void __fastcall Run();
public:
	/* TWebApplication.Create */ inline __fastcall virtual TCGIApplication(System::Classes::TComponent* AOwner) : Web::Webbroker::TWebApplication(AOwner) { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCGIFactory : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TCGIApplication* FApplication;
	System::UnicodeString __fastcall GetOutputFileName();
	void __fastcall SetOutputFileName(const System::UnicodeString Value);
	
protected:
	virtual Web::Cgihttp::TCGIRequest* __fastcall NewRequest();
	virtual Web::Cgihttp::TCGIResponse* __fastcall NewResponse(Web::Cgihttp::TCGIRequest* CGIRequest);
	__property System::UnicodeString OutputFileName = {read=GetOutputFileName, write=SetOutputFileName};
	
public:
	__fastcall TCGIFactory();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TCGIFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Cgiapp */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_CGIAPP)
using namespace Web::Cgiapp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_CgiappHPP
