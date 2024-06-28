// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.WebReq.pas' rev: 34.00 (Windows)

#ifndef Web_WebreqHPP
#define Web_WebreqHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SyncObjs.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Webreq
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWebRequestHandler;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TRequestNotification : unsigned char { rnActivateModule, rnDeactivateModule, rnCreateModule, rnFreeModule, rnStartRequest, rnFinishRequest };

class PASCALIMPLEMENTATION TWebRequestHandler : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Syncobjs::TCriticalSection* FCriticalSection;
	System::Generics::Collections::TObjectList__1<System::Classes::TComponent*>* FActiveWebModules;
	int FAddingActiveModules;
	System::Generics::Collections::TObjectList__1<System::Classes::TComponent*>* FInactiveWebModules;
	int FMaxConnections;
	bool FCacheConnections;
	System::Classes::TComponentClass FWebModuleClass;
	int __fastcall GetActiveCount();
	int __fastcall GetInactiveCount();
	void __fastcall SetCacheConnections(bool Value);
	
protected:
	System::Classes::TComponent* __fastcall ActivateWebModules();
	void __fastcall DeactivateWebModules(System::Classes::TComponent* WebModules);
	bool __fastcall HandleRequest(Web::Httpapp::TWebRequest* Request, Web::Httpapp::TWebResponse* Response);
	
public:
	__fastcall virtual TWebRequestHandler(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWebRequestHandler();
	virtual void __fastcall FreeModules();
	void __fastcall HandleException(System::TObject* Sender);
	__property System::Classes::TComponentClass WebModuleClass = {read=FWebModuleClass, write=FWebModuleClass};
	__property int ActiveCount = {read=GetActiveCount, nodefault};
	__property bool CacheConnections = {read=FCacheConnections, write=SetCacheConnections, nodefault};
	__property int InactiveCount = {read=GetInactiveCount, nodefault};
	__property int MaxConnections = {read=FMaxConnections, write=FMaxConnections, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TWebRequestHandler* __fastcall (*WebRequestHandlerProc)(void);
extern DELPHI_PACKAGE void __fastcall FreeWebModules(void);
extern DELPHI_PACKAGE TWebRequestHandler* __fastcall WebRequestHandler(void);
}	/* namespace Webreq */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_WEBREQ)
using namespace Web::Webreq;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_WebreqHPP
