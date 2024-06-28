// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdQOTDUDPServer.pas' rev: 34.00 (Android)

#ifndef IdqotdudpserverHPP
#define IdqotdudpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idqotdudpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdQotdUDPServer;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdQotdUDPGetEvent)(Idsockethandle::TIdSocketHandle* ABinding, System::UnicodeString &AQuote);

class PASCALIMPLEMENTATION TIdQotdUDPServer : public Idudpserver::TIdUDPServer
{
	typedef Idudpserver::TIdUDPServer inherited;
	
protected:
	TIdQotdUDPGetEvent FOnCommandQOTD;
	virtual void __fastcall DoOnCommandQUOTD(Idsockethandle::TIdSocketHandle* ABinding, System::UnicodeString &AQuote);
	virtual void __fastcall DoUDPRead(Idudpserver::TIdUDPListenerThread* AThread, const Idglobal::TIdBytes AData, Idsockethandle::TIdSocketHandle* ABinding);
	virtual void __fastcall InitComponent();
	
__published:
	__property DefaultPort = {default=17};
	__property TIdQotdUDPGetEvent OnCommandQOTD = {read=FOnCommandQOTD, write=FOnCommandQOTD};
public:
	/* TIdUDPServer.Destroy */ inline __fastcall virtual ~TIdQotdUDPServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdQotdUDPServer(System::Classes::TComponent* AOwner)/* overload */ : Idudpserver::TIdUDPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdQotdUDPServer()/* overload */ : Idudpserver::TIdUDPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idqotdudpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDQOTDUDPSERVER)
using namespace Idqotdudpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdqotdudpserverHPP
