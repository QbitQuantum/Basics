// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdTimeUDPServer.pas' rev: 34.00 (Windows)

#ifndef IdtimeudpserverHPP
#define IdtimeudpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idtimeudpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdCustomTimeUDPServer;
class DELPHICLASS TIdTimeUDPServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdCustomTimeUDPServer : public Idudpserver::TIdUDPServer
{
	typedef Idudpserver::TIdUDPServer inherited;
	
protected:
	System::TDateTime FBaseDate;
	virtual void __fastcall DoUDPRead(Idudpserver::TIdUDPListenerThread* AThread, const Idglobal::TIdBytes AData, Idsockethandle::TIdSocketHandle* ABinding);
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdCustomTimeUDPServer(System::Classes::TComponent* AOwner)/* overload */;
public:
	/* TIdUDPServer.Destroy */ inline __fastcall virtual ~TIdCustomTimeUDPServer() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdCustomTimeUDPServer()/* overload */ : Idudpserver::TIdUDPServer() { }
	
};


class PASCALIMPLEMENTATION TIdTimeUDPServer : public TIdCustomTimeUDPServer
{
	typedef TIdCustomTimeUDPServer inherited;
	
__published:
	__property DefaultPort = {default=37};
	__property System::TDateTime BaseDate = {read=FBaseDate, write=FBaseDate};
public:
	/* TIdCustomTimeUDPServer.Create */ inline __fastcall TIdTimeUDPServer(System::Classes::TComponent* AOwner)/* overload */ : TIdCustomTimeUDPServer(AOwner) { }
	
public:
	/* TIdUDPServer.Destroy */ inline __fastcall virtual ~TIdTimeUDPServer() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdTimeUDPServer()/* overload */ : TIdCustomTimeUDPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idtimeudpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTIMEUDPSERVER)
using namespace Idtimeudpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdtimeudpserverHPP
