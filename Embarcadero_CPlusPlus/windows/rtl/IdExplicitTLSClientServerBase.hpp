// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdExplicitTLSClientServerBase.pas' rev: 34.00 (Windows)

#ifndef IdexplicittlsclientserverbaseHPP
#define IdexplicittlsclientserverbaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdCmdTCPServer.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <IdIOHandler.hpp>
#include <IdServerIOHandler.hpp>
#include <IdTCPClient.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <IdTCPConnection.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idexplicittlsclientserverbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdExplicitTLSServer;
class DELPHICLASS TIdExplicitTLSClient;
class DELPHICLASS EIdTLSClientException;
class DELPHICLASS EIdTLSClientSSLIOHandlerRequred;
class DELPHICLASS EIdTLSClientCanNotSetWhileConnected;
class DELPHICLASS EIdTLSClientTLSNotAvailable;
class DELPHICLASS EIdTLSClientTLSNegCmdFailed;
class DELPHICLASS EIdTLSClientTLSHandShakeFailed;
class DELPHICLASS EIdTLSServerException;
class DELPHICLASS EIdTLSServerSSLIOHandlerRequired;
class DELPHICLASS EIdTLSClientCanNotSetWhileActive;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdUseTLS : unsigned char { utNoTLSSupport, utUseImplicitTLS, utUseRequireTLS, utUseExplicitTLS };

typedef void __fastcall (__closure *TIdOnTLSNegotiationFailure)(System::TObject* Asender, bool &VContinue);

class PASCALIMPLEMENTATION TIdExplicitTLSServer : public Idcmdtcpserver::TIdCmdTCPServer
{
	typedef Idcmdtcpserver::TIdCmdTCPServer inherited;
	
protected:
	System::Word FRegularProtPort;
	System::Word FImplicitTLSProtPort;
	System::Word FExplicitTLSProtPort;
	TIdUseTLS FUseTLS;
	virtual void __fastcall Loaded();
	virtual void __fastcall SetIOHandler(Idserveriohandler::TIdServerIOHandler* const AValue);
	virtual void __fastcall SetUseTLS(TIdUseTLS AValue);
	__property TIdUseTLS UseTLS = {read=FUseTLS, write=SetUseTLS, default=0};
	virtual void __fastcall InitComponent();
public:
	/* TIdCmdTCPServer.Destroy */ inline __fastcall virtual ~TIdExplicitTLSServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdExplicitTLSServer(System::Classes::TComponent* AOwner)/* overload */ : Idcmdtcpserver::TIdCmdTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdExplicitTLSServer()/* overload */ : Idcmdtcpserver::TIdCmdTCPServer() { }
	
};


class PASCALIMPLEMENTATION TIdExplicitTLSClient : public Idtcpclient::TIdTCPClientCustom
{
	typedef Idtcpclient::TIdTCPClientCustom inherited;
	
protected:
	System::Word FRegularProtPort;
	System::Word FImplicitTLSProtPort;
	System::Word FExplicitTLSProtPort;
	TIdUseTLS FUseTLS;
	TIdOnTLSNegotiationFailure FOnTLSNotAvailable;
	TIdOnTLSNegotiationFailure FOnTLSNegCmdFailed;
	TIdOnTLSNegotiationFailure FOnTLSHandShakeFailed;
	System::Classes::TStrings* FCapabilities;
	virtual bool __fastcall GetSupportsTLS();
	virtual void __fastcall CheckIfCanUseTLS();
	virtual void __fastcall Loaded();
	void __fastcall TLSNotAvailable();
	void __fastcall DoOnTLSNotAvailable();
	void __fastcall ProcessTLSNotAvail();
	void __fastcall TLSNegCmdFailed();
	void __fastcall DoOnTLSNegCmdFailed();
	void __fastcall ProcessTLSNegCmdFailed();
	void __fastcall TLSHandShakeFailed();
	void __fastcall DoOnTLSHandShakeFailed();
	void __fastcall ProcessTLSHandShakeFailed();
	virtual void __fastcall SetIOHandler(Idiohandler::TIdIOHandler* AValue);
	virtual void __fastcall SetUseTLS(TIdUseTLS AValue);
	virtual void __fastcall TLSHandshake();
	virtual void __fastcall InitComponent();
	__property TIdUseTLS UseTLS = {read=FUseTLS, write=SetUseTLS, default=0};
	
public:
	__fastcall virtual ~TIdExplicitTLSClient();
	virtual void __fastcall Connect()/* overload */;
	__property bool SupportsTLS = {read=GetSupportsTLS, nodefault};
	__property System::Classes::TStrings* Capabilities = {read=FCapabilities};
	__property TIdOnTLSNegotiationFailure OnTLSHandShakeFailed = {read=FOnTLSHandShakeFailed, write=FOnTLSHandShakeFailed};
	__property TIdOnTLSNegotiationFailure OnTLSNotAvailable = {read=FOnTLSNotAvailable, write=FOnTLSNotAvailable};
	__property TIdOnTLSNegotiationFailure OnTLSNegCmdFailed = {read=FOnTLSNegCmdFailed, write=FOnTLSNegCmdFailed};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdExplicitTLSClient(System::Classes::TComponent* AOwner)/* overload */ : Idtcpclient::TIdTCPClientCustom(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdExplicitTLSClient()/* overload */ : Idtcpclient::TIdTCPClientCustom() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Connect(const System::UnicodeString AHost){ Idtcpclient::TIdTCPClientCustom::Connect(AHost); }
	inline void __fastcall  Connect(const System::UnicodeString AHost, const System::Word APort){ Idtcpclient::TIdTCPClientCustom::Connect(AHost, APort); }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdTLSClientException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTLSClientException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTLSClientException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTLSClientException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTLSClientException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTLSClientException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdTLSClientSSLIOHandlerRequred : public EIdTLSClientException
{
	typedef EIdTLSClientException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTLSClientSSLIOHandlerRequred(const System::UnicodeString AMsg)/* overload */ : EIdTLSClientException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdTLSClientException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(NativeUInt Ident)/* overload */ : EIdTLSClientException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(System::PResStringRec ResStringRec)/* overload */ : EIdTLSClientException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(const System::UnicodeString Msg, int AHelpContext) : EIdTLSClientException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdTLSClientException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(NativeUInt Ident, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientSSLIOHandlerRequred(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTLSClientSSLIOHandlerRequred() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdTLSClientCanNotSetWhileConnected : public EIdTLSClientException
{
	typedef EIdTLSClientException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTLSClientCanNotSetWhileConnected(const System::UnicodeString AMsg)/* overload */ : EIdTLSClientException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdTLSClientException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(NativeUInt Ident)/* overload */ : EIdTLSClientException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(System::PResStringRec ResStringRec)/* overload */ : EIdTLSClientException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(const System::UnicodeString Msg, int AHelpContext) : EIdTLSClientException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdTLSClientException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(NativeUInt Ident, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientCanNotSetWhileConnected(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTLSClientCanNotSetWhileConnected() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdTLSClientTLSNotAvailable : public EIdTLSClientException
{
	typedef EIdTLSClientException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTLSClientTLSNotAvailable(const System::UnicodeString AMsg)/* overload */ : EIdTLSClientException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTLSClientTLSNotAvailable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdTLSClientException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientTLSNotAvailable(NativeUInt Ident)/* overload */ : EIdTLSClientException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientTLSNotAvailable(System::PResStringRec ResStringRec)/* overload */ : EIdTLSClientException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientTLSNotAvailable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientTLSNotAvailable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTLSClientTLSNotAvailable(const System::UnicodeString Msg, int AHelpContext) : EIdTLSClientException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTLSClientTLSNotAvailable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdTLSClientException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientTLSNotAvailable(NativeUInt Ident, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientTLSNotAvailable(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientTLSNotAvailable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientTLSNotAvailable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTLSClientTLSNotAvailable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdTLSClientTLSNegCmdFailed : public EIdTLSClientException
{
	typedef EIdTLSClientException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTLSClientTLSNegCmdFailed(const System::UnicodeString AMsg)/* overload */ : EIdTLSClientException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTLSClientTLSNegCmdFailed(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdTLSClientException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientTLSNegCmdFailed(NativeUInt Ident)/* overload */ : EIdTLSClientException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientTLSNegCmdFailed(System::PResStringRec ResStringRec)/* overload */ : EIdTLSClientException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientTLSNegCmdFailed(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientTLSNegCmdFailed(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTLSClientTLSNegCmdFailed(const System::UnicodeString Msg, int AHelpContext) : EIdTLSClientException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTLSClientTLSNegCmdFailed(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdTLSClientException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientTLSNegCmdFailed(NativeUInt Ident, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientTLSNegCmdFailed(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientTLSNegCmdFailed(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientTLSNegCmdFailed(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTLSClientTLSNegCmdFailed() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdTLSClientTLSHandShakeFailed : public EIdTLSClientException
{
	typedef EIdTLSClientException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTLSClientTLSHandShakeFailed(const System::UnicodeString AMsg)/* overload */ : EIdTLSClientException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTLSClientTLSHandShakeFailed(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdTLSClientException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientTLSHandShakeFailed(NativeUInt Ident)/* overload */ : EIdTLSClientException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientTLSHandShakeFailed(System::PResStringRec ResStringRec)/* overload */ : EIdTLSClientException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientTLSHandShakeFailed(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientTLSHandShakeFailed(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTLSClientTLSHandShakeFailed(const System::UnicodeString Msg, int AHelpContext) : EIdTLSClientException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTLSClientTLSHandShakeFailed(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdTLSClientException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientTLSHandShakeFailed(NativeUInt Ident, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientTLSHandShakeFailed(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientTLSHandShakeFailed(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientTLSHandShakeFailed(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTLSClientTLSHandShakeFailed() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdTLSServerException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTLSServerException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTLSServerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSServerException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSServerException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSServerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSServerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTLSServerException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTLSServerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSServerException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSServerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSServerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSServerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTLSServerException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdTLSServerSSLIOHandlerRequired : public EIdTLSServerException
{
	typedef EIdTLSServerException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTLSServerSSLIOHandlerRequired(const System::UnicodeString AMsg)/* overload */ : EIdTLSServerException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdTLSServerException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(NativeUInt Ident)/* overload */ : EIdTLSServerException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(System::PResStringRec ResStringRec)/* overload */ : EIdTLSServerException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSServerException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSServerException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(const System::UnicodeString Msg, int AHelpContext) : EIdTLSServerException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdTLSServerException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(NativeUInt Ident, int AHelpContext)/* overload */ : EIdTLSServerException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdTLSServerException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSServerException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSServerSSLIOHandlerRequired(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSServerException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTLSServerSSLIOHandlerRequired() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdTLSClientCanNotSetWhileActive : public EIdTLSClientException
{
	typedef EIdTLSClientException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTLSClientCanNotSetWhileActive(const System::UnicodeString AMsg)/* overload */ : EIdTLSClientException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTLSClientCanNotSetWhileActive(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdTLSClientException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientCanNotSetWhileActive(NativeUInt Ident)/* overload */ : EIdTLSClientException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTLSClientCanNotSetWhileActive(System::PResStringRec ResStringRec)/* overload */ : EIdTLSClientException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientCanNotSetWhileActive(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTLSClientCanNotSetWhileActive(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTLSClientCanNotSetWhileActive(const System::UnicodeString Msg, int AHelpContext) : EIdTLSClientException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTLSClientCanNotSetWhileActive(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdTLSClientException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientCanNotSetWhileActive(NativeUInt Ident, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTLSClientCanNotSetWhileActive(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientCanNotSetWhileActive(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTLSClientCanNotSetWhileActive(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTLSClientException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTLSClientCanNotSetWhileActive() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define ExplicitTLSVals (System::Set<TIdUseTLS, TIdUseTLS::utNoTLSSupport, TIdUseTLS::utUseExplicitTLS>() << TIdUseTLS::utUseRequireTLS << TIdUseTLS::utUseExplicitTLS )
static const TIdUseTLS DEF_USETLS = (TIdUseTLS)(0);
}	/* namespace Idexplicittlsclientserverbase */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDEXPLICITTLSCLIENTSERVERBASE)
using namespace Idexplicittlsclientserverbase;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdexplicittlsclientserverbaseHPP
