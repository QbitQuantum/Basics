﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHTTPProxyServer.pas' rev: 34.00 (Android)

#ifndef IdhttpproxyserverHPP
#define IdhttpproxyserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdGlobal.hpp>
#include <IdHeaderList.hpp>
#include <IdTCPConnection.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdCmdTCPServer.hpp>
#include <IdCommandHandlers.hpp>
#include <IdContext.hpp>
#include <IdYarn.hpp>
#include <IdTask.hpp>
#include <IdThreadSafe.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idhttpproxyserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHTTPProxyServerContext;
class DELPHICLASS TIdHTTPProxyServer;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdHTTPProxyTransferMode : unsigned char { tmFullDocument, tmStreaming };

enum DECLSPEC_DENUM TIdHTTPProxyTransferSource : unsigned char { tsClient, tsServer };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHTTPProxyServerContext : public Idcustomtcpserver::TIdServerContext
{
	typedef Idcustomtcpserver::TIdServerContext inherited;
	
protected:
	Idheaderlist::TIdHeaderList* FHeaders;
	System::UnicodeString FCommand;
	System::UnicodeString FDocument;
	Idtcpconnection::TIdTCPConnection* FOutboundClient;
	System::UnicodeString FTarget;
	TIdHTTPProxyTransferMode FTransferMode;
	TIdHTTPProxyTransferSource FTransferSource;
	
public:
	__fastcall virtual TIdHTTPProxyServerContext(Idtcpconnection::TIdTCPConnection* AConnection, Idyarn::TIdYarn* AYarn, Idthreadsafe::TIdThreadSafeObjectList* AList);
	__fastcall virtual ~TIdHTTPProxyServerContext();
	__property Idheaderlist::TIdHeaderList* Headers = {read=FHeaders};
	__property System::UnicodeString Command = {read=FCommand};
	__property System::UnicodeString Document = {read=FDocument};
	__property Idtcpconnection::TIdTCPConnection* OutboundClient = {read=FOutboundClient};
	__property System::UnicodeString Target = {read=FTarget};
	__property TIdHTTPProxyTransferMode TransferMode = {read=FTransferMode, write=FTransferMode, nodefault};
	__property TIdHTTPProxyTransferSource TransferSource = {read=FTransferSource, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TOnHTTPContextEvent)(TIdHTTPProxyServerContext* AContext);

typedef void __fastcall (__closure *TOnHTTPDocument)(TIdHTTPProxyServerContext* AContext, System::Classes::TStream* &VStream);

class PASCALIMPLEMENTATION TIdHTTPProxyServer : public Idcmdtcpserver::TIdCmdTCPServer
{
	typedef Idcmdtcpserver::TIdCmdTCPServer inherited;
	
protected:
	TIdHTTPProxyTransferMode FDefTransferMode;
	TOnHTTPContextEvent FOnHTTPBeforeCommand;
	TOnHTTPContextEvent FOnHTTPResponse;
	TOnHTTPDocument FOnHTTPDocument;
	void __fastcall CommandPassThrough(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandCONNECT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall DoHTTPBeforeCommand(TIdHTTPProxyServerContext* AContext);
	void __fastcall DoHTTPDocument(TIdHTTPProxyServerContext* AContext, System::Classes::TStream* &VStream);
	void __fastcall DoHTTPResponse(TIdHTTPProxyServerContext* AContext);
	virtual void __fastcall InitializeCommandHandlers();
	void __fastcall TransferData(TIdHTTPProxyServerContext* AContext, Idtcpconnection::TIdTCPConnection* ASrc, Idtcpconnection::TIdTCPConnection* ADest);
	virtual void __fastcall InitComponent();
	
__published:
	__property DefaultPort = {default=8080};
	__property TIdHTTPProxyTransferMode DefaultTransferMode = {read=FDefTransferMode, write=FDefTransferMode, default=0};
	__property TOnHTTPContextEvent OnHTTPBeforeCommand = {read=FOnHTTPBeforeCommand, write=FOnHTTPBeforeCommand};
	__property TOnHTTPContextEvent OnHTTPResponse = {read=FOnHTTPResponse, write=FOnHTTPResponse};
	__property TOnHTTPDocument OnHTTPDocument = {read=FOnHTTPDocument, write=FOnHTTPDocument};
public:
	/* TIdCmdTCPServer.Destroy */ inline __fastcall virtual ~TIdHTTPProxyServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdHTTPProxyServer(System::Classes::TComponent* AOwner)/* overload */ : Idcmdtcpserver::TIdCmdTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdHTTPProxyServer()/* overload */ : Idcmdtcpserver::TIdCmdTCPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word IdPORT_HTTPProxy = System::Word(0x1f90);
}	/* namespace Idhttpproxyserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHTTPPROXYSERVER)
using namespace Idhttpproxyserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdhttpproxyserverHPP
