// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSNPP.pas' rev: 34.00 (Windows)

#ifndef IdsnppHPP
#define IdsnppHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdComponent.hpp>
#include <IdGlobal.hpp>
#include <IdException.hpp>
#include <IdGlobalProtocols.hpp>
#include <IdReplyRFC.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPClient.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsnpp
{
//-- forward type declarations -----------------------------------------------
struct TCheckResp;
class DELPHICLASS TIdSNPP;
class DELPHICLASS EIdSNPPException;
class DELPHICLASS EIdSNPPConnectionRefused;
class DELPHICLASS EIdSNPPProtocolError;
class DELPHICLASS EIdSNPPNoMultiLineMessages;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TConnectionResult : unsigned char { crCanPost, crNoPost, crAuthRequired, crTempUnavailable };

struct DECLSPEC_DRECORD TCheckResp
{
public:
	short Code;
	System::UnicodeString Resp;
};


class PASCALIMPLEMENTATION TIdSNPP : public Idtcpclient::TIdTCPClientCustom
{
	typedef Idtcpclient::TIdTCPClientCustom inherited;
	
protected:
	bool __fastcall Pager(System::UnicodeString APagerId);
	bool __fastcall SNPPMsg(System::UnicodeString AMsg);
	virtual void __fastcall InitComponent();
	
public:
	virtual void __fastcall Connect()/* overload */;
	virtual void __fastcall DisconnectNotifyPeer();
	void __fastcall Reset();
	void __fastcall SendMessage(System::UnicodeString APagerId, System::UnicodeString AMsg);
	
__published:
	__property Port = {default=7777};
	__property Host = {default=0};
public:
	/* TIdTCPConnection.Destroy */ inline __fastcall virtual ~TIdSNPP() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSNPP(System::Classes::TComponent* AOwner)/* overload */ : Idtcpclient::TIdTCPClientCustom(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSNPP()/* overload */ : Idtcpclient::TIdTCPClientCustom() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Connect(const System::UnicodeString AHost){ Idtcpclient::TIdTCPClientCustom::Connect(AHost); }
	inline void __fastcall  Connect(const System::UnicodeString AHost, const System::Word APort){ Idtcpclient::TIdTCPClientCustom::Connect(AHost, APort); }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdSNPPException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSNPPException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSNPPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSNPPException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSNPPException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSNPPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSNPPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSNPPException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSNPPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSNPPException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSNPPException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSNPPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSNPPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSNPPException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdSNPPConnectionRefused : public Idreplyrfc::EIdReplyRFCError
{
	typedef Idreplyrfc::EIdReplyRFCError inherited;
	
public:
	/* EIdReplyRFCError.CreateError */ inline __fastcall virtual EIdSNPPConnectionRefused(const int AErrorCode, const System::UnicodeString AReplyMessage) : Idreplyrfc::EIdReplyRFCError(AErrorCode, AReplyMessage) { }
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSNPPConnectionRefused(const System::UnicodeString AMsg)/* overload */ : Idreplyrfc::EIdReplyRFCError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSNPPConnectionRefused(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idreplyrfc::EIdReplyRFCError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSNPPConnectionRefused(NativeUInt Ident)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSNPPConnectionRefused(System::PResStringRec ResStringRec)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSNPPConnectionRefused(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSNPPConnectionRefused(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSNPPConnectionRefused(const System::UnicodeString Msg, int AHelpContext) : Idreplyrfc::EIdReplyRFCError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSNPPConnectionRefused(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idreplyrfc::EIdReplyRFCError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSNPPConnectionRefused(NativeUInt Ident, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSNPPConnectionRefused(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSNPPConnectionRefused(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSNPPConnectionRefused(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSNPPConnectionRefused() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdSNPPProtocolError : public Idreplyrfc::EIdReplyRFCError
{
	typedef Idreplyrfc::EIdReplyRFCError inherited;
	
public:
	/* EIdReplyRFCError.CreateError */ inline __fastcall virtual EIdSNPPProtocolError(const int AErrorCode, const System::UnicodeString AReplyMessage) : Idreplyrfc::EIdReplyRFCError(AErrorCode, AReplyMessage) { }
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSNPPProtocolError(const System::UnicodeString AMsg)/* overload */ : Idreplyrfc::EIdReplyRFCError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSNPPProtocolError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idreplyrfc::EIdReplyRFCError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSNPPProtocolError(NativeUInt Ident)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSNPPProtocolError(System::PResStringRec ResStringRec)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSNPPProtocolError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSNPPProtocolError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSNPPProtocolError(const System::UnicodeString Msg, int AHelpContext) : Idreplyrfc::EIdReplyRFCError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSNPPProtocolError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idreplyrfc::EIdReplyRFCError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSNPPProtocolError(NativeUInt Ident, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSNPPProtocolError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSNPPProtocolError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSNPPProtocolError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSNPPProtocolError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdSNPPNoMultiLineMessages : public EIdSNPPException
{
	typedef EIdSNPPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSNPPNoMultiLineMessages(const System::UnicodeString AMsg)/* overload */ : EIdSNPPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSNPPNoMultiLineMessages(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSNPPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSNPPNoMultiLineMessages(NativeUInt Ident)/* overload */ : EIdSNPPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSNPPNoMultiLineMessages(System::PResStringRec ResStringRec)/* overload */ : EIdSNPPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSNPPNoMultiLineMessages(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSNPPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSNPPNoMultiLineMessages(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSNPPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSNPPNoMultiLineMessages(const System::UnicodeString Msg, int AHelpContext) : EIdSNPPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSNPPNoMultiLineMessages(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSNPPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSNPPNoMultiLineMessages(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSNPPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSNPPNoMultiLineMessages(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSNPPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSNPPNoMultiLineMessages(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSNPPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSNPPNoMultiLineMessages(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSNPPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSNPPNoMultiLineMessages() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsnpp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSNPP)
using namespace Idsnpp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsnppHPP
