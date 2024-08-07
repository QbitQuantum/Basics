﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdTelnet.pas' rev: 34.00 (Android)

#ifndef IdtelnetHPP
#define IdtelnetHPP

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
#include <IdException.hpp>
#include <IdStack.hpp>
#include <IdTCPClient.hpp>
#include <IdThread.hpp>
#include <IdTCPConnection.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idtelnet
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdTelnetReadThread;
class DELPHICLASS TIdTelnet;
class DELPHICLASS EIdTelnetError;
class DELPHICLASS EIdTelnetClientConnectError;
class DELPHICLASS EIdTelnetServerOnDataAvailableIsNil;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdTelnetCommand : unsigned char { tncNoLocalEcho, tncLocalEcho, tncEcho };

typedef void __fastcall (__closure *TIdTelnetDataAvailEvent)(TIdTelnet* Sender, const Idglobal::TIdBytes Buffer);

typedef void __fastcall (__closure *TIdTelnetCommandEvent)(TIdTelnet* Sender, TIdTelnetCommand Status);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdTelnetReadThread : public Idthread::TIdThread
{
	typedef Idthread::TIdThread inherited;
	
protected:
	TIdTelnet* FClient;
	virtual void __fastcall Run();
	
public:
	__fastcall TIdTelnetReadThread(TIdTelnet* AClient);
	__property TIdTelnet* Client = {read=FClient};
public:
	/* TIdThread.Destroy */ inline __fastcall virtual ~TIdTelnetReadThread() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TIdTelnet : public Idtcpclient::TIdTCPClientCustom
{
	typedef Idtcpclient::TIdTCPClientCustom inherited;
	
protected:
	System::UnicodeString fTerminal;
	bool fThreadedEvent;
	TIdTelnetDataAvailEvent FOnDataAvailable;
	bool fIamTelnet;
	TIdTelnetCommandEvent FOnTelnetCommand;
	TIdTelnetReadThread* FTelnetThread;
	void __fastcall DoOnDataAvailable(const Idglobal::TIdBytes Buf);
	__property bool IamTelnet = {read=fIamTelnet, write=fIamTelnet, nodefault};
	void __fastcall Negotiate();
	void __fastcall Handle_SB(const System::Byte SbType, const Idglobal::TIdBytes SbData);
	void __fastcall SendNegotiationResp(const System::Byte Response, const System::Byte ResponseData);
	void __fastcall SendSubNegotiationResp(const System::Byte SbType, const Idglobal::TIdBytes ResponseData);
	void __fastcall DoTelnetCommand(TIdTelnetCommand Status);
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdTelnet(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TIdTelnet();
	virtual void __fastcall Connect()/* overload */;
	virtual void __fastcall Disconnect(bool ANotifyPeer)/* overload */;
	void __fastcall SendCh(System::WideChar Ch);
	void __fastcall SendString(const System::UnicodeString S);
	__property TIdTelnetReadThread* TelnetThread = {read=FTelnetThread};
	
__published:
	__property Host = {default=0};
	__property Port = {default=23};
	__property TIdTelnetCommandEvent OnTelnetCommand = {read=FOnTelnetCommand, write=FOnTelnetCommand};
	__property TIdTelnetDataAvailEvent OnDataAvailable = {read=FOnDataAvailable, write=FOnDataAvailable};
	__property System::UnicodeString Terminal = {read=fTerminal, write=fTerminal};
	__property bool ThreadedEvent = {read=fThreadedEvent, write=fThreadedEvent, default=0};
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdTelnet()/* overload */ : Idtcpclient::TIdTCPClientCustom() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Connect(const System::UnicodeString AHost){ Idtcpclient::TIdTCPClientCustom::Connect(AHost); }
	inline void __fastcall  Connect(const System::UnicodeString AHost, const System::Word APort){ Idtcpclient::TIdTCPClientCustom::Connect(AHost, APort); }
	inline void __fastcall  Disconnect(){ Idtcpconnection::TIdTCPConnection::Disconnect(); }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdTelnetError : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTelnetError(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTelnetError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTelnetError(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTelnetError(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTelnetError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTelnetError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTelnetError(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTelnetError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTelnetError(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTelnetError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTelnetError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTelnetError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTelnetError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdTelnetClientConnectError : public EIdTelnetError
{
	typedef EIdTelnetError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTelnetClientConnectError(const System::UnicodeString AMsg)/* overload */ : EIdTelnetError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTelnetClientConnectError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdTelnetError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTelnetClientConnectError(NativeUInt Ident)/* overload */ : EIdTelnetError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTelnetClientConnectError(System::PResStringRec ResStringRec)/* overload */ : EIdTelnetError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTelnetClientConnectError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTelnetError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTelnetClientConnectError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTelnetError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTelnetClientConnectError(const System::UnicodeString Msg, int AHelpContext) : EIdTelnetError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTelnetClientConnectError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdTelnetError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTelnetClientConnectError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdTelnetError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTelnetClientConnectError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdTelnetError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTelnetClientConnectError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTelnetError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTelnetClientConnectError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTelnetError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTelnetClientConnectError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdTelnetServerOnDataAvailableIsNil : public EIdTelnetError
{
	typedef EIdTelnetError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdTelnetServerOnDataAvailableIsNil(const System::UnicodeString AMsg)/* overload */ : EIdTelnetError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdTelnetError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(NativeUInt Ident)/* overload */ : EIdTelnetError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(System::PResStringRec ResStringRec)/* overload */ : EIdTelnetError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTelnetError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdTelnetError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(const System::UnicodeString Msg, int AHelpContext) : EIdTelnetError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdTelnetError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(NativeUInt Ident, int AHelpContext)/* overload */ : EIdTelnetError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdTelnetError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTelnetError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdTelnetServerOnDataAvailableIsNil(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdTelnetError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdTelnetServerOnDataAvailableIsNil() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Byte TNC_EOR = System::Byte(0xef);
static constexpr System::Byte TNC_SE = System::Byte(0xf0);
static constexpr System::Byte TNC_NOP = System::Byte(0xf1);
static constexpr System::Byte TNC_DATA_MARK = System::Byte(0xf2);
static constexpr System::Byte TNC_BREAK = System::Byte(0xf3);
static constexpr System::Byte TNC_IP = System::Byte(0xf4);
static constexpr System::Byte TNC_AO = System::Byte(0xf5);
static constexpr System::Byte TNC_AYT = System::Byte(0xf6);
static constexpr System::Byte TNC_EC = System::Byte(0xf7);
static constexpr System::Byte TNC_EL = System::Byte(0xf8);
static constexpr System::Byte TNC_GA = System::Byte(0xf9);
static constexpr System::Byte TNC_SB = System::Byte(0xfa);
static constexpr System::Byte TNC_WILL = System::Byte(0xfb);
static constexpr System::Byte TNC_WONT = System::Byte(0xfc);
static constexpr System::Byte TNC_DO = System::Byte(0xfd);
static constexpr System::Byte TNC_DONT = System::Byte(0xfe);
static constexpr System::Byte TNC_IAC = System::Byte(0xff);
static constexpr System::Int8 TNO_BINARY = System::Int8(0x0);
static constexpr System::Int8 TNO_ECHO = System::Int8(0x1);
static constexpr System::Int8 TNO_RECONNECT = System::Int8(0x2);
static constexpr System::Int8 TNO_SGA = System::Int8(0x3);
static constexpr System::Int8 TNO_AMSN = System::Int8(0x4);
static constexpr System::Int8 TNO_STATUS = System::Int8(0x5);
static constexpr System::Int8 TNO_TIMING_MARK = System::Int8(0x6);
static constexpr System::Int8 TNO_RCTE = System::Int8(0x7);
static constexpr System::Int8 TNO_OLW = System::Int8(0x8);
static constexpr System::Int8 TNO_OPS = System::Int8(0x9);
static constexpr System::Int8 TNO_OCRD = System::Int8(0xa);
static constexpr System::Int8 TNO_OHTS = System::Int8(0xb);
static constexpr System::Int8 TNO_OHTD = System::Int8(0xc);
static constexpr System::Int8 TNO_OFD = System::Int8(0xd);
static constexpr System::Int8 TNO_OVT = System::Int8(0xe);
static constexpr System::Int8 TNO_OVTD = System::Int8(0xf);
static constexpr System::Int8 TNO_OLD = System::Int8(0x10);
static constexpr System::Int8 TNO_EA = System::Int8(0x11);
static constexpr System::Int8 TNO_LOGOUT = System::Int8(0x12);
static constexpr System::Int8 TNO_BYTE_MACRO = System::Int8(0x13);
static constexpr System::Int8 TNO_DET = System::Int8(0x14);
static constexpr System::Int8 TNO_SUPDUP = System::Int8(0x15);
static constexpr System::Int8 TNO_SUPDUP_OUTPUT = System::Int8(0x16);
static constexpr System::Int8 TNO_SL = System::Int8(0x17);
static constexpr System::Int8 TNO_TERMTYPE = System::Int8(0x18);
static constexpr System::Int8 TNO_EOR = System::Int8(0x19);
static constexpr System::Int8 TNO_TACACS_ID = System::Int8(0x1a);
static constexpr System::Int8 TNO_OM = System::Int8(0x1b);
static constexpr System::Int8 TNO_TLN = System::Int8(0x1c);
static constexpr System::Int8 TNO_3270REGIME = System::Int8(0x1d);
static constexpr System::Int8 TNO_X3PAD = System::Int8(0x1e);
static constexpr System::Int8 TNO_NAWS = System::Int8(0x1f);
static constexpr System::Int8 TNO_TERM_SPEED = System::Int8(0x20);
static constexpr System::Int8 TNO_RFLOW = System::Int8(0x21);
static constexpr System::Int8 TNO_LINEMODE = System::Int8(0x22);
static constexpr System::Int8 TNO_XDISPLOC = System::Int8(0x23);
static constexpr System::Int8 TNO_ENV = System::Int8(0x24);
static constexpr System::Int8 TNO_AUTH = System::Int8(0x25);
static constexpr System::Int8 TNO_ENCRYPT = System::Int8(0x26);
static constexpr System::Int8 TNO_NEWENV = System::Int8(0x27);
static constexpr System::Int8 TNO_TN3270E = System::Int8(0x28);
static constexpr System::Int8 TNO_XAUTH = System::Int8(0x29);
static constexpr System::Int8 TNO_CHARSET = System::Int8(0x2a);
static constexpr System::Int8 TNO_RSP = System::Int8(0x2b);
static constexpr System::Int8 TNO_COMPORT = System::Int8(0x2c);
static constexpr System::Int8 TNO_SUPLOCALECHO = System::Int8(0x2d);
static constexpr System::Int8 TNO_STARTTLS = System::Int8(0x2e);
static constexpr System::Int8 TNO_KERMIT = System::Int8(0x2f);
static constexpr System::Int8 TNO_SEND_URL = System::Int8(0x30);
static constexpr System::Int8 TNO_FORWARD_X = System::Int8(0x31);
static constexpr System::Byte TNO_PRAGMA_LOGON = System::Byte(0x8a);
static constexpr System::Byte TNO_SSPI_LOGON = System::Byte(0x8b);
static constexpr System::Byte TNO_PRAGMA_HEARTBEAT = System::Byte(0x8c);
static constexpr System::Byte TNO_EOL = System::Byte(0xff);
static constexpr System::Int8 TNOS_TERM_IS = System::Int8(0x0);
static constexpr System::Int8 TNOS_TERMTYPE_SEND = System::Int8(0x1);
static constexpr System::Int8 TNOS_REPLY = System::Int8(0x2);
static constexpr System::Int8 TNOS_NAME = System::Int8(0x3);
static constexpr System::Int8 TNOAUTH_IS = System::Int8(0x0);
static constexpr System::Int8 TNOAUTH_SEND = System::Int8(0x1);
static constexpr System::Int8 TNOAUTH_REPLY = System::Int8(0x2);
static constexpr System::Int8 TNOAUTH_NAME = System::Int8(0x3);
static constexpr System::Int8 TNOAUTH_NULL = System::Int8(0x0);
static constexpr System::Int8 TNOAUTH_KERBEROS_V4 = System::Int8(0x1);
static constexpr System::Int8 TNOAUTH_KERBEROS_V5 = System::Int8(0x2);
static constexpr System::Int8 TNOAUTH_SPX = System::Int8(0x3);
static constexpr System::Int8 TNOAUTH_MINK = System::Int8(0x4);
static constexpr System::Int8 TNOAUTH_SRP = System::Int8(0x5);
static constexpr System::Int8 TNOAUTH_RSA = System::Int8(0x6);
static constexpr System::Int8 TNOAUTH_SSL = System::Int8(0x7);
static constexpr System::Int8 TNOAUTH_LOKI = System::Int8(0xa);
static constexpr System::Int8 TNOAUTH_SSA = System::Int8(0xb);
static constexpr System::Int8 TNOAUTH_KEA_SJ = System::Int8(0xc);
static constexpr System::Int8 TNOAUTH_KEA_SJ_INTEG = System::Int8(0xd);
static constexpr System::Int8 TNOAUTH_DSS = System::Int8(0xe);
static constexpr System::Int8 TNOAUTH_NTLM = System::Int8(0xf);
static constexpr System::Int8 TNOAUTH_KRB4_AUTH = System::Int8(0x0);
static constexpr System::Int8 TNOAUTH_KRB4_REJECT = System::Int8(0x1);
static constexpr System::Int8 TNOAUTH_KRB4_ACCEPT = System::Int8(0x2);
static constexpr System::Int8 TNOAUTH_KRB4_CHALLENGE = System::Int8(0x3);
static constexpr System::Int8 TNOAUTH_KRB4_RESPONSE = System::Int8(0x4);
static constexpr System::Int8 TNOAUTH_KRB4_FORWARD = System::Int8(0x5);
static constexpr System::Int8 TNOAUTH_KRB4_FORWARD_ACCEPT = System::Int8(0x6);
static constexpr System::Int8 TNOAUTH_KRB4_FORWARD_REJECT = System::Int8(0x7);
static constexpr System::Int8 TNOAUTH_KRB4_EXP = System::Int8(0x8);
static constexpr System::Int8 TNOAUTH_KRB4_PARAMS = System::Int8(0x9);
static constexpr System::Int8 TNOAUTH_KRB5_AUTH = System::Int8(0x0);
static constexpr System::Int8 TNOAUTH_KRB5_REJECT = System::Int8(0x1);
static constexpr System::Int8 TNOAUTH_KRB5_ACCEPT = System::Int8(0x2);
static constexpr System::Int8 TNOAUTH_KRB5_RESPONSE = System::Int8(0x3);
static constexpr System::Int8 TNOAUTH_KRB5_FORWARD = System::Int8(0x4);
static constexpr System::Int8 TNOAUTH_KRB5_FORWARD_ACCEPT = System::Int8(0x5);
static constexpr System::Int8 TNOAUTH_KRB5_FORWARD_REJECT = System::Int8(0x6);
static constexpr System::Int8 TNOAUTH_DSS_INITIALIZE = System::Int8(0x1);
static constexpr System::Int8 TNOAUTH_DSS_TOKENBA = System::Int8(0x2);
static constexpr System::Int8 TNOAUTH_DSS_CERTA_TOKENAB = System::Int8(0x3);
static constexpr System::Int8 TNOAUTH_DSS_CERTB_TOKENBA2 = System::Int8(0x4);
static constexpr System::Int8 TNOAUTH_SRP_AUTH = System::Int8(0x0);
static constexpr System::Int8 TNOAUTH_SRP_REJECT = System::Int8(0x1);
static constexpr System::Int8 TNOAUTH_SRP_ACCEPT = System::Int8(0x2);
static constexpr System::Int8 TNOAUTH_SRP_CHALLENGE = System::Int8(0x3);
static constexpr System::Int8 TNOAUTH_SRP_RESPONSE = System::Int8(0x4);
static constexpr System::Int8 TNOAUTH_SRP_EXP = System::Int8(0x8);
static constexpr System::Int8 TNOAUTH_SRP_PARAMS = System::Int8(0x9);
static constexpr System::Int8 TNOAUTH_KEA_CERTA_RA = System::Int8(0x1);
static constexpr System::Int8 TNOAUTH_KEA_CERTB_RB_IVB_NONCEB = System::Int8(0x2);
static constexpr System::Int8 TNOAUTH_KEA_IVA_RESPONSEB_NONCEA = System::Int8(0x3);
static constexpr System::Int8 TNOAUTH_KEA_RESPONSEA = System::Int8(0x4);
static constexpr System::Int8 TNOENC_IS = System::Int8(0x0);
static constexpr System::Int8 TNOENC_SUPPORT = System::Int8(0x1);
static constexpr System::Int8 TNOENC_REPLY = System::Int8(0x2);
static constexpr System::Int8 TNOENC_START = System::Int8(0x3);
static constexpr System::Int8 TNOENC_END = System::Int8(0x4);
static constexpr System::Int8 TNOENC_REQUEST_START = System::Int8(0x5);
static constexpr System::Int8 TNOENC_REQUEST_END = System::Int8(0x6);
static constexpr System::Int8 TNOENC_ENC_KEYID = System::Int8(0x7);
static constexpr System::Int8 TNOENC_DEC_KEYID = System::Int8(0x8);
static constexpr System::Int8 TNOENC_NULL = System::Int8(0x0);
static constexpr System::Int8 TNOENC_DES_CFB64 = System::Int8(0x1);
static constexpr System::Int8 TNOENC_DES_OFB64 = System::Int8(0x2);
static constexpr System::Int8 TNOENC_DES3_CFB64 = System::Int8(0x3);
static constexpr System::Int8 TNOENC_DES3_OFB64 = System::Int8(0x4);
static constexpr System::Int8 TNOENC_CAST5_40_CFB64 = System::Int8(0x8);
static constexpr System::Int8 TNOENC_CAST5_40_OFB64 = System::Int8(0x9);
static constexpr System::Int8 TNOENC_CAST128_CFB64 = System::Int8(0xa);
static constexpr System::Int8 TNOENC_CAST128_OFB64 = System::Int8(0xb);
static constexpr System::Int8 TNOENC_AES_CCM = System::Int8(0xc);
static constexpr System::Int8 TNOENC_CFB64_IV = System::Int8(0x1);
static constexpr System::Int8 TNOENC_CFB64_IV_OK = System::Int8(0x2);
static constexpr System::Int8 TNOENC_CFB64_IV_BAD = System::Int8(0x3);
static constexpr System::Int8 TNOENC_OFB64_IV = System::Int8(0x1);
static constexpr System::Int8 TNOENC_OFB64_IV_OK = System::Int8(0x2);
static constexpr System::Int8 TNOENC_OFB64_IV_BAD = System::Int8(0x3);
}	/* namespace Idtelnet */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTELNET)
using namespace Idtelnet;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdtelnetHPP
