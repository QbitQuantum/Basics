// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdCmdTCPServer.pas' rev: 34.00 (iOS)

#ifndef IdcmdtcpserverHPP
#define IdcmdtcpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdCommandHandlers.hpp>
#include <IdContext.hpp>
#include <IdIOHandler.hpp>
#include <IdReply.hpp>
#include <IdTCPServer.hpp>
#include <System.SysUtils.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idcmdtcpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdCmdTCPServer;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdCmdTCPServerAfterCommandHandlerEvent)(TIdCmdTCPServer* ASender, Idcontext::TIdContext* AContext);

typedef void __fastcall (__closure *TIdCmdTCPServerBeforeCommandHandlerEvent)(TIdCmdTCPServer* ASender, System::UnicodeString &AData, Idcontext::TIdContext* AContext);

class PASCALIMPLEMENTATION TIdCmdTCPServer : public Idtcpserver::TIdTCPServer
{
	typedef Idtcpserver::TIdTCPServer inherited;
	
protected:
	Idcommandhandlers::TIdCommandHandlers* FCommandHandlers;
	bool FCommandHandlersInitialized;
	Idreply::TIdReply* FExceptionReply;
	Idreply::TIdReply* FHelpReply;
	Idreply::TIdReply* FGreeting;
	Idreply::TIdReply* FMaxConnectionReply;
	TIdCmdTCPServerAfterCommandHandlerEvent FOnAfterCommandHandler;
	TIdCmdTCPServerBeforeCommandHandlerEvent FOnBeforeCommandHandler;
	Idreply::TIdReplyClass FReplyClass;
	Idreply::TIdReplies* FReplyTexts;
	Idreply::TIdReply* FReplyUnknownCommand;
	virtual void __fastcall CheckOkToBeActive();
	virtual Idreply::TIdReply* __fastcall CreateExceptionReply();
	virtual Idreply::TIdReply* __fastcall CreateGreeting();
	virtual Idreply::TIdReply* __fastcall CreateHelpReply();
	virtual Idreply::TIdReply* __fastcall CreateMaxConnectionReply();
	virtual Idreply::TIdReply* __fastcall CreateReplyUnknownCommand();
	void __fastcall DoAfterCommandHandler(Idcommandhandlers::TIdCommandHandlers* ASender, Idcontext::TIdContext* AContext);
	void __fastcall DoBeforeCommandHandler(Idcommandhandlers::TIdCommandHandlers* ASender, System::UnicodeString &AData, Idcontext::TIdContext* AContext);
	virtual void __fastcall DoConnect(Idcontext::TIdContext* AContext);
	virtual bool __fastcall DoExecute(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoMaxConnectionsExceeded(Idiohandler::TIdIOHandler* AIOHandler);
	virtual void __fastcall DoReplyUnknownCommand(Idcontext::TIdContext* AContext, System::UnicodeString ALine);
	Idreply::TIdReply* __fastcall GetExceptionReply();
	Idreply::TIdReply* __fastcall GetGreeting();
	Idreply::TIdReply* __fastcall GetHelpReply();
	Idreply::TIdReply* __fastcall GetMaxConnectionReply();
	virtual Idreply::TIdRepliesClass __fastcall GetRepliesClass();
	virtual Idreply::TIdReplyClass __fastcall GetReplyClass();
	Idreply::TIdReply* __fastcall GetReplyUnknownCommand();
	virtual void __fastcall InitializeCommandHandlers();
	virtual void __fastcall InitComponent();
	virtual System::UnicodeString __fastcall ReadCommandLine(Idcontext::TIdContext* AContext);
	virtual void __fastcall Startup();
	void __fastcall SetCommandHandlers(Idcommandhandlers::TIdCommandHandlers* AValue);
	void __fastcall SetExceptionReply(Idreply::TIdReply* AValue);
	void __fastcall SetGreeting(Idreply::TIdReply* AValue);
	void __fastcall SetHelpReply(Idreply::TIdReply* AValue);
	void __fastcall SetMaxConnectionReply(Idreply::TIdReply* AValue);
	void __fastcall SetReplyUnknownCommand(Idreply::TIdReply* AValue);
	void __fastcall SetReplyTexts(Idreply::TIdReplies* AValue);
	
public:
	__fastcall virtual ~TIdCmdTCPServer();
	
__published:
	__property Idcommandhandlers::TIdCommandHandlers* CommandHandlers = {read=FCommandHandlers, write=SetCommandHandlers};
	__property Idreply::TIdReply* ExceptionReply = {read=GetExceptionReply, write=SetExceptionReply};
	__property Idreply::TIdReply* Greeting = {read=GetGreeting, write=SetGreeting};
	__property Idreply::TIdReply* HelpReply = {read=GetHelpReply, write=SetHelpReply};
	__property Idreply::TIdReply* MaxConnectionReply = {read=GetMaxConnectionReply, write=SetMaxConnectionReply};
	__property Idreply::TIdReplies* ReplyTexts = {read=FReplyTexts, write=SetReplyTexts};
	__property Idreply::TIdReply* ReplyUnknownCommand = {read=GetReplyUnknownCommand, write=SetReplyUnknownCommand};
	__property TIdCmdTCPServerAfterCommandHandlerEvent OnAfterCommandHandler = {read=FOnAfterCommandHandler, write=FOnAfterCommandHandler};
	__property TIdCmdTCPServerBeforeCommandHandlerEvent OnBeforeCommandHandler = {read=FOnBeforeCommandHandler, write=FOnBeforeCommandHandler};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdCmdTCPServer(System::Classes::TComponent* AOwner)/* overload */ : Idtcpserver::TIdTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdCmdTCPServer()/* overload */ : Idtcpserver::TIdTCPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idcmdtcpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDCMDTCPSERVER)
using namespace Idcmdtcpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdcmdtcpserverHPP
