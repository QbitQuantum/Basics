// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdUnixTimeUDP.pas' rev: 34.00 (iOS)

#ifndef IdunixtimeudpHPP
#define IdunixtimeudpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdTimeUDP.hpp>
#include <IdUDPClient.hpp>
#include <IdUDPBase.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idunixtimeudp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdUnixTimeUDP;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdUnixTimeUDP : public Idtimeudp::TIdCustomTimeUDP
{
	typedef Idtimeudp::TIdCustomTimeUDP inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdUnixTimeUDP(System::Classes::TComponent* AOwner)/* overload */;
	
__published:
	__property Port = {default=519};
public:
	/* TIdUDPClient.Destroy */ inline __fastcall virtual ~TIdUnixTimeUDP() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdUnixTimeUDP()/* overload */ : Idtimeudp::TIdCustomTimeUDP() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idunixtimeudp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDUNIXTIMEUDP)
using namespace Idunixtimeudp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdunixtimeudpHPP
