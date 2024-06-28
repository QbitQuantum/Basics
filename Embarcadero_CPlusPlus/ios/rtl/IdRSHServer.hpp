// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdRSHServer.pas' rev: 34.00 (iOS)

#ifndef IdrshserverHPP
#define IdrshserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdContext.hpp>
#include <IdRemoteCMDServer.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPServer.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idrshserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdRSHServer;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdRSHCommandEvent)(Idcontext::TIdContext* AThread, Idtcpclient::TIdTCPClient* AStdError, System::UnicodeString AClientUserName, System::UnicodeString AHostUserName, System::UnicodeString ACommand);

class PASCALIMPLEMENTATION TIdRSHServer : public Idremotecmdserver::TIdRemoteCMDServer
{
	typedef Idremotecmdserver::TIdRemoteCMDServer inherited;
	
protected:
	TIdRSHCommandEvent FOnCommand;
	virtual void __fastcall DoCMD(Idcontext::TIdContext* AThread, Idtcpclient::TIdTCPClient* AStdError, System::UnicodeString AParam1, System::UnicodeString AParam2, System::UnicodeString ACommand);
	virtual void __fastcall InitComponent();
	
__published:
	__property TIdRSHCommandEvent OnCommand = {read=FOnCommand, write=FOnCommand};
	__property DefaultPort = {default=514};
	__property bool ForcePortsInRange = {read=FForcePortsInRange, write=FForcePortsInRange, default=1};
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdRSHServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdRSHServer(System::Classes::TComponent* AOwner)/* overload */ : Idremotecmdserver::TIdRemoteCMDServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdRSHServer()/* overload */ : Idremotecmdserver::TIdRemoteCMDServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr bool RSH_FORCEPORTSINRANGE = true;
}	/* namespace Idrshserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDRSHSERVER)
using namespace Idrshserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdrshserverHPP
