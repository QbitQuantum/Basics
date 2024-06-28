// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.ApacheApp.pas' rev: 34.00 (Windows)

#ifndef Web_ApacheappHPP
#define Web_ApacheappHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Web.ApacheHTTP.hpp>
#include <Web.HTTPDMethods.hpp>
#include <Web.HTTPApp.hpp>
#include <Web.WebBroker.hpp>
#include <Web.WebReq.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Apacheapp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TApacheApplication;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (*TApacheTerminateProc)();

class PASCALIMPLEMENTATION TApacheApplication : public Web::Webbroker::TWebApplication
{
	typedef Web::Webbroker::TWebApplication inherited;
	
private:
	TApacheTerminateProc FTerminateProc;
	void __fastcall ApacheHandleException(System::TObject* Sender);
	
protected:
	Web::Apachehttp::TApacheRequest* __fastcall NewRequest(const Web::Httpdmethods::PHTTPDRequest r);
	Web::Apachehttp::TApacheResponse* __fastcall NewResponse(Web::Apachehttp::TApacheRequest* ApacheRequest);
	
public:
	__fastcall virtual TApacheApplication(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TApacheApplication();
	int __fastcall ProcessRequest(const Web::Httpdmethods::PHTTPDRequest r);
	int __fastcall TerminateExtension();
	__property TApacheTerminateProc OnTerminate = {read=FTerminateProc, write=FTerminateProc};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall InitApplication(const void * AModuleData, const System::UTF8String AHandlerName = System::UTF8String());
}	/* namespace Apacheapp */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_APACHEAPP)
using namespace Web::Apacheapp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_ApacheappHPP
