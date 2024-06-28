// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdUnixTimeUDPServer.pas' rev: 34.00 (Windows)

#ifndef IdunixtimeudpserverHPP
#define IdunixtimeudpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdUDPServer.hpp>
#include <IdTimeUDPServer.hpp>
#include <IdUDPBase.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idunixtimeudpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdUnixTimeUDPServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdUnixTimeUDPServer : public Idtimeudpserver::TIdCustomTimeUDPServer
{
	typedef Idtimeudpserver::TIdCustomTimeUDPServer inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdUnixTimeUDPServer(System::Classes::TComponent* AOwner)/* overload */;
	
__published:
	__property DefaultPort = {default=519};
public:
	/* TIdUDPServer.Destroy */ inline __fastcall virtual ~TIdUnixTimeUDPServer() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdUnixTimeUDPServer()/* overload */ : Idtimeudpserver::TIdCustomTimeUDPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idunixtimeudpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDUNIXTIMEUDPSERVER)
using namespace Idunixtimeudpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdunixtimeudpserverHPP
