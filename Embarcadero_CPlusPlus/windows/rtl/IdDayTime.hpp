// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdDayTime.pas' rev: 34.00 (Windows)

#ifndef IddaytimeHPP
#define IddaytimeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iddaytime
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDayTime;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdDayTime : public Idtcpclient::TIdTCPClientCustom
{
	typedef Idtcpclient::TIdTCPClientCustom inherited;
	
protected:
	System::UnicodeString __fastcall GetDayTimeStr();
	virtual void __fastcall InitComponent();
	
public:
	__property System::UnicodeString DayTimeStr = {read=GetDayTimeStr};
	
__published:
	__property Port = {default=13};
	__property Host = {default=0};
public:
	/* TIdTCPConnection.Destroy */ inline __fastcall virtual ~TIdDayTime() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdDayTime(System::Classes::TComponent* AOwner)/* overload */ : Idtcpclient::TIdTCPClientCustom(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDayTime()/* overload */ : Idtcpclient::TIdTCPClientCustom() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Iddaytime */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDDAYTIME)
using namespace Iddaytime;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IddaytimeHPP
