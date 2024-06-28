// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdIdent.pas' rev: 34.00 (Android)

#ifndef IdidentHPP
#define IdidentHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdException.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idident
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdIdent;
class DELPHICLASS EIdIdentException;
class DELPHICLASS EIdIdentReply;
class DELPHICLASS EIdIdentInvalidPort;
class DELPHICLASS EIdIdentNoUser;
class DELPHICLASS EIdIdentHiddenUser;
class DELPHICLASS EIdIdentUnknownError;
class DELPHICLASS EIdIdentQueryTimeOut;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdIdent : public Idtcpclient::TIdTCPClientCustom
{
	typedef Idtcpclient::TIdTCPClientCustom inherited;
	
protected:
	int FQueryTimeOut;
	System::UnicodeString FReplyString;
	System::UnicodeString __fastcall GetReplyCharset();
	System::UnicodeString __fastcall GetReplyOS();
	System::UnicodeString __fastcall GetReplyOther();
	System::UnicodeString __fastcall GetReplyUserName();
	System::UnicodeString __fastcall FetchUserReply();
	System::UnicodeString __fastcall FetchOS();
	void __fastcall ParseError();
	virtual void __fastcall InitComponent();
	
public:
	void __fastcall Query(System::Word APortOnServer, System::Word APortOnClient);
	__property System::UnicodeString Reply = {read=FReplyString};
	__property System::UnicodeString ReplyCharset = {read=GetReplyCharset};
	__property System::UnicodeString ReplyOS = {read=GetReplyOS};
	__property System::UnicodeString ReplyOther = {read=GetReplyOther};
	__property System::UnicodeString ReplyUserName = {read=GetReplyUserName};
	
__published:
	__property int QueryTimeOut = {read=FQueryTimeOut, write=FQueryTimeOut, default=60000};
	__property Port = {default=113};
	__property Host = {default=0};
public:
	/* TIdTCPConnection.Destroy */ inline __fastcall virtual ~TIdIdent() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdIdent(System::Classes::TComponent* AOwner)/* overload */ : Idtcpclient::TIdTCPClientCustom(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdIdent()/* overload */ : Idtcpclient::TIdTCPClientCustom() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdIdentException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdIdentException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdIdentException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdIdentException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdIdentException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdIdentException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdIdentReply : public EIdIdentException
{
	typedef EIdIdentException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdIdentReply(const System::UnicodeString AMsg)/* overload */ : EIdIdentException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdIdentReply(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdIdentException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentReply(NativeUInt Ident)/* overload */ : EIdIdentException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentReply(System::PResStringRec ResStringRec)/* overload */ : EIdIdentException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentReply(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentReply(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdIdentReply(const System::UnicodeString Msg, int AHelpContext) : EIdIdentException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdIdentReply(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdIdentException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentReply(NativeUInt Ident, int AHelpContext)/* overload */ : EIdIdentException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentReply(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdIdentException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentReply(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentReply(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdIdentReply() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdIdentInvalidPort : public EIdIdentReply
{
	typedef EIdIdentReply inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdIdentInvalidPort(const System::UnicodeString AMsg)/* overload */ : EIdIdentReply(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdIdentInvalidPort(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdIdentReply(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentInvalidPort(NativeUInt Ident)/* overload */ : EIdIdentReply(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentInvalidPort(System::PResStringRec ResStringRec)/* overload */ : EIdIdentReply(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentInvalidPort(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentReply(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentInvalidPort(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentReply(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdIdentInvalidPort(const System::UnicodeString Msg, int AHelpContext) : EIdIdentReply(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdIdentInvalidPort(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdIdentReply(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentInvalidPort(NativeUInt Ident, int AHelpContext)/* overload */ : EIdIdentReply(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentInvalidPort(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdIdentReply(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentInvalidPort(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentReply(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentInvalidPort(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentReply(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdIdentInvalidPort() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdIdentNoUser : public EIdIdentReply
{
	typedef EIdIdentReply inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdIdentNoUser(const System::UnicodeString AMsg)/* overload */ : EIdIdentReply(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdIdentNoUser(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdIdentReply(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentNoUser(NativeUInt Ident)/* overload */ : EIdIdentReply(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentNoUser(System::PResStringRec ResStringRec)/* overload */ : EIdIdentReply(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentNoUser(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentReply(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentNoUser(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentReply(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdIdentNoUser(const System::UnicodeString Msg, int AHelpContext) : EIdIdentReply(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdIdentNoUser(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdIdentReply(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentNoUser(NativeUInt Ident, int AHelpContext)/* overload */ : EIdIdentReply(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentNoUser(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdIdentReply(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentNoUser(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentReply(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentNoUser(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentReply(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdIdentNoUser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdIdentHiddenUser : public EIdIdentReply
{
	typedef EIdIdentReply inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdIdentHiddenUser(const System::UnicodeString AMsg)/* overload */ : EIdIdentReply(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdIdentHiddenUser(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdIdentReply(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentHiddenUser(NativeUInt Ident)/* overload */ : EIdIdentReply(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentHiddenUser(System::PResStringRec ResStringRec)/* overload */ : EIdIdentReply(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentHiddenUser(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentReply(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentHiddenUser(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentReply(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdIdentHiddenUser(const System::UnicodeString Msg, int AHelpContext) : EIdIdentReply(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdIdentHiddenUser(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdIdentReply(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentHiddenUser(NativeUInt Ident, int AHelpContext)/* overload */ : EIdIdentReply(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentHiddenUser(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdIdentReply(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentHiddenUser(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentReply(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentHiddenUser(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentReply(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdIdentHiddenUser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdIdentUnknownError : public EIdIdentReply
{
	typedef EIdIdentReply inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdIdentUnknownError(const System::UnicodeString AMsg)/* overload */ : EIdIdentReply(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdIdentUnknownError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdIdentReply(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentUnknownError(NativeUInt Ident)/* overload */ : EIdIdentReply(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentUnknownError(System::PResStringRec ResStringRec)/* overload */ : EIdIdentReply(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentUnknownError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentReply(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentUnknownError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentReply(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdIdentUnknownError(const System::UnicodeString Msg, int AHelpContext) : EIdIdentReply(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdIdentUnknownError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdIdentReply(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentUnknownError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdIdentReply(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentUnknownError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdIdentReply(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentUnknownError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentReply(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentUnknownError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentReply(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdIdentUnknownError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdIdentQueryTimeOut : public EIdIdentReply
{
	typedef EIdIdentReply inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdIdentQueryTimeOut(const System::UnicodeString AMsg)/* overload */ : EIdIdentReply(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdIdentQueryTimeOut(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdIdentReply(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentQueryTimeOut(NativeUInt Ident)/* overload */ : EIdIdentReply(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdIdentQueryTimeOut(System::PResStringRec ResStringRec)/* overload */ : EIdIdentReply(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentQueryTimeOut(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentReply(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIdentQueryTimeOut(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdIdentReply(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdIdentQueryTimeOut(const System::UnicodeString Msg, int AHelpContext) : EIdIdentReply(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdIdentQueryTimeOut(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdIdentReply(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentQueryTimeOut(NativeUInt Ident, int AHelpContext)/* overload */ : EIdIdentReply(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIdentQueryTimeOut(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdIdentReply(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentQueryTimeOut(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentReply(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIdentQueryTimeOut(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdIdentReply(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdIdentQueryTimeOut() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word IdIdentQryTimeout = System::Word(0xea60);
}	/* namespace Idident */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDIDENT)
using namespace Idident;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdidentHPP
