// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdDayTimeUDP.pas' rev: 34.00 (Windows)

#ifndef IddaytimeudpHPP
#define IddaytimeudpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iddaytimeudp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDayTimeUDP;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdDayTimeUDP : public Idudpclient::TIdUDPClient
{
	typedef Idudpclient::TIdUDPClient inherited;
	
protected:
	System::UnicodeString __fastcall GetDayTimeStr();
	virtual void __fastcall InitComponent();
	
public:
	__property System::UnicodeString DayTimeStr = {read=GetDayTimeStr};
	
__published:
	__property Port = {default=13};
public:
	/* TIdUDPClient.Destroy */ inline __fastcall virtual ~TIdDayTimeUDP() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdDayTimeUDP(System::Classes::TComponent* AOwner)/* overload */ : Idudpclient::TIdUDPClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDayTimeUDP()/* overload */ : Idudpclient::TIdUDPClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Iddaytimeudp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDDAYTIMEUDP)
using namespace Iddaytimeudp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IddaytimeudpHPP
