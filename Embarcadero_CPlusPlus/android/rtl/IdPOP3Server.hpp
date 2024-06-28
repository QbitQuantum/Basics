// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdPOP3Server.pas' rev: 34.00 (Android)

#ifndef Idpop3serverHPP
#define Idpop3serverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdCommandHandlers.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdCmdTCPServer.hpp>
#include <IdException.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdGlobal.hpp>
#include <IdReply.hpp>
#include <IdTCPServer.hpp>
#include <IdServerIOHandler.hpp>
#include <IdMailBox.hpp>
#include <IdBaseComponent.hpp>
#include <IdTCPConnection.hpp>
#include <IdYarn.hpp>
#include <IdTask.hpp>
#include <System.SysUtils.hpp>
#include <IdComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idpop3server
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdPOP3ServerContext;
class DELPHICLASS EIdPOP3ServerException;
class DELPHICLASS EIdPOP3ImplicitTLSRequiresSSL;
class DELPHICLASS TIdPOP3Server;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdPOP3ServerContext : public Idcustomtcpserver::TIdServerContext
{
	typedef Idcustomtcpserver::TIdServerContext inherited;
	
protected:
	System::UnicodeString fUsername;
	System::UnicodeString fPassword;
	bool fAuthenticated;
	System::UnicodeString fAPOP3Challenge;
	bool __fastcall GetUsingTLS();
	bool __fastcall GetCanUseExplicitTLS();
	bool __fastcall GetTLSIsRequired();
	
public:
	__property System::UnicodeString APOP3Challenge = {read=fAPOP3Challenge, write=fAPOP3Challenge};
	__property bool Authenticated = {read=fAuthenticated, nodefault};
	__property System::UnicodeString Username = {read=fUsername};
	__property System::UnicodeString Password = {read=fPassword};
	__property bool UsingTLS = {read=GetUsingTLS, nodefault};
	__property bool CanUseExplicitTLS = {read=GetCanUseExplicitTLS, nodefault};
	__property bool TLSIsRequired = {read=GetTLSIsRequired, nodefault};
public:
	/* TIdContext.Create */ inline __fastcall virtual TIdPOP3ServerContext(Idtcpconnection::TIdTCPConnection* AConnection, Idyarn::TIdYarn* AYarn, Idthreadsafe::TIdThreadSafeObjectList* AList) : Idcustomtcpserver::TIdServerContext(AConnection, AYarn, AList) { }
	/* TIdContext.Destroy */ inline __fastcall virtual ~TIdPOP3ServerContext() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TIdPOP3ServerNoParamEvent)(Idcommandhandlers::TIdCommand* aCmd);

typedef void __fastcall (__closure *TIdPOP3ServerStatEvent)(Idcommandhandlers::TIdCommand* aCmd, /* out */ int &oCount, /* out */ __int64 &oSize);

typedef void __fastcall (__closure *TIdPOP3ServerMessageNumberEvent)(Idcommandhandlers::TIdCommand* aCmd, int AMsgNo);

typedef void __fastcall (__closure *TIdPOP3ServerLogin)(Idcontext::TIdContext* aContext, TIdPOP3ServerContext* aServerContext);

typedef void __fastcall (__closure *TIdPOP3ServerCAPACommandEvent)(Idcontext::TIdContext* aContext, System::Classes::TStrings* aCapabilities);

typedef void __fastcall (__closure *TIdPOP3ServerAPOPCommandEvent)(Idcommandhandlers::TIdCommand* aCmd, System::UnicodeString aMailboxID, System::UnicodeString &vUsersPassword);

typedef void __fastcall (__closure *TIdPOP3ServerTOPCommandEvent)(Idcommandhandlers::TIdCommand* aCmd, int aMsgNo, int aLines);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdPOP3ServerException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdPOP3ServerException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdPOP3ServerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdPOP3ServerException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdPOP3ServerException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdPOP3ServerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdPOP3ServerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdPOP3ServerException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdPOP3ServerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdPOP3ServerException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdPOP3ServerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdPOP3ServerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdPOP3ServerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdPOP3ServerException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdPOP3ImplicitTLSRequiresSSL : public EIdPOP3ServerException
{
	typedef EIdPOP3ServerException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdPOP3ImplicitTLSRequiresSSL(const System::UnicodeString AMsg)/* overload */ : EIdPOP3ServerException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdPOP3ServerException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(NativeUInt Ident)/* overload */ : EIdPOP3ServerException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(System::PResStringRec ResStringRec)/* overload */ : EIdPOP3ServerException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdPOP3ServerException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdPOP3ServerException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(const System::UnicodeString Msg, int AHelpContext) : EIdPOP3ServerException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdPOP3ServerException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(NativeUInt Ident, int AHelpContext)/* overload */ : EIdPOP3ServerException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdPOP3ServerException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdPOP3ServerException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdPOP3ImplicitTLSRequiresSSL(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdPOP3ServerException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdPOP3ImplicitTLSRequiresSSL() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TIdPOP3Server : public Idexplicittlsclientserverbase::TIdExplicitTLSServer
{
	typedef Idexplicittlsclientserverbase::TIdExplicitTLSServer inherited;
	
protected:
	TIdPOP3ServerLogin fCommandLogin;
	TIdPOP3ServerMessageNumberEvent fCommandList;
	TIdPOP3ServerMessageNumberEvent fCommandRetr;
	TIdPOP3ServerMessageNumberEvent fCommandDele;
	TIdPOP3ServerMessageNumberEvent fCommandUIDL;
	TIdPOP3ServerTOPCommandEvent fCommandTop;
	TIdPOP3ServerNoParamEvent fCommandQuit;
	TIdPOP3ServerStatEvent fCommandStat;
	TIdPOP3ServerNoParamEvent fCommandRset;
	TIdPOP3ServerAPOPCommandEvent fCommandAPOP;
	TIdPOP3ServerCAPACommandEvent fCommandCapa;
	bool __fastcall IsAuthed(Idcommandhandlers::TIdCommand* aCmd, bool aAssigned);
	void __fastcall MustUseTLS(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandUser(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandPass(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandList(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandRetr(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandDele(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandQuit(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandAPOP(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandStat(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandRset(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandTop(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandUIDL(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandSTLS(Idcommandhandlers::TIdCommand* aCmd);
	void __fastcall CommandCAPA(Idcommandhandlers::TIdCommand* aCmd);
	virtual Idreply::TIdReply* __fastcall CreateExceptionReply();
	virtual Idreply::TIdReply* __fastcall CreateGreeting();
	virtual Idreply::TIdReply* __fastcall CreateHelpReply();
	virtual Idreply::TIdReply* __fastcall CreateMaxConnectionReply();
	virtual Idreply::TIdReply* __fastcall CreateReplyUnknownCommand();
	virtual void __fastcall InitializeCommandHandlers();
	virtual void __fastcall DoReplyUnknownCommand(Idcontext::TIdContext* AContext, System::UnicodeString ALine);
	virtual Idreply::TIdReplyClass __fastcall GetReplyClass();
	virtual Idreply::TIdRepliesClass __fastcall GetRepliesClass();
	virtual void __fastcall SendGreeting(Idcontext::TIdContext* AContext, Idreply::TIdReply* AGreeting);
	virtual void __fastcall InitComponent();
	
__published:
	__property DefaultPort = {default=110};
	__property TIdPOP3ServerLogin OnCheckUser = {read=fCommandLogin, write=fCommandLogin};
	__property TIdPOP3ServerMessageNumberEvent OnList = {read=fCommandList, write=fCommandList};
	__property TIdPOP3ServerMessageNumberEvent OnRetrieve = {read=fCommandRetr, write=fCommandRetr};
	__property TIdPOP3ServerMessageNumberEvent OnDelete = {read=fCommandDele, write=fCommandDele};
	__property TIdPOP3ServerMessageNumberEvent OnUIDL = {read=fCommandUIDL, write=fCommandUIDL};
	__property TIdPOP3ServerStatEvent OnStat = {read=fCommandStat, write=fCommandStat};
	__property TIdPOP3ServerTOPCommandEvent OnTop = {read=fCommandTop, write=fCommandTop};
	__property TIdPOP3ServerNoParamEvent OnReset = {read=fCommandRset, write=fCommandRset};
	__property TIdPOP3ServerNoParamEvent OnQuit = {read=fCommandQuit, write=fCommandQuit};
	__property TIdPOP3ServerAPOPCommandEvent OnAPOP = {read=fCommandAPOP, write=fCommandAPOP};
	__property TIdPOP3ServerCAPACommandEvent OnCAPA = {read=fCommandCapa, write=fCommandCapa};
	__property UseTLS = {default=0};
public:
	/* TIdCmdTCPServer.Destroy */ inline __fastcall virtual ~TIdPOP3Server() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdPOP3Server(System::Classes::TComponent* AOwner)/* overload */ : Idexplicittlsclientserverbase::TIdExplicitTLSServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdPOP3Server()/* overload */ : Idexplicittlsclientserverbase::TIdExplicitTLSServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr bool DEF_POP3_IMPLICIT_TLS = false;
}	/* namespace Idpop3server */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDPOP3SERVER)
using namespace Idpop3server;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idpop3serverHPP
