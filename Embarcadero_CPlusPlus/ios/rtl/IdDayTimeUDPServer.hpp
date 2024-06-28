// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdDayTimeUDPServer.pas' rev: 34.00 (iOS)

#ifndef IddaytimeudpserverHPP
#define IddaytimeudpserverHPP

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

namespace Iddaytimeudpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDayTimeUDPServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdDayTimeUDPServer : public Idudpserver::TIdUDPServer
{
	typedef Idudpserver::TIdUDPServer inherited;
	
protected:
	System::UnicodeString FTimeZone;
	virtual void __fastcall DoUDPRead(Idudpserver::TIdUDPListenerThread* AThread, const Idglobal::TIdBytes AData, Idsockethandle::TIdSocketHandle* ABinding);
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdDayTimeUDPServer(System::Classes::TComponent* AOwner)/* overload */;
	
__published:
	__property System::UnicodeString TimeZone = {read=FTimeZone, write=FTimeZone};
	__property DefaultPort = {default=13};
public:
	/* TIdUDPServer.Destroy */ inline __fastcall virtual ~TIdDayTimeUDPServer() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDayTimeUDPServer()/* overload */ : Idudpserver::TIdUDPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Iddaytimeudpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDDAYTIMEUDPSERVER)
using namespace Iddaytimeudpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IddaytimeudpserverHPP
