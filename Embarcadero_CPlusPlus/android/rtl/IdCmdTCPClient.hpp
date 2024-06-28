// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdCmdTCPClient.pas' rev: 34.00 (Android)

#ifndef IdcmdtcpclientHPP
#define IdcmdtcpclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdContext.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <IdReply.hpp>
#include <IdResourceStringsCore.hpp>
#include <IdThread.hpp>
#include <IdTCPClient.hpp>
#include <IdCommandHandlers.hpp>
#include <IdTask.hpp>
#include <System.Classes.hpp>
#include <IdTCPConnection.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idcmdtcpclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdCmdClientContext;
class DELPHICLASS TIdCmdTCPClientListeningThread;
class DELPHICLASS TIdCmdTCPClient;
class DELPHICLASS EIdCmdTCPClientError;
class DELPHICLASS EIdCmdTCPClientConnectError;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdCmdTCPClientAfterCommandHandlerEvent)(TIdCmdTCPClient* ASender, Idcontext::TIdContext* AContext);

typedef void __fastcall (__closure *TIdCmdTCPClientBeforeCommandHandlerEvent)(TIdCmdTCPClient* ASender, System::UnicodeString &AData, Idcontext::TIdContext* AContext);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdCmdClientContext : public Idcontext::TIdContext
{
	typedef Idcontext::TIdContext inherited;
	
protected:
	TIdCmdTCPClient* FClient;
	
public:
	__property TIdCmdTCPClient* Client = {read=FClient};
public:
	/* TIdContext.Create */ inline __fastcall virtual TIdCmdClientContext(Idtcpconnection::TIdTCPConnection* AConnection, Idyarn::TIdYarn* AYarn, Idthreadsafe::TIdThreadSafeObjectList* AList) : Idcontext::TIdContext(AConnection, AYarn, AList) { }
	/* TIdContext.Destroy */ inline __fastcall virtual ~TIdCmdClientContext() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdCmdTCPClientListeningThread : public Idthread::TIdThread
{
	typedef Idthread::TIdThread inherited;
	
protected:
	TIdCmdClientContext* FContext;
	TIdCmdTCPClient* FClient;
	System::UnicodeString FRecvData;
	virtual void __fastcall Run();
	
public:
	__fastcall TIdCmdTCPClientListeningThread(TIdCmdTCPClient* AClient);
	__fastcall virtual ~TIdCmdTCPClientListeningThread();
	__property TIdCmdTCPClient* Client = {read=FClient};
	__property System::UnicodeString RecvData = {read=FRecvData, write=FRecvData};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TIdCmdTCPClient : public Idtcpclient::TIdTCPClient
{
	typedef Idtcpclient::TIdTCPClient inherited;
	
protected:
	Idreply::TIdReply* FExceptionReply;
	TIdCmdTCPClientListeningThread* FListeningThread;
	Idcommandhandlers::TIdCommandHandlers* FCommandHandlers;
	TIdCmdTCPClientAfterCommandHandlerEvent FOnAfterCommandHandler;
	TIdCmdTCPClientBeforeCommandHandlerEvent FOnBeforeCommandHandler;
	void __fastcall DoAfterCommandHandler(Idcommandhandlers::TIdCommandHandlers* ASender, Idcontext::TIdContext* AContext);
	void __fastcall DoBeforeCommandHandler(Idcommandhandlers::TIdCommandHandlers* ASender, System::UnicodeString &AData, Idcontext::TIdContext* AContext);
	virtual void __fastcall DoReplyUnknownCommand(Idcontext::TIdContext* AContext, System::UnicodeString ALine);
	virtual Idcommandhandlers::TIdCommandHandlerClass __fastcall GetCmdHandlerClass();
	virtual void __fastcall InitComponent();
	void __fastcall SetCommandHandlers(Idcommandhandlers::TIdCommandHandlers* AValue);
	void __fastcall SetExceptionReply(Idreply::TIdReply* AValue);
	
public:
	virtual void __fastcall Connect()/* overload */;
	__fastcall virtual ~TIdCmdTCPClient();
	virtual void __fastcall Disconnect(bool ANotifyPeer)/* overload */;
	
__published:
	__property Idcommandhandlers::TIdCommandHandlers* CommandHandlers = {read=FCommandHandlers, write=SetCommandHandlers};
	__property Idreply::TIdReply* ExceptionReply = {read=FExceptionReply, write=SetExceptionReply};
	__property TIdCmdTCPClientAfterCommandHandlerEvent OnAfterCommandHandler = {read=FOnAfterCommandHandler, write=FOnAfterCommandHandler};
	__property TIdCmdTCPClientBeforeCommandHandlerEvent OnBeforeCommandHandler = {read=FOnBeforeCommandHandler, write=FOnBeforeCommandHandler};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdCmdTCPClient(System::Classes::TComponent* AOwner)/* overload */ : Idtcpclient::TIdTCPClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdCmdTCPClient()/* overload */ : Idtcpclient::TIdTCPClient() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Connect(const System::UnicodeString AHost){ Idtcpclient::TIdTCPClientCustom::Connect(AHost); }
	inline void __fastcall  Connect(const System::UnicodeString AHost, const System::Word APort){ Idtcpclient::TIdTCPClientCustom::Connect(AHost, APort); }
	inline void __fastcall  Disconnect(){ Idtcpconnection::TIdTCPConnection::Disconnect(); }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdCmdTCPClientError : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdCmdTCPClientError(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdCmdTCPClientError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdCmdTCPClientError(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdCmdTCPClientError(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCmdTCPClientError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCmdTCPClientError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdCmdTCPClientError(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdCmdTCPClientError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCmdTCPClientError(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCmdTCPClientError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCmdTCPClientError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCmdTCPClientError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdCmdTCPClientError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdCmdTCPClientConnectError : public EIdCmdTCPClientError
{
	typedef EIdCmdTCPClientError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdCmdTCPClientConnectError(const System::UnicodeString AMsg)/* overload */ : EIdCmdTCPClientError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdCmdTCPClientConnectError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdCmdTCPClientError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdCmdTCPClientConnectError(NativeUInt Ident)/* overload */ : EIdCmdTCPClientError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdCmdTCPClientConnectError(System::PResStringRec ResStringRec)/* overload */ : EIdCmdTCPClientError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCmdTCPClientConnectError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdCmdTCPClientError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCmdTCPClientConnectError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdCmdTCPClientError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdCmdTCPClientConnectError(const System::UnicodeString Msg, int AHelpContext) : EIdCmdTCPClientError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdCmdTCPClientConnectError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdCmdTCPClientError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCmdTCPClientConnectError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdCmdTCPClientError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCmdTCPClientConnectError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdCmdTCPClientError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCmdTCPClientConnectError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdCmdTCPClientError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCmdTCPClientConnectError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdCmdTCPClientError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdCmdTCPClientConnectError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idcmdtcpclient */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDCMDTCPCLIENT)
using namespace Idcmdtcpclient;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdcmdtcpclientHPP
