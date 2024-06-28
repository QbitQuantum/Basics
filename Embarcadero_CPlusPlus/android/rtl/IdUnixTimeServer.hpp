// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdUnixTimeServer.pas' rev: 34.00 (Android)

#ifndef IdunixtimeserverHPP
#define IdunixtimeserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdGlobalProtocols.hpp>
#include <IdTimeServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idunixtimeserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdUnixTimeServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdUnixTimeServer : public Idtimeserver::TIdCustomTimeServer
{
	typedef Idtimeserver::TIdCustomTimeServer inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdUnixTimeServer(System::Classes::TComponent* AOwner)/* overload */;
	
__published:
	__property DefaultPort = {default=519};
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdUnixTimeServer() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdUnixTimeServer()/* overload */ : Idtimeserver::TIdCustomTimeServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idunixtimeserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDUNIXTIMESERVER)
using namespace Idunixtimeserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdunixtimeserverHPP
