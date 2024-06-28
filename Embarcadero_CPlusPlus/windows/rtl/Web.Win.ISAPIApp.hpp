// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.Win.ISAPIApp.pas' rev: 34.00 (Windows)

#ifndef Web_Win_IsapiappHPP
#define Web_Win_IsapiappHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.SyncObjs.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <Web.WebBroker.hpp>
#include <Web.Win.IsapiHTTP.hpp>
#include <Winapi.Isapi2.hpp>
#include <Web.WebReq.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Win
{
namespace Isapiapp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TISAPIApplication;
class DELPHICLASS TISAPIFactory;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (*TISAPITerminateProc)();

typedef void __fastcall (*TISAPIServerExceptionProc)(System::TObject* E, Winapi::Isapi2::TEXTENSION_CONTROL_BLOCK &ECB);

class PASCALIMPLEMENTATION TISAPIApplication : public Web::Webbroker::TWebApplication
{
	typedef Web::Webbroker::TWebApplication inherited;
	
private:
	TISAPIFactory* FFactory;
	TISAPITerminateProc FTerminateProc;
	TISAPIServerExceptionProc FServerExceptionProc;
	Web::Win::Isapihttp::TISAPIRequest* __fastcall NewRequest(Winapi::Isapi2::TEXTENSION_CONTROL_BLOCK &AECB);
	Web::Win::Isapihttp::TISAPIResponse* __fastcall NewResponse(Web::Win::Isapihttp::TISAPIRequest* ISAPIRequest);
	void __fastcall ISAPIHandleException(System::TObject* Sender);
	
public:
	System::LongBool __fastcall GetExtensionVersion(Winapi::Isapi2::HSE_VERSION_INFO &Ver);
	unsigned __fastcall HttpExtensionProc(Winapi::Isapi2::TEXTENSION_CONTROL_BLOCK &ECB);
	System::LongBool __fastcall TerminateExtension(unsigned dwFlags);
	__fastcall virtual TISAPIApplication(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TISAPIApplication();
	__property TISAPITerminateProc OnTerminate = {read=FTerminateProc, write=FTerminateProc};
	__property TISAPIServerExceptionProc OnServerException = {read=FServerExceptionProc, write=FServerExceptionProc};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TISAPIFactory : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual Web::Win::Isapihttp::TISAPIRequest* __fastcall NewRequest(Winapi::Isapi2::TEXTENSION_CONTROL_BLOCK &AECB);
	virtual Web::Win::Isapihttp::TISAPIResponse* __fastcall NewResponse(Web::Win::Isapihttp::TISAPIRequest* ISAPIRequest);
	
public:
	__fastcall TISAPIFactory();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISAPIFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall (__closure *DispatchThread)(Winapi::Isapi2::PEXTENSION_CONTROL_BLOCK AECB);
extern DELPHI_PACKAGE System::LongBool __stdcall GetExtensionVersion(Winapi::Isapi2::HSE_VERSION_INFO &Ver);
extern DELPHI_PACKAGE unsigned __stdcall HttpExtensionProc(Winapi::Isapi2::TEXTENSION_CONTROL_BLOCK &ECB);
extern DELPHI_PACKAGE System::LongBool __stdcall TerminateExtension(unsigned dwFlags);
}	/* namespace Isapiapp */
}	/* namespace Win */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_WIN_ISAPIAPP)
using namespace Web::Win::Isapiapp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_WIN)
using namespace Web::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_Win_IsapiappHPP
