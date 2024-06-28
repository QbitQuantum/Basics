// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSimpleServer.pas' rev: 34.00 (Windows)

#ifndef IdsimpleserverHPP
#define IdsimpleserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
#include <IdTCPConnection.hpp>
#include <IdStackConsts.hpp>
#include <IdIOHandler.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsimpleserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSimpleServer;
class DELPHICLASS EIdCannotUseNonSocketIOHandler;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSimpleServer : public Idtcpconnection::TIdTCPConnection
{
	typedef Idtcpconnection::TIdTCPConnection inherited;
	
protected:
	bool FAbortedRequested;
	int FAcceptWait;
	System::UnicodeString FBoundIP;
	System::Word FBoundPort;
	System::Word FBoundPortMin;
	System::Word FBoundPortMax;
	Idglobal::TIdIPVersion FIPVersion;
	NativeUInt FListenHandle;
	bool FListening;
	System::Classes::TNotifyEvent FOnBeforeBind;
	System::Classes::TNotifyEvent FOnAfterBind;
	void __fastcall Bind();
	virtual void __fastcall DoBeforeBind();
	virtual void __fastcall DoAfterBind();
	Idsockethandle::TIdSocketHandle* __fastcall GetBinding();
	virtual void __fastcall InitComponent();
	virtual void __fastcall SetIOHandler(Idiohandler::TIdIOHandler* AValue);
	void __fastcall SetIPVersion(const Idglobal::TIdIPVersion AValue);
	
public:
	virtual void __fastcall Abort();
	virtual void __fastcall BeginListen();
	void __fastcall CreateBinding();
	virtual void __fastcall EndListen();
	virtual void __fastcall Listen(int ATimeout = 0xffffffff);
	__property int AcceptWait = {read=FAcceptWait, write=FAcceptWait, default=1000};
	
__published:
	__property System::UnicodeString BoundIP = {read=FBoundIP, write=FBoundIP};
	__property System::Word BoundPort = {read=FBoundPort, write=FBoundPort, nodefault};
	__property System::Word BoundPortMin = {read=FBoundPortMin, write=FBoundPortMin, nodefault};
	__property System::Word BoundPortMax = {read=FBoundPortMax, write=FBoundPortMax, nodefault};
	__property Idsockethandle::TIdSocketHandle* Binding = {read=GetBinding};
	__property Idglobal::TIdIPVersion IPVersion = {read=FIPVersion, write=SetIPVersion, default=0};
	__property System::Classes::TNotifyEvent OnBeforeBind = {read=FOnBeforeBind, write=FOnBeforeBind};
	__property System::Classes::TNotifyEvent OnAfterBind = {read=FOnAfterBind, write=FOnAfterBind};
public:
	/* TIdTCPConnection.Destroy */ inline __fastcall virtual ~TIdSimpleServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSimpleServer(System::Classes::TComponent* AOwner)/* overload */ : Idtcpconnection::TIdTCPConnection(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSimpleServer()/* overload */ : Idtcpconnection::TIdTCPConnection() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdCannotUseNonSocketIOHandler : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdCannotUseNonSocketIOHandler(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdCannotUseNonSocketIOHandler(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdCannotUseNonSocketIOHandler(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdCannotUseNonSocketIOHandler(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCannotUseNonSocketIOHandler(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCannotUseNonSocketIOHandler(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdCannotUseNonSocketIOHandler(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdCannotUseNonSocketIOHandler(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCannotUseNonSocketIOHandler(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCannotUseNonSocketIOHandler(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCannotUseNonSocketIOHandler(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCannotUseNonSocketIOHandler(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdCannotUseNonSocketIOHandler() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
static const System::Word ID_ACCEPT_WAIT = System::Word(0x3e8);
}	/* namespace Idsimpleserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSIMPLESERVER)
using namespace Idsimpleserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsimpleserverHPP
