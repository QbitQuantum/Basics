// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdWhoIsServer.pas' rev: 34.00 (iOS)

#ifndef IdwhoisserverHPP
#define IdwhoisserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idwhoisserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdWhoIsServer;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TGetEvent)(Idcontext::TIdContext* AContext, System::UnicodeString ALookup, System::UnicodeString &VResponse);

class PASCALIMPLEMENTATION TIdWhoIsServer : public Idcustomtcpserver::TIdCustomTCPServer
{
	typedef Idcustomtcpserver::TIdCustomTCPServer inherited;
	
protected:
	TGetEvent FOnCommandLookup;
	virtual bool __fastcall DoExecute(Idcontext::TIdContext* AContext);
	virtual void __fastcall InitComponent();
	
__published:
	__property TGetEvent OnCommandLookup = {read=FOnCommandLookup, write=FOnCommandLookup};
	__property DefaultPort = {default=43};
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdWhoIsServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdWhoIsServer(System::Classes::TComponent* AOwner)/* overload */ : Idcustomtcpserver::TIdCustomTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdWhoIsServer()/* overload */ : Idcustomtcpserver::TIdCustomTCPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idwhoisserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDWHOISSERVER)
using namespace Idwhoisserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdwhoisserverHPP
