// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdMappedPortTCP.pas' rev: 34.00 (Windows)

#ifndef IdmappedporttcpHPP
#define IdmappedporttcpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdGlobal.hpp>
#include <IdStack.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>
#include <IdYarn.hpp>
#include <System.SysUtils.hpp>
#include <IdTask.hpp>
#include <IdThreadSafe.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idmappedporttcp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMappedPortContext;
class DELPHICLASS TIdMappedPortTCP;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdMappedPortContext : public Idcustomtcpserver::TIdServerContext
{
	typedef Idcustomtcpserver::TIdServerContext inherited;
	
protected:
	Idtcpconnection::TIdTCPConnection* FOutboundClient;
	Idstack::TIdSocketList* FReadList;
	Idstack::TIdSocketList* FDataAvailList;
	int FConnectTimeOut;
	Idglobal::TIdBytes FNetData;
	TIdMappedPortTCP* FServer;
	virtual void __fastcall CheckForData(bool DoRead);
	virtual void __fastcall HandleLocalClientData();
	virtual void __fastcall HandleOutboundClientData();
	virtual void __fastcall OutboundConnect();
	
public:
	__fastcall virtual TIdMappedPortContext(Idtcpconnection::TIdTCPConnection* AConnection, Idyarn::TIdYarn* AYarn, Idthreadsafe::TIdThreadSafeObjectList* AList);
	__fastcall virtual ~TIdMappedPortContext();
	__property TIdMappedPortTCP* Server = {read=FServer, write=FServer};
	__property int ConnectTimeOut = {read=FConnectTimeOut, write=FConnectTimeOut, default=-1};
	__property Idglobal::TIdBytes NetData = {read=FNetData, write=FNetData};
	__property Idtcpconnection::TIdTCPConnection* OutboundClient = {read=FOutboundClient, write=FOutboundClient};
};


class PASCALIMPLEMENTATION TIdMappedPortTCP : public Idcustomtcpserver::TIdCustomTCPServer
{
	typedef Idcustomtcpserver::TIdCustomTCPServer inherited;
	
protected:
	System::UnicodeString FMappedHost;
	System::Word FMappedPort;
	Idcustomtcpserver::TIdServerThreadEvent FOnBeforeConnect;
	Idcustomtcpserver::TIdServerThreadEvent FOnOutboundConnect;
	Idcustomtcpserver::TIdServerThreadEvent FOnOutboundData;
	Idcustomtcpserver::TIdServerThreadEvent FOnOutboundDisConnect;
	virtual void __fastcall ContextCreated(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoBeforeConnect(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoConnect(Idcontext::TIdContext* AContext);
	virtual bool __fastcall DoExecute(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoDisconnect(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoLocalClientConnect(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoLocalClientData(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoOutboundClientConnect(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoOutboundClientData(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoOutboundDisconnect(Idcontext::TIdContext* AContext);
	Idcustomtcpserver::TIdServerThreadEvent __fastcall GetOnConnect();
	Idcustomtcpserver::TIdServerThreadEvent __fastcall GetOnExecute();
	void __fastcall SetOnConnect(const Idcustomtcpserver::TIdServerThreadEvent Value);
	void __fastcall SetOnExecute(const Idcustomtcpserver::TIdServerThreadEvent Value);
	Idcustomtcpserver::TIdServerThreadEvent __fastcall GetOnDisconnect();
	void __fastcall SetOnDisconnect(const Idcustomtcpserver::TIdServerThreadEvent Value);
	virtual void __fastcall InitComponent();
	
__published:
	__property Idcustomtcpserver::TIdServerThreadEvent OnBeforeConnect = {read=FOnBeforeConnect, write=FOnBeforeConnect};
	__property System::UnicodeString MappedHost = {read=FMappedHost, write=FMappedHost};
	__property System::Word MappedPort = {read=FMappedPort, write=FMappedPort, nodefault};
	__property Idcustomtcpserver::TIdServerThreadEvent OnConnect = {read=GetOnConnect, write=SetOnConnect};
	__property Idcustomtcpserver::TIdServerThreadEvent OnOutboundConnect = {read=FOnOutboundConnect, write=FOnOutboundConnect};
	__property Idcustomtcpserver::TIdServerThreadEvent OnExecute = {read=GetOnExecute, write=SetOnExecute};
	__property Idcustomtcpserver::TIdServerThreadEvent OnOutboundData = {read=FOnOutboundData, write=FOnOutboundData};
	__property Idcustomtcpserver::TIdServerThreadEvent OnDisconnect = {read=GetOnDisconnect, write=SetOnDisconnect};
	__property Idcustomtcpserver::TIdServerThreadEvent OnOutboundDisconnect = {read=FOnOutboundDisConnect, write=FOnOutboundDisConnect};
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdMappedPortTCP() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdMappedPortTCP(System::Classes::TComponent* AOwner)/* overload */ : Idcustomtcpserver::TIdCustomTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMappedPortTCP()/* overload */ : Idcustomtcpserver::TIdCustomTCPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idmappedporttcp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDMAPPEDPORTTCP)
using namespace Idmappedporttcp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdmappedporttcpHPP
