// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHTTPServer.pas' rev: 34.00 (iOS)

#ifndef IdhttpserverHPP
#define IdhttpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdCustomHTTPServer.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idhttpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHTTPServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdHTTPServer : public Idcustomhttpserver::TIdCustomHTTPServer
{
	typedef Idcustomhttpserver::TIdCustomHTTPServer inherited;
	
__published:
	__property OnCreatePostStream;
	__property OnDoneWithPostStream;
	__property OnCommandGet;
public:
	/* TIdCustomHTTPServer.Create */ inline __fastcall TIdHTTPServer(System::Classes::TComponent* AOwner)/* overload */ : Idcustomhttpserver::TIdCustomHTTPServer(AOwner) { }
	/* TIdCustomHTTPServer.Destroy */ inline __fastcall virtual ~TIdHTTPServer() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdHTTPServer()/* overload */ : Idcustomhttpserver::TIdCustomHTTPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idhttpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHTTPSERVER)
using namespace Idhttpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdhttpserverHPP
