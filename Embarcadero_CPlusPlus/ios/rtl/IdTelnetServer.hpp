// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdTelnetServer.pas' rev: 34.00 (iOS)

#ifndef IdtelnetserverHPP
#define IdtelnetserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdBaseComponent.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPConnection.hpp>
#include <IdYarn.hpp>
#include <IdTask.hpp>
#include <IdThreadSafe.hpp>
#include <IdComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idtelnetserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTelnetData;
class DELPHICLASS TIdTelnetServerContext;
class DELPHICLASS TIdTelnetServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTelnetData : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString Username;
	System::UnicodeString Password;
	unsigned HUserToken;
public:
	/* TObject.Create */ inline __fastcall TTelnetData() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTelnetData() { }
	
};


class PASCALIMPLEMENTATION TIdTelnetServerContext : public Idcustomtcpserver::TIdServerContext
{
	typedef Idcustomtcpserver::TIdServerContext inherited;
	
private:
	TTelnetData* FTelnetData;
	
public:
	__fastcall virtual TIdTelnetServerContext(Idtcpconnection::TIdTCPConnection* AConnection, Idyarn::TIdYarn* AYarn, Idthreadsafe::TIdThreadSafeObjectList* AList);
	__fastcall virtual ~TIdTelnetServerContext();
	__property TTelnetData* TelnetData = {read=FTelnetData};
};


typedef void __fastcall (__closure *TIdTelnetNegotiateEvent)(Idcontext::TIdContext* AContext);

typedef void __fastcall (__closure *TAuthenticationEvent)(Idcontext::TIdContext* AContext, const System::UnicodeString AUsername, const System::UnicodeString APassword, bool &AAuthenticated);

class PASCALIMPLEMENTATION TIdTelnetServer : public Idcustomtcpserver::TIdCustomTCPServer
{
	typedef Idcustomtcpserver::TIdCustomTCPServer inherited;
	
protected:
	int FLoginAttempts;
	TAuthenticationEvent FOnAuthentication;
	System::UnicodeString FLoginMessage;
	TIdTelnetNegotiateEvent FOnNegotiate;
	virtual void __fastcall DoConnect(Idcontext::TIdContext* AContext);
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdTelnetServer(System::Classes::TComponent* AOwner)/* overload */;
	virtual bool __fastcall DoAuthenticate(Idcontext::TIdContext* AContext, const System::UnicodeString AUsername, const System::UnicodeString APassword);
	virtual void __fastcall DoNegotiate(Idcontext::TIdContext* AContext);
	
__published:
	__property DefaultPort = {default=23};
	__property int LoginAttempts = {read=FLoginAttempts, write=FLoginAttempts, default=3};
	__property System::UnicodeString LoginMessage = {read=FLoginMessage, write=FLoginMessage};
	__property TAuthenticationEvent OnAuthentication = {read=FOnAuthentication, write=FOnAuthentication};
	__property TIdTelnetNegotiateEvent OnNegotiate = {read=FOnNegotiate, write=FOnNegotiate};
	__property OnExecute;
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdTelnetServer() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdTelnetServer()/* overload */ : Idcustomtcpserver::TIdCustomTCPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 GLoginAttempts = System::Int8(0x3);
}	/* namespace Idtelnetserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTELNETSERVER)
using namespace Idtelnetserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdtelnetserverHPP
