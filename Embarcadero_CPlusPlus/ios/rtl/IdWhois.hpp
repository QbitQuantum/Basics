// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdWhois.pas' rev: 34.00 (iOS)

#ifndef IdwhoisHPP
#define IdwhoisHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idwhois
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdWhois;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdWhois : public Idtcpclient::TIdTCPClientCustom
{
	typedef Idtcpclient::TIdTCPClientCustom inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdWhois(System::Classes::TComponent* AOwner)/* overload */;
	System::UnicodeString __fastcall WhoIs(const System::UnicodeString ADomain);
	
__published:
	__property Port = {default=43};
	__property Host = {default=0};
public:
	/* TIdTCPConnection.Destroy */ inline __fastcall virtual ~TIdWhois() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdWhois()/* overload */ : Idtcpclient::TIdTCPClientCustom() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idwhois */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDWHOIS)
using namespace Idwhois;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdwhoisHPP
