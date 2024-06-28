// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdRawClient.pas' rev: 34.00 (Windows)

#ifndef IdrawclientHPP
#define IdrawclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdGlobal.hpp>
#include <IdRawBase.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idrawclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdRawClient;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdRawClient : public Idrawbase::TIdRawBase
{
	typedef Idrawbase::TIdRawBase inherited;
	
__published:
	__property ReceiveTimeout = {default=0};
	__property Host = {default=0};
	__property Port = {default=0};
	__property Protocol = {default=255};
	__property ProtocolIPv6;
	__property IPVersion = {default=0};
public:
	/* TIdRawBase.Destroy */ inline __fastcall virtual ~TIdRawClient() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdRawClient(System::Classes::TComponent* AOwner)/* overload */ : Idrawbase::TIdRawBase(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdRawClient()/* overload */ : Idrawbase::TIdRawBase() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idrawclient */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDRAWCLIENT)
using namespace Idrawclient;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdrawclientHPP
