// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdRemoteCMDServer.pas' rev: 34.00 (Windows)

#ifndef IdremotecmdserverHPP
#define IdremotecmdserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdContext.hpp>
#include <IdTCPClient.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idremotecmdserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdRemoteCMDServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdRemoteCMDServer : public Idcustomtcpserver::TIdCustomTCPServer
{
	typedef Idcustomtcpserver::TIdCustomTCPServer inherited;
	
protected:
	bool FForcePortsInRange;
	bool FStdErrorPortsInRange;
	virtual bool __fastcall DoExecute(Idcontext::TIdContext* AThread);
	virtual void __fastcall DoCMD(Idcontext::TIdContext* AThread, Idtcpclient::TIdTCPClient* AStdError, System::UnicodeString AParam1, System::UnicodeString AParam2, System::UnicodeString ACommand) = 0 ;
	
public:
	void __fastcall SendError(Idcontext::TIdContext* AThread, Idtcpclient::TIdTCPClient* AStdErr, System::UnicodeString AMsg);
	void __fastcall SendResults(Idcontext::TIdContext* AThread, Idtcpclient::TIdTCPClient* AStdErr, System::UnicodeString AMsg);
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdRemoteCMDServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdRemoteCMDServer(System::Classes::TComponent* AOwner)/* overload */ : Idcustomtcpserver::TIdCustomTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdRemoteCMDServer()/* overload */ : Idcustomtcpserver::TIdCustomTCPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idremotecmdserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDREMOTECMDSERVER)
using namespace Idremotecmdserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdremotecmdserverHPP
