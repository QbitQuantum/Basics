// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSystatUDP.pas' rev: 34.00 (Android)

#ifndef IdsystatudpHPP
#define IdsystatudpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsystatudp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSystatUDP;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSystatUDP : public Idudpclient::TIdUDPClient
{
	typedef Idudpclient::TIdUDPClient inherited;
	
protected:
	virtual void __fastcall InitComponent();
	
public:
	void __fastcall GetStat(System::Classes::TStrings* ADest);
	
__published:
	__property ReceiveTimeout = {default=1000};
	__property Port = {default=11};
public:
	/* TIdUDPClient.Destroy */ inline __fastcall virtual ~TIdSystatUDP() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSystatUDP(System::Classes::TComponent* AOwner)/* overload */ : Idudpclient::TIdUDPClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSystatUDP()/* overload */ : Idudpclient::TIdUDPClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word DefIdSysUDPTimeout = System::Word(0x3e8);
}	/* namespace Idsystatudp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSYSTATUDP)
using namespace Idsystatudp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsystatudpHPP
