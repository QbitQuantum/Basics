// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdReplyRFC.pas' rev: 34.00 (Android)

#ifndef IdreplyrfcHPP
#define IdreplyrfcHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdReply.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idreplyrfc
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdReplyRFC;
class DELPHICLASS TIdRepliesRFC;
class DELPHICLASS EIdReplyRFCError;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdReplyRFC : public Idreply::TIdReply
{
	typedef Idreply::TIdReply inherited;
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* ADest);
	virtual bool __fastcall CheckIfCodeIsValid(const System::UnicodeString ACode);
	virtual System::Classes::TStrings* __fastcall GetFormattedReply();
	virtual void __fastcall SetFormattedReply(System::Classes::TStrings* const AValue);
	
public:
	__classmethod virtual bool __fastcall IsEndMarker(const System::UnicodeString ALine);
	virtual void __fastcall RaiseReplyError();
	virtual bool __fastcall ReplyExists();
public:
	/* TIdReply.Create */ inline __fastcall virtual TIdReplyRFC(System::Classes::TCollection* ACollection) : Idreply::TIdReply(ACollection) { }
	/* TIdReply.CreateWithReplyTexts */ inline __fastcall virtual TIdReplyRFC(System::Classes::TCollection* ACollection, Idreply::TIdReplies* AReplyTexts) : Idreply::TIdReply(ACollection, AReplyTexts) { }
	/* TIdReply.Destroy */ inline __fastcall virtual ~TIdReplyRFC() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRepliesRFC : public Idreply::TIdReplies
{
	typedef Idreply::TIdReplies inherited;
	
public:
	__fastcall virtual TIdRepliesRFC(System::Classes::TPersistent* AOwner)/* overload */;
	__fastcall virtual TIdRepliesRFC(System::Classes::TPersistent* AOwner, const Idreply::TIdReplyClass AReplyClass)/* overload */;
	virtual void __fastcall UpdateText(Idreply::TIdReply* AReply);
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdRepliesRFC() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdReplyRFCError : public Idreply::EIdReplyError
{
	typedef Idreply::EIdReplyError inherited;
	
protected:
	int FErrorCode;
	
public:
	__fastcall virtual EIdReplyRFCError(const int AErrorCode, const System::UnicodeString AReplyMessage);
	__property int ErrorCode = {read=FErrorCode, nodefault};
public:
	/* EIdException.Create */ inline __fastcall virtual EIdReplyRFCError(const System::UnicodeString AMsg)/* overload */ : Idreply::EIdReplyError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdReplyRFCError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idreply::EIdReplyError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdReplyRFCError(NativeUInt Ident)/* overload */ : Idreply::EIdReplyError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdReplyRFCError(System::PResStringRec ResStringRec)/* overload */ : Idreply::EIdReplyError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdReplyRFCError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreply::EIdReplyError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdReplyRFCError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreply::EIdReplyError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdReplyRFCError(const System::UnicodeString Msg, int AHelpContext) : Idreply::EIdReplyError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdReplyRFCError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idreply::EIdReplyError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdReplyRFCError(NativeUInt Ident, int AHelpContext)/* overload */ : Idreply::EIdReplyError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdReplyRFCError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idreply::EIdReplyError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdReplyRFCError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreply::EIdReplyError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdReplyRFCError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreply::EIdReplyError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdReplyRFCError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idreplyrfc */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDREPLYRFC)
using namespace Idreplyrfc;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdreplyrfcHPP
