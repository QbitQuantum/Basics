// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdQotdServer.pas' rev: 34.00 (Windows)

#ifndef IdqotdserverHPP
#define IdqotdserverHPP

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

namespace Idqotdserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdQOTDServer;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdQOTDGetEvent)(Idcontext::TIdContext* AContext, System::UnicodeString &AQuote);

class PASCALIMPLEMENTATION TIdQOTDServer : public Idcustomtcpserver::TIdCustomTCPServer
{
	typedef Idcustomtcpserver::TIdCustomTCPServer inherited;
	
protected:
	TIdQOTDGetEvent FOnCommandQOTD;
	virtual bool __fastcall DoExecute(Idcontext::TIdContext* AContext);
	virtual void __fastcall InitComponent();
	
__published:
	__property TIdQOTDGetEvent OnCommandQOTD = {read=FOnCommandQOTD, write=FOnCommandQOTD};
	__property DefaultPort = {default=17};
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdQOTDServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdQOTDServer(System::Classes::TComponent* AOwner)/* overload */ : Idcustomtcpserver::TIdCustomTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdQOTDServer()/* overload */ : Idcustomtcpserver::TIdCustomTCPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idqotdserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDQOTDSERVER)
using namespace Idqotdserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdqotdserverHPP
