// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdTraceRoute.pas' rev: 34.00 (iOS)

#ifndef IdtracerouteHPP
#define IdtracerouteHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdIcmpClient.hpp>
#include <IdRawBase.hpp>
#include <IdRawClient.hpp>
#include <IdThread.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idtraceroute
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdTraceRoute;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdTraceRoute : public Idicmpclient::TIdCustomIcmpClient
{
	typedef Idicmpclient::TIdCustomIcmpClient inherited;
	
protected:
	bool FResolveHostNames;
	virtual void __fastcall DoReply();
	
public:
	void __fastcall Trace();
	
__published:
	__property PacketSize = {default=32};
	__property ReceiveTimeout = {default=0};
	__property bool ResolveHostNames = {read=FResolveHostNames, write=FResolveHostNames, nodefault};
	__property OnReply;
public:
	/* TIdCustomIcmpClient.Destroy */ inline __fastcall virtual ~TIdTraceRoute() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdTraceRoute(System::Classes::TComponent* AOwner)/* overload */ : Idicmpclient::TIdCustomIcmpClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdTraceRoute()/* overload */ : Idicmpclient::TIdCustomIcmpClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idtraceroute */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTRACEROUTE)
using namespace Idtraceroute;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdtracerouteHPP
