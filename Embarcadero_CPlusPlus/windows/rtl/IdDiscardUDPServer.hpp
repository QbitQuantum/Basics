// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdDiscardUDPServer.pas' rev: 34.00 (Windows)

#ifndef IddiscardudpserverHPP
#define IddiscardudpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdSocketHandle.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iddiscardudpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDiscardUDPServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdDiscardUDPServer : public Idudpserver::TIdUDPServer
{
	typedef Idudpserver::TIdUDPServer inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
__published:
	__property DefaultPort = {default=9};
public:
	/* TIdUDPServer.Destroy */ inline __fastcall virtual ~TIdDiscardUDPServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdDiscardUDPServer(System::Classes::TComponent* AOwner)/* overload */ : Idudpserver::TIdUDPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDiscardUDPServer()/* overload */ : Idudpserver::TIdUDPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Iddiscardudpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDDISCARDUDPSERVER)
using namespace Iddiscardudpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IddiscardudpserverHPP
