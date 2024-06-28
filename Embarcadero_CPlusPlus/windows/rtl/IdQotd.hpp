// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdQotd.pas' rev: 34.00 (Windows)

#ifndef IdqotdHPP
#define IdqotdHPP

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

namespace Idqotd
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdQOTD;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdQOTD : public Idtcpclient::TIdTCPClientCustom
{
	typedef Idtcpclient::TIdTCPClientCustom inherited;
	
protected:
	System::UnicodeString __fastcall GetQuote();
	virtual void __fastcall InitComponent();
	
public:
	__property System::UnicodeString Quote = {read=GetQuote};
	
__published:
	__property Port = {default=17};
	__property Host = {default=0};
public:
	/* TIdTCPConnection.Destroy */ inline __fastcall virtual ~TIdQOTD() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdQOTD(System::Classes::TComponent* AOwner)/* overload */ : Idtcpclient::TIdTCPClientCustom(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdQOTD()/* overload */ : Idtcpclient::TIdTCPClientCustom() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idqotd */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDQOTD)
using namespace Idqotd;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdqotdHPP
