// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdEcho.pas' rev: 34.00 (Windows)

#ifndef IdechoHPP
#define IdechoHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdGlobal.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idecho
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdEcho;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdEcho : public Idtcpclient::TIdTCPClient
{
	typedef Idtcpclient::TIdTCPClient inherited;
	
protected:
	unsigned FEchoTime;
	virtual void __fastcall InitComponent();
	
public:
	System::UnicodeString __fastcall Echo(const System::UnicodeString AText);
	__property unsigned EchoTime = {read=FEchoTime, nodefault};
	
__published:
	__property Port = {default=7};
public:
	/* TIdTCPConnection.Destroy */ inline __fastcall virtual ~TIdEcho() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdEcho(System::Classes::TComponent* AOwner)/* overload */ : Idtcpclient::TIdTCPClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdEcho()/* overload */ : Idtcpclient::TIdTCPClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idecho */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDECHO)
using namespace Idecho;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdechoHPP
