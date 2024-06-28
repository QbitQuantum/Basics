// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.WebBroker.pas' rev: 34.00 (Windows)

#ifndef Web_WebbrokerHPP
#define Web_WebbrokerHPP

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
#include <Web.WebReq.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Webbroker
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWebApplication;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TServerExceptionEvent)(System::Sysutils::Exception* E, Web::Httpapp::TWebResponse* wr);

typedef void __fastcall (*TUnloadProc)();

class PASCALIMPLEMENTATION TWebApplication : public Web::Webreq::TWebRequestHandler
{
	typedef Web::Webreq::TWebRequestHandler inherited;
	
private:
	System::UnicodeString FTitle;
	TUnloadProc FUnloadProc;
	
public:
	__fastcall virtual TWebApplication(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWebApplication();
	virtual void __fastcall CreateForm(System::Classes::TComponentClass InstanceClass, void *Reference);
	virtual void __fastcall Initialize();
	virtual void __fastcall Run();
	__property System::UnicodeString Title = {read=FTitle, write=FTitle};
	__property TUnloadProc OnUnload = {read=FUnloadProc, write=FUnloadProc};
};


typedef void __fastcall (*THandleShutdownException)(System::Sysutils::Exception* E);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TWebApplication* Application;
extern DELPHI_PACKAGE THandleShutdownException HandleShutdownException;
}	/* namespace Webbroker */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_WEBBROKER)
using namespace Web::Webbroker;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_WebbrokerHPP
