// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdTimeUDP.pas' rev: 34.00 (Android)

#ifndef IdtimeudpHPP
#define IdtimeudpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdUDPBase.hpp>
#include <IdGlobalProtocols.hpp>
#include <IdUDPClient.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idtimeudp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdCustomTimeUDP;
class DELPHICLASS TIdTimeUDP;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdCustomTimeUDP : public Idudpclient::TIdUDPClient
{
	typedef Idudpclient::TIdUDPClient inherited;
	
protected:
	System::TDateTime FBaseDate;
	unsigned FRoundTripDelay;
	unsigned __fastcall GetDateTimeCard();
	System::TDateTime __fastcall GetDateTime();
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdCustomTimeUDP(System::Classes::TComponent* AOwner)/* overload */;
	bool __fastcall SyncTime();
	__property unsigned DateTimeCard = {read=GetDateTimeCard, nodefault};
	__property System::TDateTime DateTime = {read=GetDateTime};
	__property unsigned RoundTripDelay = {read=FRoundTripDelay, nodefault};
public:
	/* TIdUDPClient.Destroy */ inline __fastcall virtual ~TIdCustomTimeUDP() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdCustomTimeUDP()/* overload */ : Idudpclient::TIdUDPClient() { }
	
};


class PASCALIMPLEMENTATION TIdTimeUDP : public TIdCustomTimeUDP
{
	typedef TIdCustomTimeUDP inherited;
	
__published:
	__property System::TDateTime BaseDate = {read=FBaseDate, write=FBaseDate};
	__property Port = {default=37};
public:
	/* TIdCustomTimeUDP.Create */ inline __fastcall TIdTimeUDP(System::Classes::TComponent* AOwner)/* overload */ : TIdCustomTimeUDP(AOwner) { }
	
public:
	/* TIdUDPClient.Destroy */ inline __fastcall virtual ~TIdTimeUDP() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdTimeUDP()/* overload */ : TIdCustomTimeUDP() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idtimeudp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTIMEUDP)
using namespace Idtimeudp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdtimeudpHPP
