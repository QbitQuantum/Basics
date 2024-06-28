// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdEchoUDP.pas' rev: 34.00 (iOS)

#ifndef IdechoudpHPP
#define IdechoudpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdGlobal.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idechoudp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdEchoUDP;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdEchoUDP : public Idudpclient::TIdUDPClient
{
	typedef Idudpclient::TIdUDPClient inherited;
	
protected:
	unsigned FEchoTime;
	virtual void __fastcall InitComponent();
	
public:
	System::UnicodeString __fastcall Echo(System::UnicodeString AText);
	__property unsigned EchoTime = {read=FEchoTime, nodefault};
	
__published:
	__property Port = {default=7};
public:
	/* TIdUDPClient.Destroy */ inline __fastcall virtual ~TIdEchoUDP() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdEchoUDP(System::Classes::TComponent* AOwner)/* overload */ : Idudpclient::TIdUDPClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdEchoUDP()/* overload */ : Idudpclient::TIdUDPClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idechoudp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDECHOUDP)
using namespace Idechoudp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdechoudpHPP
